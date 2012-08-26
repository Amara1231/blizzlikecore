@ECHO OFF
@title BlizzLikeRealm
CLS
ECHO Initializing Realm (Logon-Server)...
:1
start "BlizzLike Realm" /B /MIN /WAIT blizzlike-realm.exe -c blizzlikerealm.conf
if %errorlevel% == 0 goto end
goto 1
:end