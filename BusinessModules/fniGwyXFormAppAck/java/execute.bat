@echo off
set LIB=C:\Program Files (x86)\Jenkins\workspace\New-FNI\emx-transformation-volante\v5.2.1\lib\runtime
set CLASSPATH=.;%LIB%\volante-client.jar;%LIB%\volante-test.jar;%LIB%\simplert.jar;%LIB%\resourcemanager.jar;^
C:\Users\sys\Desktop\Source_Maven\BusinessModules\fniGwyXFormAppAck\java\fniGwyXFormSwfAck.jar;^
C:\Users\sys\Desktop\Source_Maven\BusinessModules\java\CommonFunctions.jar;^
C:\Program Files (x86)\Jenkins\workspace\New-FNI\emx-transformation-volante\v5.2.1\lib\runtime\transformrt.jar;^
C:\Program Files (x86)\Jenkins\workspace\New-FNI\emx-transformation-volante\v5.2.1\lib\runtime\generalutils.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\transformrt.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\generalutils.jar;^
%LIB%\..\ext\hsqldb.jar;

"C:\Program Files\Java\jdk1.8.0_73\jre\bin\java"  -server -mx500m -ms200m com.tplus.transform.runtime.external.client.Execute %*
