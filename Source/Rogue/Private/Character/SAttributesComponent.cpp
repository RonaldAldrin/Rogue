

#include "Character/SAttributesComponent.h"

USAttributesComponent::USAttributesComponent()
{
	Health = 100.f;

	PrimaryComponentTick.bCanEverTick = false;

}

bool USAttributesComponent::ApplyHealthChange(float Delta)
{
	Health = FMath::Clamp(Health + Delta, 0, 100);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

