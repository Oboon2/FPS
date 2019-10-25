
#include "LobbyPC.h"
#include "Lobby/LobbyWidgetBase.h"
#include "Components/Button.h"

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{

		// #include "Path", ���, UE4 Asset, BP
		FSoftClassPath LobbyWidgetClass_CPP_PATH(TEXT("WidgetBlueprint'/Game/Blueprints/UI/Lobby/LobbyWidget.LobbyWidget_C'"));

		// #include "" ����
		UClass* LobbyWidgetClass_BP = LobbyWidgetClass_CPP_PATH.TryLoadClass<ULobbyWidgetBase>();

		if (LobbyWidgetClass_BP)
		{
			// new
			//LobbyWidget = Cast<ULobbyWidgetBase>(NewObject<ULobbyWidgetBase>(this, LobbyWidgetClass_BP));
			LobbyWidget = CreateWidget<ULobbyWidgetBase>(this, LobbyWidgetClass);
			if (LobbyWidget)
			{
				LobbyWidget->AddToViewport();
				bShowMouseCursor = true;
				SetInputMode(FInputModeGameAndUI());
				// ȣ��Ʈ�� �ƴѰ������� ���ӽ�ŸƮ ��ư ����
				if (!HasAuthority())
				{
					LobbyWidget->GameStartButton->SetVisibility(ESlateVisibility::Collapsed);
				}
				else 
				{
					LobbyWidget->PlayStartButton();
				}
			}
		}

		//LobbyWidget = CreateWidget<ULobbyWidgetBase>(this, LobbyWidgetClass);
		//if (LobbyWidget)
		//{
		//	LobbyWidget->AddToViewport();
		//}
	}
}

bool ALobbyPC::C2S_SendMessage_Validate(const FText & Message)
{
	return true;
}

void ALobbyPC::C2S_SendMessage_Implementation(const FText & Message)
{
	for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*iter);
		if (PC)
		{
			UE_LOG(LogClass, Warning, TEXT("C2S_SendMessage_Implementation"));
			PC->S2C_SendMessage(Message);
		}
	}
}

void ALobbyPC::S2C_SendMessage_Implementation(const FText & Message)
{
	LobbyWidget->AddMessage(Message);
}
