// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackBTTask.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

UAttackBTTask::UAttackBTTask()
{
    NodeName = TEXT("Attack Target");
    bNotifyTick = false;
}

EBTNodeResult::Type UAttackBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AHorrorBaseCharacter* self = TryGetCharacter(OwnerComp);
    if (!self || !self->AttackMontage)
    {
        return EBTNodeResult::Failed;
    }

    UAnimInstance* AnimInstance = self->GetMesh()->GetAnimInstance();
    if (!AnimInstance) return EBTNodeResult::Failed;

    // Bind delegate
    AnimInstance->OnMontageEnded.AddDynamic(this, &UAttackBTTask::OnMontageEnded);

    self->PlayAnimMontage(self->AttackMontage);

    // Tell BT task is "in progress"
    return EBTNodeResult::InProgress;
}

void UAttackBTTask::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (CachedOwnerComp)
    {
        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
    }
}

void UAttackBTTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type Result)
{
    AHorrorBaseCharacter* self = TryGetCharacter(OwnerComp);

    if (self)
    {
        if (UAnimInstance* AnimInstance = self->GetMesh()->GetAnimInstance())
        {
            AnimInstance->OnMontageEnded.RemoveAll(this);
        }
    }
}

AHorrorBaseCharacter* UAttackBTTask::TryGetCharacter(UBehaviorTreeComponent& OwnerComp)
{
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    if (!Blackboard)
    {
        return nullptr;
    }

    return Cast<AHorrorBaseCharacter>(Blackboard->GetValueAsObject(SelfKey.SelectedKeyName));
}