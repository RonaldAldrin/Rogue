#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ASMagicProjectile;



UCLASS()
class ROGUE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	

private:

	//=====================
	// FUNCTIONS
	//=====================

	void SetInputMappingContext();

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

	void PrimaryAttack();

	//=====================
	// COMPONENTS
	//=====================

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;



	//=====================
	// INPUTS
	//=====================

	UPROPERTY(EditDefaultsOnly,Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;

	//=====================
	// ACTORS
	//=====================

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ASMagicProjectile> MagicProjectileClass;

	UPROPERTY()
	TObjectPtr<ASMagicProjectile> MagicProjectile;
};
