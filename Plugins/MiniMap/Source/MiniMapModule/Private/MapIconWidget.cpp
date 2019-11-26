#include "MapIconWidget.h"
#include "MapWidget.h"

#include <Brushes/SlateDynamicImageBrush.h>
#include <Components/Image.h>
#include <Components/Throbber.h>
#include <Engine/Texture2D.h>



void UMapIconWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsValid(MyActor)) 
	{
		// Position
		FVector2D MapLocation;
		bool OnMap = MyMap->GetMapLocation(MyActor->GetActorLocation(), MapLocation);
		CurrentIcon->SetRenderTranslation(MapLocation);

		// Orientation
		FRotator Rotation = MyActor->GetActorRotation();

		// 4.22.3
		//CurrentIcon->SetRenderAngle(Rotation.Yaw);

		// 4.23.0
		CurrentIcon->SetRenderTransformAngle(Rotation.Yaw);

		// Determine visibility
		if (!OnMap && !bAlwaysRelevant) 
		{
			CurrentIcon->SetVisibility(ESlateVisibility::Hidden);
		}
		else 
		{
			CurrentIcon->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else 
	{
		RemoveFromParent();
	}
}

void UMapIconWidget::Setup(const FColor& IconTint, UTexture2D* IconImage, UMapWidget* InMap, AActor* InActor, bool bAlwaysShow) 
{
	MyMap = InMap;
	MyActor = InActor;
	bAlwaysRelevant = bAlwaysShow;

	// Use specified parameters
	if (IconImage) 
	{
		if (!IconImage->IsRooted()) 
		{
			IconImage->AddToRoot();
		}
		FLinearColor Color = IconTint;
		FSlateDynamicImageBrush SlateBrush(IconImage, FVector2D(16.0f, 16.0f), NAME_None, Color);
		if (CustomIcon) 
		{
			CustomIcon->SetBrush(SlateBrush);
			CustomIcon->SetVisibility(ESlateVisibility::Visible);
			DefaultIcon->SetVisibility(ESlateVisibility::Hidden);
			CurrentIcon = CustomIcon;
		}
	}

	// No image, use default 
	else 
	{
		CustomIcon->SetVisibility(ESlateVisibility::Hidden);
		DefaultIcon->SetVisibility(ESlateVisibility::Visible);
		CurrentIcon = DefaultIcon;
	}
}


// Initialize icon widget
bool UMapIconWidget::Initialize() 
{
	if (!Super::Initialize()) { return false; }

	if (!ensure(DefaultIcon)) { return false; }
	if (!ensure(CustomIcon)) { return false; }
	
	return true;
}
