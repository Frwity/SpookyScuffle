// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SpookyScuffleGameMode.h"
#include "Character/SpookyScuffleCharacter.h"
#include "AI/EnemyAIManager.h"
#include "AI/EnemyAIController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"


ASpookyScuffleGameMode::ASpookyScuffleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	state = E_GAMESTATE::STARTING;
}

void ASpookyScuffleGameMode::BeginPlay()
{
	TArray<AActor*> _enemyAIManager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIManager::StaticClass(), _enemyAIManager);
	enemyAIManager = Cast<AEnemyAIManager>(_enemyAIManager[0]);

	TArray<AActor*> enemyAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), enemyAIs);

	for (auto enemyAI : enemyAIs)
	{	
		Cast<AEnemyAIController>(enemyAI)->SetEnemyAIManager(enemyAIManager);
	}
}