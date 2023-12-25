
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SGameplayInterface.h"
#include "Components/TimelineComponent.h"
#include "SBaseActor.generated.h"

class UCurveFloat;

UCLASS()
class ROGUE_API ASBaseActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASBaseActor();

	//===Begin ISGameplayInterface
	virtual void Interact_Implementation(APawn* InstigatorPawn);
	//===End ISGameplayInterface

	UPROPERTY(EditAnywhere,Category = "ActorProperties")
	float TargetPitch;

protected:
	virtual void BeginPlay() override;



	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> SecondMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ThirdMesh;


	//=======================
	// TIMELINE ANIMATION
	//=======================

	UFUNCTION()
	virtual void TimelineUpdate(float Value);

	UFUNCTION()
	virtual void TimelineFinished();

	UFUNCTION()
	void TimelinePlay();


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTimelineComponent> SecondMeshTimeline;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> TimelineCurve;

	FOnTimelineFloat TimelineValue;
	FOnTimelineEvent TimelineFinishedEvent;

	UPROPERTY(BlueprintReadOnly)
	bool bNotActivated;




public:	
	virtual void Tick(float DeltaTime) override;

};
