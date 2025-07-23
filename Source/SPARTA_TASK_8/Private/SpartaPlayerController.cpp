#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h" 

#include "SpartaGameInstance.h"
#include "SpartaGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include <SpartaCoinMode.h>
#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaPlayerController)

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
    HUDWidgetClass(nullptr),
    HUDWidgetInstance(nullptr),
    MainMenuWidgetClass(nullptr),
    MainMenuWidgetInstance(nullptr)
{
}


void ASpartaPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 현재 PlayerController에 연결된 Local Player 객체를 가져옴    
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        // Local Player에서 EnhancedInputLocalPlayerSubsystem을 획득
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                // Subsystem을 통해 우리가 할당한 IMC를 활성화
                // 우선순위(Priority)는 0이 가장 높은 우선순위
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }

    FString CurrentMapName = GetWorld()->GetMapName();
    if (CurrentMapName.Contains("MenuLevel"))
    {
        ShowMainMenu(false);
    }

	// 30초 후에 OnLevelTimeUp()가 호출되도록 타이머 설정
	GetWorldTimerManager().SetTimer(
			HUDUpdateTimerHandle,
			this,
			&ASpartaPlayerController::UpdateHUD,
			0.1f,
			true
		);
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
    return HUDWidgetInstance;
}

// 메뉴 UI 표시
void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	// 메뉴 UI 생성
	if (MainMenuWidgetClass)
	{		
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
		
		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (ASpartaGameState* GState = Cast<ASpartaGameState>(GetWorld()->GetGameState()))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Score: %d"), GState->GetScore())
					));
				}
			}
		}
	}
}

// 게임 HUD 표시
void ASpartaPlayerController::ShowGameHUD()
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
			UpdateHUD();
		}
	}
}

void ASpartaPlayerController::UpdateHUD()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return;
	}
	ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController);
	UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget();
	if (!IsValid(HUDWidget))
	{
		return;
	}
	
	auto* SpartaGameInst = GetGameInstance<USpartaGameInstance>();
	ASpartaGameState* GState = Cast<ASpartaGameState>(GetWorld()->GetGameState());
	ASpartaCoinMode* GMode = Cast<ASpartaCoinMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
	{
		if (GState)
		{
			float RemainingTime = GState->GetRemainingWaveTime();
			TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
		}
	}

	if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
	{
		if (GState)
		{
			ScoreText->SetText(FText::FromString(
				FString::Printf(TEXT("Score: %d"), GState->GetScore())
			));
		}
	}
	if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
	{
		LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), SpartaGameInst->GetCurrentLevelIndex() + 1)));
	}
	if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
	{
		WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d"), GMode->GetCurrentWaveIndex() + 1)));
	}
}