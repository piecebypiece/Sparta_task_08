


#include "Item/CoinItem.h"
#include "SpartaCoinMode.h"
#include "Kismet/GameplayStatics.h"

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

	ASpartaCoinMode* Mode = Cast<ASpartaCoinMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (Mode)
	{
		Mode->OnCoinCollected(this);
	}

	DestroyItem();
}

// Called every frame
void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


