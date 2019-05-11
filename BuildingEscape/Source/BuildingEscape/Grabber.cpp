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
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( m_PlayerController )
	{
		// Get view point vectors/
		FVector PlayerLocation;
		FRotator PlayerViewPointRotation;
		m_PlayerController -> GetPlayerViewPoint( OUT PlayerLocation, OUT PlayerViewPointRotation );

		FVector LineTraceEnd = PlayerLocation + PlayerViewPointRotation.Vector() * m_VisionReach;
		// DrawVisionLine( PlayerLocation, LineTraceEnd ); // For debugging
	}
}


void UGrabber::DrawVisionLine( FVector PlayerLocation, FVector LineTraceEnd )
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
