// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APuzzleBase::APuzzleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleBase::Interact_Implementation()
{
	if (StartSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, StartSound, GetActorLocation());
	}
	GetWorldTimerManager().SetTimer(DelayHandle, this, &APuzzleBase::StartPuzzle, StartDelay, false);
}

bool APuzzleBase::CanInteract_Implementation()
{
	return GameState == Inactive || GameState == Failed;
}

void APuzzleBase::StartPuzzle()
{
	if (GameState == Running || GameState == Victory)
	{
		return;
	}

	if (GameMusic)
	{
		MusicComponent = UGameplayStatics::SpawnSoundAttached(GameMusic, GetRootComponent());
	}

	OnPuzzleStart.Broadcast();
	EndTime = GetWorld()->GetTimeSeconds() + TimeLimit;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APuzzleBase::FailPuzzle, TimeLimit, false);
	GameState = Running;
}

void APuzzleBase::FailPuzzle()
{
	if (GameState != Running)
	{
		return;
	}

	if (FailSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FailSound, GetActorLocation());
	}

	GameState = Failed;
	OnPuzzleFail.Broadcast();
	EndPuzzle();
}

void APuzzleBase::PassPuzzle()
{
	if (GameState != Running)
	{
		return;
	}

	if (FailSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SuccessSound, GetActorLocation());
	}

	GameState = Victory;
	
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(RewardDelayHandle, this, &APuzzleBase::DispenseReward, RewardDelay, false);
	OnPuzzleSuccess.Broadcast();
	EndPuzzle();
}

void APuzzleBase::EndPuzzle()
{
	if (MusicComponent)
	{
		MusicComponent->Stop();
	}

	OnPuzzleEnd.Broadcast();
}

void APuzzleBase::DispenseReward()
{
	if (!RewardItem)
	{
		return;
	}

	RewardItem->SetActorHiddenInGame(false);
	if (RewardDispenseSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RewardDispenseSound, RewardItem->GetActorLocation());
	}
}

float APuzzleBase::GetTimeRemaining()
{
	return FMath::Max(0.f, EndTime - GetWorld()->GetTimeSeconds());
}

