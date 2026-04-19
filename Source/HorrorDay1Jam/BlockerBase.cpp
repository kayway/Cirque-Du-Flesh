// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockerBase.h"

// Sets default values
ABlockerBase::ABlockerBase()
{
}

// Called when the game starts or when spawned
void ABlockerBase::BeginPlay()
{
	Super::BeginPlay();
	
	for (AKeyItemBase* RequiredItem : RequiredItems)
	{
		if (RequiredItem)
		{
			RequiredItemsData.Add(RequiredItem->ItemData);
		}
	}
}

bool ABlockerBase::CheckSuccess(APlayerCharacter* Player)
{
	int RequiredItemsObtained = 0;
	for (FKeyItem PlayerItem : Player->KeyItems)
	{
		for (FKeyItem RequiredItemData : RequiredItemsData)
		{
			if (PlayerItem.ItemName == RequiredItemData.ItemName)
			{
				RequiredItemsObtained++;
				break;
			}
		}

		if (RequiredItemsObtained >= RequiredItemsData.Num())
		{
			return true;
		}
	}

	return RequiredItemsObtained >= RequiredItemsData.Num();
}

