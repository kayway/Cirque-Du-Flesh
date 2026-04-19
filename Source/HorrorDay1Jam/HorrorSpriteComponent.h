// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "HorrorSpriteComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HORRORDAY1JAM_API UHorrorSpriteComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:
	UHorrorSpriteComponent();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float YawOffset = 90.f;
	APlayerCameraManager* PlayerCameraManager;

};
