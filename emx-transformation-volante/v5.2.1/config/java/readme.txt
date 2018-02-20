EJB Deployment:
   ${DESIGNER_HOME}${SEPARATOR}lib${SEPARATOR}runtime${SEPARATOR}beanrt.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end

Simple Runtime Deployment:
   ${DESIGNER_HOME}${SEPARATOR}lib${SEPARATOR}runtime${SEPARATOR}simplert.jar
   ${DESIGNER_HOME}${SEPARATOR}lib${SEPARATOR}runtime${SEPARATOR}resourcemanager.jar
   ${DESIGNER_HOME}${SEPARATOR}lib${SEPARATOR}runtime${SEPARATOR}j2ee.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end


