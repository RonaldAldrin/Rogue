// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Explosive.h"
#include "Character/SCharacter.h"

#include "PhysicsEngine/RadialForceComponent.h"

AExplosive::AExplosive()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
	BaseMesh->SetCollisionProfileName(FName("PhysicsActor"));
	BaseMesh->SetSimulatePhysics(true);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(BaseMesh);
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 2000.f;
	RadialForceComp->ForceStrength = 50.f;
	RadialForceComp->Radius = 400.f;
	
}

void AExplosive::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AExplosive::Explode);
}

void AExplosive::Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASCharacter* Character = Cast<ASCharacter>(OtherActor);
	if (OtherActor != Character)
	{
		RadialForceComp->FireImpulse();
	}
}



