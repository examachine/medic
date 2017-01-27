REM SET CLASSGENSCRIPT=..\classgen\generate-classes.BAT

echo autogen script running
rem echo %CLASSGENSCRIPT%
echo %1 Build
..\classgen\generate-classes.BAT %1
