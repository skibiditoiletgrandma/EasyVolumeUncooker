#include "VolumeExporterEditorWidget.h"

void UVolumeExporterEditorWidget::ExportButtonPressed()
{
    OnExportButtonPressedDelegate.ExecuteIfBound();
}

void UVolumeExporterEditorWidget::ImportButtonPressed()
{
    OnImportButtonPressedDelegate.ExecuteIfBound();
}