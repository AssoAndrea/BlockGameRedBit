// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StandardBlock.h"
#include "BlockGameRedBit/BlockGameRedBitGameModeBase.h"
#include "SpecialBlock.h"
#include "Grid.generated.h"

UCLASS()
class BLOCKGAMEREDBIT_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ABlockGameRedBitGameModeBase* GM;

public:	
	// Called every frame

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlockSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AStandardBlock> StandardBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpecialBlock> SpecialBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	float SpecialProb = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FVector2D,ABlock*> Blocks;


	void DestroyOnRange(FVector2D pos,int Range = 1);
	void DestroyAllHorizontal(FVector2D pos);
	void DestroyAllVertical(FVector2D pos);
	void DestroyAllOfColor(FVector2D pos, FLinearColor color);

	bool GRIDCONTAIN(FVector2D pos) const;

private:
	TArray<FVector2d> PosToReplace;

	UFUNCTION()
	void ReplaceEmpty();

	void CreateGrid();

	void RemoveBlock(FVector2D pos);

	void TryColorDestroyNearest(FVector2D pos, FLinearColor color);

	bool CheckForCombination();
	
	ABlock* SpawnOnGrid(FVector2D pos, TSubclassOf<ABlock> BlockToSpawn);

	void StartWaitTimer();

	bool HaveColoNear(FVector2D pos, FLinearColor color);

	void GameOver();

	FTimerHandle WaitHandler;

	bool bCanMove;

	int blockAccumulator;

};
