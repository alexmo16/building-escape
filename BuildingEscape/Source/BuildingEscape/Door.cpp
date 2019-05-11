// Copyright alexmo16 2019.


#include "Door.h"

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_Actor = GetOwner();
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

	FRotator newRotation( 0.f, -90.f, 0.f ); // parameters order: pitch, yaw, roll.
	RotateDoor( newRotation );
}


void UDoor::RotateDoor(FRotator NewRotation)
{
	m_Actor -> SetActorRotation( NewRotation );
}


// Called every frame
void UDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

