// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatBBComparerDecorator.h"

UFloatBBComparerDecorator::UFloatBBComparerDecorator()
{
    NodeName = TEXT("Compare Float Blackboard Values");
}

bool UFloatBBComparerDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory
) const
{
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard)
    {
        return false;
    }

    float A = Blackboard->GetValueAsFloat(AKey.SelectedKeyName);
    float B = Blackboard->GetValueAsFloat(BKey.SelectedKeyName);

    switch (CompareType)
    {
        case EFloatCompareType::LessThan:
            return A < B;

        case EFloatCompareType::LessOrEqual:
            return A <= B;

        case EFloatCompareType::GreaterThan:
            return A > B;

        case EFloatCompareType::GreaterOrEqual:
            return A >= B;

        case EFloatCompareType::Equal:
            return FMath::Abs(A - B) <= Tolerance;

        case EFloatCompareType::NotEqual:
            return FMath::Abs(A - B) > Tolerance;
    }

    return false;
}

FString UFloatBBComparerDecorator::GetStaticDescription() const
{
    FString Op;

    switch (CompareType)
    {
        case EFloatCompareType::LessThan:        Op = "<"; break;
        case EFloatCompareType::LessOrEqual:     Op = "<="; break;
        case EFloatCompareType::GreaterThan:     Op = ">"; break;
        case EFloatCompareType::GreaterOrEqual:  Op = ">="; break;
        case EFloatCompareType::Equal:           Op = "=="; break;
        case EFloatCompareType::NotEqual:        Op = "!="; break;
    }

    return FString::Printf(
        TEXT("%s %s %s"),
        *AKey.SelectedKeyName.ToString(),
        *Op,
        *BKey.SelectedKeyName.ToString()
    );
}