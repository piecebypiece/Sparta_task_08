// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API AHealingItem : public AItemBase
{
	GENERATED_BODY()
	
public:
	AHealingItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
