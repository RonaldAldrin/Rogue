

#include "Projectile/SProjectileBase.h"
#include "Character/SAttributesComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

ASProjectileBase::ASProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	SphereComp->SetCollisionProfileName("Projectile");
	

	EffectsComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectsComp");
	EffectsComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

}

void ASProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}


void ASProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::DestroyProjectile);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectileBase::OnActorOverlap);
}

void ASProjectileBase::DestroyProjectile(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation(), false);

		Destroy();
	}

	
}

void ASProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		//Get the ActorComponent of the class
		USAttributesComponent* AttributeComp = Cast<USAttributesComponent>(OtherActor->GetComponentByClass(USAttributesComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.f);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), GetActorRotation(), false);

			Destroy();
		}

	}
}

