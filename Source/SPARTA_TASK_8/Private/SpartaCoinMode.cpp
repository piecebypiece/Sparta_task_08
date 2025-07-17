// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaCoinMode.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h" // PlayerController 클래스를 사용

ASpartaCoinMode::ASpartaCoinMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}
