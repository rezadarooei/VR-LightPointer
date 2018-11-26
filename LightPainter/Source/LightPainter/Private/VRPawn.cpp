// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "HandController.h"
#include "Engine/World.h"
#include "Saving/PainterSaveGame.h"
#include "Camera/CameraComponent.h"
// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	VRRoot = CreateDefaultSubobject<USceneComponent>("VRRoot");
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->AttachTo(VRRoot);
	

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (HandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		
	}
	UPainterSaveGame* SaveGame = UPainterSaveGame::Create();
	SaveGame->Save();
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed,this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released,this, &AVRPawn::ReleaseTriggerReleased);

}

