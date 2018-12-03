// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		void AddPainting();
	
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta =(BindWidget))
	class UUniformGridPanel* PaintingGrid;
};
