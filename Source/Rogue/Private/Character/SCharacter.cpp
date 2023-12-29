
#include "Character/SCharacter.h"
#include "Projectile/SMagicProjectile.h"
#include "Character/SInteractionComponent.h"
#include "Character/SAttributesComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0.f, 80.f, 10.f);


	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<USAttributesComponent>("AttributeComp");

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
	//checkf(PrimaryProjectileClass, TEXT("Set MagicProjectileClass in BP_SCharacter. MagicProjectileClass is nullptr"));

	PlayAnimMontage(AttackMontage);
	
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FHitResult CameraHitResult;

	CameraLineTrace(CameraHitResult);

	const FVector HandSocketLocation = GetMesh()->GetSocketLocation(FName("Muzzle_01"));
	
	FRotator Rotation = (AdjustedTraceEnd - HandSocketLocation).Rotation(); // Similar to UKismetMathLibrary::FindLookAtRotation
	const FTransform SpawnTransform = FTransform(Rotation, HandSocketLocation); // GetControlRotation is where the camera is looking
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	if (ensure(PrimaryProjectileClass))
	{
		PrimaryProjectile = GetWorld()->SpawnActor<ASMagicProjectile>(PrimaryProjectileClass, SpawnTransform, SpawnParams);
	}
	
	

	
}

void ASCharacter::PrimaryInteract()
{
	InteractionComp->PrimaryInteract();
}

void ASCharacter::CameraLineTrace(FHitResult HitResult)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//FVector TraceDirection = GetControlRotation().Vector();

	const FVector TraceStart = GetCameraComp()->GetComponentLocation(); //+ (TraceDirection * 15.f);
	const FVector TraceEnd = TraceStart + (GetCameraComp()->GetForwardVector() * 5000.f);
	

	AdjustedTraceEnd = TraceEnd;

	if (bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, Params))
	{
		AdjustedTraceEnd = HitResult.ImpactPoint;
	}

}

