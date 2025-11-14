#pragma once

#include "CoreMinimal.h"
#include "VolumeExporterEditorBase.h"
#include "VolumeExporterEditor.generated.h"

UCLASS()
class VOLUMEEXPORTEREDITOR_API UVolumeExporterEditor : public UVolumeExporterEditorBase
{
	GENERATED_BODY()

public:
	virtual void InitializeTheWidget() override;

private:
    void OnExportButtonPressed();
    void OnImportButtonPressed();
};