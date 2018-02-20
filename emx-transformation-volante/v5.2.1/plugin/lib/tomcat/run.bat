set TOMLIB=lib
set CP=.;%TOMLIB%\catalina.jar;%TOMLIB%\volante-jta.jar;%TOMLIB%\catalina-optional.jar;%TOMLIB%\commons-el.jar;%TOMLIB%\commons-el.jar;%TOMLIB%\commons-logging-1.1.1.jar;%TOMLIB%\commons-modeler-2.0.1.jar;%TOMLIB%\jasper-compiler.jar;%TOMLIB%\jasper-compiler-jdt.jar;%TOMLIB%\jasper-runtime.jar;%TOMLIB%\jsp-api.jar;%TOMLIB%\naming-factory.jar;%TOMLIB%\naming-resources.jar;%TOMLIB%\servlet-api.jar;%TOMLIB%\servlets-default.jar;%TOMLIB%\tomcat-coyote.jar;%TOMLIB%\tomcat-http.jar;%TOMLIB%\tomcat-util.jar;%TOMLIB%\jmxri.jar
java -classpath %CP% EmbeddedTomcat
