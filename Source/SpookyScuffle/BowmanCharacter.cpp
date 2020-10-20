// Fill out your copyright notice in the Description page of Project Settings.


#include "BowmanCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ABowmanCharacter::ABowmanCharacter()
	: AGeneralCharacter{}
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));;
	weaponMesh->SetupAttachment(GetMesh(), FName("LeftWeaponShield"));

}

void ABowmanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABowmanCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ABowmanCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void ABowmanCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ABowmanCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}

void ABowmanCharacter::Attack()
{
	Super::Attack();
}