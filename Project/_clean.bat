rmdir /S /Q .\..\.Build
rmdir /S /Q .\Bin\GCC

del .\..\Bin\*.map
del .\..\Bin\*.elf

del *.cscope_file_list
del *.depend
del *.elay