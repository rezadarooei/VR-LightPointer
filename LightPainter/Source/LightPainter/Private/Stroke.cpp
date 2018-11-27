// Fill out your copyright notice in the Description page of Project Settings.

#include "Stroke.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/World.h"

AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Stroke Meshes");
	StrokeMeshes->SetupAttachment(Root);

	JointeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Joint Meshes");
	JointeMeshes->SetupAttachment(Root);
}
FStrokeState AStroke::SerilizeToStruct() const {

	FStrokeState StrokeState;
	StrokeState.Class = GetClass();
	StrokeState.ControlPoints = ControlPoints;
	return StrokeState;
}

AStroke* AStroke::SpawnAndDeserelizeFromStruct(UWorld* World, const FStrokeState& StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.Class);
	for (FVector ControlPoint : StrokeState.ControlPoints)
	{
		Stroke->Update(ControlPoint);
	}
	return Stroke;
}

void AStroke::Update(FVector CurrentCursorLocation)
{
	ControlPoints.Add(CurrentCursorLocation);
	if (PreviousCursorLocation.IsNearlyZero()) 
	{
		PreviousCursorLocation = CurrentCursorLocation;
		JointeMeshes->AddInstance(GetNextJointTransform(CurrentCursorLocation));
		return;
	}
	
	//create instance static mesh in the location need transform for creating new instance
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CurrentCursorLocation));

	JointeMeshes->AddInstance(GetNextJointTransform(CurrentCursorLocation));
	//update endpoints
	 PreviousCursorLocation= CurrentCursorLocation;
}



FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;
	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));

	return SegmentTransform;
}

FVector AStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	
	FVector Segment = CurrentLocation - PreviousCursorLocation;
	return FVector(Segment.Size(), 1, 1);
}

FQuat AStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{

	FVector Segment = CurrentLocation - PreviousCursorLocation;
	FVector SegmentNormal = Segment.GetSafeNormal();
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentNormal);
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	return GetTransform().InverseTransformPosition(PreviousCursorLocation);
}

FTransform AStroke::GetNextJointTransform(FVector CurrentLocation)
{
	FTransform JointTransform;
	JointTransform.InverseTransformPosition(CurrentLocation);
	return JointTransform;
}
