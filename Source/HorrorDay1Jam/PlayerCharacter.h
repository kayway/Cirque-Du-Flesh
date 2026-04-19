// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HorrorBaseCharacter.h"
#include "InputActionValue.h"
#include "KeyItemBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class HORRORDAY1JAM_API APlayerCharacter : public AHorrorBaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MeleeAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* HealAction;
	

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UObject* InteractionTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	float InteractionRadius = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	int HealItems = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	int HealItemEffectAmount = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	int Ammo = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	bool InConversation = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	int GunDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundBase* EmptyVialSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundBase* ShootSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundBase* NoAmmoSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio, meta = (AllowPrivateAccess = "true"))
	class USoundBase* WalkSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool DebugInteraction = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (AllowPrivateAccess = "true"))
	bool DebugShooting = false;


public:
	APlayerCharacter();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	TArray<FKeyItem> KeyItems;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> PauseMenuWidgetType;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> InventoryMenuWidgetType;


	virtual void Tick(float DeltaTime) override;

protected:


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void InteractWithTarget(const FInputActionValue& Value);
	void Melee(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void Heal(const FInputActionValue& Value);


private:

	class UAudioComponent* WalkAudioComp;

	//bool IsPaused;

	FVector GetLOSStartPosition() const;
	FVector GetLOSEndPosition(float distance) const;

};
