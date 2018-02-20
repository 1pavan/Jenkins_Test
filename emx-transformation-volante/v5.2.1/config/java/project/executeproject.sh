#!/bin/sh
LIB=${DESIGNER_HOME}/lib/runtime
CLASSPATH=.:$LIB/volante-client.jar:$LIB/volante-test.jar:$LIB/simplert.jar:$LIB/resourcemanager.jar:#foreach($jar in ${JARFILES})${jar}:#end$LIB/../ext/hsqldb.jar:

"${JRE_HOME}/bin/java"  -classpath "$CLASSPATH" -server -mx500m -ms200m com.tplus.transform.runtime.external.client.Execute $*
