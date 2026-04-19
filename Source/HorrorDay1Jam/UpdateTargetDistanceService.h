// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdateTargetDistanceService.generated.h"

/**
 * 
 */
UCLASS()
class HORRORDAY1JAM_API UUpdateTargetDistanceService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Input Keys")
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, Category = "Input Keys")
	FBlackboardKeySelector AttackerKey;

	UPROPERTY(EditAnywhere, Category = "Output Keys")
	FBlackboardKeySelector DistanceKey;

	UPROPERTY(EditAnywhere, Category = "Output Keys")
	FBlackboardKeySelector LOSKey;


public:
	UUpdateTargetDistanceService();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
