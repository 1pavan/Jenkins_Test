#!/bin/sh
LIB=${DESIGNER_HOME}/lib/runtime
CLASSPATH=.:$LIB/volante-client.jar:$LIB/simplert.jar:$LIB/transformrt.jar:$LIB/resourcemanager.jar:$LIB/generalutils.jar:#foreach($jar in ${JARFILES})${jar}:#end$LIB/../ext/hsqldb.jar:

"${JRE_HOME}/bin/java"  -classpath "$CLASSPATH" -server -mx500m -ms200m  ${MAINCLASS} $*
