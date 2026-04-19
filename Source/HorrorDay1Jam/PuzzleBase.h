// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "KeyItemBase.h"
#include "PuzzleBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleFail);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleEnd);
UCLASS()
class HORRORDAY1JAM_API APuzzleBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float TimeLimit = 10.0f;

	UPROPERTY(EditAnywhere)
	float StartDelay = 1.0f;

	UPROPERTY(EditAnywhere)
	float RewardDelay = 2.0f;

	UPROPERTY(EditAnywhere, Category="Audio")
	class USoundBase* GameMusic;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* StartSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* FailSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	class USoundBase* RewardDispenseSound;

	UPROPERTY(Transient)
	TObjectPtr<UAudioComponent> MusicComponent;

	enum PuzzleState
	{
		Inactive,
		Running,
		Victory,
		Failed
	};

	PuzzleState GameState = Inactive;

	float EndTime = 1.0f;

	FTimerHandle TimerHandle;
	FTimerHandle DelayHandle;
	FTimerHandle RewardDelayHandle;

	void StartPuzzle();
	void EndPuzzle();
	void DispenseReward();

public:	
	// Sets default values for this actor's properties
	APuzzleBase();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TObjectPtr<AKeyItemBase> RewardItem;

	UFUNCTION(BlueprintCallable)
	void FailPuzzle();

	UFUNCTION(BlueprintCallable)
	void PassPuzzle();

	UFUNCTION(BlueprintCallable)
	float GetTimeRemaining();

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleStart OnPuzzleStart;

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleFail OnPuzzleFail;

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleSuccess OnPuzzleSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleEnd OnPuzzleEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Interact_Implementation() override;
	bool CanInteract_Implementation() override;

};
