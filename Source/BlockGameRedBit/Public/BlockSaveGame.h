// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BlockSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API UBlockSaveGame : public USaveGame
{
	GENERATED_BODY()

	UBlockSaveGame();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int HighScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int LastPoints;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	FString SlotName;
};
