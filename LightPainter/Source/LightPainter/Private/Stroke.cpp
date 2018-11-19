// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/SplineMeshComponent.h"

AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
}

void AStroke::Update(FVector CurrentCursorLocation)
{
	//create SplineMesh
	USplineMeshComponent* SplineMesh = CreateSpline();
	FVector StartPostion=GetActorTransform().InverseTransformPosition(CurrentCursorLocation);

	FVector EndPostion= GetActorTransform().InverseTransformPosition(PreviousCursorLocation);

	if (SplineMesh)
	{
		SplineMesh->SetStartAndEnd(StartPostion, FVector::ZeroVector, EndPostion, FVector::ZeroVector);
	}
	//update endpoints
	  PreviousCursorLocation= CurrentCursorLocation;
}

 USplineMeshComponent* AStroke::CreateSpline()
{
	USplineMeshComponent* CurrentSplineMesh = NewObject<USplineMeshComponent>(this);
	CurrentSplineMesh->SetMobility(EComponentMobility::Movable);
	CurrentSplineMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	CurrentSplineMesh->SetStaticMesh(SplineMesh);
	CurrentSplineMesh->SetMaterial(0, SplineMaterial);
	CurrentSplineMesh->RegisterComponent();
	return CurrentSplineMesh;
}

