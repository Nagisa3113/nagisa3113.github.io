// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "Templates/SharedPointer.h"
#include "RequestTool.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpSuccessEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHttpFailureEvent);

/**
 * 
 */
UCLASS(BlueprintType)
class MOBILEPROJECT_API URequestTool : public UObject
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "RequestTool")
	void GetMethod(FString URL);

	UFUNCTION(BlueprintCallable, Category = "RequestTool")
	void PostMethod(FString URL, FString Key, FString Value);

	void OnResponseReceived(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);


	UPROPERTY(BlueprintAssignable, Category = "HTTP")
	FHttpSuccessEvent OnHttpSuccessEvent;

	UPROPERTY(BlueprintAssignable, Category = "HTTP")
	FHttpFailureEvent OnHttpFailureEvent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RequestTool")
	FString FResponseContent = "";


	UFUNCTION(BlueprintCallable, Category = "RequestTool")
	TArray<FString> ProcessResponseJson(FString Res);

	// UPROPERTY(BlueprintReadWrite, Category = "RequestTool")
	// TArray<FString> Scores;
};
