// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "GeneralCharacter.h"
#include "TimerManager.h"


AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	arrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	arrowMesh->SetupAttachment(RootComponent);
	arrowMesh->SetSimulatePhysics(true);

	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	hitBox->SetupAttachment(arrowMesh);
	hitBox->SetRelativeLocation({ 0,0,0 });
	hitBox->SetMobility(EComponentMobility::Movable);

	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnBeginOverlap);
}

AArrow::AArrow(FVector _direction, E_TEAMS _team)
	: AArrow()
{
	direction = _direction;
	team = _team;
}

void AArrow::DestroyArrow()
{
	Destroy();
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();

	arrowMesh = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Arrow")));

	FTimerHandle _timeHandle;
	GetWorldTimerManager().SetTimer(_timeHandle, this, &AArrow::DestroyArrow, lifeTime, false);
}

void AArrow::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	FHitResult outHit;
	arrowMesh->AddWorldOffset(direction * speed * deltaTime, true, &outHit);
	

}

void AArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGeneralCharacter* _target = Cast<AGeneralCharacter>(OtherActor);


	if (_target && team != _target->GetTeam())
	{
		_target->ModifyLife(-damage, team, false);
		Destroy();
	}
}