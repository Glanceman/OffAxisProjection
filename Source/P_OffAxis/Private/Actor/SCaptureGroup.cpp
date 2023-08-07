// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SCaptureGroup.h"


#include "Actor/SVirtualPlane.h"
#include "Components/SceneCaptureComponent2D.h"
#include "SLibary/SMathTool.h"

// Sets default values
ASCaptureGroup::ASCaptureGroup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root =CreateDefaultSubobject<USceneComponent>("Root");
	Root->Mobility=EComponentMobility::Static;
	SetRootComponent(Root);
	CaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>("FrontCapture");
	ChildActorPlane = CreateDefaultSubobject<UChildActorComponent>("Plane");
	ChildActorPlane->SetupAttachment(RootComponent);
	CaptureComp->SetupAttachment(RootComponent);
	
	ChildActorPlane->SetChildActorClass(ASVirtualPlane::StaticClass());
	
	ChildActorPlane->SetRelativeLocation(FVector(Depth,0,0));
	CaptureComp->SetRelativeLocation(FVector(0,0,0));


	
}

// Called when the game starts or when spawned
void ASCaptureGroup::BeginPlay()
{
	Super::BeginPlay();
	VirtualPlane = Cast<ASVirtualPlane>(ChildActorPlane->GetChildActor());
	if(VirtualPlane==nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("ChildActorComponent's class is not SVirtualPlane"));
		EndPlay(EEndPlayReason::Quit);
	}
	CaptureComp->bUseCustomProjectionMatrix=bUseCustomProjectionMatrix;
	
}

void ASCaptureGroup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ChildActorPlane->SetRelativeLocation(FVector(Depth,0,0));
	CaptureComp->CustomNearClippingPlane=NearClip;
}

// Called every frame
void ASCaptureGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FourCorners = VirtualPlane->GetFourCorners();
	if(CaptureComp->bUseCustomProjectionMatrix)
	{
		//const FMatrix ProjectionMatrix = USMathTool::OffAxisMatrix(Corners,ScreenDirection,CaptureComp->GetComponentLocation(),NearClip,FarClip,true);
		//const FReversedZPerspectiveMatrix PerspectiveMatrix(CustomFOV,-Plane->Width,-Plane->Height,NearClip);
		//const FMatrix ProjectionMatrix = PerspectiveMatrix;
		const TArray<FVector> ScreenDirections = VirtualPlane->GetNormalDirections();
		const FVector EyeRelativeCoordinate=CaptureComp->GetComponentLocation();
		const FMatrix ProjectionMatrix=USMathTool::OffAxisMatrix(FourCorners,ScreenDirections,EyeRelativeCoordinate,1,10000,true);
		CaptureComp->CustomProjectionMatrix=ProjectionMatrix;
	}
	
	if(bDebug)
	{
		if(bShowWire)
		{
			DrawDebugLine(GetWorld(),CaptureComp->GetComponentLocation(),FourCorners[0],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),CaptureComp->GetComponentLocation(),FourCorners[1],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),CaptureComp->GetComponentLocation(),FourCorners[2],FColor::Green,false,-1,0,bDebugLineThickness);
			DrawDebugLine(GetWorld(),CaptureComp->GetComponentLocation(),FourCorners[3],FColor::Green,false,-1,0,bDebugLineThickness);
		}
		if(bShowCam)
		{
			DrawDebugSphere(GetWorld(),CaptureComp->GetComponentLocation(),20,4,FColor::Purple,false,-1,bDebugLineThickness);	
		}

	}
}




