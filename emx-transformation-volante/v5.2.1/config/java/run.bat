REM Deprecated in 3.0 use execute.bat
set LIB=${designer.home}/lib/runtime
set CLASSPATH=.;%LIB%\simplert.jar;%LIB%\..\ext\hsqldb.jar;#foreach($jar in ${JARFILES})${jar};#end

"${JRE_HOME}\bin\java" Main %1
