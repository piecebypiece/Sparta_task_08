// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BigCoinItem.h"


ABigCoinItem::ABigCoinItem()
{
	PointValue = 50;
	ItemType = TEXT("BigCoin");
}

void ABigCoinItem::ActivateItem(AActor* activator)
{
	DestroyItem();
}
