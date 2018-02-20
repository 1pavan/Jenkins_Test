@echo off
set LIB=${DESIGNER_HOME}\lib\runtime
set CLASSPATH=.;%LIB%\volante-client.jar;%LIB%\simplert.jar;%LIB%\resourcemanager.jar;%LIB%\generalutils.jar;^
#foreach($jar in ${JARFILES})
${jar};^
#end
%LIB%\..\ext\hsqldb.jar;

"${JRE_HOME}\bin\java" ${MAINCLASS} %*
