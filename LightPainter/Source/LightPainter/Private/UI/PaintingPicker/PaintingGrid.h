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

	
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta =(BindWidget))
	class UUniformGridPanel* PaintingGrid;


public:
	UFUNCTION(BlueprintCallable)
		void AddPainting();
	

private: 
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> GridCardClass;

};
