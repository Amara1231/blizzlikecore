@ECHO OFF
@title BlizzLikeCore
CLS
ECHO Initializing Core (World-Server)...
:1
start "BlizzLike Core" /B /MIN /WAIT blizzlike-core.exe -c blizzlikecore.conf
if %errorlevel% == 0 goto end
goto 1
:end