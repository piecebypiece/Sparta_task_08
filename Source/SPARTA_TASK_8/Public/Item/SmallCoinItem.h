// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/CoinItem.h"
#include "SmallCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API ASmallCoinItem : public ACoinItem
{
	GENERATED_BODY()
public :
	ASmallCoinItem();

	virtual void ActivateItem(AActor* activator) override;
};
