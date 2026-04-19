// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueLine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY(DialogueLine);


void UDialogueLine::PlayDialogue(UTextBlock* DialogueTextObject, UAudioComponent* DialogueSpeaker)
{
	UE_LOG(DialogueLine, Log, TEXT("Playing dialogue line %s..."), *GetName());
	if (!DialogueTextObject)
	{
		UE_LOG(DialogueLine, Error, TEXT("No text object for subtitles found!"));
		return;
	}

	if (!VoiceLine)
	{
		UE_LOG(DialogueLine, Error, TEXT("No valid voice line found!"));
		return;
	}

	if (!DialogueSpeaker)
	{
		UE_LOG(DialogueLine, Error, TEXT("No valid speaker found!"));
		return;
	}

	TextObject = DialogueTextObject;

	DialogueSpeaker->SetSound(VoiceLine);
	DialogueSpeaker->Play();
	PlayLine();
}

void UDialogueLine::PlayLine()
{
	if(lineIdx >= Lines.Num())
	{
		UE_LOG(DialogueLine, Log, TEXT("Finished playing dialogue line %s."), *GetName());
		OnFinishedDialogue.Broadcast();
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		LineTimerHandle,
		this,
		&UDialogueLine::PlayLine,
		Lines[lineIdx].Duration,
		false
	);

	TextObject->SetText(Lines[lineIdx].Line);

	lineIdx++;
}