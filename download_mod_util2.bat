@echo OFF
echo Downloading Mod List
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://code.lumpology.com/BlockStoryMods/Defaut-13.1/Blocksters.Terrain.dll', 'Blocksters.Terrain.dll')"
md Defaut-13.1
move "Blocksters.Terrain.dll" "Defaut-13.1\Blocksters.Terrain.dll"
echo done!
goto :eof
