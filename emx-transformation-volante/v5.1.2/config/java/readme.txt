EJB Deployment:
   ${DESIGNER_HOME}\lib\runtime\beanrt.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end

Simple Runtime Deployment:
   ${DESIGNER_HOME}\lib\runtime\simplert.jar
   ${DESIGNER_HOME}\lib\runtime\resourcemanager.jar
   ${DESIGNER_HOME}\lib\runtime\j2ee.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end


