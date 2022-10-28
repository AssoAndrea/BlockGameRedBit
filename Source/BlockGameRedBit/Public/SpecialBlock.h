// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "PaperSpriteComponent.h"
#include "SpecialBlock.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class SpecialType : uint8
{
	Bomb UMETA(DisplayName = "Bomb"),
	Horizontal UMETA(DisplayName = "Horizontal"),
	Vertical UMETA(DisplayName = "Vertical"),
	MAX,
};
/**
 * 
 */
UCLASS()
class BLOCKGAMEREDBIT_API ASpecialBlock : public ABlock
{
	GENERATED_BODY()


	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<SpecialType, UPaperSprite*> BombTypeSprites;

	virtual void BlockClicked(AActor* Target, FKey ButtonPressed) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SpecialType Type;

};
