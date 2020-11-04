// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIManager.h"
#include "EnemyAIController.h"
#include "../Character/GeneralCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


AEnemyAIManager::AEnemyAIManager()
{
	PrimaryActorTick.bCanEverTick = true;


}

void AEnemyAIManager::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AGeneralCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (int i = 0; i < 50; ++i)
		randNumber[i] = FMath::FRandRange(-noise, noise);
}


void AEnemyAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int _nbEnemy = enemyAIs.Num();
	FVector _playerPos = player->GetActorLocation();
	
	if (_nbEnemy > 0)
	{
		// set the first enemy to be the one locked
		int _pos = 0;
		for (AEnemyAIController* _enemyAI : enemyAIs)
		{
			if (_enemyAI->IsLock())
			{
				TArray<AEnemyAIController*> _tempEnemy;
				for (int i = 0; i < _nbEnemy; ++i)
				{
					_tempEnemy.Add(enemyAIs[(i + _pos) % (_nbEnemy)]);
				}
				enemyAIs.Empty();
				enemyAIs.Append(_tempEnemy);
				break;
			}
			_pos++;
		}

		// set target for all enemy
		int _i = 0;
		FVector _targetPos = (enemyAIs[0]->GetPawn()->GetActorLocation() - _playerPos).GetSafeNormal2D() * enemyAIs[0]->GetSafeDistance() + _playerPos;
		for (AEnemyAIController* _enemyAI : enemyAIs)
		{
			_enemyAI->isAFighter = false;
			_enemyAI->SetTargetPos(_targetPos);
			_targetPos = (_targetPos - _playerPos).RotateAngleAxis(360.0f / _nbEnemy, { 0.0f, 0.0f, -1.0f }) + _playerPos + FVector(randNumber[_i++], randNumber[_i++], 0);
		} 
	}

	// set a fighter
	attackTimer += GetWorld()->GetDeltaSeconds();

	if (_nbEnemy == 1)
		enemyAIs[0]->isAFighter = true;
	else if (_nbEnemy == 2)
	{
		if (attackTimer < attackerCooldown)
			enemyAIs[0]->isAFighter = true;
		else if (attackTimer < attackerCooldown * 2)
			enemyAIs[1]->isAFighter = true;
		else
			attackTimer = 0;
	}
	else if (_nbEnemy > 2)
	{
		if (attackTimer < attackerCooldown)
		{
			if (enemyAIs[0]->IsLock())
				enemyAIs[0]->isAFighter = true;
			else
				attackTimer += attackerCooldown;
		}
		else if (attackTimer < attackerCooldown * 2)
		{
			if (!fighterChoosen)
			{
				if (enemyAIs[0]->IsLock())
					fighterPos = FMath::RandRange(1, _nbEnemy - 1);
				else
					fighterPos = FMath::RandRange(0, _nbEnemy - 1);
				fighterChoosen = true;
			}
			enemyAIs[fighterPos % (_nbEnemy - 1)]->isAFighter = true;
		}
		else 
		{
			attackTimer = 0;
			fighterChoosen = false;
		}
	}
}

void AEnemyAIManager::AddEnemyAI(AEnemyAIController* enemyAI)
{
	int _insertNum = 0;

	int _nbEnemy = enemyAIs.Num();

	if (_nbEnemy > 0)
	{
		FVector _playerPos = player->GetActorLocation();
		FVector _v1 = enemyAIs[0]->GetPawn()->GetActorLocation() - _playerPos;
		FVector _v2 = enemyAI->GetPawn()->GetActorLocation() - _playerPos;

		float _angle = atan2(_v1.Y, _v1.X) - atan2(_v2.Y, _v2.X);

		if (_angle < 0)
			_angle += 2 * PI;
		
		_angle = FMath::RadiansToDegrees(_angle);

		int _newPos = (FMath::FloorToInt(_angle / (360.0f / _nbEnemy)) + 1);

		enemyAIs.Insert(enemyAI, _newPos);
		
		if (letPlaceToNewAI)
		{
			TArray<AEnemyAIController*> _tempEnemy;
			for (int i = 0; i < _nbEnemy + 1; ++i)
			{
				_tempEnemy.Add(enemyAIs[(i + _newPos) % (_nbEnemy + 1)]);
			}
			enemyAIs.Empty();
			enemyAIs.Append(_tempEnemy);
		}
	}
	else
	{
		enemyAIs.Insert(enemyAI, _insertNum);
	}
}

void AEnemyAIManager::RemoveEnemyAI(AEnemyAIController* enemyAI)
{
	enemyAIs.Remove(enemyAI);
}
