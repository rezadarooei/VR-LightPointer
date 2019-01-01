// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/PaintingGridCard.h"

#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

	
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta =(BindWidget))
	class UUniformGridPanel* PaintingGrid;


public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex,FString PaintingName);
	

private: 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;

};
