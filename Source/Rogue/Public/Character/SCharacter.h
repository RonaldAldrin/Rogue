#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class UInputMappingContext;
class UInputAction;
class ASMagicProjectile;
class UAnimMontage;



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
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();

	//=====================
	// COMPONENTS
	//=====================

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	TObjectPtr<USInteractionComponent> InteractionComp;



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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	//=====================
	// ACTORS
	//=====================

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ASMagicProjectile> MagicProjectileClass;

	UPROPERTY()
	TObjectPtr<ASMagicProjectile> MagicProjectile;

	//=====================
	// Animation Montages
	//=====================

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

	//=====================
	// Variables
	//==================

	FTimerHandle TimerHandle_PrimaryAttack;
};
