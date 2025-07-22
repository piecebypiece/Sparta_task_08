// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Item/CoinItem.h"
#include "SpartaPlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaGameState)

inline ASpartaGameState::ASpartaGameState()
{
	Score = 0;
}


int32 ASpartaGameState::GetScore() const
{
    return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
    Score += Amount;
	if (auto* instance = Cast<USpartaGameInstance>(GetGameInstance()))
	{
		instance->AddToScore(Amount);
	}
}

int32 ASpartaGameState::GetSpawnedCoinCount() const
{
	return SpawnedCoinCount;
}

int32 ASpartaGameState::GetCollectedCoinCount() const
{
	return CollectedCoinCount;
}

void ASpartaGameState::SetSpawnedCoinCount(int32 Count)
{
	SpawnedCoinCount = Count;
}

void ASpartaGameState::SetCollectedCoinCount(int32 Count)
{
	CollectedCoinCount = Count;
}

float ASpartaGameState::GetRemainingWaveTime() const
{
	return RemainingWaveTime;
}

void ASpartaGameState::SetRemainingWaveTime(float Time)
{
	RemainingWaveTime = Time;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();
}




