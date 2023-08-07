// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "SOffAxisSceneCaptureComponent2D.generated.h"

class USVirtualPlaneComponent;
class ASVirtualPlane;
/**
 * 
 */
UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class P_OFFAXIS_API USOffAxisSceneCaptureComponent2D : public USceneCaptureComponent2D
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,Category="Components", BlueprintReadWrite)
	USVirtualPlaneComponent* VirtualPlaneComponent =nullptr;

	/**
	 * @VirtualPlaneName: used to find the plane within the owner; 
	 **/
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	FName VirtualPlaneName = "Front";
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	float FarClip = 10000.f;
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	float NearClip = 10.f;
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	bool bUseOffAxisProjectionMatrix = true;
	
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bDebug = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bShowWire = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bShowCam = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	float bDebugLineThickness=2;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};
