// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SOffAxisSceneCaptureComponent2D.h"
#include "Components/SVirtualPlaneComponent.h"
#include "SLibary/SMathTool.h"


void USOffAxisSceneCaptureComponent2D::BeginPlay()
{
	Super::BeginPlay();
	
	UObject* Temp = GetOwner()->GetDefaultSubobjectByName(VirtualPlaneName);
	VirtualPlaneComponent = Cast<USVirtualPlaneComponent>(Temp);
	if(VirtualPlaneComponent==nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("ChildActorComponent's class is not VirtualPlaneComponent"));
	}
	bUseCustomProjectionMatrix=bUseOffAxisProjectionMatrix;
	
}

void USOffAxisSceneCaptureComponent2D::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if( VirtualPlaneComponent==nullptr) return;

	
	TArray<FVector> FourCorners = VirtualPlaneComponent->GetFourWorldCorners();
	if(bUseCustomProjectionMatrix)
	{
		const TArray<FVector> ScreenDirections = VirtualPlaneComponent->GetNormalDirections();
		const FVector EyeRelativeCoordinate=GetComponentLocation();
		const FMatrix ProjectionMatrix=USMathTool::OffAxisMatrix(FourCorners,ScreenDirections,EyeRelativeCoordinate,1,10000,true);
		CustomProjectionMatrix=ProjectionMatrix;
	}
	
	if(bDebug)
	{
		if(bShowWire)
		{
			DrawDebugLine(GetWorld(),GetComponentLocation(),FourCorners[0],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),GetComponentLocation(),FourCorners[1],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),GetComponentLocation(),FourCorners[2],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),GetComponentLocation(),FourCorners[3],FColor::Green,false,-1,0,bDebugLineThickness);
		}
		if(bShowCam)
		{
			DrawDebugSphere(GetWorld(),GetComponentLocation(),20,4,FColor::Purple,false,-1,bDebugLineThickness);	
		}

	}
}
