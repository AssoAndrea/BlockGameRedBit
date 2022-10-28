// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecialBlock.h"
#include "PaperSpriteComponent.h"
#include "Grid.h"

void ASpecialBlock::BeginPlay()
{
	Super::BeginPlay();
	Type = (SpecialType)FMath::RandRange(0, (int)SpecialType::MAX - 1);
	if (BombTypeSprites.Contains(Type))
	{
		GetRenderComponent()->SetSprite(BombTypeSprites[Type]);
		UE_LOG(LogTemp, Warning, TEXT("trovato"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("non trovo in dict %d"),(int)Type);
	}
	GetRenderComponent()->SetSpriteColor(FLinearColor::White);
}

void ASpecialBlock::BlockClicked(AActor* Target, FKey ButtonPressed)
{
	Super::BlockClicked(Target,ButtonPressed);
	switch (Type)
	{
	case SpecialType::Bomb:
		Owner->DestroyOnRange(GridPosition);
		break;
	case SpecialType::Horizontal:
		Owner->DestroyAllHorizontal(GridPosition);
		break;
	case SpecialType::Vertical:
		Owner->DestroyAllVertical(GridPosition);
		break;
	case SpecialType::MAX:
		break;
	default:
		break;
	}
}
