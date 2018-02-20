@echo off

set LIB=C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime
set REDIST=C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\redist\cpp\lib\vc2010\Release
copy "%REDIST%\jexecute.exe"
copy "%REDIST%\jtransformrt.dll"
copy "%REDIST%\transformrt.dll"
set CLASSPATH=.;%LIB%\simplert.jar;%LIB%\transformrt.jar;%LIB%\resourcemanager.jar;%LIB%\generalutils.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\Messages.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT3-4_2015.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT6-7_2015.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT5_2015.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT1-2_2015.jar;C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\Messages\java\MT8-9_2015.jar;C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\swiftresources.jar;C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\transformrt.jar;C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\swiftrt.jar;C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\generalutils.jar;%LIB%\..\ext\hsqldb.jar;
set JVM=C:\Program Files\Java\jdk1.8.0_73\jre\bin\client\jvm.dll
jexecute.exe %* 