// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyItemBase.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCharacter.h"

// Sets default values
AKeyItemBase::AKeyItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InterractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collision"));

}

// Called when the game starts or when spawned
void AKeyItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AKeyItemBase::Interact_Implementation()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!player)
	{
		return;
	}

	player->KeyItems.Add(ItemData);

	Destroy();
}

bool AKeyItemBase::CanInteract_Implementation()
{
	return true;
}

