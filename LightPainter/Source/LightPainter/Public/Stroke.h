// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();

	void Update(FVector CurrentCursorLocation);

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	class USplineMeshComponent* CreateSpline();


	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh* SplineMesh;

	UPROPERTY(EditDefaultsOnly)
	class UMaterialInterface* SplineMaterial;

	FVector PreviousCursorLocation;

};
