


#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include <Kismet\GameplayStatics.h>
#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaGameInstance)



USpartaGameInstance::USpartaGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = -1;

	//LevelDuration = 30.0f;
	//MaxLevels = 0; // 실제 맵 개수에 따라 설정될 예정
	//LevelMapNames.Add(TEXT("BasicLevel"));
	//LevelMapNames.Add(TEXT("IntermediateLevel"));
	//LevelMapNames.Add(TEXT("AdvancedLevel"));
	//MaxLevels = LevelMapNames.Num();
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


void USpartaGameInstance::EndLevel(bool bIsClear)
{
	if (bIsClear == false)
	{
		auto World = GetWorld();

		auto PlayerController = World->GetFirstPlayerController();

		auto SpartaController = Cast<ASpartaPlayerController>(PlayerController);
		SpartaController->ShowMainMenu(true);

		return;
	}


	// 다음 레벨 인덱스로
	CurrentLevelIndex++;

	// TODO : 클리어 UI 표시
	if (CurrentLevelIndex >= GetMaxLevels())
	{
		return;
	}

	// 레벨 맵 이름이 있다면 해당 맵 불러오기
	if (LevelInfos.IsValidIndex(CurrentLevelIndex))
	{
		FString AssetPath = LevelInfos[CurrentLevelIndex].levelAsset.ToSoftObjectPath().ToString();
		FString ShortName = FPackageName::GetShortName(AssetPath);
		UGameplayStatics::OpenLevel(GetWorld(), FName(*ShortName));
	}
}

// 게임 시작 - BasicLevel 오픈, GameInstance 데이터 리셋
void USpartaGameInstance::StartGame()
{
	CurrentLevelIndex = 0;
	TotalScore = 0;
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetPause(false);  // 일시정지
	}
}
