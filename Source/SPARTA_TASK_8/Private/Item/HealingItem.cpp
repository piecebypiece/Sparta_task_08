// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealingItem.h"
#include "SpartaCharacter.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(HealingItem)

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	

	if ((Activator || Activator->ActorHasTag("Player")) == false)
	{
		return;
	}

	ASpartaCharacter* Character = Cast<ASpartaCharacter>(Activator);
	Character->AddHealth(HealAmount);
	DestroyItem();
}