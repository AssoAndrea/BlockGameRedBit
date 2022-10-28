// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "StandardBlock.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API AStandardBlock : public ABlock
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void BlockClicked(AActor* Target, FKey ButtonPressed) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<FLinearColor> RandomColors;

	FLinearColor SelectedColor;
	
	bool operator==(const AStandardBlock& Other) const
	{
		return SelectedColor == Other.SelectedColor;
	}
};
