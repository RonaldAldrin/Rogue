// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SItemChest.h"

#include "Particles/ParticleSystemComponent.h"

ASItemChest::ASItemChest()
{
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp");
	ParticleSystemComp->SetupAttachment(ThirdMesh);

	ParticleSystemComp->bAutoActivate = false;
}

void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ASItemChest::TimelineUpdate(float Value)
{
	float TargetLerp = FMath::Lerp(0, TargetPitch, Value);

	SecondMesh->SetRelativeRotation(FRotator(TargetLerp, 0, 0));
}

void ASItemChest::TimelineFinished()
{
	Super::TimelineFinished();

	ParticleSystemComp->Activate();

}

void ASItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
}


