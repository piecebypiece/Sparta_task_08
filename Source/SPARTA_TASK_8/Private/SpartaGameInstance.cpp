


#include "SpartaGameInstance.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(SpartaGameInstance)



USpartaGameInstance::USpartaGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void USpartaGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}