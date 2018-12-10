// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingGrid.h"
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"


void UPaintingGrid::AddPainting()
{
	if (!PaintingGrid) return;
	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	if (!NewWidget) return;

	USizeBox* CardConiner = Cast<USizeBox>(PaintingGrid->GetChildAt(0));
	if (!CardConiner) return;

	CardConiner->AddChild(NewWidget);
}
