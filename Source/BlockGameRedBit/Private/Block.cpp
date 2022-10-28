// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Grid.h"
#include "PaperSpriteComponent.h"


void ABlock::ChangeColor(FLinearColor newColor)
{
	GetRenderComponent()->SetSpriteColor(newColor);
}

void ABlock::Setup(AGrid* newOwner,FVector2D position)
{
	Owner = newOwner;
	GridPosition = position;
}

FLinearColor ABlock::GetColor()
{
	return GetRenderComponent()->GetSpriteColor();
}



void ABlock::BlockClicked(AActor* Target, FKey ButtonPressed)
{
}


void ABlock::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddUniqueDynamic(this, &ABlock::BlockClicked);
}
