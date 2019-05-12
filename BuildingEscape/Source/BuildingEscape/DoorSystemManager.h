// Copyright alexmo16 2019.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

#include "DoorSystemManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnOpenRequest );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCloseRequest );

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

	UPROPERTY( BlueprintAssignable )
	FOnOpenRequest OnOpenRequest;

	UPROPERTY( BlueprintAssignable )
	FOnCloseRequest OnCloseRequest;

private:
	AActor* m_Door = nullptr;

	UPROPERTY( EditAnywhere )
	ATriggerVolume* m_PressurePlate = nullptr;
	
	UPROPERTY( EditAnywhere )
	AActor* m_ActorThatOpens = nullptr;
};
