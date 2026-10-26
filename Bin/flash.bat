@ echo off
echo.

"%STM32CLT_PATH%\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe" -c port=USB1 -d %1.hex
