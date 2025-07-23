

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.h"
#include "WaveSpawnVolumeGroup.generated.h"

/// <summary>
/// SpawnVolume 여러개를 묶어 각 Wave가 시작 될 때 스폰시켜주는 VolumeGroup
/// </summary>
UCLASS(BlueprintType)
class SPARTA_TASK_8_API AWaveSpawnVolumeGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveSpawnVolumeGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void Spawn(int32 InCollectCoinScore);
	

protected:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void OnWaveStart(int32 WaveIndex, struct FWaveInfo WaveInfo);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 SpawnWaveIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 SpawnNum;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Spawning")
	TArray<TObjectPtr<ASpawnVolume>> Volumes;
};
