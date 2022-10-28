// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameUtils.h"
#include "Kismet/GameplayStatics.h"


UBlockSaveGame* USaveGameUtils::GetGameSave(TSubclassOf<UBlockSaveGame> SaveClass)
{
	const FString slot = SaveClass.GetDefaultObject()->SlotName;
	if (UGameplayStatics::DoesSaveGameExist(slot, 0))
	{
		return Cast<UBlockSaveGame>(UGameplayStatics::LoadGameFromSlot(slot, 0));
	}
	else
	{
		return Cast<UBlockSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveClass.GetDefaultObject()->StaticClass()));
	}
}

void USaveGameUtils::SaveGame(TSubclassOf<UBlockSaveGame> SaveClass,int LastPoints ,int newHighScore)
{
	const FString slot = SaveClass.GetDefaultObject()->SlotName;
	if (UBlockSaveGame* SaveGameInstance = Cast<UBlockSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlockSaveGame::StaticClass())))
	{
		SaveGameInstance->HighScore = newHighScore;
		SaveGameInstance->LastPoints = LastPoints;
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, slot, 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("game saved %d"),SaveGameInstance->LastPoints);
		}
	}
}
