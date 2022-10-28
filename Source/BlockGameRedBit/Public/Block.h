// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Block.generated.h"


class AGrid;
/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API ABlock : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	void ChangeColor(FLinearColor newColor);
	void Setup(AGrid* newOwner,FVector2D position);
	FLinearColor GetColor();

	UFUNCTION()
	virtual void BlockClicked(AActor* Target, FKey ButtonPressed);

	//void NotifyActorOnClicked(FKey ButtonPressed) override;
	virtual void BeginPlay() override;

protected:
	AGrid* Owner;
	FVector2D GridPosition;
};


