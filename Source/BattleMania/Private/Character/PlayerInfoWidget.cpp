


#include "PlayerInfoWidget.h"

#include <Components/VerticalBox.h>
#include <Components/TextBlock.h>


UPlayerInfoWidget::UPlayerInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) 
{
}


bool UPlayerInfoWidget::Initialize() 
{
	if (!Super::Initialize()) { return false; }
	if (!PlayerInfo) { return false; }
	return true;
}


void UPlayerInfoWidget::SetPlayerInfo(const TArray<FString>& InfoStrings) 
{
	if (!PlayerInfo) { return; }

	PlayerInfo->ClearChildren();
	AddPlayerInfo(InfoStrings);
}


void UPlayerInfoWidget::AddPlayerInfo(const TArray<FString>& InfoStrings) 
{
	if (!PlayerInfo) { return; }

	UTextBlock* TextBlock = nullptr;
	for (FString String : InfoStrings) 
	{
		TextBlock = NewObject<UTextBlock>(UTextBlock::StaticClass());
		TextBlock->SetColorAndOpacity(Color.ReinterpretAsLinear());
		TextBlock->Font.Size = FontSize;
		TextBlock->SetText(FText::FromString(String));
		PlayerInfo->AddChildToVerticalBox(TextBlock);
	}
}


void UPlayerInfoWidget::SetColor(FColor NewColor) 
{
	Color = NewColor;
}

void UPlayerInfoWidget::SetFontSize(int32 NewFontSize) 
{
	FontSize = NewFontSize;
}

