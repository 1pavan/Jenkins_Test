set HOME=..\..
set CLASSPATH=.;%HOME%\lib\ext\hsqldb.jar
..\..\jre\bin\java  org.hsqldb.util.DatabaseManager -driver org.hsqldb.jdbcDriver -url jdbc:hsqldb:hsql://localhost:1608 -user sa -password "" %1 %2 %3 %4 %5 %6 %7 %8 %9
