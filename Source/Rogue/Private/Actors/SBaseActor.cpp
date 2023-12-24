

#include "Actors/SBaseActor.h"

ASBaseActor::ASBaseActor()
{
	TargetPitch = 110;

	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);


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
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

