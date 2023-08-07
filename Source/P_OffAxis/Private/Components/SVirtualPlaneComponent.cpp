// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SVirtualPlaneComponent.h"

// Sets default values for this component's properties
USVirtualPlaneComponent::USVirtualPlaneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	bTickInEditor = true;
	// ...
}


// Called when the game starts
void USVirtualPlaneComponent::BeginPlay()
{
	Super::BeginPlay();
	// BottomLeft=FVector(0,-Width/2,-Height/2);
	// BottomRight=FVector(0,Width/2,-Height/2);
	// TopLeft=FVector(0,-Width/2,Height/2);
	// TopRight=FVector(0,Width/2,Height/2);
	// ...
	BottomLeft= (-GetRightVector()*(Width/2)-GetUpVector()*(Height/2))+GetComponentLocation();
	BottomRight= (GetRightVector()*(Width/2)-GetUpVector()*(Height/2))+GetComponentLocation();
	TopLeft= (-GetRightVector()*(Width/2)+GetUpVector()*(Height/2))+GetComponentLocation();
	TopRight= (GetRightVector()*(Width/2)+GetUpVector()*(Height/2))+GetComponentLocation();
	
}

void USVirtualPlaneComponent::OnRegister()
{
	Super::OnRegister();

}


// Called every frame
void USVirtualPlaneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(bDebug)
	{
		BottomLeft= (-GetRightVector()*(Width/2)-GetUpVector()*(Height/2))+GetComponentLocation();
		BottomRight= (GetRightVector()*(Width/2)-GetUpVector()*(Height/2))+GetComponentLocation();
		TopLeft= (-GetRightVector()*(Width/2)+GetUpVector()*(Height/2))+GetComponentLocation();
		TopRight= (GetRightVector()*(Width/2)+GetUpVector()*(Height/2))+GetComponentLocation();
		VisualizeStructure();
	}
}

void USVirtualPlaneComponent::VisualizeStructure() const
{
	decltype(GetFourWorldCorners()) Corners = GetFourWorldCorners();
	DrawDebugLine(GetWorld(),Corners[0],Corners[1],FColor::Orange,false,-1,0,bDebugLineThickness);
	DrawDebugLine(GetWorld(),Corners[0],Corners[2],FColor::Orange,false,-1,0,bDebugLineThickness);
	DrawDebugLine(GetWorld(),Corners[1],Corners[3],FColor::Orange,false,-1,0,bDebugLineThickness);
	DrawDebugLine(GetWorld(),Corners[2],Corners[3],FColor::Orange,false,-1,0,bDebugLineThickness);
	DrawDebugSphere(GetWorld(),Corners[0],10,4,FColor::Red,false,-1,0,bDebugLineThickness);
	DrawDebugSphere(GetWorld(),Corners[1],10,4,FColor::Green,false,-1,0,bDebugLineThickness);
	DrawDebugSphere(GetWorld(),Corners[2],10,4,FColor::Blue,false,-1,0,bDebugLineThickness);
	DrawDebugSphere(GetWorld(),Corners[3],10,4,FColor::Silver,false,-1,0,bDebugLineThickness);
	if(bDebugPlaneNormal)
	{
		TArray<FVector> Normals = GetNormalDirections();
		DrawDebugLine(GetWorld(),GetComponentLocation(),GetComponentLocation()+Normals[0]*100,FColor::Red,false,-1,0,bDebugLineThickness);
		DrawDebugLine(GetWorld(),GetComponentLocation(),GetComponentLocation()+Normals[1]*100,FColor::Green,false,-1,0,bDebugLineThickness);
		DrawDebugLine(GetWorld(),GetComponentLocation(),GetComponentLocation()+Normals[2]*100,FColor::Blue,false,-1,0,bDebugLineThickness);
	}
}

/**
 * Get the World locations of three corners from the plane 
 * @return 0-BotLeft 1-BotRight 2-TopLeft 3-TopRight
 **/
TArray<FVector> USVirtualPlaneComponent::GetFourWorldCorners() const
{
	TArray<FVector> Result;
	Result.Add(BottomLeft);
	Result.Add(BottomRight);
	Result.Add(TopLeft);
	Result.Add(TopRight);
	return Result;
}
/**
 * @return Normals of the plane 0-Normal 1-RightNormal 2-UpNormal
 **/
TArray<FVector> USVirtualPlaneComponent::GetNormalDirections() const
{
	TArray<FVector> Result;
	Result.Add(bFlipNormal==true?GetForwardVector()*-1:GetForwardVector());
	Result.Add(GetRightVector());
	Result.Add(GetUpVector());
	return Result;
}

