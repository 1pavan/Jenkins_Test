@echo off
set LIB=C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime
set CLASSPATH=.;%LIB%\volante-client.jar;%LIB%\volante-test.jar;%LIB%\simplert.jar;%LIB%\resourcemanager.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\Messages.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT3-4_2015.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT6-7_2015.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT5_2015.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT1-2_2015.jar;^
C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT8-9_2015.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\swiftresources.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\transformrt.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\swiftrt.jar;^
C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\generalutils.jar;^
%LIB%\..\ext\hsqldb.jar;

"C:\Program Files\Java\jdk1.8.0_73\jre\bin\java"  -server -mx500m -ms200m com.tplus.transform.runtime.external.client.Execute %*
