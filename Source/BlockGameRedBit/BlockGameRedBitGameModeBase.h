// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlockGameRedBitGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API ABlockGameRedBitGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ABlockGameRedBitGameModeBase();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

public:
	void GameOver();
	void BlockDestroyed(int nOfBlock);

	UPROPERTY(EditAnywhere)
	TAssetPtr<UWorld> GameOverLevel;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float StartTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Points;

	int HighScore;



};
