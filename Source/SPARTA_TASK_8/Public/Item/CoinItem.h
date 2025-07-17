

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "CoinItem.generated.h"

UCLASS()
class SPARTA_TASK_8_API ACoinItem : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 코인 획득 시 얻을 점수 (자식 클래스에서 상속받아 값만 바꿔줄 예정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
