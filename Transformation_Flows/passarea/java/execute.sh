#!/bin/sh
LIB=C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1/lib/runtime
CLASSPATH=.:$LIB/volante-client.jar:$LIB/simplert.jar:$LIB/volante-test.jar:$LIB/transformrt.jar:$LIB/resourcemanager.jar:C:\Users\sys\Desktop\Source_Maven\Transformation_Flows\passarea\java\Pass_Areas.jar:C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\asciifixedrt.jar:C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\universalrt.jar:C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\transformrt.jar:C:\Users\sys\Desktop\Source_Maven\emx-transformation-volante\v5.2.1\lib\runtime\generalutils.jar:$LIB/../ext/hsqldb.jar:

"C:\Program Files\Java\jdk1.8.0_73\jre/bin/java"  -classpath "$CLASSPATH" -server -mx500m -ms200m com.tplus.transform.runtime.external.client.Execute $*
