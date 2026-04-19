// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyItemBase.h"
#include "PlayerCharacter.h"
#include "BlockerBase.generated.h"

UCLASS()
class HORRORDAY1JAM_API ABlockerBase : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockerBase();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Blocker")
	TArray<TObjectPtr<AKeyItemBase>> RequiredItems;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool CheckSuccess(APlayerCharacter* Player);

private:
	TArray<FKeyItem> RequiredItemsData;

};
