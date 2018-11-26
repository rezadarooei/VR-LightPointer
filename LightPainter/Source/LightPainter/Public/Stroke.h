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

	//functions
	FTransform GetNextSegmentTransform(FVector CurrentLocation) const;
	
	FVector GetNextSegmentScale(FVector CurrentLocation) const;

	FQuat GetNextSegmentRotation(FVector CurrentLocation) const;

	FVector GetNextSegmentLocation(FVector CurrentLocation) const;

	FTransform GetNextJointTransform(FVector CurrentLocation);
	//config
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root; 

	UPROPERTY(VisibleAnywhere)
	class UInstancedStaticMeshComponent* StrokeMeshes;

	UPROPERTY(VisibleAnywhere)
	class UInstancedStaticMeshComponent* JointeMeshes;

	//state
	FVector PreviousCursorLocation;

};
