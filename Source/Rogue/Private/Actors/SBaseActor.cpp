

#include "Actors/SBaseActor.h"

ASBaseActor::ASBaseActor()
{
	TargetPitch = 110;
	bNotActivated = true;

	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

	SecondMesh = CreateDefaultSubobject<UStaticMeshComponent>("SecondMesh");
	SecondMesh->SetupAttachment(BaseMesh);

	ThirdMesh = CreateDefaultSubobject<UStaticMeshComponent>("ThirdMesh");
	ThirdMesh->SetupAttachment(BaseMesh);

	SecondMeshTimeline = CreateDefaultSubobject<UTimelineComponent>("SecondMeshTimeline");

}


void ASBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBaseActor::Interact_Implementation(APawn* InstigatorPawn)
{
	TimelinePlay();
}

void ASBaseActor::TimelineUpdate(float Value)
{

}

void ASBaseActor::TimelineFinished()
{
	bNotActivated = !bNotActivated;
}


void ASBaseActor::TimelinePlay()
{
	TimelineValue.BindDynamic(this, &ASBaseActor::TimelineUpdate);
	TimelineFinishedEvent.BindDynamic(this, &ASBaseActor::TimelineFinished);
	if (TimelineCurve && SecondMeshTimeline)
	{
		SecondMeshTimeline->AddInterpFloat(TimelineCurve, TimelineValue);
		SecondMeshTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
		if (bNotActivated)
		{
			SecondMeshTimeline->Play();
		}
		else
		{
			SecondMeshTimeline->Reverse();
		}
		
	}
}

