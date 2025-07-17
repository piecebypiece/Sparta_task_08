// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCoinMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h" // PlayerController 클래스를 사용
#include "SpartaGameState.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaCoinMode)

ASpartaCoinMode::ASpartaCoinMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}
