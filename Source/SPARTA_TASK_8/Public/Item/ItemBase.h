

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "ItemBase.generated.h"

class USphereComponent;

UCLASS()
class SPARTA_TASK_8_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USceneComponent> Scene;
	// 충돌 컴포넌트 (플레이어 진입 범위 감지용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USphereComponent> Collision;
	// 아이템 시각 표현용 스태틱 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	// Inherited via IItemInterface
	virtual void OnItemOverlap(	UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void ActivateItem(AActor* Activator) override;

	virtual FName GetItemType() const override;

	// 아이템을 제거하는 공통 함수 (추가 이펙트나 로직을 넣을 수 있음)
	virtual void DestroyItem();
};
