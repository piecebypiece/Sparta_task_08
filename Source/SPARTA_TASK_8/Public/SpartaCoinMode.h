// Fill out your coright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StageWaveInfo.h"
#include "SpartaCoinMode.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API ASpartaCoinMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// 현재 스테이지의 웨이브 정보가 담긴 데이터 애셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TObjectPtr<class UStageWaveInfo> CurrentStageData;

	// 현재 진행 중인 웨이브의 인덱스
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;

	void ProcessWaveFunction(EWaveFunction FuncType);

public:
	ASpartaCoinMode();

	// 게임이 완전히 끝났을 때 (모든 레벨 종료) 실행되는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	// 레벨을 시작할 때, 아이템 스폰 및 타이머 설정
	void StartLevel();
	// 코인을 주웠을 때 호출
	void OnCoinCollected(class ACoinItem* Coin);

	// 웨이브 시작 함수
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartWave();

	// 웨이브 종료 함수
	UFUNCTION(BlueprintCallable, Category = "Wave")
	void EndWave();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};