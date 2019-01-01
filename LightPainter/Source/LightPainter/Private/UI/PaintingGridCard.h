// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		class UTextBlock* SlotName;
public:
	void SetPaintingName(FString PaintingName);
};
