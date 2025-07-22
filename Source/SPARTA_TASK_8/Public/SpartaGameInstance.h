

#pragma once

#include "CoreMinimal.h"
#include "SpartaGameInstance.generated.h"

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

	// 각 레벨이 유지되는 시간 (초 단위)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	// 실제 레벨 맵 이름 배열. 여기 있는 인덱스를 차례대로 연동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);	

	// 현재 레벨 인덱스를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetCurrentLevelIndex(int32 Index);
	// 현재 레벨 인덱스를 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "Level")
	int32 GetCurrentLevelIndex() const;

	// 최대 레벨 개수를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetMaxLevels(int32 Count);
	// 최대 레벨 개수를 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "Level")
	int32 GetMaxLevels() const;

	// 레벨 맵 이름을 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void SetLevelMapNames(const TArray<FName>& Names);
	// 레벨 맵 이름을 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "Level")
	const TArray<FName>& GetLevelMapNames() const;	
	

	void EndLevel();
};
