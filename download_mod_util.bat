@echo OFF
echo Downloading Mod List
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://code.lumpology.com/blockstory_mod_list.txt', 'blockstory_mod_list.txt')"
echo done!
goto :eof
