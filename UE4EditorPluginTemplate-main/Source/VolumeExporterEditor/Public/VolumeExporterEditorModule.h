#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;
class UVolumeExporterEditor;

class FVolumeExporterEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OpenPluginWindow();

private:
	void OnPostEngineInit();
	void RegisterMenus();

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	UVolumeExporterEditor* PluginLogic;
};