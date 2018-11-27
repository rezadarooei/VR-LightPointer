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
	
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed,this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released,this, &AVRPawn::ReleaseTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("Save"), IE_Released, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction(TEXT("Load"), IE_Released, this, &AVRPawn::Load);

}

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	Painting->SetState("Hello World");
	Painting->SerilizeFromWorld(GetWorld());
	Painting->Save();
	UE_LOG(LogTemp,Warning,TEXT("Saved"))
}

void AVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	if (Painting) 
	{
		Painting->DeSerilizeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Painitng State : %s"), *Painting->GetState())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found"))
	}
}

