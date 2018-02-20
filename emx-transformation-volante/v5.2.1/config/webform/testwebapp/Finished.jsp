<%@ page import="com.tplus.transform.runtime.*,
                 com.tplus.transform.runtime.webforms.*,
                 java.util.*,
                 java.io.*" %>
<TABLE width="100%">
  <TBODY>
    <TR>
      <TD>
        <DIV align="left">
		 <%
             String format = request.getParameter("format");
             String modelName = format + "model";
             DataObject no = (DataObject)session.getAttribute(modelName);
             String task = request.getParameter("task");

         %>
            Completed
        </DIV>
	  </TD>
      <TD>
	   </TD>
	</TR>
  </TBODY>
</TABLE>

