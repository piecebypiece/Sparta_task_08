#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // FTableRowBase 정의가 들어있는 헤더
#include "SpawnVolume.h"
#include "StageWaveInfo.generated.h"

UENUM(BlueprintType)
enum class EWaveFunction : uint8
{
	NONE UMETA(DisplayName = "None"),
	FLOOR_REMOVE UMETA(DisplayName="Floor remove"),
};

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ASpawnVolume>> SpawnVolumeArray;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWaveFunction WaveFunctionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CollectCoinScore;
};


/// <summary>
///  스테이지 웨이브에 대한 정보 
/// </summary>
UCLASS(BlueprintType)
class UStageWaveInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWaveInfo> WaveInfo;
	
};


