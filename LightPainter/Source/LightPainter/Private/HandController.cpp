// Fill out your copyright notice in the Description page of Project Settings.

#include "HandController.h"
#include "MotionControllerComponent.h"
#include "Stroke.h"
#include "Engine/World.h"
AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>("HandController");
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
	
	//

}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStroke) 
	{
		CurrentStroke->Update(GetActorLocation());
	}
}

void AHandController::TriggerPressed()
{
	CurrentStroke= GetWorld()->SpawnActor<AStroke>(StrokeClass);
	CurrentStroke->SetActorLocation(GetActorLocation());
}

void AHandController::Triggerreleased()
{
	CurrentStroke = nullptr;
}

