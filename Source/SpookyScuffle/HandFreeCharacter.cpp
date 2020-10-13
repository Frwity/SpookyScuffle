// Fill out your copyright notice in the Description page of Project Settings.


#include "HandFreeCharacter.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoHandedSwordCharacter.h"
#include "AttackComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


AHandFreeCharacter::AHandFreeCharacter()
	: AGeneralCharacter{}
{
}

void AHandFreeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHandFreeCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AHandFreeCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void AHandFreeCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void AHandFreeCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}