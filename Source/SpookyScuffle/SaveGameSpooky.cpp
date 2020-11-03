// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSpooky.h"
#include "Kismet/GameplayStatics.h"
#include "Character/GeneralCharacter.h"
#include "Engine/World.h"
#include "Character/SpookyScuffleCharacter.h"
#include "Character/VillagerCharacter.h"
#include "Character/SquireCharacter.h"
#include "LDBlock/CheckPoint.h"

USaveGameSpooky::USaveGameSpooky()
{
    playerName = TEXT("player");
	saveSlotName = TEXT("saveSlot");
	userIndex = 0;
}
USaveGameSpooky::USaveGameSpooky(FString namePlayer, FString nameSlot, int index)
{
    playerName = namePlayer;
    saveSlotName = nameSlot;
    userIndex = index;
}

void USaveGameSpooky::SetSavedGame(FString namePlayer, FString nameSlot, int index)
{
    this->playerName = namePlayer;
    this->saveSlotName = nameSlot;
    this->userIndex = index;
}

// ============================================= SAVE FUNCTION ============================================= //

void USaveGameSpooky::mySaveGame()
{
    UE_LOG(LogTemp, Warning, TEXT("SAVING..."));

    USaveGameSpooky* _saveOfGame = Cast<USaveGameSpooky>(UGameplayStatics::CreateSaveGameObject(USaveGameSpooky::StaticClass()));

    _saveOfGame->transformCharacter.Empty();
    _saveOfGame->indexCharacter.Empty();
    _saveOfGame->isAliveCharacter.Empty();
    _saveOfGame->indexMax = 0;

    TArray<AActor*> _FoundCharacters;
    UGameplayStatics::GetAllActorsOfClass(myCheckPoint->GetWorld(), AGeneralCharacter::StaticClass(), _FoundCharacters);
    int _index = 0;

    for (AActor* _character : _FoundCharacters)
    {
        AGeneralCharacter* _gCharacter = Cast<AGeneralCharacter>(_character);

        _gCharacter->indexSave = _index;
        _saveOfGame->transformCharacter.Add(_gCharacter->GetActorTransform());
        _saveOfGame->indexCharacter.Add(_gCharacter->indexSave);
        _saveOfGame->isAliveCharacter.Add(_gCharacter->IsAlive());

        _index++;
    }

    _saveOfGame->indexMax = _index;
    UE_LOG(LogTemp, Warning, TEXT("MAX SAVE INDEX: %i"), _saveOfGame->indexMax);

    if (UGameplayStatics::SaveGameToSlot(_saveOfGame, TEXT("oui"), 1))
    {
        UE_LOG(LogTemp, Warning, TEXT("SAVE SUCEED"));
    }
}

// ============================================= LOAD FUNCTION ============================================= //

void USaveGameSpooky::LoadGame(FString slot, int index)
{
    UE_LOG(LogTemp, Warning, TEXT("LOADING..."));
    UE_LOG(LogTemp, Warning, TEXT("Slot : %s"), *slot);
    UE_LOG(LogTemp, Warning, TEXT("IndexSlot : %i"), index);

    if (UGameplayStatics::DoesSaveGameExist("oui", 1))
    {
        if (Cast<USaveGameSpooky>(UGameplayStatics::LoadGameFromSlot("oui", 1)))
        {
            UE_LOG(LogTemp, Warning, TEXT("Cast SUCEED"));
        }

        USaveGameSpooky* _loadedGame = Cast<USaveGameSpooky>(UGameplayStatics::LoadGameFromSlot("oui", 1));

            // try to load game
        
        

        UE_LOG(LogTemp, Warning, TEXT("Index Max : %i"), _loadedGame->indexMax);

        if (_loadedGame->indexMax > 0)
        {
            indexMax = _loadedGame->indexMax;

            for (int i = 0; i <= _loadedGame->indexMax; i++)
            {
                AGeneralCharacter* myCharacter = nullptr;
                myCharacter = myCharacter->FindCharacterByIndex(_loadedGame->indexCharacter[i]);
                myCharacter->SetActorTransform(_loadedGame->transformCharacter[i]);
                myCharacter->SetIsAlive(_loadedGame->isAliveCharacter[i]);
                myCharacter->CheckIsAliveToCheckPoint();

            }

            // The operation was successful, so LoadedGame now contains the data we saved earlier.
            UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *_loadedGame->playerName);
        }
    }
    else
        UE_LOG(LogTemp, Warning, TEXT("ERROR NO SAVE"));
}