// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "PaintBrushHandController.h"
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
	//if we choose hand controller in BP
	if (PaintBrushHandControllerClass)
	{
		//RightPaintBrushHandController=APaintBrushHandController 
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		
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
//push button and save
void AVRPawn::Save()
{
	//our save game class it has our save game property
		//define new variable or create new savegame class and cast it with our savegame
	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	//it get string as input it is our state
	Painting->SetState("Hello World");
	//it is serializing game data for save it means we compact our data
	Painting->SerilizeFromWorld(GetWorld());
	//after compact data we need to save
	Painting->Save();
	UE_LOG(LogTemp,Warning,TEXT("Saved"))
}

void AVRPawn::Load()
{
	//load saved game with test name
	UPainterSaveGame* Painting = UPainterSaveGame::Load();
	// if we saved before
	if (Painting) 
	{
		//decompacting the data from world 
		Painting->DeSerilizeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Painitng State : %s"), *Painting->GetState())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found"))
	}
}

