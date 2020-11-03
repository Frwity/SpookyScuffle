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
}


void AEnemyAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int _nbEnemy = enemyAIs.Num();
	FVector _playerPos = player->GetActorLocation();
	
	if (_nbEnemy > 0)
	{
		int _pos = 0;
		for (AEnemyAIController* _enemyAI : enemyAIs)
		{
			_pos++;
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
		}
		FVector _targetPos = (enemyAIs[0]->GetPawn()->GetActorLocation() - _playerPos).GetSafeNormal2D() * enemyAIs[0]->GetSafeDistance() + _playerPos;
		for (AEnemyAIController* _enemyAI : enemyAIs)
		{
			_enemyAI->SetTargetPos(_targetPos);
			_targetPos = (_targetPos - _playerPos).RotateAngleAxis(360.0f / _nbEnemy, { 0.0f, 0.0f, -1.0f }) + _playerPos;
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
