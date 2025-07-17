

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class SPARTA_TASK_8_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	ASpartaPlayerController();
public :
	// 에디터에서 세팅할 IMC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	// IA_Move를 지정할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	// IA_Jump를 지정할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> JumpAction;
	// IA_Look를 지정할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	TObjectPtr<UInputAction> LookAction;
	// IA_Sprint를 지정할 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;
	
protected:
	virtual void BeginPlay() override;
};
