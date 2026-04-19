// Fill out your copyright notice in the Description page of Project Settings.

#include "HorrorSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

UHorrorSpriteComponent::UHorrorSpriteComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHorrorSpriteComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	}
}


void UHorrorSpriteComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CompRot = GetComponentRotation();
	FRotator LookRotation = (PlayerCameraManager->GetCameraLocation() - GetComponentLocation()).Rotation();

	SetWorldRotation(FRotator(CompRot.Pitch, LookRotation.Yaw + YawOffset, CompRot.Roll));
}