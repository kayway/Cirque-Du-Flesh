// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueLine.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DialogueLine, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedDialogue);

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Line;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class HORRORDAY1JAM_API UDialogueLine : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FLine> Lines;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* VoiceLine;

	UFUNCTION(BlueprintCallable)
	void PlayDialogue(UTextBlock* DialogueTextObject, UAudioComponent* DialogueSpeaker);

	UPROPERTY(BlueprintAssignable)
	FOnFinishedDialogue OnFinishedDialogue;
	
private:

	void PlayLine();

	FTimerHandle LineTimerHandle;
	UTextBlock* TextObject;
	int32 lineIdx = 0;

};
