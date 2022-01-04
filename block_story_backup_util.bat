@echo OFF
echo Creating Block Story Restore Point.
md backup
copy "C:\Program Files (x86)\Steam\steamapps\common\BlockStory\Block Story_Data\Managed\Blocksters.Terrain.dll" "backup\Blocksters.Terrain.dll"
echo Restore Point Created, type the 'restore' command to remove mods at any time
goto :eof
