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
	if ( m_InputComponent )
	{
		m_InputComponent -> BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
		m_InputComponent -> BindAction( "Grab", IE_Released, this, &UGrabber::Release );
	}
}


// Grab an actor.
void UGrabber::Grab()
{
	// Line trace and see if we reach any actors with physics body collision channel set.
	FHitResult Hit = GetFirstPhysicsBodyInReach();

	if ( Hit.IsValidBlockingHit() )
	{
		AActor* ActorHit = Hit.GetActor();

		// If we hit something then attach a physics handle.
		if ( ActorHit && m_PhysicsHandle )
		{
			m_PhysicsHandle -> GrabComponent( Hit.GetComponent(), NAME_None, ActorHit -> GetActorLocation(), true );
		}
	}
}


// Return hit for first physics body in reach.
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	if ( m_PlayerController )
	{
		FCollisionQueryParams CollisionQuery( FName(""), false, GetOwner() ); // Ignore the pawn because the vision continiously hit the pawn.
		FTwoVectors LinesTrace = GetLineTracePoints();

		// Get collisions with the view point vector.
		GetWorld() -> LineTraceSingleByObjectType( 
			OUT Hit, 
			LinesTrace.v1, 
			LinesTrace.v2, 
			FCollisionObjectQueryParams( ECollisionChannel::ECC_PhysicsBody ),
			CollisionQuery
		);
	}

	return Hit;
}


// Get the player location and the location of the reach vector from what is looking at.
FTwoVectors UGrabber::GetLineTracePoints() const
{
	FVector PlayerLocation;
	FRotator PlayerViewPointRotation;
	if ( m_PlayerController )
	{
		m_PlayerController -> GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerViewPointRotation );

		FVector EndLocation = PlayerLocation + PlayerViewPointRotation.Vector() * m_Reach;
		return FTwoVectors( PlayerLocation, EndLocation );
	}
	 return FTwoVectors ( FVector(), FVector() );
}

// Release the grabbed actor.
void UGrabber::Release()
{
	if ( m_PhysicsHandle && m_PhysicsHandle -> GrabbedComponent )
	{
		m_PhysicsHandle ->ReleaseComponent();
	}
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// If the physics handle is attached
	// move the object that we're holding.
	if ( m_PhysicsHandle && m_PhysicsHandle -> GrabbedComponent )
	{
		m_PhysicsHandle -> SetTargetLocation( GetLineTracePoints().v2 );
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
