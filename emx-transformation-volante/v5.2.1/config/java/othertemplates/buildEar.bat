#set ( $APPNAME = "${Cartridge}App" )

cd ${APPNAME}\application
jar cvfM ..\..\\${APPNAME}.ear *.jar META-INF\*.*
cd..
cd..