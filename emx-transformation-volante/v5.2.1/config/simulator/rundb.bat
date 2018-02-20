REM The simulator database is automatically started along with simulator
REM It is shutdown when the Desinger exits.
REM You normally would not need to run this batch file
set HOME=..\..
set CLASSPATH=.;%HOME%\lib\ext\hsqldb.jar
..\..\jre\bin\java  org.hsqldb.Server -port 1608 -database  database\volantedb