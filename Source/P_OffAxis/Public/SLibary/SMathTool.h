// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SMathTool.generated.h"

/**
 * 
 */
UCLASS()
class P_OFFAXIS_API USMathTool : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
#pragma region Functions
	static FMatrix FrustumMatrix2(double Left, double Right, double Bottom, double Top, double NearVal, double FarVal);
	UFUNCTION(BlueprintCallable, Category="SMathTool")
	static FMatrix FrustumMatrix(float left, float right, float bottom, float top, float nearVal, float farVal);

	static FMatrix OffAxisMatrix(const TArray<FVector>& CornerPoints, const TArray<FVector>& ScreenDirection, const FVector& EyeLocation, double
	                             NearClip, double FarClip, bool
	                             bDebug);
	
	
#pragma endregion Functions

};
