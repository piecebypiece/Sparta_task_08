


#include "WaveSpawnVolumeGroup.h"
#include "Kismet/GameplayStatics.h"
#include "Item\CoinItem.h"
#include <SpartaCoinMode.h>
#include <SpartaGameState.h>
#include UE_INLINE_GENERATED_CPP_BY_NAME(WaveSpawnVolumeGroup)

AWaveSpawnVolumeGroup::AWaveSpawnVolumeGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWaveSpawnVolumeGroup::BeginPlay()
{
	Super::BeginPlay();
	
	auto World = GetWorld();
	if (World)
	{
		auto SpartaGameMode = Cast<ASpartaCoinMode>(UGameplayStatics::GetGameMode(World));
		if (SpartaGameMode)
		{
			SpartaGameMode->OnWaveStart.AddDynamic(this, &AWaveSpawnVolumeGroup::OnWaveStart);
		}
	}
}

// Called every frame
void AWaveSpawnVolumeGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveSpawnVolumeGroup::OnWaveStart(int32 WaveIndex, FWaveInfo WaveInfo)
{
	if (WaveIndex != SpawnWaveIndex)
		return;

	Spawn(WaveInfo.CollectCoinScore);
}

void AWaveSpawnVolumeGroup::Spawn(int32 InCollectCoinScore)
{
	TArray<TObjectPtr<ASpawnVolume>> FoundVolumes = Volumes;

	ASpartaGameState* SpartaGameState = Cast<ASpartaGameState>(GetWorld()->GetGameState());

	if (FoundVolumes.Num() > 0)
	{
		TArray<int32> VolumeSpawnNums;
		VolumeSpawnNums.Reserve(FoundVolumes.Num());
		for (int32 i = 0; i < FoundVolumes.Num(); ++i)
			VolumeSpawnNums.Push(0);

		int32 CollectCoinScore = InCollectCoinScore;
		bool bLastSpawn = true; 
		while (bLastSpawn)
		{
			bLastSpawn = false;
			for (int32 i = 0; i < FoundVolumes.Num(); ++i)
			{
				//const auto SpawnVolumesActor = FoundVolumes[i];
				const auto SpawnVolume = FoundVolumes[i];
				if (IsValid(SpawnVolume) == false
					or VolumeSpawnNums[i] == SpawnNum)
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
					VolumeSpawnNums[i] = SpawnNum;
					bLastSpawn = false;
				}
			}
		}
	}
}


