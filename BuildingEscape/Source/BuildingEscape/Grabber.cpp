// Copyright alexmo16 2019.

#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT // Output tag to remember variables passed to a function will change after the function execution.

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UWorld* currentWorld = GetWorld();
	if ( currentWorld )
	{
		m_PlayerController = currentWorld -> GetFirstPlayerController();
	}
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Look for attached Physics Handle.

	m_PhysicsHandle = GetOwner() -> FindComponentByClass < UPhysicsHandleComponent > ();
	if ( !m_PhysicsHandle )
	{
		UE_LOG( LogTemp, Error, TEXT( "Error : %s missing Physics Handle." ), *GetOwner() -> GetName() );
		return;
	}

	m_InputComponent = GetOwner() -> FindComponentByClass < UInputComponent > ();
	if ( !m_InputComponent )
	{
		UE_LOG( LogTemp, Error, TEXT( "Error : %s missing Input Component." ), *GetOwner() -> GetName() );
		return;
	}

	m_InputComponent -> BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
	m_InputComponent -> BindAction( "Grab", IE_Released, this, &UGrabber::Release );
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( m_PlayerController )
	{
		// Get view point vectors
		
		FVector PlayerLocation;
		FRotator PlayerViewPointRotation;
		m_PlayerController -> GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerViewPointRotation );

		FVector LineTraceEnd = PlayerLocation + PlayerViewPointRotation.Vector() * m_Reach;
		// DrawVisionLine( PlayerLocation, LineTraceEnd ); // For debugging


		FHitResult Hit;
		FCollisionQueryParams CollisionQuery( FName(""), false, GetOwner() ); // Ignore the pawn because the vision continiously hit the pawn.

		GetWorld() -> LineTraceSingleByObjectType( 
			OUT Hit, 
			PlayerLocation, 
			LineTraceEnd, 
			FCollisionObjectQueryParams( ECollisionChannel::ECC_PhysicsBody ),
			CollisionQuery
		);

		AActor* ActorHit = Hit.GetActor();
		if ( ActorHit )
		{
			UE_LOG( LogTemp, Warning, TEXT("Pawn hit: %s."), *ActorHit -> GetName() );
		}
	}
}


void UGrabber::DrawVisionLine( FVector& PlayerLocation, FVector& LineTraceEnd )
{
	DrawDebugLine(
			GetWorld(),
			PlayerLocation,
			LineTraceEnd,
			FColor( 255, 0, 0 ), // Red color.
			false,
			0.f,
			0.f,
			10.f
		);
}


void UGrabber::Grab()
{
	UE_LOG( LogTemp, Warning, TEXT( "%s wants to grab." ), *GetOwner() -> GetName() );
}


void UGrabber::Release()
{
	UE_LOG( LogTemp, Warning, TEXT( "%s is tired." ), *GetOwner() -> GetName() );
}
