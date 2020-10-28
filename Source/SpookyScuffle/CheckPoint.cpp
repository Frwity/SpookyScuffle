// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "SaveGameSpooky.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GeneralCharacter.h"
#include "DoorEnemy.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint::CheckIsOk()
{
	if (!isCheck)
	{
		isCheck = true;

        SaveDataCharacters();
        SaveDataDoor();
	}
}

void ACheckPoint::LoadGameAtCheckPoint()
{
    if (isCheck)
    {
        LoadDataCharacters();
        LoadDataDoor();
    }
}

// ===================================== Save Data ===================================== //

void ACheckPoint::SaveDataCharacters()
{
    transformCharacter.Empty();
    isAliveCharacter.Empty();

    // Enemies
    TArray<AActor*> _FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneralCharacter::StaticClass(), _FoundCharacters);
    int _index = 0;

    for (AActor* _character : _FoundCharacters)
    {
        AGeneralCharacter* _gCharacter = Cast<AGeneralCharacter>(_character);

        _gCharacter->indexSave = _index;
        transformCharacter.Add(_gCharacter->GetActorTransform());
        isAliveCharacter.Add(_gCharacter->IsAlive());

        _index++;
    }
}

void ACheckPoint::SaveDataDoor()
{
    // Door
    savePosDoor.Empty();

    TArray<AActor*> _FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorEnemy::StaticClass(), _FoundDoors);
    int _indexDoor = 0;

    for (AActor* _door : _FoundDoors)
    {
        ADoorEnemy* _gDoor = Cast<ADoorEnemy>(_door);

        _gDoor->indexSave = _indexDoor;
        savePosDoor.Add(_gDoor->GetActorLocation());

        _indexDoor++;
    }
}

// ===================================== Load Data ===================================== //

void ACheckPoint::LoadDataCharacters()
{
    TArray<AActor*> _FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeneralCharacter::StaticClass(), _FoundCharacters);

    for (AActor* _character : _FoundCharacters)
    {
        AGeneralCharacter* _gCharacter = Cast<AGeneralCharacter>(_character);

        _gCharacter->SetActorTransform(transformCharacter[_gCharacter->indexSave]);
        _gCharacter->SetIsAlive(isAliveCharacter[_gCharacter->indexSave]);
        _gCharacter->CheckIsAliveToCheckPoint();
    }
}

void ACheckPoint::LoadDataDoor()
{
    TArray<AActor*> _FoundDoors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorEnemy::StaticClass(), _FoundDoors);

    for (AActor* _door : _FoundDoors)
    {
        ADoorEnemy* _gDoor = Cast<ADoorEnemy>(_door);

        _gDoor->SetActorLocation(savePosDoor[_gDoor->indexSave]);
    }
}