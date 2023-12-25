// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SBaseActor.h"
#include "SLever.generated.h"

/**
 * 
 */
UCLASS()
class ROGUE_API ASLever : public ASBaseActor
{
	GENERATED_BODY()
	

public:

	//===Begin ISGameplayInterface
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	//===End ISGameplayInterface

protected:

	virtual void BeginPlay() override;

	virtual void TimelineUpdate(float Value) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorProperties")
	TObjectPtr<AActor> SelectedActor;

private:





};
