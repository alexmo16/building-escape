// Copyright alexmo16 2019.

#include "PositionReporter.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_Actor = GetOwner();
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString actorLocation = m_Actor->GetTransform().GetLocation().ToString();

	UE_LOG( LogTemp, Warning, TEXT( "PositionReporter initialization of %s..." ), *m_Actor-> GetName() );
	UE_LOG( LogTemp, Warning, TEXT( "Location of %s is at: %s" ), *m_Actor-> GetName(), *actorLocation );
}


// Called every frame
void UPositionReporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

