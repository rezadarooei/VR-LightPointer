// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandController.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent * PlayerInputComponent) override;

private:
	//config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;
	// Components
	class UCameraComponent* Camera;

	class USceneComponent* VRRoot;
	//References

	 AHandController* RightHandController;

	 //functions
	 void RightTriggerPressed() { if (RightHandController) { RightHandController->TriggerPressed(); } };
	 void ReleaseTriggerReleased() { if (RightHandController) { RightHandController->Triggerreleased(); } };
};
