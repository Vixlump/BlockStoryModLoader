@echo OFF
echo Creating Block Story Restore Point.
md backup
copy "backup\Blocksters.Terrain.dll" "C:\Program Files (x86)\Steam\steamapps\common\BlockStory\Block Story_Data\Managed\Blocksters.Terrain.dll"
echo Block Story has restored from the backup
goto :eof
