// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FloatBBComparerDecorator.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EFloatCompareType : uint8
{
    LessThan       UMETA(DisplayName = "<"),
    LessOrEqual    UMETA(DisplayName = "<="),
    GreaterThan    UMETA(DisplayName = ">"),
    GreaterOrEqual UMETA(DisplayName = ">="),
    Equal          UMETA(DisplayName = "=="),
    NotEqual       UMETA(DisplayName = "!=")
};
UCLASS()
class HORRORDAY1JAM_API UFloatBBComparerDecorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

    // --- Blackboard keys ---
    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector AKey;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector BKey;

    // --- Comparison type ---
    UPROPERTY(EditAnywhere, Category = "Condition")
    EFloatCompareType CompareType = EFloatCompareType::LessThan;

    // Optional tolerance for equality checks
    UPROPERTY(EditAnywhere, Category = "Condition")
    float Tolerance = 0.01f;

public:
    UFloatBBComparerDecorator();
	
protected:

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

    virtual FString GetStaticDescription() const override;

};
