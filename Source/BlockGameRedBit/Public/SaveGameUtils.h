// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlockSaveGame.h"
#include "SaveGameUtils.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API USaveGameUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static UBlockSaveGame* GetGameSave(TSubclassOf<UBlockSaveGame> SaveClass);

	UFUNCTION(BlueprintCallable)
	static void SaveGame(TSubclassOf<UBlockSaveGame> SaveClass,int LastPoints, int newHighScore);
	
};
