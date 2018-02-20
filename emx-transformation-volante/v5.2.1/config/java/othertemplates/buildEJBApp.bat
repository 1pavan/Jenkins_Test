set LIB="${DESIGNER_HOME}/lib/runtime
#set ( $APPDIR = "${Cartridge}App" )
mkdir ${APPDIR}
cd ${APPDIR}
mkdir application\META-INF
set APPNAME=${APPDIR}
mkdir client


cd..
REM copy generated Jars 
#foreach($jar in ${JARFILES})
copy $jar ${APPDIR}\application;
#end

copy %LIB%\asciifixedrt.jar" ${APPDIR}\application
copy %LIB%\asciirt.jar" ${APPDIR}\application\
copy %LIB%\fcsrt.jar" ${APPDIR}\application
copy %LIB%\fixrt.jar" ${APPDIR}\application
copy %LIB%\realrt.jar" ${APPDIR}\application
copy %LIB%\siaccanonicalrt.jar" ${APPDIR}\application
copy %LIB%\swiftrt.jar" ${APPDIR}\application
copy %LIB%\swiftresources.jar" ${APPDIR}\application
copy %LIB%\universalrt.jar" ${APPDIR}\application
copy %LIB%\xmlrt.jar" ${APPDIR}\application




REM copy dependent Jars (format plugins) 
#foreach($jar in ${DEPENDENTJARS})
copy $jar ${APPDIR}\application;
#end


REM copy standard Jars 
copy %LIB%\sqlutils.jar" ${APPDIR}\application
copy %LIB%\beanrt.jar" ${APPDIR}\application
copy %LIB%\transformrt.jar" ${APPDIR}\application
copy %LIB%\transformbeans.jar" ${APPDIR}\application
copy %LIB%\jakarta-regexp.jar" ${APPDIR}\application
copy %LIB%\generalutils.jar" ${APPDIR}\application


copy %LIB%\deploy\cp.jar" ${APPDIR}\client
copy application.xml ${APPDIR}\application\META-INF


REM Apply paramters to EJB templates
call "${DESIGNER_HOME}\tools\template.bat" "${DESIGNER_HOME}\config\java\EJBTemplates\jndi.properties" ${APPDIR}\client\jndi.properties "APPNAME=${APPDIR}"
call "${DESIGNER_HOME}\tools\template.bat" "${DESIGNER_HOME}\config\java\EJBTemplates\execute.bat" ${APPDIR}\client\execute.bat
call "${DESIGNER_HOME}\tools\template.bat" "${DESIGNER_HOME}\config\java\EJBTemplates\setpath.bat" ${APPDIR}\client\setpath.bat
set CART_DIR=%~dp0%APPNAME%\application
call "${DESIGNER_HOME}\tools\template.bat" "${DESIGNER_HOME}\config\java\EJBTemplates\ToDo.html" ${APPDIR}\ToDo.html  "APPNAME=${APPDIR}" "CARTDIR=%CART_DIR%"