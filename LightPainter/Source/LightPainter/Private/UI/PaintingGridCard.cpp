// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGridCard.h"
#include "Components/TextBlock.h"



void UPaintingGridCard::SetPaintingName(FString PaintingName)
{
	
	SlotName->SetText(FText::FromString(PaintingName));
}
