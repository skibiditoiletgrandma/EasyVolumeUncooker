#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "VolumeExporterEditorWidget.generated.h"

DECLARE_DELEGATE(FOnExportButtonPressed);
DECLARE_DELEGATE(FOnImportButtonPressed);

UCLASS()
class VOLUMEEXPORTEREDITOR_API UVolumeExporterEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
    FOnExportButtonPressed OnExportButtonPressedDelegate;
    FOnImportButtonPressed OnImportButtonPressedDelegate;

protected:
    UFUNCTION(BlueprintCallable, Category = "Volume Exporter")
    void ExportButtonPressed();

    UFUNCTION(BlueprintCallable, Category = "Volume Exporter")
    void ImportButtonPressed();
};