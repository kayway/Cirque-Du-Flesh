// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "InteractionInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"

APlayerCharacter::APlayerCharacter()
{
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());

	FirstPersonCamera->bUsePawnControlRotation = true;

	WalkAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("WalkingAudioComp"));
	WalkAudioComp->SetSound(WalkSound);
	WalkAudioComp->bAutoActivate = false;
	WalkAudioComp->bAllowSpatialization = false;
	WalkAudioComp->bOverrideAttenuation = true;
	WalkAudioComp->AttenuationOverrides.bAttenuate = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (InConversation)
	{
		return;
	}

	FVector Start = GetLOSStartPosition();
	FVector End = GetLOSEndPosition(InteractionRadius);

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	float Radius = 50.f;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	TArray<FHitResult> Hits;

	bool bHit = World->SweepMultiByChannel(
		Hits,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		Sphere,
		Params
	);

	InteractionTarget = nullptr;

	FVector ImpactPoint = FVector::Zero();
	if (bHit)
	{
		for (FHitResult Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor->Implements<UInteractionInterface>())
			{
				if (IInteractionInterface::Execute_CanInteract(HitActor))
				{
					ImpactPoint = Hit.ImpactPoint;
					InteractionTarget = HitActor;
					break;
				}
			}
			else
			{
				HitActor->GetComponentsByInterface(UInteractionInterface::StaticClass());
				for (UActorComponent* Component : HitActor->GetComponentsByInterface(UInteractionInterface::StaticClass()))
				{
					if (IInteractionInterface::Execute_CanInteract(Component))
					{
						ImpactPoint = Hit.ImpactPoint;
						InteractionTarget = Component;
						break;
					}
				}

				if (InteractionTarget)
				{
					break;
				}
			}
		}
	}

	if (DebugInteraction)
	{
		// Debug draw
		FColor Color = InteractionTarget ? FColor::Red : FColor::Green;

		DrawDebugLine(World, Start, End, Color, false, 1.f, 0, 1.f);
		DrawDebugSphere(World, InteractionTarget ? ImpactPoint : End, Radius, 16, Color, false);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::MoveCompleted);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::InteractWithTarget);
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Melee);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);
		EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Heal);
	}

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !InConversation)
	{
		WalkAudioComp->Play();
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerCharacter::MoveCompleted(const FInputActionValue& Value)
{
	WalkAudioComp->Stop();
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr && !InConversation)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::InteractWithTarget(const FInputActionValue& Value)
{
	if(InteractionTarget)
	{
		IInteractionInterface::Execute_Interact(InteractionTarget);
	}
}

void APlayerCharacter::Melee(const FInputActionValue& Value)
{
	//MeleeAttack();
}

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	if (Ammo <= 0)
	{
		UGameplayStatics::PlaySound2D(this, NoAmmoSound);
		return;
	}

	UGameplayStatics::PlaySound2D(this, ShootSound);

	Ammo--;
	FVector Start = GetLOSStartPosition();
	FVector End = GetLOSEndPosition(10000.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if (DebugShooting)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 10.f, 0, 1.f);
	}

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *Hit.GetActor()->GetName());
		UGameplayStatics::ApplyDamage(Hit.GetActor(), GunDamage, this->GetController(), this, UDamageType::StaticClass());
	}
}

void APlayerCharacter::Heal(const FInputActionValue& Value)
{
	if (HealItems <= 0)
	{
		UGameplayStatics::PlaySound2D(this, EmptyVialSound);
		return;
	}

	HealItems--;
	UGameplayStatics::ApplyDamage(this, -HealItemEffectAmount, this->GetController(), this, UDamageType::StaticClass());
}

FVector APlayerCharacter::GetLOSStartPosition() const
{
	return FirstPersonCamera->GetComponentLocation();
}

FVector APlayerCharacter::GetLOSEndPosition(float distance) const
{
	return GetLOSStartPosition() + (FirstPersonCamera->GetForwardVector() * distance);
}

