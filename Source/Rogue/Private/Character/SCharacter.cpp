
#include "Character/SCharacter.h"
#include "Projectile/SMagicProjectile.h"
#include "Character/SInteractionComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetInputMappingContext();
	
}


void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	PlayerInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCharacter::Move);
	PlayerInput->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ASCharacter::Turn);
	PlayerInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	PlayerInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	PlayerInput->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &ASCharacter::PrimaryAttack);
	PlayerInput->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &ASCharacter::PrimaryInteract);

}

void ASCharacter::SetInputMappingContext()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ASCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (InputValue != FVector2D::ZeroVector)
	{
		const FRotator RotationYaw(0, GetControlRotation().Yaw, 0);

		FVector ForwardVector = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);
		FVector RightVector = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, InputValue.Y);
		AddMovementInput(RightVector, InputValue.X);
	}
}

void ASCharacter::Turn(const FInputActionValue& Value)
{
	FVector2D TurnValue = Value.Get<FVector2D>();

	AddControllerYawInput(TurnValue.X);
	AddControllerPitchInput(TurnValue.Y * -1);
}

void ASCharacter::PrimaryAttack()
{
	checkf(MagicProjectileClass, TEXT("Set MagicProjectileClass in BP_SCharacter. MagicProjectileClass is nullptr"));

	PlayAnimMontage(AttackMontage);
	
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{

	const FVector HandLocation = GetMesh()->GetSocketLocation(FName("Muzzle_01"));
	const FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation); // GetControlRotation is where the camera is looking

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ASMagicProjectile>(MagicProjectileClass, SpawnTransform, SpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

