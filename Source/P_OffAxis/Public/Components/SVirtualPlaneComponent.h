// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SVirtualPlaneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P_OFFAXIS_API USVirtualPlaneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USVirtualPlaneComponent();


	UPROPERTY(VisibleAnywhere, Category="Params",BlueprintReadOnly)
	FVector BottomLeft = FVector(0,0,0);
	UPROPERTY(VisibleAnywhere, Category="Params",BlueprintReadOnly)
	FVector BottomRight = FVector(0,0,0);
	UPROPERTY(VisibleAnywhere, Category="Params",BlueprintReadOnly)
	FVector TopLeft = FVector(0,0,0);
	UPROPERTY(VisibleAnywhere, Category="Params",BlueprintReadOnly)
	FVector TopRight = FVector(0,0,0);
	
	UPROPERTY(EditDefaultsOnly, Category="Params", BlueprintReadWrite)
	float Width=400;
	UPROPERTY(EditDefaultsOnly, Category="Params", BlueprintReadWrite)
	float Height=400;
	UPROPERTY(EditDefaultsOnly, Category="Params", BlueprintReadWrite)
	bool bFlipNormal = true;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bDebug=false;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	float bDebugLineThickness=2;
	UPROPERTY(EditDefaultsOnly, Category="Debug Params", BlueprintReadWrite)
	bool bDebugPlaneNormal=false;
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetFourWorldCorners() const;
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetNormalDirections() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void VisualizeStructure() const;
};
