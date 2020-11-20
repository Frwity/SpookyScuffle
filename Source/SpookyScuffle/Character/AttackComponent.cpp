// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Engine/Engine.h"
#include "GeneralCharacter.h"
#include "SpookyScuffleCharacter.h"

UAttackComponent::UAttackComponent()
{
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnBeginOverlap);

}


void UAttackComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGeneralCharacter* Attacker = Cast<AGeneralCharacter>(GetOwner());
	AGeneralCharacter* _OtherActor = Cast<AGeneralCharacter>(OtherActor);

	if (Attacker != nullptr && _OtherActor != nullptr)
	{
		if (Attacker->GetTeam() != _OtherActor->GetTeam() && _OtherActor->IsAlive())
			Attacker->hasMissed = false;
		if (_OtherActor->ModifyLife(-Attacker->GetDamage(), Attacker->GetTeam(), true))
		{
			ASpookyScuffleCharacter* player = Cast<ASpookyScuffleCharacter>(Attacker);
			if (player)
				player->AddKill();
		}
	}
}
