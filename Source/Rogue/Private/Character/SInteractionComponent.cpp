

#include "Character/SInteractionComponent.h"
#include "Character/SCharacter.h"

#include "Interface/SGameplayInterface.h"
#include "Camera/CameraComponent.h"

USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	APawn* MyPawn = Cast<APawn>(MyOwner);

	ASCharacter* MyCharacter = Cast<ASCharacter>(MyOwner);

	FRotator EyeRotation2 = MyPawn->GetViewRotation();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation); 

	UCameraComponent* MyCamera = MyCharacter->GetCameraComp();

	//const FVector End =  EyeLocation + (EyeRotation2.Vector() * 1000.f);
	const FVector Start = MyCamera->GetComponentLocation();
	const FVector End = Start + (MyCamera->GetForwardVector() * 500.f);
	
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);


	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(30.f);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			/*if (ISGameplayInterface* GameplayInterface = Cast<ISGameplayInterface>(HitActor))
			{
				GameplayInterface->Interact_Implementation(MyPawn);
				break;
			}*/

			//// this method is working when implementing the interface in blueprint
			if (HitActor->Implements<USGameplayInterface>())
			{
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.f, 12,LineColor, false, 2.f);
	}

	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 12.f,0,2.f);
}

