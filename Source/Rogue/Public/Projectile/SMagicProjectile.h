
#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SMagicProjectile.generated.h"



UCLASS()
class ROGUE_API ASMagicProjectile : public ASProjectileBase
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

public:	


};
