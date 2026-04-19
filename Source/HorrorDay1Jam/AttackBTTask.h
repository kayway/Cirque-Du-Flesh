// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "HorrorBaseCharacter.h"
#include "AttackBTTask.generated.h"


/**
 * 
 */
UCLASS()
class HORRORDAY1JAM_API UAttackBTTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "Blackboard Values")
    FBlackboardKeySelector SelfKey;

public:
    UAttackBTTask();
	
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type Result) override;

private:
    UFUNCTION()
    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

    AHorrorBaseCharacter* TryGetCharacter(UBehaviorTreeComponent& OwnerComp);

    UBehaviorTreeComponent* CachedOwnerComp;
};
