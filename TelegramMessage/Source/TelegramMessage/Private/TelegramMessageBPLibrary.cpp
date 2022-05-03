// Copyright 2022 Awesomium team LLC. All Rights Reserved.

#include "TelegramMessageBPLibrary.h"
#include "Misc/Paths.h"
#include "Containers/UnrealString.h"
#include "HttpModule.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonWriter.h"
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
//sendDice		 -- https://core.telegram.org/bots/api#senddice +
//sendPoll		 -- https://core.telegram.org/bots/api#sendpoll - (Testing) (WIP)
//sendchAtaction --https://tlgrm.ru/docs/bots/api#sendchataction +- (STATUS)

// Callback (Debug info) / Дебаг подлючения [TODO]
void UTelegramMessageBPLibrary::OnRequestFinish(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded)
	{
		// GOOD Http / Всё ок с соединением
		FString JSONString = HttpResponse->GetContentAsString();
		UE_LOG(LogTemp, Log, TEXT("HTTP Send and getted: %s"), *JSONString);
	}
	else
	{
		// ERROR Http / Ошибка отправки
		UE_LOG(LogTemp, Error, TEXT("HTTP ERROR: Not sended (Couldn't connect to server)"));
	}
}

// Message / Сообщение
void UTelegramMessageBPLibrary::SendTelegramMessage(
	const FString& Token,
	const FString& ChatID,
	const FString& Message
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest(); // TEMPED on static void / Временное ГОВНО во время режима статика у void 

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish); [WIP virtual void or void]
	Request->SetVerb("GET");
	//Request->SetVerb(Verb); [WIP virtual void or void]
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendMessage?chat_id=") + ChatID + TEXT("&text=") + Message);
	//Request->SetURL(TGBot + Token / MSendMessage + MChatID + ChatID + PText + Message); [WIP virtual void or void]
	Request->ProcessRequest();

	//UE_LOG(LogTemp, Log, TEXT("Debug: %s"), *FString(TGBot + Token / MSendMessage + MChatID + ChatID + PText + Message)); // DEBUG
};

// Contact / Контакты
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
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendContact?chat_id=") + ChatID + TEXT("&phone_number=") + Number + TEXT("&first_name=") + NameContact);
	//Request->SetURL(TGBot + Token / MSendContact + MChatID + ChatID + PNumber + Number + PFName + NameContact);
	Request->ProcessRequest();
};

// Location / Локация
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
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendLocation?chat_id=") + ChatID + TEXT("&latitude=") + Latitude + TEXT("&longitude=") + Longitude);
	//Request->SetURL(TGBot + Token / MSendLocation + MChatID + ChatID + PX + Latitude + PY + Longitude);
	Request->ProcessRequest();
};

// Venue / Локация с описанием
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
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendVenue?chat_id=") + ChatID + TEXT("&latitude=") + Latitude + TEXT("&longitude=") + Longitude + TEXT("&title=") + Title + TEXT("&address=") + Address);
	//Request->SetURL(TGBot + Token / MSendVenue + MChatID + ChatID + PX + Latitude + PY + Longitude + PStreet + Title + PAddress + Address);
	Request->ProcessRequest();
};

// Poll / Голосование (WIP)
void UTelegramMessageBPLibrary::SendTelegramPoll(
	const FString& Token,
	const FString& ChatID,
	const FString& Question,
	const TArray<FString>& Options
	)
{
	//TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	UE_LOG(LogTemp, Warning, TEXT("%s"), Options.GetData() );

	Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb(Verb);
	Request->SetURL(TGBot + Token / MSendPoll + MChatID + ChatID + PQuestions + Question + POptions + *Options.GetData());

	//Request->SetVerb("POST");
	//Request->SetURL(TEXT("https://api.telegram.org/bot") + Token + TEXT("/sendPoll?chat_id=") + ChatID + TEXT("&question=") + Question + TEXT("&options=") + *Options.GetData());
	//Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	Request->ProcessRequest();
};

// Dice / Кости
void UTelegramMessageBPLibrary::SendTelegramDice(
	const FString& Token,
	const FString& ChatID
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendDice?chat_id=") + ChatID);
	//Request->SetURL(TGBot + Token / MSendDice + MChatID + ChatID);
	Request->ProcessRequest();
};

