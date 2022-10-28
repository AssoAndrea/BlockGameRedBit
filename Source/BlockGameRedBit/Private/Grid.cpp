// Fill out your copyright notice in the Description page of Project Settings.

#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	GM = Cast< ABlockGameRedBitGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GM))
	{
		UE_LOG(LogTemp, Error, TEXT("wrong Game mode"));
	}

	CreateGrid();
	bCanMove = true;
}


void AGrid::DestroyOnRange(FVector2D pos,int Range)
{
	if (!bCanMove) return;

	int StartX = pos.X + Range;
	int StartY = pos.Y + Range;
	int EndX = pos.X - Range;
	int EndY = pos.Y - Range;
	StartX = FMath::Clamp(StartX, 0, GridSize.X - 1);
	StartY = FMath::Clamp(StartY, 0, GridSize.Y - 1);
	EndX = FMath::Clamp(EndX, 0, GridSize.X - 1);
	EndY = FMath::Clamp(EndY, 0, GridSize.Y - 1);

	for (int y = StartY; y >= EndY; y--)
	{
		for (int x = StartX; x >= EndX; x--)
		{
			if (Blocks.Contains(FVector2D(x, y)))
			{
				RemoveBlock(FVector2D(x, y));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("%d : %d not in dict"), x, y);
			}
		}
	}
	StartWaitTimer();

}

void AGrid::RemoveBlock(FVector2D pos)
{
	ABlock* block = Blocks[pos];
	blockAccumulator++;
	Blocks.Remove(pos);
	block->Destroy();
	PosToReplace.Add(pos);
}

void AGrid::TryColorDestroyNearest(FVector2D pos, FLinearColor color)
{
	RemoveBlock(pos);

	FVector2D rightPos = pos + FVector2D(-1, 0);
	if (GRIDCONTAIN(rightPos) && Blocks[rightPos]->GetColor() == color)
	{
		TryColorDestroyNearest(rightPos,color);
	}

	FVector2D leftPos = pos + FVector2D(1, 0);
	if (GRIDCONTAIN(leftPos) && Blocks[leftPos]->GetColor() == color)
	{
		TryColorDestroyNearest(leftPos, color);
	}

	FVector2D upPos = pos + FVector2D(0, 1);
	if (GRIDCONTAIN(upPos) && Blocks[upPos]->GetColor() == color)
	{
		TryColorDestroyNearest(upPos, color);
	}

	FVector2D downPos = pos + FVector2D(0, -1);
	if (GRIDCONTAIN(downPos) && Blocks[downPos]->GetColor() == color)
	{
		TryColorDestroyNearest(downPos, color);
	}


}

bool AGrid::CheckForCombination()
{
	for (size_t y = 0; y < GridSize.X; y++)
	{
		for (size_t x = 0; x < GridSize.Y; x++)
		{
			if (GRIDCONTAIN(FVector2D(x, y)))
			{
				if (HaveColoNear(FVector2D(x, y), Blocks[FVector2D(x, y)]->GetColor()))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void AGrid::DestroyAllHorizontal(FVector2D pos)
{
	if (!bCanMove) return;

	for (int x = 0; x < GridSize.X; x++)
	{
		RemoveBlock(FVector2D(x, pos.Y));
	}

	StartWaitTimer();

}

void AGrid::DestroyAllVertical(FVector2D pos)
{
	if (!bCanMove) return;

	for (int y = 0; y < GridSize.Y; y++)
	{
		RemoveBlock(FVector2D(pos.X, y));
	}

	StartWaitTimer();
}

void AGrid::DestroyAllOfColor(FVector2D pos, FLinearColor color)
{
	if (!bCanMove || !HaveColoNear(pos,color)) return;
	TryColorDestroyNearest(pos, color);
	StartWaitTimer();
}

bool AGrid::GRIDCONTAIN(FVector2D pos) const
{
	return Blocks.Contains(pos);
}

void AGrid::CreateGrid()
{
	Blocks.Empty();
	do
	{
		for (size_t y = 0; y < GridSize.X; y++)
		{
			for (size_t x = 0; x < GridSize.Y; x++)
			{
				TSubclassOf<ABlock> BlockToSpawn = StandardBlock;
				float prob = FMath::FRand();
				if (prob < SpecialProb / 100)
				{
					BlockToSpawn = SpecialBlock;
				}
				SpawnOnGrid(FVector2D(x, y), BlockToSpawn);
			}
		}
	} while (!CheckForCombination());
}



void AGrid::ReplaceEmpty()
{
	for (FVector2D pos : PosToReplace)
	{
		float prob = FMath::FRand();
		TSubclassOf<ABlock> BlockToSpawn = StandardBlock;
		if (prob < SpecialProb / 100)
		{
			BlockToSpawn = SpecialBlock;
		}
		SpawnOnGrid(pos, BlockToSpawn);
	}
	PosToReplace.Empty();
	bCanMove = true;

	if (!CheckForCombination()) //GAME OVER
	{
		GM->GameOver();
	}
}

ABlock* AGrid::SpawnOnGrid(FVector2D pos,TSubclassOf<ABlock> BlockToSpawn)
{
	FVector StartPosition = GetActorLocation() - FVector((GridSize.Y - 1) * BlockSize / 2, 0, (GridSize.X - 1) * BlockSize / 2);
	FVector newPos = StartPosition + FVector(pos.X, 0, pos.Y) * BlockSize;
	ABlock* SpawnedBlock = GetWorld()->SpawnActor<ABlock>(BlockToSpawn, newPos, FRotator::ZeroRotator);
	SpawnedBlock->Setup(this, pos);
	Blocks.Add(pos, SpawnedBlock);
	return SpawnedBlock;
}

void AGrid::StartWaitTimer()
{
	GM->BlockDestroyed(blockAccumulator);
	blockAccumulator = 0;
	bCanMove = false;
	GetWorld()->GetTimerManager().SetTimer(WaitHandler, this, &AGrid::ReplaceEmpty, WaitTime, false);
}

bool AGrid::HaveColoNear(FVector2D pos, FLinearColor color)
{
	FVector2D rightPos = pos + FVector2D(-1, 0);
	FVector2D leftPos = pos + FVector2D(1, 0);
	FVector2D upPos = pos + FVector2D(0, 1);
	FVector2D downPos = pos + FVector2D(0, -1);

	return	(GRIDCONTAIN(rightPos) && Blocks[rightPos]->GetColor() == color) ||
		(GRIDCONTAIN(leftPos) && Blocks[leftPos]->GetColor() == color) ||
		(GRIDCONTAIN(upPos) && Blocks[upPos]->GetColor() == color) ||
		(GRIDCONTAIN(downPos) && Blocks[downPos]->GetColor() == color);
}

void AGrid::GameOver()
{
	GM->GameOver();
}

