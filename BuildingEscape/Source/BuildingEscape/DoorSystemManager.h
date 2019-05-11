// Copyright alexmo16 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

#include "DoorSystemManager.generated.h"


UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BUILDINGESCAPE_API UDoorSystemManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorSystemManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor();
	void CloseDoor();

private:
	AActor* m_Door;
	
	UPROPERTY(VisibleAnywhere)
	float m_OpenAngle = -90.f; // Open the door inside the room.

	UPROPERTY( EditAnywhere )
	ATriggerVolume* m_PressurePlate;
	
	AActor* m_ActorThatOpens;
};
