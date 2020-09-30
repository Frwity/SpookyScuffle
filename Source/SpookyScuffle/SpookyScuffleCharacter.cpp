// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpookyScuffleCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"	
#include "Animation/AnimTypes.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


ASpookyScuffleCharacter::ASpookyScuffleCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(RootComponent);
	cameraBoom->TargetArmLength = 300.0f;
	cameraBoom->bUsePawnControlRotation = true;

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

}

void ASpookyScuffleCharacter::BeginPlay()
{
	Super::BeginPlay();

	life = maxLife;
	isAlive = true;
}

void ASpookyScuffleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (life <= 0)
	{
		isAlive = false;
	}

}

void ASpookyScuffleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASpookyScuffleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpookyScuffleCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpookyScuffleCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpookyScuffleCharacter::LookUpAtRate);
}

void ASpookyScuffleCharacter::TurnAtRate(float _rate)
{
	AddControllerYawInput(_rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::LookUpAtRate(float _rate)
{
	AddControllerPitchInput(_rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASpookyScuffleCharacter::MoveForward(float _value)
{
	if ((Controller != NULL) && (_value != 0.0f))
	{
		// find out which way is forward
		const FRotator _rotation = Controller->GetControlRotation();
		const FRotator _yawRotation(0, _rotation.Yaw, 0);

		// get forward vector
		const FVector _direction = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(_direction, _value);
	}
}

void ASpookyScuffleCharacter::MoveRight(float _value)
{
	if ( (Controller != NULL) && (_value != 0.0f) )
	{
		// find out which way is right
		const FRotator _rotation = Controller->GetControlRotation();
		const FRotator _yawRotation(0, _rotation.Yaw, 0);
	
		// get right vector 
		const FVector _direction = FRotationMatrix(_yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(_direction, _value);
	}
}

void ASpookyScuffleCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	if (_lifePoint < 0 && team != _team)
	{
		life += _lifePoint;

		if (onHitParticle)
		{
			UGameplayStatics::SpawnEmitterAttached(onHitParticle, GetRootComponent());
		}
	}
}
