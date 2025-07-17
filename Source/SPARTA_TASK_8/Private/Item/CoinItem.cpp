


#include "Item/CoinItem.h"
#include "SpartaGameState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CoinItem)

// Sets default values
ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if ((Activator || Activator->ActorHasTag("Player")) == false)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
		{
			GameState->AddScore(PointValue);
			GameState->OnCoinCollected();
		}
	}
	DestroyItem();
}

// Called every frame
void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


