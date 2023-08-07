// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SVirtualPlane.h"

// Sets default values
ASVirtualPlane::ASVirtualPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root =CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Root->Mobility=EComponentMobility::Static;

	BottomLeftCorner = CreateDefaultSubobject<USceneComponent>("BottomLeft");
	BottomRightCorner = CreateDefaultSubobject<USceneComponent>("BottomRight");
	TopLeftCorner = CreateDefaultSubobject<USceneComponent>("TopLeft");
	TopRightCorner = CreateDefaultSubobject<USceneComponent>("TopRight");

	BottomLeftCorner->SetupAttachment(RootComponent);
	BottomRightCorner->SetupAttachment(RootComponent);
	TopLeftCorner->SetupAttachment(RootComponent);
	TopRightCorner->SetupAttachment(RootComponent);
	

	

}


// Called when the game starts or when spawned
void ASVirtualPlane::BeginPlay()
{
	Super::BeginPlay();
	BottomLeftCorner->SetRelativeLocation(FVector(0,-Width/2,-Height/2));
	BottomRightCorner->SetRelativeLocation(FVector(0,Width/2,-Height/2));
	TopLeftCorner->SetRelativeLocation(FVector(0,-Width/2,Height/2));
	TopRightCorner->SetRelativeLocation(FVector(0,Width/2,Height/2));
}

void ASVirtualPlane::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	BottomLeftCorner->SetRelativeLocation(FVector(0,-Width/2,-Height/2));
	BottomRightCorner->SetRelativeLocation(FVector(0,Width/2,-Height/2));
	TopLeftCorner->SetRelativeLocation(FVector(0,-Width/2,Height/2));
	TopRightCorner->SetRelativeLocation(FVector(0,Width/2,Height/2));
}


// Called every frame
void ASVirtualPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bDebug)
	{
		DrawDebugLine(GetWorld(),BottomLeftCorner->GetComponentLocation(),BottomRightCorner->GetComponentLocation(),FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugLine(GetWorld(),BottomLeftCorner->GetComponentLocation(),TopLeftCorner->GetComponentLocation(),FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugLine(GetWorld(),BottomRightCorner->GetComponentLocation(),TopRightCorner->GetComponentLocation(),FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugLine(GetWorld(),TopLeftCorner->GetComponentLocation(),TopRightCorner->GetComponentLocation(),FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugSphere(GetWorld(),BottomLeftCorner->GetComponentLocation(),10,4,FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugSphere(GetWorld(),BottomRightCorner->GetComponentLocation(),10,4,FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugSphere(GetWorld(),TopLeftCorner->GetComponentLocation(),10,4,FColor::Orange,false,-1,0,bDebugLineThickness);
		DrawDebugSphere(GetWorld(),TopRightCorner->GetComponentLocation(),10,4,FColor::Orange,false,-1,0,bDebugLineThickness);
		if(bDebugPlaneNormal)
		{
			TArray<FVector> Normals = GetNormalDirections();
			DrawDebugLine(GetWorld(),Root->GetComponentLocation(),RootComponent->GetComponentLocation()+Normals[0]*100,FColor::Red,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),Root->GetComponentLocation(),RootComponent->GetComponentLocation()+Normals[1]*100,FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),Root->GetComponentLocation(),RootComponent->GetComponentLocation()+Normals[2]*100,FColor::Blue,false,-1,0,bDebugLineThickness);
		}
		
	}
}

/**
 * Get the World locations of three corners from the plane 
 * @return 0-BotLeft 1-BotRight 2-TopLeft 3-TopRight
 **/
TArray<FVector> ASVirtualPlane::GetFourCorners() const
{
	TArray<FVector> Result;
	Result.Add(BottomLeftCorner->GetComponentLocation());
	Result.Add(BottomRightCorner->GetComponentLocation());
	Result.Add(TopLeftCorner->GetComponentLocation());
	Result.Add(TopRightCorner->GetComponentLocation());
	return Result;
}
/**
 * @return Normals of the plane 0-Normal 1-RightNormal 2-UpNormal
 **/
TArray<FVector> ASVirtualPlane::GetNormalDirections() const
{
	TArray<FVector> Result;
	Result.Add(bFlipNormal==true?Root->GetForwardVector()*-1:Root->GetForwardVector());
	Result.Add(Root->GetRightVector());
	Result.Add(Root->GetUpVector());
	return Result;
}

