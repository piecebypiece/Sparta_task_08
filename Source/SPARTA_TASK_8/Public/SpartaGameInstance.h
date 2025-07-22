

#pragma once

#include "CoreMinimal.h"
#include "SpartaGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FLevelInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> levelAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataAsset> levelWaveInfo;
};

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USpartaGameInstance();

	// 게임 전체 누적 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	// 현재 레벨 인덱스 (GameState에서도 관리할 수 있지만, 맵 전환 후에도 살리고 싶다면 GameInstance에 복제할 수 있음)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FLevelInfo> LevelInfos;
	//TArray<FName> LevelMapNames;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);	

	// 현재 레벨 인덱스를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetCurrentLevelIndex(int32 Index);
	// 현재 레벨 인덱스를 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "Level")
	int32 GetCurrentLevelIndex() const;

	// 최대 레벨 개수를 가져오는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetMaxLevels() const { return LevelInfos.Num(); };	

	const FLevelInfo* GetCurrentLevelInfo() const
	{
		if (LevelInfos.IsValidIndex(CurrentLevelIndex))
		{
			return &LevelInfos[CurrentLevelIndex];
		}
		return nullptr;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Level")
	void EndLevel(bool bIsClear);
	UFUNCTION(BlueprintCallable, Category = "Level")
	void StartGame();
};
