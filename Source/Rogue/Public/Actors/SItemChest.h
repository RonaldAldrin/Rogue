// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SBaseActor.h"
#include "SItemChest.generated.h"

/**
 * 
 */
UCLASS()
class ROGUE_API ASItemChest : public ASBaseActor
{
	GENERATED_BODY()
	

public:
	ASItemChest();

	//===Begin ISGameplayInterface
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	//===End ISGameplayInterface

protected:

	virtual void BeginPlay() override;

	virtual void TimelineUpdate(float Value) override;

	virtual void TimelineFinished() override;


private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UParticleSystemComponent> ParticleSystemComp;
};