// Action status / Чат статус | (typing) for text messages, (upload_photo) for photos, (record_video) or (upload_video) for videos, (record_audio) or (upload_audio) for audio files, (upload_document) for general files, (find_location) for location data
void UTelegramMessageBPLibrary::SendTelegramAction(
	const FString& Token,
	const FString& ChatID,
	const FString& Action
	//const EStatus& Action
	)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetTimeout(15);
	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	Request->SetVerb("GET");
	//Request->SetVerb(Verb);
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendChatAction?chat_id=") + ChatID + TEXT("&action=") + Action);
	//Request->SetURL(TGBot + Token / MSendAction + MChatID + ChatID + PAction + Action);
	Request->ProcessRequest();
};

// Photo / Фото
void UTelegramMessageBPLibrary::SendTelegramPhoto(
	const FString& Token,
	const FString& ChatID,
	const FString& Photo
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendPhoto?chat_id=") + ChatID);

	//Request->OnProcessRequestComplete().BindUObject(this, &UTelegramMessageBPLibrary::OnRequestFinish);
	//Request->SetVerb(Verb);
	//Request->SetURL(TGBot + Token / MSendVenue + MChatID + ChatID + MSendPhoto);
	//Request->ProcessRequest();

	// Форматирование и запрс
	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	// Байт на файл
	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Photo))
	{
		// Начало форматирования
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		// Начало для фотки
		FString FileHeader = "Content-Disposition: form-data;name=\"photo\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Photo) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		// Сам файл
		RequestContent.Append(FileContent);
	}

	// Заканчиваем форматирование
	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};

// Audio / Аудиозаписи
void UTelegramMessageBPLibrary::SendTelegramAudio(
	const FString& Token,
	const FString& ChatID,
	const FString& Audio
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendAudio?chat_id=") + ChatID);

	// Форматирование и запрс
	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Audio))
	{
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		FString FileHeader = "Content-Disposition: form-data;name=\"audio\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Audio) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		RequestContent.Append(FileContent);
	}

	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};

// Video / Видеозаписи
void UTelegramMessageBPLibrary::SendTelegramVideo(
	const FString& Token,
	const FString& ChatID,
	const FString& Video
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendVideo?chat_id=") + ChatID);

	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Video))
	{
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		FString FileHeader = "Content-Disposition: form-data;name=\"video\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Video) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		RequestContent.Append(FileContent);
	}

	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};

// Voice / Голосовое сообщение
void UTelegramMessageBPLibrary::SendTelegramVoice(
	const FString& Token,
	const FString& ChatID,
	const FString& Audio
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendVoice?chat_id=") + ChatID);

	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Audio))
	{
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		FString FileHeader = "Content-Disposition: form-data;name=\"voice\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Audio) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		RequestContent.Append(FileContent);
	}

	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};

// Document / Документ до 50 мб
void UTelegramMessageBPLibrary::SendTelegramDocument(
	const FString& Token,
	const FString& ChatID,
	const FString& Document
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendDocument?chat_id=") + ChatID);

	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Document))
	{
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		FString FileHeader = "Content-Disposition: form-data;name=\"document\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Document) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		RequestContent.Append(FileContent);
	}

	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};

// Sticker / Стикер
void UTelegramMessageBPLibrary::SendTelegramSticker(
	const FString& Token,
	const FString& ChatID,
	const FString& Sticker
)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("https://api.telegram.org/bot") + Token / TEXT("sendSticker?chat_id=") + ChatID);

	FString Boundary = "---------------------------" + FString::FromInt(FDateTime::Now().GetTicks());
	Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));
	Request->SetVerb(TEXT("POST"));

	TArray<uint8> RequestContent;

	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *Sticker))
	{
		FString BeginBoundry = "\r\n--" + Boundary + "\r\n";
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundry), BeginBoundry.Len());

		FString FileHeader = "Content-Disposition: form-data;name=\"sticker\";";
		FileHeader.Append("filename=\"" + FPaths::GetCleanFilename(Sticker) + "\"\r\n");
		FileHeader.Append("Content-Type: \r\n\r\n");
		RequestContent.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());

		RequestContent.Append(FileContent);
	}

	FString EndBoundary = "\r\n--" + Boundary + "--\r\n";
	RequestContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

	Request->SetContent(RequestContent);
	Request->ProcessRequest();

};
