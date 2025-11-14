#include "VolumeExporterEditorBase.h"
#include "VolumeExporterEditorWidget.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/ObjectLibrary.h"

UVolumeExporterEditorBase::UVolumeExporterEditorBase()
{
	
}

void UVolumeExporterEditorBase::SetEditorWidget(UVolumeExporterEditorWidget* InEditorWidget)
{
	EditorWidget = InEditorWidget;
}

void UVolumeExporterEditorBase::CreateTheWidget()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
#if ((ENGINE_MAJOR_VERSION == 5) && (ENGINE_MINOR_VERSION >= 1))
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(FSoftObjectPath("/VolumeExporter/VolumeExporterWidget_BP.VolumeExporterWidget_BP"));
#else
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath("/VolumeExporter/VolumeExporterWidget_BP.VolumeExporterWidget_BP");
#endif
	UObject* ObjectToEdit = AssetData.GetAsset();
	UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(ObjectToEdit);

	if (WidgetBlueprint)
	{
		if (WidgetBlueprint->GeneratedClass->IsChildOf(UVolumeExporterEditorWidget::StaticClass()))
		{
			UVolumeExporterEditorWidget* CreatedWidget = CreateWidget<UVolumeExporterEditorWidget>(WidgetBlueprint);
			if (CreatedWidget)
			{
				SetEditorWidget(CreatedWidget);
				InitializeTheWidget();
			}
		}
	}
}

void UVolumeExporterEditorBase::InitializeTheWidget()
{
}