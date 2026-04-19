// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "HorrorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORDAY1JAM_API AHorrorPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UUserWidget* PlayerHUD;
	
public:
	//APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> PauseMenuWidgetType;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> InventoryMenuWidgetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* PlayerMappingContext;

	void CreateMappingContext();

protected:
	virtual void BeginPlay() override;


	UPROPERTY(Transient)
	UUserWidget* PauseMenuWidget;

	virtual void SetupInputComponent() override;

	void PauseGame(const FInputActionValue& Value);
	void OpenInventory(const FInputActionValue& Value);



private:

	UPROPERTY(Transient)
	UUserWidget* InventoryMenuWidget;

	void ToggleMenu(UUserWidget*& MenuWidget, TSubclassOf<UUserWidget> WidgetClass);


};