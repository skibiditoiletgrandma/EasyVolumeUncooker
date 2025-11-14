#include "VolumeExporterEditorModule.h"
#include "VolumeExporterEditorStyle.h"
#include "VolumeExporterEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "VolumeExporterEditor.h"
#include "Editor/EditorEngine.h"
#include "Engine/Engine.h"

static const FName VolumeExporterEditorTabName("VolumeExporterEditor");

#define LOCTEXT_NAMESPACE "FVolumeExporterEditorModule"

void FVolumeExporterEditorModule::StartupModule()
{
	FVolumeExporterEditorStyle::Initialize();
	FVolumeExporterEditorStyle::ReloadTextures();

	FVolumeExporterEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FVolumeExporterEditorCommands::Get().OpenVolumeExporterWindow,
		FExecuteAction::CreateRaw(this, &FVolumeExporterEditorModule::OpenPluginWindow),
		FCanExecuteAction());

	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FVolumeExporterEditorModule::OnPostEngineInit);
}

void FVolumeExporterEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FVolumeExporterEditorStyle::Shutdown();

	FVolumeExporterEditorCommands::Unregister();
}

void FVolumeExporterEditorModule::OpenPluginWindow()
{
	if (PluginLogic)
	{
		PluginLogic->CreateTheWidget();
	}
}

void FVolumeExporterEditorModule::OnPostEngineInit()
{
	PluginLogic = NewObject<UVolumeExporterEditor>();
	PluginLogic->AddToRoot();
	RegisterMenus();
}

void FVolumeExporterEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

#if ((ENGINE_MAJOR_VERSION == 5) && (ENGINE_MINOR_VERSION >= 4))
	UToolMenu* Menu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.Tools");
	if (Menu)
	{
		Menu->AddMenuEntry(NAME_None, FToolMenuEntry::InitMenuEntryWithCommandList(
			FVolumeExporterEditorCommands::Get().OpenVolumeExporterWindow,
			PluginCommands,
			FText::FromString(TEXT("Volume Exporter")),
			FText::FromString(TEXT("Opens Volume Exporter Window")),
			FSlateIcon(FVolumeExporterEditorStyle::GetStyleSetName(), "VolumeExporterEditorStyle.MenuIcon")
		));
	}
#else
	TSharedPtr<FExtender> MainMenuExtender = MakeShareable(new FExtender);
	MainMenuExtender->AddMenuExtension(
#if (ENGINE_MAJOR_VERSION == 5)
		FName(TEXT("Tools")),
#else
		FName(TEXT("General")),
#endif
		EExtensionHook::After,
		PluginCommands,
		FMenuExtensionDelegate::CreateLambda([](FMenuBuilder& MenuBuilder)
		{
			MenuBuilder.AddMenuEntry(
				FVolumeExporterEditorCommands::Get().OpenVolumeExporterWindow,
				NAME_None,
				FText::FromString(TEXT("Volume Exporter")),
				FText::FromString(TEXT("Opens Volume Exporter Window")),
				FSlateIcon(FVolumeExporterEditorStyle::GetStyleSetName(), "VolumeExporterEditorStyle.MenuIcon")
			);
		})
	);
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MainMenuExtender);
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FVolumeExporterEditorModule, VolumeExporterEditor)