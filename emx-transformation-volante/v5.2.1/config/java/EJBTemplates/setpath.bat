@echo off
set ORION_DIR=D:\orion1.6
if NOT EXIST %ORION_DIR%\orion.jar goto wrongdir

:run
set CLASSPATH=.;%ORION_DIR%\orion.jar;%ORION_DIR%\jndi.jar;%ORION_DIR%\ejb.jar;lib\log4j.jar;..\application\transformrt.jar;..\application\generalutils.jar;..\client\cp.jar;

goto finish

:wrongdir
echo The ORION_DIR environment variable is incorrect. Edit setpath.bat script to set this environment variable.
goto finish


:finish
