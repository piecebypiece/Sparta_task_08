// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CoinItem.h"
#include "BigCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API ABigCoinItem : public ACoinItem
{
	GENERATED_BODY()
	
public :
	ABigCoinItem();
	
	virtual void ActivateItem(AActor* activator) override;
};
