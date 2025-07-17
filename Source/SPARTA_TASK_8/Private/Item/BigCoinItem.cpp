// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BigCoinItem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BigCoinItem)

ABigCoinItem::ABigCoinItem()
{
	PointValue = 50;
	ItemType = TEXT("BigCoin");
}

void ABigCoinItem::ActivateItem(AActor* activator)
{
	DestroyItem();
}
