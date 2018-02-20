@echo off

set LIB=${DESIGNER_HOME}\lib\runtime
set REDIST=${DESIGNER_HOME}\redist\cpp\lib\vc2010\Release
copy "%REDIST%\jexecute.exe"
copy "%REDIST%\jtransformrt.dll"
copy "%REDIST%\transformrt.dll"
set CLASSPATH=.;%LIB%\simplert.jar;%LIB%\transformrt.jar;%LIB%\resourcemanager.jar;%LIB%\generalutils.jar;#foreach($jar in ${JARFILES})${jar};#end%LIB%\..\ext\hsqldb.jar;
set JVM=${JRE_HOME}\bin\client\jvm.dll
jexecute.exe %* 