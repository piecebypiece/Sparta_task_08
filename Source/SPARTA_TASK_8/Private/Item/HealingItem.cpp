// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealingItem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(HealingItem)

AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	// 플레이어 캐릭터의 체력을 20만큼 회복시키는 로직 등을 구현 가능
	DestroyItem();
}