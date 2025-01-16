cd /d "%~dp0"
make -f micropython_embed.mk clean
make -f micropython_embed.mk
rmdir /S /Q build-embed
