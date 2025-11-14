# Unreal Engine Volume Exporter/Importer Plugin

This plugin for Unreal Engine allows you to export the location, rotation, scale, and size of selected `AVolume` actors to a JSON file. You can then import this file to recreate the volumes in any level.

It works on UE4.27, UE5.0, UE5.1, UE5.2, UE5.3 and UE5.4.

## How to Use

1.  Compile the plugin with your game project.
2.  Enable the "Volume Exporter" plugin in the Plugins menu.
3.  Open the plugin window by going to `Tools > Volume Exporter` in the main menu.
4.  The plugin UI will open.

### Setting up the UI

The C++ logic is complete, but you need to create the UI buttons in the Editor Utility Widget.

1.  In the Content Browser, navigate to the `VolumeExporter` content folder.
2.  Open the `VolumeExporterWidget_BP` Editor Utility Widget.
3.  In the Designer tab, add two `Button` widgets to the canvas. Name them "Export" and "Import".
4.  Select the "Export" button. In the Details panel, scroll down to the Events section and click the `+` next to `On Clicked`.
5.  This will open the Event Graph. From the new `OnClicked` node, drag a wire and search for the `ExportButtonPressed` function. Connect it.
6.  Go back to the Designer tab and select the "Import" button. Create an `OnClicked` event for it as well.
7.  In the Event Graph, connect its `OnClicked` node to the `ImportButtonPressed` function.
8.  Compile and save the blueprint.

### Exporting Volumes

1.  In the level editor, select one or more `AVolume` actors.
2.  In the Volume Exporter window, click the "Export" button.
3.  A "Save File" dialog will appear. Choose a location and name for your `.json` file.

### Importing Volumes

1.  In the Volume Exporter window, click the "Import" button.
2.  An "Open File" dialog will appear. Select the `.json` file you previously exported.
3.  The volumes will be created in the level at their saved locations and sizes.