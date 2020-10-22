// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameSpooky.h"
#include "Kismet/GameplayStatics.h"

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

// ============================================= BASIC Function ============================================= //

void USaveGameSpooky::SaveGame()
{
    if (USaveGameSpooky* SaveGameInstance = Cast<USaveGameSpooky>(UGameplayStatics::CreateSaveGameObject(USaveGameSpooky::StaticClass())))
    {
        // Set data on the savegame object.
        SaveGameInstance->playerName = TEXT("playerOne");
        SaveGameInstance->saveSlotName = TEXT("playerOneSlot");
        SaveGameInstance->userIndex = 0;

        // Save the data immediately.
        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->saveSlotName, SaveGameInstance->userIndex))
        {
            // Save succeeded.
        }
    }
}

void USaveGameSpooky::SaveGame(FString name, FString slot, int index)
{
    if (USaveGameSpooky* SaveGameInstance = Cast<USaveGameSpooky>(UGameplayStatics::CreateSaveGameObject(USaveGameSpooky::StaticClass())))
    {
        // Set data on the savegame object.
        SaveGameInstance->playerName = name;
        SaveGameInstance->saveSlotName = slot;
        SaveGameInstance->userIndex = index;

        // Save the data immediately.
        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->saveSlotName, SaveGameInstance->userIndex))
        {
            // Save succeeded.
        }
    }
}

void USaveGameSpooky::LoadGame()
{
    if (USaveGameSpooky* LoadedGame = Cast<USaveGameSpooky>(UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex)))
    {
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->playerName);
    }
}

void USaveGameSpooky::LoadGame(FString slot , int index)
{
    if (USaveGameSpooky* LoadedGame = Cast<USaveGameSpooky>(UGameplayStatics::LoadGameFromSlot(slot, index)))
    {
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->playerName);
    }
}

// ============================================= MY Function ============================================= //

void USaveGameSpooky::SetSavedGame(FString namePlayer, FString nameSlot, int index)
{
    this->playerName = namePlayer;
    this->saveSlotName = nameSlot;
    this->userIndex = index;
}

void USaveGameSpooky::mySaveGame()
{
    if (UGameplayStatics::SaveGameToSlot(this, saveSlotName, userIndex))
    {
        // Save succeeded.
        UE_LOG(LogTemp, Warning, TEXT("Save: %s"), *playerName);
    }
}