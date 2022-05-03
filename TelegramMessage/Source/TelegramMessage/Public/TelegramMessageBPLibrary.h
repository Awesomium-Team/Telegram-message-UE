// Copyright 2022 Awesomium team LLC. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Logging/LogMacros.h"
#include "Modules/ModuleManager.h"
#include "TelegramMessageBPLibrary.generated.h"

// OLD Method https://gist.github.com/MrKuBu/ced721375072d2fad9d5390cbc8f47ff

UENUM(BlueprintType)
enum class EStatus : uint8
{
	typing				UMETA(DisplayName = "Typing"),
	upload_photo			UMETA(DisplayName = "Upload Photo"),
	record_video			UMETA(DisplayName = "Recording video"),
	upload_video			UMETA(DisplayName = "Upload video"),
	record_audio			UMETA(DisplayName = "Record audio"),
	upload_audio			UMETA(DisplayName = "Upload audio"),
	upload_document			UMETA(DisplayName = "Upload document"),
	find_location			UMETA(DisplayName = "Find location")
};


UCLASS()
class UTelegramMessageBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:

	// [TODO] [WIP virtual void or void]
	// HTTP Core
	FHttpModule& http = FHttpModule::Get();
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> Request = http.CreateRequest();

	FString Verb = TEXT("GET");

	// Telegram API
	FString TGBot			= TEXT("https://api.telegram.org/bot");

	// Symbols / Ñèìâîëû
	FString SQuestion		= TEXT("?");
	FString SAmpersand		= TEXT("&");
	FString SEquals			= TEXT("=");

	// Sended parametr / Ïàðàìåòðû äëÿ îòïðàâêè
	//Message|Ñîîáùåíèÿ
	FString PText			= TEXT("&text=");
	//Contact
	FString PNumber			= TEXT("&phone_number=");
	FString PFName			= TEXT("&first_name=");
	//Location + Venue|Ãåîëîêàöèÿ
	FString PX			= TEXT("&latitude=");
	FString PY			= TEXT("&longitude=");
	FString PStreet			= TEXT("&title=");
	FString PAddress		= TEXT("&address=");
	//Poll|Ãîëîñîâàíèå
	FString PQuestions		= TEXT("&question=");
	FString POptions		= TEXT("&options=");
	//Action|Ñòàòóñ áîòà/äåéñòâèå áîòà
	FString PAction			= TEXT("&añtion=");


	// Methods / Ðåæèìû ðàáîòû
	FString MChatID			= TEXT("chat_id=");

	FString MSendMessage		= TEXT("sendMessage?");
	FString MSendContact		= TEXT("sendContact?");
	FString MSendLocation		= TEXT("sendLocation?");
	FString MSendVenue		= TEXT("sendVenue?");
	FString MSendDice		= TEXT("sendDice?");
	FString MSendPhoto		= TEXT("sendPhoto?");
	FString MSendAudio		= TEXT("sendAudio?");
	FString MSendVideo		= TEXT("sendVideo?");
	FString MSendVoice		= TEXT("sendVoice?");
	FString MSendDoc		= TEXT("sendDocument?");
	FString MSendSticer		= TEXT("sendSticker?");
	FString MSendAction		= TEXT("sendChatAction?");
	FString MSendPoll		= TEXT("sendPoll?");

	// Callback / Îòâåò îò ñåðâåðà
	virtual void OnRequestFinish(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

public:

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Messages"))
		//virtual void SendTelegramDice(
		static void SendTelegramMessage(
			const FString& Token,
			const FString& ChatID,
			const FString& Message
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Contact"))
		static void SendTelegramContact(
			const FString& Token,
			const FString& ChatID,
			const FString& NameContact,
			const FString& Number
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Location"))
		static void SendTelegramLocation(
			const FString& Token,
			const FString& ChatID,
			const FString& Latitude,
			const FString& Longitude
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Location"))
		static void SendTelegramVenue(
			const FString& Token,
			const FString& ChatID,
			const FString& Latitude,
			const FString& Longitude,
			const FString& Title,
			const FString& Address
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Dice"))
		static void SendTelegramDice(
			const FString& Token,
			const FString& ChatID
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Status, action"))
		static void SendTelegramAction(
			const FString& Token,
			const FString& ChatID,
			const FString& Action
			//const TEnumAsByte<EStatus>& Action
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Photo, Media"))
		static void SendTelegramPhoto(
			const FString& Token,
			const FString& ChatID,
			const FString& Photo
		);

	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Audio, Media"))
		static void SendTelegramAudio(
			const FString& Token,
			const FString& ChatID,
			const FString& Audio
		); 
	
	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Video, Media"))
		static void SendTelegramVideo(
			const FString& Token,
			const FString& ChatID,
			const FString& Video
		); 
	
	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Voice, Media"))
		static void SendTelegramVoice(
			const FString& Token,
			const FString& ChatID,
			const FString& Audio
		); 
	
	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Document, File, Media"))
		static void SendTelegramDocument(
			const FString& Token,
			const FString& ChatID,
			const FString& Document
		); 
	
	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Document, Media"))
		static void SendTelegramSticker(
			const FString& Token,
			const FString& ChatID,
			const FString& Sticker
		);


	UFUNCTION(BlueprintCallable, Category = "Telegram", meta = (AutoCreateRefTerm = "Poll"))
		virtual void SendTelegramPoll(
			const FString& Token,
			const FString& ChatID,
			const FString& Question,
			const TArray<FString>& Options
		);

};
