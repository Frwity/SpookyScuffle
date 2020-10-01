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
	: ATwoHandedSwordCharacter{}
{
	baseTurnRate = 45.f;
	baseLookUpRate = 45.f;

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
}

void ASpookyScuffleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void ASpookyScuffleCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &ASpookyScuffleCharacter::Attack);

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
	Super::MoveForward(_value);
}

void ASpookyScuffleCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ASpookyScuffleCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}

void ASpookyScuffleCharacter::Attack()
{
	Super::Attack();
}