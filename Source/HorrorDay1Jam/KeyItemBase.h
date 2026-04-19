// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InteractionInterface.h"
#include "UObject/Object.h"
#include "KeyItemBase.generated.h"

USTRUCT(BlueprintType)
struct FKeyItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName = "";

	UPROPERTY()
	UObject* SafeObjectPointer = nullptr;
};

UCLASS()
class HORRORDAY1JAM_API AKeyItemBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USoundBase* PickupSound;

public:

	// Sets default values for this actor's properties
	AKeyItemBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InterractCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKeyItem ItemData;

protected:

	virtual void Interact_Implementation() override;

	virtual bool CanInteract_Implementation() override;

};

UCLASS(BlueprintType)
class HORRORDAY1JAM_API UKeyItemInventoryUIData: public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FKeyItem ItemData;
};