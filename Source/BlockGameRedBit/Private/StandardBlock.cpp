// Fill out your copyright notice in the Description page of Project Settings.

#include "StandardBlock.h"
#include "PaperSpriteComponent.h"
#include "Grid.h"

void AStandardBlock::BeginPlay()
{
	Super::BeginPlay();
	int RandIndex = FMath::RandRange(0, RandomColors.Num() - 1);
	GetRenderComponent()->SetSpriteColor(RandomColors[RandIndex]);
}

void AStandardBlock::BlockClicked(AActor* Target, FKey ButtonPressed)
{
	Owner->DestroyAllOfColor(GridPosition, GetColor());
}
