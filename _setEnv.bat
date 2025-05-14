@echo off
echo Set enviroment variable ORB to current path

setx ORB "%cd%"

if /I "%ERRORLEVEL%" EQU "0" (
	set ORB
	echo.
) else (
	echo Error: ORB not set.
)

@pause