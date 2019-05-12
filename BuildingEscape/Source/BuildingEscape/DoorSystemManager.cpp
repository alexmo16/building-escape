// Copyright alexmo16 2019.


#include "DoorSystemManager.h"

// Sets default values for this component's properties
UDoorSystemManager::UDoorSystemManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_Door = GetOwner();
}


// Called when the game starts
void UDoorSystemManager::BeginPlay()
{
	Super::BeginPlay();

	// Make sure the door is closed.
	CloseDoor();
}


void UDoorSystemManager::OpenDoor()
{
	FRotator newRotation( 0.f, m_OpenAngle, 0.f ); // parameters order: pitch, yaw, roll.
	m_Door -> SetActorRotation( newRotation );
}


void UDoorSystemManager::CloseDoor()
{
	FRotator newRotation( 0.f, 0.f, 0.f ); // parameters order: pitch, yaw, roll.
	m_Door -> SetActorRotation( newRotation );
}


// Called every frame
void UDoorSystemManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
	// If the m_Door is in the volume open the door, else make sure it is closed.
	if ( m_PressurePlate && m_PressurePlate -> IsOverlappingActor( m_ActorThatOpens ) )
	{
		OpenDoor();
	}
	else if ( m_Door -> GetActorRotation().Yaw != 0.f )
	{
		CloseDoor();
	}
}
