REM Build script for engine
@ECHO OFF
SetLocal EnableDelayedExpansion

REM Get a list of all the .c files in the engine directory
SET cFilenames=
FOR /R . %%F IN (*.c) DO (
    SET cFilenames=!cFilenames! "%%F"
)

REM echo "Files:" %cFilenames%

SET assembly=engine
SET compilerFlags= -g -shared -Wvarargs -Wall -Werror
REM -Wall -Werror
SET includeFlags=-Isrc -I%VULCAN_SDK%/Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULCAN_SDK%/Lib
SET defines=-D-DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%..."
clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%