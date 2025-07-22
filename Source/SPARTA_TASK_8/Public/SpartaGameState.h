// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API ASpartaGameState : public AGameState
{
    GENERATED_BODY()

protected:
    // 전역 점수를 저장하는 변수
    UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Score")
    int32 Score;

    // 현재 레벨에서 스폰된 코인 개수
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Coin")
    int32 SpawnedCoinCount;
    // 플레이어가 수집한 코인 개수
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Coin")
    int32 CollectedCoinCount;

	// 현재 웨이브의 남은 시간
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Wave")
	float RemainingWaveTime;

public:
    ASpartaGameState();

    // 현재 점수를 읽는 함수
    UFUNCTION(BlueprintPure, Category="Score")
    int32 GetScore() const;
    // 점수를 추가해주는 함수
    UFUNCTION(BlueprintCallable, Category="Score")
    void AddScore(int32 Amount);

	// 현재 레벨에서 스폰된 코인 개수를 읽는 함수
	UFUNCTION(BlueprintPure, Category = "Coin")
	int32 GetSpawnedCoinCount() const;
	// 플레이어가 수집한 코인 개수를 읽는 함수
	UFUNCTION(BlueprintPure, Category = "Coin")
	int32 GetCollectedCoinCount() const;

	// 현재 레벨에서 스폰된 코인 개수를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Coin")
	void SetSpawnedCoinCount(int32 Count);
	// 플레이어가 수집한 코인 개수를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Coin")
	void SetCollectedCoinCount(int32 Count);

	// 현재 웨이브의 남은 시간을 읽는 함수
	UFUNCTION(BlueprintPure, Category = "Wave")
	float GetRemainingWaveTime() const;
	// 현재 웨이브의 남은 시간을 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void SetRemainingWaveTime(float Time);
    

protected:
    virtual void BeginPlay() override;
};
