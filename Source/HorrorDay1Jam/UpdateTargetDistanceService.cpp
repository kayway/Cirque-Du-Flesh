// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateTargetDistanceService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/KismetMathLibrary.h>

UUpdateTargetDistanceService::UUpdateTargetDistanceService()
{
	//Interval = 0.3f;      // how often the service runs
	RandomDeviation = 0.1f;
}

void UUpdateTargetDistanceService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	
	if (!Blackboard)
	{
		return;
	}

	AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName));
	AActor* Self = Cast<AActor>(Blackboard->GetValueAsObject(AttackerKey.SelectedKeyName));

	if (!Target || !Self)
	{
		return;
	}

	

	FVector TargetLocation = Target->GetActorLocation();
	FVector SelfLocation = Self->GetActorLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SelfLocation, TargetLocation);
	
	Self->SetActorRotation(FRotator(0, LookAtRotation.Yaw, 0));

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Self);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		SelfLocation,
		TargetLocation,
		ECC_Visibility,
		Params
	);



	float distance = FVector::Distance(TargetLocation, SelfLocation);
	Blackboard->SetValueAsFloat(DistanceKey.SelectedKeyName, distance);
	Blackboard->SetValueAsBool(LOSKey.SelectedKeyName, !bHit);

}