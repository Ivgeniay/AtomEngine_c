:start
echo Choose:
echo 1. open notepad
echo 2. exit
set /p choice=Your choiceр:
if %choice%==1 goto open_notepad
if %choice%==2 goto exit
goto start

:open_notepad
echo "opening notepad"
goto start

:exit
echo "exiting"
exit