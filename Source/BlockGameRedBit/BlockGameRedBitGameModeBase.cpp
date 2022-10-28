// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGameRedBitGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameUtils.h"

ABlockGameRedBitGameModeBase::ABlockGameRedBitGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ABlockGameRedBitGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer -= DeltaTime;
	if (Timer <= 0)
	{
		GameOver();
	}
}

void ABlockGameRedBitGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HighScore = USaveGameUtils::GetGameSave(UBlockSaveGame::StaticClass())->HighScore;
	Timer = StartTimer;
}

void ABlockGameRedBitGameModeBase::GameOver()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameOverLevel);
}

void ABlockGameRedBitGameModeBase::BlockDestroyed(int nOfBlock)
{
	int x = nOfBlock;
	Points += FMath::Abs((x - 1) * 80 + FMath::Pow(((x - 2) / 5), 2));
	Timer += 10 + FMath::Pow(((x - 2) / 3), 2) * 20;

	if (Points > HighScore)
	{
		HighScore = Points;
	}

	USaveGameUtils::SaveGame(UBlockSaveGame::StaticClass(), Points, HighScore);
}
