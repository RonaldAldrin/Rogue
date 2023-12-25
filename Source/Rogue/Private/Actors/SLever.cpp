// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SLever.h"

void ASLever::BeginPlay()
{
	Super::BeginPlay();

}

void ASLever::TimelineUpdate(float Value)
{
	float TargetLerp = FMath::Lerp(0, TargetPitch, Value);

	SecondMesh->SetRelativeRotation(FRotator(TargetLerp, 0, 0));
}

void ASLever::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
}
