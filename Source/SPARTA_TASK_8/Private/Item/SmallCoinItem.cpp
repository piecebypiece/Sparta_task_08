// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SmallCoinItem.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(SmallCoinItem)
ASmallCoinItem::ASmallCoinItem()
{
	PointValue = 10;
	ItemType = TEXT("SmallCoin");
}

void ASmallCoinItem::ActivateItem(AActor* activator)
{
	DestroyItem();
}
