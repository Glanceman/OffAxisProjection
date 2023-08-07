// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCaptureGroup.generated.h"

class ASVirtualPlane;

UCLASS()
class P_OFFAXIS_API ASCaptureGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASCaptureGroup();
	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneCaptureComponent2D* CaptureComp = nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	UChildActorComponent* ChildActorPlane =nullptr;
	UPROPERTY(Category="Components", BlueprintReadOnly)
	ASVirtualPlane* VirtualPlane =nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneComponent* Root =nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Params", BlueprintReadWrite)
	float Depth = 300;
	
	/**
	 * @ CustomFOV Expected Radian
	 **/
	UPROPERTY(EditAnywhere, Category="Params", BlueprintReadWrite)
	float CustomFOV = PI/4; 
	
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	float FarClip = 10000.f;
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	float NearClip = 10.f;
	UPROPERTY(EditDefaultsOnly,Category="Params",BlueprintReadWrite)
	bool bUseCustomProjectionMatrix = true;
	
	

	
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bDebug = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bShowWire = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bShowCam = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	float bDebugLineThickness=2;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	TArray<FVector> FourCorners;

};
