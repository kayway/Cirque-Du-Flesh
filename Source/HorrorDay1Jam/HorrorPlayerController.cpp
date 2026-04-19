// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AHorrorPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UUserWidget>(this, PlayerHUDClass);

		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}

	CreateMappingContext();
}

void AHorrorPlayerController::CreateMappingContext()
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void AHorrorPlayerController::SetupInputComponent()
{
	if (!InputComponent)
	{
		return;
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (PauseAction)
		{
			EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AHorrorPlayerController::PauseGame);
		}
		if (InventoryAction)
		{
			EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &AHorrorPlayerController::OpenInventory);
		}
	}

}

void AHorrorPlayerController::PauseGame(const FInputActionValue& Value)
{
	ToggleMenu(PauseMenuWidget, PauseMenuWidgetType);
}

void AHorrorPlayerController::OpenInventory(const FInputActionValue& Value)
{
	ToggleMenu(InventoryMenuWidget, InventoryMenuWidgetType);
}

void AHorrorPlayerController::ToggleMenu(UUserWidget*& MenuWidget, TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return;
	}

	if (!MenuWidget || !MenuWidget->IsInViewport())
	{
		if (!MenuWidget)
		{
			MenuWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		}

		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			SetInputMode(FInputModeGameAndUI());
			SetShowMouseCursor(true);
			SetPause(true);
		}
	}
	else
	{
		if (MenuWidget)
		{
			MenuWidget->RemoveFromParent();
			SetInputMode(FInputModeGameOnly());
			SetShowMouseCursor(false);
			SetPause(false);
		}
	}
}