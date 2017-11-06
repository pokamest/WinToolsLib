call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
msbuild /p:Configuration=DebugMD /p:Platform=Win32 /t:Rebuild
msbuild /p:Configuration=ReleaseMD /p:Platform=Win32 /t:Rebuild
msbuild /p:Configuration=DebugMD /p:Platform=x64 /t:Rebuild
msbuild /p:Configuration=ReleaseMD /p:Platform=x64 /t:Rebuild