// Fill out your copyright notice in the Description page of Project Settings.

#include "UIPointerHandController.h"
#include "Components/WidgetInteractionComponent.h"






AUIPointerHandController::AUIPointerHandController()
{
	Pointer = CreateAbstractDefaultSubobject<UWidgetInteractionComponent>("Widget Interaction");
	Pointer->SetupAttachment(GetRootComponent());
}

void AUIPointerHandController::TriggerPressed()
{
	Pointer->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::Triggerreleased()
{
	Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
}
