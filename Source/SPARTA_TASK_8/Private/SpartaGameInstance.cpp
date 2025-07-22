


#include "SpartaGameInstance.h"
#include <Kismet\GameplayStatics.h>
#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaGameInstance)



USpartaGameInstance::USpartaGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;

	LevelDuration = 30.0f;
	MaxLevels = 0; // 실제 맵 개수에 따라 설정될 예정
	LevelMapNames.Add(TEXT("BasicLevel"));
	LevelMapNames.Add(TEXT("IntermediateLevel"));
	LevelMapNames.Add(TEXT("AdvancedLevel"));
	MaxLevels = LevelMapNames.Num();
}

void USpartaGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}

void USpartaGameInstance::SetCurrentLevelIndex(int32 Index)
{
	CurrentLevelIndex = Index;
}

int32 USpartaGameInstance::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

void USpartaGameInstance::SetMaxLevels(int32 Count)
{
	MaxLevels = Count;
}

int32 USpartaGameInstance::GetMaxLevels() const
{
	return MaxLevels;
}

void USpartaGameInstance::SetLevelMapNames(const TArray<FName>& Names)
{
	LevelMapNames = Names;
}

const TArray<FName>& USpartaGameInstance::GetLevelMapNames() const
{
	return LevelMapNames;
}


void USpartaGameInstance::EndLevel()
{
	// 다음 레벨 인덱스로
	CurrentLevelIndex++;

	// TODO : 클리어 UI 표시
	if (CurrentLevelIndex >= MaxLevels)
	{
		return;
	}

	// 레벨 맵 이름이 있다면 해당 맵 불러오기
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
}