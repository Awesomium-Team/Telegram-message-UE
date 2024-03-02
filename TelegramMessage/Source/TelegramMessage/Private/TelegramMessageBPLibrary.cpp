// Copyright 2024 Awesomium team LLC. All Rights Reserved.

#include "TelegramMessageBPLibrary.h"
#include "Misc/Paths.h"
#include "Containers/UnrealString.h"
#include "HttpModule.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonWriter.h"
#include "Misc/FeedbackContextMarkup.h" // For FMarkup::URLEncode
#include "Serialization/JsonSerializer.h"

//application/x-www-form-urlencoded
//application/json (не подходит для загрузки файлов)
//multipart/form-data (для загрузки файлов)

// OLD Method https://gist.github.com/MrKuBu/a860da03c76fe162a44641331ffae1bd

//sendPhoto   	 -- https://tlgrm.ru/docs/bots/api#sendphoto 	+
//sendAudio   	 -- https://tlgrm.ru/docs/bots/api#sendaudio 	+
//sendDocument   -- https://tlgrm.ru/docs/bots/api#senddocument	+
//sendSticker    -- https://tlgrm.ru/docs/bots/api#sendsticker	+
//sendVideo   	 -- https://tlgrm.ru/docs/bots/api#sendvideo	+
//sendVoice   	 -- https://tlgrm.ru/docs/bots/api#sendvoice	+
//sendLocation   -- https://tlgrm.ru/docs/bots/api#sendlocation	+
//sendVenue   	 -- https://tlgrm.ru/docs/bots/api#sendvenue	+
//sendContact    -- https://tlgrm.ru/docs/bots/api#sendcontact 	+
//sendMessage    -- https://tlgrm.ru/docs/bots/api#sendmessage 	+
//sendDice	 	 -- https://core.telegram.org/bots/api#senddice +
//sendPoll	 	 -- https://core.telegram.org/bots/api#sendpoll +
//sendchAtaction --https://tlgrm.ru/docs/bots/api#sendchataction+

// Callback (Debug info)
void UTelegramMessageBPLibrary::OnRequestFinish(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded)
	{
		// GOOD Http
		FString JSONString = HttpResponse->GetContentAsString();
		UE_LOG(LogTemp, Log, TEXT("HTTP Send and getted: %s"), *JSONString);
	}
	else
	{
		// ERROR Http
		UE_LOG(LogTemp, Error, TEXT("HTTP ERROR: Not sended (Couldn't connect to server)"));
	}
}

// Message
void UTelegramMessageBPLibrary::SendTelegramMessage(
	const FString& Token,
	const FString& ChatID,
	const FString& Message
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish); [WIP virtual void or void]
	Request->SetVerb("GET");
	//Request->SetVerb(Verb); [WIP virtual void or void]
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendMessage?chat_id=") 
		+ ChatID 
		+ TEXT("&text=") 
		+ FGenericPlatformHttp::UrlEncode(Message)
	);
	//Request->SetURL(TGBot + Token / MSendMessage + MChatID + ChatID + PText + Message); [WIP virtual void or void]
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

	//UE_LOG(LogTemp, Log, TEXT("Debug: %s"), *FString(TGBot + Token / MSendMessage + MChatID + ChatID + PText + Message)); // DEBUG
};

// Contact
void UTelegramMessageBPLibrary::SendTelegramContact(
	const FString& Token,
	const FString& ChatID,
	const FString& NameContact,
	const FString& Number
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendContact?chat_id=") 
		+ ChatID 
		+ TEXT("&phone_number=") 
		+ Number 
		+ TEXT("&first_name=") 
		+ FGenericPlatformHttp::UrlEncode(NameContact)
	);
	//Request->SetURL(TGBot + Token / MSendContact + MChatID + ChatID + PNumber + Number + PFName + NameContact);
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

// Location
void UTelegramMessageBPLibrary::SendTelegramLocation(
	const FString& Token,
	const FString& ChatID,
	const FString& Latitude,
	const FString& Longitude
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendLocation?chat_id=") 
		+ ChatID 
		+ TEXT("&latitude=") 
		+ Latitude 
		+ TEXT("&longitude=") 
		+ Longitude
	);
	//Request->SetURL(TGBot + Token / MSendLocation + MChatID + ChatID + PX + Latitude + PY + Longitude);
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

// Venue
void UTelegramMessageBPLibrary::SendTelegramVenue(
	const FString& Token,
	const FString& ChatID,
	const FString& Latitude,
	const FString& Longitude,
	const FString& Title,
	const FString& Address
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendVenue?chat_id=") 
		+ ChatID 
		+ TEXT("&latitude=") 
		+ Latitude 
		+ TEXT("&longitude=") 
		+ Longitude 
		+ TEXT("&title=") 
		+ FGenericPlatformHttp::UrlEncode(Title) 
		+ TEXT("&address=")
		+ FGenericPlatformHttp::UrlEncode(Address) 
	);
	//Request->SetURL(TGBot + Token / MSendVenue + MChatID + ChatID + PX + Latitude + PY + Longitude + PStreet + Title + PAddress + Address);
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

