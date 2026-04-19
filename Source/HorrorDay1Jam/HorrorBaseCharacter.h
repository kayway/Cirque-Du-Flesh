// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "HorrorBaseCharacter.generated.h"

UCLASS()
class HORRORDAY1JAM_API AHorrorBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorBaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	class USoundBase* MissSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Combat")
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MeleeDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<AActor> MeleeTargetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	UBoxComponent* MeleeCollision;
};
