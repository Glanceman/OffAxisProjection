// Fill out your copyright notice in the Description page of Project Settings.


#include "SLibary/SMathTool.h"


// template<typename T>
// FORCEINLINE TReversedZPerspectiveMatrix<T>::TReversedZPerspectiveMatrix(T HalfFOV, T Width, T Height, T MinZ)
// 	: TMatrix<T>(
// 		TPlane<T>(1.0f / FMath::Tan(HalfFOV),	0.0f,									0.0f, 0.0f),
// 		TPlane<T>(0.0f,							Width / FMath::Tan(HalfFOV) / Height,	0.0f, 0.0f),
// 		TPlane<T>(0.0f,							0.0f,									0.0f, 1.0f),
// 		TPlane<T>(0.0f,							0.0f,									MinZ, 0.0f)
// 	)
// { }

// FMatrix USMathTool::FrustumMatrix2(double Left, double Right, double Bottom, double Top, double NearVal, double FarVal)
// {
// 	const FMatrix Result = FMatrix(
// 	UE::Math::TPlane<double>((2*NearVal)/(Right-Left), 0,							(Right+Left)/(Right-Left),				0),
// 	UE::Math::TPlane<double>(0,						(2*NearVal)/(Top-Bottom),	(Top+Bottom)/(Top-Bottom),				0),
// 	UE::Math::TPlane<double>(0,						0,                       -(FarVal+NearVal)/(FarVal-NearVal),			(-2*FarVal*NearVal)/(FarVal-NearVal)),
// 	UE::Math::TPlane<double>(0,                       0,						-1,									0)
// 	);
// 	return Result;
// 	
// }


FMatrix USMathTool::FrustumMatrix(float left, float right, float bottom, float top, float nearVal, float farVal)
{
	//column-major order
	FMatrix Result;
	Result.SetIdentity();
	Result.M[0][0] = (2.0f * nearVal) / (right - left);
	Result.M[1][1] = (2.0f * nearVal) / (top - bottom);
	Result.M[2][0] = -(right + left) / (right - left);
	Result.M[2][1] = -(top + bottom) / (top - bottom);
	Result.M[2][2] = (farVal) / (farVal - nearVal);
	Result.M[2][3] = 1.0f;
	Result.M[3][2] = -(farVal * nearVal) / (farVal - nearVal);
	Result.M[3][3] = 0.0f;

	return Result;
}
/**
* Calculate offAxis Perspective Projection Matrix
*
* @param CornerPoints - corner points of screen 0-bottom left , 1-bottom right, 2-topLeft, 3-TopRight
* @param ScreenDirection - (Unit Vector) Screen Normals 0-Right 1-Up 2-Normal;
* @param EyeLocation - location that viewing the screen
* @param NearClip
* @param FarClip
* @param bDebug
* @return	true -> offAxisMatrix, false-> empty Matrix
*/
FMatrix USMathTool::OffAxisMatrix(const TArray<FVector>& CornerPoints, const TArray<FVector>& ScreenDirection, const FVector& EyeLocation,double NearClip, double FarClip, bool bDebug=false)
{
	if(CornerPoints.Num() !=4)
	{
		UE_LOG(LogTemp,Error,TEXT("Expect length of 4 of Cornerpoints but only get %d"),CornerPoints.Num());
		return FMatrix();
	}
	if(ScreenDirection.Num() !=3)
	{
		UE_LOG(LogTemp,Error,TEXT("Expect length of 4 of Cornerpoints but only get %d"),ScreenDirection.Num());
		return FMatrix();
	}

	const FVector BottomLeft = CornerPoints[0];
	const FVector BottomRight = CornerPoints[1];
	const FVector TopLeft = CornerPoints[2];
	const FVector TopRight = CornerPoints[3];

	const FVector ScreenDirNormal = ScreenDirection[0];
	const FVector ScreenDirRight = ScreenDirection[1];
	const FVector ScreenDirUp = ScreenDirection[2];
	// direction vector to 3 corners
	const FVector EyeToBotLeft = BottomLeft - EyeLocation;
	const FVector EyeToBotRight = BottomRight - EyeLocation;
	const FVector EyeToTopLeft = TopLeft - EyeLocation;

	const double EyeToScreen = -FVector::DotProduct(EyeToBotLeft,ScreenDirNormal);
	const double Ratio = NearClip/EyeToScreen;
	
	const double LeftDist= FVector::DotProduct(EyeToBotLeft,ScreenDirRight)*Ratio;
	const double RightDist=FVector::DotProduct(EyeToBotRight,ScreenDirRight)*Ratio;
	const double BotDist = FVector::DotProduct(EyeToBotLeft, ScreenDirUp)*Ratio;
	const double TopDist= FVector::DotProduct(EyeToTopLeft,ScreenDirUp)*Ratio;

	const FMatrix Projection = FrustumMatrix(LeftDist,RightDist,BotDist,TopDist,NearClip,FarClip);
	// const FMatrix Translation =   FMatrix(
	// UE::Math::TPlane<double>(1, 0,0,-EyeLocation.X),
	// UE::Math::TPlane<double>(0,1,	0,-EyeLocation.Y),
	// UE::Math::TPlane<double>(0,0,1,-EyeLocation.Z),
	// UE::Math::TPlane<double>(0,0,0,1)
	// );
	const FMatrix Translation = FTranslationMatrix(FVector(-EyeLocation.Y,-EyeLocation.Z,-EyeLocation.X));
	// todo: rotation
	FMatrix Result = Projection;
	Result *= 1.0f / Result.M[0][0];
	Result.M[2][2] = 0.f; //?
	Result.M[3][2] = NearClip; //?
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Orange, FString::Printf(TEXT("point-BotLeft: %s"), *BottomLeft.ToString()));
		GEngine->AddOnScreenDebugMessage(2, 2, FColor::Orange, FString::Printf(TEXT("point-BotLeft: %s"), *BottomRight.ToString()));
		GEngine->AddOnScreenDebugMessage(3, 2, FColor::Orange, FString::Printf(TEXT("point-BotLeft: %s"), *TopLeft.ToString()));
		GEngine->AddOnScreenDebugMessage(4, 2, FColor::Orange, FString::Printf(TEXT("point-Eye: %s"), *EyeLocation.ToString()));
		// 		GEngine->AddOnScreenDebugMessage(5, 2, FColor::Black, FString::Printf(TEXT("vr: %s"), *vu.ToString()));
		// 		GEngine->AddOnScreenDebugMessage(6, 2, FColor::Black, FString::Printf(TEXT("vu: %s"), *vr.ToString()));
		// 		GEngine->AddOnScreenDebugMessage(7, 2, FColor::Black, FString::Printf(TEXT("vn: %s"), *vn.ToString()));
		GEngine->AddOnScreenDebugMessage(8, 4, FColor::Red, FString::Printf(TEXT("Screen Normal: %f \t %f \t %f  "),  ScreenDirNormal.X,ScreenDirNormal.Y,ScreenDirNormal.Z));
		GEngine->AddOnScreenDebugMessage(8, 4, FColor::Red, FString::Printf(TEXT("Frustum: %f \t %f \t %f \t %f \t %f \t %f \t "), LeftDist, RightDist, BotDist, TopDist, NearClip, FarClip));
		GEngine->AddOnScreenDebugMessage(9, 2, FColor::Orange, FString::Printf(TEXT("Eye-Screen-Distance: %f"), EyeToScreen));
		GEngine->AddOnScreenDebugMessage(10, 4, FColor::Orange, FString::Printf(TEXT("Ratio: %f"), Ratio));
	}

	return Result;
}
