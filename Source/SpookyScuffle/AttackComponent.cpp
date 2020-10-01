// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Engine/Engine.h"
#include "CharacterInterface.h"

UAttackComponent::UAttackComponent()
{
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnBeginOverlap);

}


void UAttackComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ICharacterInterface* Attacker = Cast<ICharacterInterface>(GetOwner());
	Cast<ICharacterInterface>(OtherActor)->ModifyLife(-Attacker->GetDamage(), Attacker->GetTeam());
}
