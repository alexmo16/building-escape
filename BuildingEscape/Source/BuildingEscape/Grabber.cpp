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

	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Look for attached Physics Handle.
void UGrabber::FindPhysicsHandleComponent()
{
	m_PhysicsHandle = GetOwner() -> FindComponentByClass < UPhysicsHandleComponent > ();
	if ( !m_PhysicsHandle )
	{
		UE_LOG( LogTemp, Error, TEXT( "Error : %s missing Physics Handle." ), *GetOwner() -> GetName() );
		return;
	}
}


void UGrabber::SetupInputComponent()
{
	FindInputComponent();
	BindInputs();
}


// Look for attached Input Component.
void UGrabber::FindInputComponent()
{
	m_InputComponent = GetOwner() -> FindComponentByClass < UInputComponent > ();
	if ( !m_InputComponent )
	{
		UE_LOG( LogTemp, Error, TEXT( "Error : %s missing Input Component." ), *GetOwner() -> GetName() );
		return;
	}
}


// Binds differents inputs from m_InputComponent to different functions in this class.
void UGrabber::BindInputs()
{
	m_InputComponent -> BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
	m_InputComponent -> BindAction( "Grab", IE_Released, this, &UGrabber::Release );
}


// Grab an actor.
void UGrabber::Grab()
{
	// Line trace and see if we reach any actors with physics body collision channel set.
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	AActor* ActorHit = Hit.GetActor();

	// If we hit something then attach a physics handle.
	if ( ActorHit )
	{
	}
}


// Return hit for first physics body in reach.
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	if ( m_PlayerController )
	{
		/// Get view point vectors
		FVector PlayerLocation;
		FRotator PlayerViewPointRotation;
		m_PlayerController -> GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerViewPointRotation );

		FVector LineTraceEnd = PlayerLocation + PlayerViewPointRotation.Vector() * m_Reach;
		FCollisionQueryParams CollisionQuery( FName(""), false, GetOwner() ); // Ignore the pawn because the vision continiously hit the pawn.

		GetWorld() -> LineTraceSingleByObjectType( 
			OUT Hit, 
			PlayerLocation, 
			LineTraceEnd, 
			FCollisionObjectQueryParams( ECollisionChannel::ECC_PhysicsBody ),
			CollisionQuery
		);
	}

	return Hit;
}


// Release the grabbed actor.
void UGrabber::Release()
{
	UE_LOG( LogTemp, Warning, TEXT( "%s is tired." ), *GetOwner() -> GetName() );

	// release physics handle component.
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If the physics handle is attached
		// move the object that we're holding.
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
