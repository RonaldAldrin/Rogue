#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class USAttributesComponent;
class UInputMappingContext;
class UInputAction;
class ASProjectileBase;
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

	void CameraLineTrace(FHitResult HitResult);

	//=====================
	// COMPONENTS
	//=====================

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USAttributesComponent> AttributeComp;



	FVector AdjustedTraceEnd;

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
	TSubclassOf<ASProjectileBase> PrimaryProjectileClass;

	UPROPERTY()
	TObjectPtr<ASProjectileBase> PrimaryProjectile;

	//=====================
	// Animation Montages
	//=====================

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TObjectPtr<UAnimMontage> AttackMontage;

	//=====================
	// Variables
	//==================

	FTimerHandle TimerHandle_PrimaryAttack;
	

public:

	FORCEINLINE UCameraComponent* GetCameraComp() const { return CameraComp; }
};