// Poll
void UTelegramMessageBPLibrary::SendTelegramPoll(
    const FString& Token,
    const FString& ChatID,
    const FString& Question,
    const TArray<FString>& Options
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

    // Array to Json
    FString OptionsJson = TEXT("[");
    for (int32 i = 0; i < Options.Num(); i++)
    {
        OptionsJson += TEXT("\"") + Options[i].Replace(TEXT("\""), TEXT("\\\"")) + TEXT("\"");
        if (i < Options.Num() - 1)
        {
            OptionsJson += TEXT(",");
        }
    }
    OptionsJson += TEXT("]");

    Request->SetVerb("POST");
    Request->SetURL(TEXT("https://api.telegram.org/bot") + Token + TEXT("/sendPoll"));

    FString RequestContent = TEXT("chat_id=") 
							+ ChatID 
							+ TEXT("&question=") + FGenericPlatformHttp::UrlEncode(Question) 
							+ TEXT("&options=") + FGenericPlatformHttp::UrlEncode(OptionsJson);

    Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
    Request->SetContentAsString(RequestContent);
    Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

}

// Dice
void UTelegramMessageBPLibrary::SendTelegramDice(
	const FString& Token,
	const FString& ChatID
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendDice?chat_id=") 
		+ FGenericPlatformHttp::UrlEncode(ChatID)
	);
	//Request->SetURL(TGBot + Token / MSendDice + MChatID + ChatID);
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

// Action status / (typing) for text messages, (upload_photo) for photos, (record_video) or (upload_video) for videos, (record_audio) or (upload_audio) for audio files, (upload_document) for general files, (find_location) for location data
void UTelegramMessageBPLibrary::SendTelegramAction(
	const FString& Token,
	const FString& ChatID,
	const EStatus Action
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	// EStatus - String
     	//const UEnum* EnumStatusPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EStatus"), true); // 5.0 and lower
	const UEnum* EnumStatusPtr = FindFirstObjectSafe<UEnum>(TEXT("EStatus")); // 5.1 and higher

	//Request->SetTimeout(15);
	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(
		TEXT("https://api.telegram.org/bot") 
		+ Token / TEXT("sendChatAction?chat_id=") 
		+ ChatID 
		+ TEXT("&action=") 
		+ ActionStr
	);
	//Request->SetURL(TGBot + Token / MSendAction + MChatID + ChatID + PAction + Action);
	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

// HELPER FUNCTION (File to bytes)
TArray<uint8> UTelegramMessageBPLibrary::PrepareRequestContent(
	const FString& Boundary, 
	const TArray<uint8>& FileContent, 
	const FString& FileName,
	const FString& FieldName
)
{
	TArray<uint8> RequestContent;

	// Formatting (Start)
	FString BeginBoundary = "\r\n--" + Boundary + "\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

	// Start header
	FString FileHeader = "Content-Disposition: form-data; name=\"" + FieldName + "\"; filename=\"" + FileName + "\"\r\n";
	FileHeader.Append("Content-Type: \r\n\r\n");
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

	// File
	RequestContent.Append(FileContent);

	// Formatting (End)
	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	return RequestContent;
}

// Upload files (50mb max)
void UTelegramMessageBPLibrary::SendTelegramFiles(
	const FString& Token,
	const FString& ChatID,
	const ESendFile SendFile,
	const FString& FilePath
)
{

	// ESendFile - String
    	//const UEnum* EnumSendPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESendFile"), true); // 5.0 and lower
	const UEnum* EnumSendPtr = FindFirstObjectSafe<UEnum>(TEXT("ESendFile")); // 5.1 and higher
	FString ActionStrWithoutPrefix = EnumSendStr;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / EnumSendStr + TEXT("?chat_id=") + ChatID);

	// Formatting
	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	// Delete prefix "send" and lowercase
    ActionStrWithoutPrefix.RemoveFromStart(TEXT("send"));
    if (ActionStrWithoutPrefix.Len() > 0)
    {
        ActionStrWithoutPrefix[0] = FChar::ToLower(ActionStrWithoutPrefix[0]);
    }

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *FilePath))
	{
		TArray<uint8> RequestContent = PrepareRequestContent(Boundary, FileContent, FPaths::GetCleanFilename(FilePath), ActionStrWithoutPrefix);
		Request->SetContent(RequestContent);
	}

	Request->ProcessRequest();

	// Callback (Debug info)
	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			// Callback request
			UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message: %s"), *Response->GetContentAsString());
		}
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message: Not sended (Couldn't connect to server)"));
		}
	});

};

void UTelegramMessageBPLibrary::GetTelegramUpdates(
    const FString& Token,
    const FString& Offset,
    const FString& Limit,
    const FString& Timeout
)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetVerb("GET");


    FString Url = FString::Printf(TEXT("https://api.telegram.org/bot%s/getUpdates?offset=%s&limit=%s&timeout=%s"), 
                                  *Token, 
                                  *Offset, 
                                  *Limit, 
                                  *Timeout);
    Request->SetURL(Url);
    Request->ProcessRequest();

    Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        if (bWasSuccessful && Response.IsValid())
        {
            // Print response
            UE_LOG(LogTemp, Log, TEXT("[Callback]TG Message(BOT): %s"), *Response->GetContentAsString());
        }
		else
		{
			// Error request
			UE_LOG(LogTemp, Error, TEXT("[ERROR]TG Message(BOT): Not recived (Couldn't connect to server)"));
		}
    });
}
