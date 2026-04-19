// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AHorrorBaseCharacter::AHorrorBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeleeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Melee Collision"));
	MeleeCollision->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AHorrorBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	//Box->OnComponentHit.AddDynamic(this, &ADoor::Collide);
}

// Called every frame
void AHorrorBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHorrorBaseCharacter::StartDeath()
{
	DetachFromControllerPendingDestroy();



	Destroy();
}

void AHorrorBaseCharacter::MeleeAttack()
{
	TArray<AActor*> OverlappingActors;
	MeleeCollision->GetOverlappingActors(OverlappingActors);
	bool HitAnything = false;
	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor->IsA(MeleeTargetClass))
		{
			continue;
		}
		HitAnything = true;
		UGameplayStatics::ApplyDamage(Actor, MeleeDamage, nullptr, this, UDamageType::StaticClass());
	}

	if (!HitAnything && MissSound)
	{
		UGameplayStatics::PlaySound2D(this, MissSound);
	}
}