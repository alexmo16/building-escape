// Copyright alexmo16 2019.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void Grab();
	void Release();

private:
	void DrawVisionLine( FVector& PlayerLocation, FVector& LineTraceEnd ); // Debug function.
	
	void FindPhysicsHandleComponent();
	
	void SetupInputComponent();
	void FindInputComponent();
	void BindInputs();

	FHitResult GetFirstPhysicsBodyInReach() const;
	FTwoVectors GetLineTracePoints() const;

	APlayerController* m_PlayerController = nullptr;

	UPROPERTY( EditAnywhere )
	float m_Reach = 100.f; // in cm.

	UPhysicsHandleComponent* m_PhysicsHandle = nullptr;

	UInputComponent* m_InputComponent = nullptr;
};
