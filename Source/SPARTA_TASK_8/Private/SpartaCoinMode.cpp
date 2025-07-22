// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCoinMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h" 
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "StageWaveInfo.h"
#include "Item/CoinItem.h"
#include "SpawnVolume.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaCoinMode)

ASpartaCoinMode::ASpartaCoinMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}

void ASpartaCoinMode::BeginPlay()
{
	Super::BeginPlay();
	auto& GInst = *GetGameInstance<USpartaGameInstance>();
	if (GInst.GetCurrentLevelIndex() > -1)
	{
		// 게임 시작 시 첫 레벨부터 진행
		StartLevel();
	}
}

void ASpartaCoinMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (SpartaGameState)
	{
		float CurrentRemainingTime = SpartaGameState->GetRemainingWaveTime();
		CurrentRemainingTime -= DeltaSeconds;

		if (CurrentRemainingTime <= 0.0f)
		{
			CurrentRemainingTime = 0.f;
			OnGameOver();
		}
		SpartaGameState->SetRemainingWaveTime(CurrentRemainingTime);
	}
}

void ASpartaCoinMode::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
	EndWave(false);
}

void ASpartaCoinMode::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD();
		}
	}
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (SpartaGameState)
	{
		SpartaGameState->AddScore(-SpartaGameState->GetScore());
	}
	// 첫 웨이브 시작
	CurrentWaveIndex = 0;
	StartWave();
}

void ASpartaCoinMode::StartWave()
{
	const FLevelInfo* CurrentStageData = GetGameInstance<USpartaGameInstance>()->GetCurrentLevelInfo();
	UStageWaveInfo* levelWaveInfo = nullptr;
	levelWaveInfo = CurrentStageData ? 
		Cast<UStageWaveInfo>(CurrentStageData->levelWaveInfo) : nullptr;

	const bool bShouldEndLevel = 
		!CurrentStageData || 
		!levelWaveInfo || 
		levelWaveInfo->WaveInfo.Num() <= CurrentWaveIndex;

	if (bShouldEndLevel)
	{
		GetGameInstance<USpartaGameInstance>()->EndLevel(true);
		return;
	}

	const FWaveInfo& CurrentWave = levelWaveInfo->WaveInfo[CurrentWaveIndex];

	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (SpartaGameState)
	{
		// 웨이브 시작 시, 코인 개수 초기화 (각 웨이브마다 스폰되는 코인 개수를 초기화)
		SpartaGameState->SetSpawnedCoinCount(0);
		SpartaGameState->SetCollectedCoinCount(0);

		// 웨이브 남은 시간 설정
		SpartaGameState->SetRemainingWaveTime(CurrentWave.Time);
	}

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	if (FoundVolumes.Num() > 0)
	{
		int32 CollectCoinScore = CurrentWave.CollectCoinScore;

		TArray<int32> VolumeSpawnNums;
		VolumeSpawnNums.Reserve(FoundVolumes.Num());
		for (int32 i = 0; i < FoundVolumes.Num(); ++i)
			VolumeSpawnNums.Push(0);

		bool bLastSpawn = true; 
		while (bLastSpawn)
		{
			bLastSpawn = false;
			for (int32 i = 0; i < FoundVolumes.Num(); ++i)
			{
				const auto SpawnVolumesActor = FoundVolumes[i];
				const auto SpawnVolume = Cast<ASpawnVolume>(SpawnVolumesActor);
				if (IsValid(SpawnVolume) == false
					or VolumeSpawnNums[i] == SpawnVolume->GetSpawnNum())
				{
					continue;
				}

				TSubclassOf<AActor> RandomItemClass = SpawnVolume->RandomItemClass();
				bool bIsCoin = RandomItemClass->IsChildOf(ACoinItem::StaticClass());
				AActor* SpawnedActor = nullptr;

				++VolumeSpawnNums[i];
				bLastSpawn = true;

				if (bIsCoin)
				{	// 코인은 정해진 만큼만 소환된다.
					ACoinItem* CDOCoin = Cast<ACoinItem>(RandomItemClass.GetDefaultObject());
					CollectCoinScore -= CDOCoin->GetPointValue();
				}
				SpawnedActor = SpawnVolume->SpawnItem(RandomItemClass);
				// 만약 스폰된 액터가 코인 타입이라면 SpawnedCoinCount 증가
				if (SpawnedActor && bIsCoin)
				{
					SpartaGameState->SetSpawnedCoinCount(SpartaGameState->GetSpawnedCoinCount() + 1);
				}

				if (bIsCoin and CollectCoinScore < 0)
				{	// 더이상 코인은 소환할 수 없기 때문에 이 볼륨에서 추가 소환을 막는다.
					VolumeSpawnNums[i] = SpawnVolume->GetSpawnNum();
					bLastSpawn = false;
				}
			}
		}
	}

	// 웨이브 함수 실행
	ProcessWaveFunction(CurrentWave.WaveFunctionType);



	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start! Duration: %.1f"), CurrentWaveIndex + 1, CurrentWave.Time);
}

void ASpartaCoinMode::EndWave(bool bIsClear)
{
	if(bIsClear)
	{
		// 다음 웨이브로 진행
		CurrentWaveIndex++;
		StartWave();
	}
	else
	{
		GetGameInstance<USpartaGameInstance>()->EndLevel(false);
	}
}

void ASpartaCoinMode::ProcessWaveFunction(EWaveFunction FuncType)
{
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (!SpartaGameState)
	{
		return;
	}

	switch (FuncType)
	{
		case EWaveFunction::NONE:
			// 아무것도 하지 않음
			break;
		case EWaveFunction::FLOOR_REMOVE:
			// TODO: 바닥 제거 로직 구현
			
			break;
		default:
			break;
	}

	UE_LOG(LogTemp, Log, TEXT("Spawned %d coin"), SpartaGameState->GetSpawnedCoinCount());
}



void ASpartaCoinMode::OnCoinCollected(ACoinItem* CoinItem)
{

	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (SpartaGameState)
	{
		SpartaGameState->AddScore(CoinItem->GetPointValue());
		SpartaGameState->SetCollectedCoinCount(SpartaGameState->GetCollectedCoinCount() + 1);

		UE_LOG(LogTemp, Log, TEXT("Coin Collected: %d / %d"), 
			SpartaGameState->GetCollectedCoinCount(),
			SpartaGameState->GetSpawnedCoinCount())

		ASpartaPlayerController* Controller = nullptr;
		UWorld* World = GetWorld();

		if (World)
		{
			Controller = Cast<ASpartaPlayerController>(World->GetFirstPlayerController());
			if (Controller)
				Controller->UpdateHUD();
		}

		// 현재 레벨에서 스폰된 코인을 전부 주웠다면 즉시 Wave 종료
		if (SpartaGameState->GetSpawnedCoinCount() > 0 
			&& SpartaGameState->GetCollectedCoinCount() >= SpartaGameState->GetSpawnedCoinCount())
		{
			EndWave(true);
		}

	}
}
