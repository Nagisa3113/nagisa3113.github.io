// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestTool.h"


void URequestTool::GetMethod(FString URL)
{
	// URL = "https://jsonplaceholder.typicode.com/posts/1";
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &URequestTool::OnResponseReceived);
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}


void URequestTool::PostMethod(FString URL, FString Key, FString Value)
{
	// URL = "https://jsonplaceholder.typicode.com/posts";
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField(Key, Value);
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &URequestTool::OnResponseReceived);
	Request->SetURL(URL);

	Request->SetTimeout(3);

	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
	FResponseContent = URL;
}

void URequestTool::OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!bSucceeded)
	{
		OnHttpFailureEvent.Broadcast();
		return;
	}

	FResponseContent = *HttpResponse->GetContentAsString();

	OnHttpSuccessEvent.Broadcast();

	// UE_LOG(LogTemp, Display, TEXT("Http Request Received %s"), *HttpResponse->GetContentAsString());
	// UE_LOG(LogTemp, Display, TEXT("Title: %s"), *ResponseObj->GetStringField(TEXT("Title")));
}

TArray<FString> URequestTool::ProcessResponseJson(FString JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);


	TArray<FString> Scores;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		// TSharedPtr<FJsonObject> DataObject = JsonObject->GetObjectField(TEXT("data"));
		if (JsonObject->HasField(TEXT("data")))
		{
			TArray<TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField(TEXT("data"));

			for (const auto& Item : DataArray)
			{
				TSharedPtr<FJsonObject> DataItem = Item->AsObject();

				FString score = DataItem->GetStringField(TEXT("score"));
				FString time = DataItem->GetStringField(TEXT("upload_time"));
				Scores.Add(score);
			}
		}
	}
	return Scores;
}
