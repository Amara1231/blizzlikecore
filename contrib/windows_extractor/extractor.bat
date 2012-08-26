@echo off
color 0b
:panel
cls
echo.
echo ///////////////////////////////////////////////
echo /// BlizzLike Core dbc/maps/vmaps extractor ///
echo ///////////////////////////////////////////////
echo.
echo Extract dbc/maps [1]
echo Extract vmaps	 [2]
echo Exit		 [0]
echo.
set /p opc=what is your option? 
cls
if "%opc%" == "1" goto 1_extract_dbc_maps
if "%opc%" == "2" goto 2_extract_vmaps
if "%opc%" == "0" goto exit
goto panel
:1_extract_dbc_maps
map_extractor.exe
if %ERRORLEVEL% == 0 (cls
echo.
echo.
echo Process done! 
echo Copy dbc/maps folders to the core main directory.
echo Press any key to panel . . .
pause>nul
goto panel)
echo.
echo.
echo Process finalized with errors.
echo Press any key to panel . . .
pause>nul
goto panel
:2_extract_vmaps
if exist buildings (cls
echo.
echo.
echo The buildings folder already exist do you want to delete it?
echo if YES hit Enter to continue if no CLOSE the program now! . . .
pause>nul
DEL /S /Q buildings)
vmap_extractor.exe
md vmaps
vmap_assembler.exe buildings vmaps
if %ERRORLEVEL% == 0 (cls
echo.
echo.
echo Process done! 
echo Copy vmaps folder to the core main directory.
echo Press any key to panel . . .
pause>nul
goto panel)
echo.
echo.
echo Process finalized with errors.
echo Press any key to panel . . .
pause>nul
goto panel
:exit