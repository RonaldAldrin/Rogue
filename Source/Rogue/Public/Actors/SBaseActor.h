// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SGameplayInterface.h"
#include "SBaseActor.generated.h"

UCLASS()
class ROGUE_API ASBaseActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASBaseActor();

	//===Begin ISGameplayInterface
	void Interact_Implementation(APawn* InstigatorPawn);
	//===End ISGameplayInterface

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	virtual void BeginPlay() override;



	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LidMesh;

public:	
	virtual void Tick(float DeltaTime) override;

};
