#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HorrorBaseCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = MaxHealth;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (isDead)
	{
		return;
	}

	Health -= Damage;

	if (Damage > 0.0f)
	{
		if (Health <= 0.0f)
		{
			OnDeathDelegate.Broadcast();
			isDead = true;
		}
		if (HitSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, DamagedActor->GetActorLocation());
		}
	}
	else
	{
		if (HitSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HealSound, DamagedActor->GetActorLocation());
		}
	}
}
