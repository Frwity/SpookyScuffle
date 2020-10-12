// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoHandedSwordCharacter.h"
#include "AttackComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"


ATwoHandedSwordCharacter::ATwoHandedSwordCharacter()
	: AGeneralCharacter{}
{
	rightWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightSword"));;
	rightWeaponMesh->SetupAttachment(GetMesh(), FName("RightWeaponShield"));
	leftWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftSword"));
	leftWeaponMesh->SetupAttachment(GetMesh(), FName("LeftWeaponShield"));


	rightAttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("RightAttackComponent"));
	rightAttackComponent->SetupAttachment(rightWeaponMesh);
	rightAttackComponent->SetRelativeLocation({ 0,0,0 });
	rightAttackComponent->SetMobility(EComponentMobility::Movable);

	leftAttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("LeftAttackComponent"));
	leftAttackComponent->SetupAttachment(leftWeaponMesh);
	leftAttackComponent->SetRelativeLocation({ 0,0,0 });
	leftAttackComponent->SetMobility(EComponentMobility::Movable);
}

void ATwoHandedSwordCharacter::BeginPlay()
{
	Super::BeginPlay();

	rightAttackComponent = Cast<UAttackComponent>(GetDefaultSubobjectByName(TEXT("RightAttackComponent")));
	rightAttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	leftAttackComponent = Cast<UAttackComponent>(GetDefaultSubobjectByName(TEXT("LeftAttackComponent")));
	leftAttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATwoHandedSwordCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ATwoHandedSwordCharacter::MoveForward(float _value)
{
	Super::MoveForward(_value);
}

void ATwoHandedSwordCharacter::MoveRight(float _value)
{
	Super::MoveRight(_value);
}

void ATwoHandedSwordCharacter::ModifyLife(int _lifePoint, E_TEAMS _team)
{
	Super::ModifyLife(_lifePoint, _team);
}

void ATwoHandedSwordCharacter::ActivateAttackComponent()
{
	Super::ActivateAttackComponent();
	rightAttackComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	leftAttackComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATwoHandedSwordCharacter::DeactivateAttackComponent()
{
	Super::DeactivateAttackComponent();
	rightAttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftAttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATwoHandedSwordCharacter::Attack()
{
	Super::Attack();
}