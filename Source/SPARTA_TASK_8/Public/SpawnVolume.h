// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item\ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTA_TASK_8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:
    ASpawnVolume();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    AActor* SpawnRandomItem();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    int32 GetSpawnNum() const { return SpawnNum; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning")
    TObjectPtr<USceneComponent> Scene;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TObjectPtr<UBoxComponent> SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    TObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    int32 SpawnNum;

    FVector GetRandomPointInVolume() const;
    FItemSpawnRow* GetRandomItem() const;
    AActor* SpawnItem(TSubclassOf<AActor> ItemClass);

};