// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SVirtualPlane.generated.h"

UCLASS()
class P_OFFAXIS_API ASVirtualPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASVirtualPlane();

	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneComponent* Root =nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneComponent* BottomLeftCorner=nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneComponent* BottomRightCorner=nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Components", BlueprintReadOnly)
	USceneComponent* TopLeftCorner=nullptr;
	UPROPERTY(EditDefaultsOnly, Category="Components" , BlueprintReadOnly)
	USceneComponent* TopRightCorner =nullptr;;

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
	TArray<FVector> GetFourCorners() const;
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetNormalDirections() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
