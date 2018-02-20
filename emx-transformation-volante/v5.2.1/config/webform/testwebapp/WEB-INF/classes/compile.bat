REM Please set the 'DESIGNER_HOME' variable before compilation.
set DESIGNER_HOME=G:\Program Files\Volante704
set LIB_RUNTIME=%DESIGNER_HOME%\lib\runtime
set CLASSPATH=".;%LIB_RUNTIME%\commons-logging.jar;%LIB_RUNTIME%\generalutils.jar;%LIB_RUNTIME%\transformrt.jar;%LIB_RUNTIME%\deploy\cp.jar;"
javac.exe test\PerfMain.java
