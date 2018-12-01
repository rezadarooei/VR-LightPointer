// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"
#include "EngineUtils.h"



UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewSaveGame= UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0);
}

UPainterSaveGame* UPainterSaveGame::Load()
{
	return Cast<UPainterSaveGame>( UGameplayStatics::LoadGameFromSlot(TEXT("Test"),0));

}

void UPainterSaveGame::SerilizeFromWorld( UWorld* World)
{
	//clear array
		//strokes is array of FStrokeStates 
	Strokes.Empty();
	//iterates over all strokes
	//it is searching whole stroke classes in the world
	for (TActorIterator<AStroke> StrokeItr(World);StrokeItr;++StrokeItr)
	{
		//all strokes will be serialize and it contains class t subclass and its place
		//add new strokes and its places to our array
		Strokes.Add(StrokeItr->SerilizeToStruct());
		//TODO serialize

	}
	//Store class type
}

void UPainterSaveGame::DeSerilizeToWorld(UWorld* World)
{
	ClearWorld(World);

	for (FStrokeState StrokeState : Strokes) 
	{
		AStroke::SpawnAndDeserelizeFromStruct(World,StrokeState);
	}
		//for all strokes
		//spawn strokes of that type.
	
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World);StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}

