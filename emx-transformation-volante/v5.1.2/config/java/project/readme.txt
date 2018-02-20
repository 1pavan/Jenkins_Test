This document list all the jars that are needed for the project.

EJB Deployment:

   Deploy the all the cartridge jars as EJB modules; all other jars as dependent libs

   ${DESIGNER_HOME}\lib\runtime\beanrt.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end

----------------------------------------------------------------------------------------------

Simple Runtime Deployment:
   ${DESIGNER_HOME}\lib\runtime\simplert.jar
   ${DESIGNER_HOME}\lib\runtime\resourcemanager.jar
   ${DESIGNER_HOME}\lib\runtime\j2ee.jar
#foreach($jar in ${JARFILES})
   ${jar}
#end


