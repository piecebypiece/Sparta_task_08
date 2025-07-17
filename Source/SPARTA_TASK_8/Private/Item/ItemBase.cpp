#include "Item\ItemBase.h"
#include "Components/SphereComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ItemBase)
// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    // 루트 컴포넌트 생성 및 설정
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    // 충돌 컴포넌트 생성 및 설정
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    // 겹침만 감지하는 프로파일 설정
    Collision.Get()->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    // 루트 컴포넌트로 설정
    Collision->SetupAttachment(Scene);

    // 스태틱 메시 컴포넌트 생성 및 설정
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision.Get());
    // 메시가 불필요하게 충돌을 막지 않도록 하기 위해, 별도로 NoCollision 등으로 설정할 수 있음.

    // Overlap 이벤트 바인딩
    Collision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemEndOverlap);

}

void AItemBase::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor and OtherActor->ActorHasTag("Player") == false)
    {
        return;
    }
    
    ActivateItem(OtherActor);
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!")));
}

void AItemBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AItemBase::ActivateItem(AActor* Activator)
{

}

FName AItemBase::GetItemType() const
{
	return ItemType;
}

void AItemBase::DestroyItem()
{
	Destroy();
}



