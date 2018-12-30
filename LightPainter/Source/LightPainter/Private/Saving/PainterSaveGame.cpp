// Fill out your copyright notice in the Description page of Project Settings.

#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "Saving/PainterSaveGameIndex.h"


UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame= Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	//Slot name is something random
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if(!NewSaveGame->Save()) return nullptr;
	UPainterSaveGameIndex* Index=UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();
	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{

	return Cast<UPainterSaveGame>( UGameplayStatics::LoadGameFromSlot(SlotName,0));

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

