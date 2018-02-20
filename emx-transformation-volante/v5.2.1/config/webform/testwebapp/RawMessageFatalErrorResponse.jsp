<%@ page language="java" session="true" %>
<%@ page errorPage="Error.jsp" %>
<%@ page import="com.tplus.transform.runtime.*,
                 com.tplus.transform.runtime.webforms.*,
                 com.tplus.transform.runtime.persistence.expression.*,
                 java.util.*,
                 java.io.*" %>
<%@ taglib uri="http://www.volantetech.com/taglibs/webforms" prefix="volante" %>
<html>
<META HTTP-EQUIV="Cache-control" CONTENT="no-cache, no-store, must-revalidate">
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="01 Apr 1995 01:10:10 GMT">
<title>SWIFT Message Error</title>
<head>
    <SCRIPT LANGUAGE="JAVASCRIPT" SRC="scrollpos.js"></SCRIPT>
    <%@ include file="Header.html" %>
</head>

<body style="margin :0">
<center>
    <%
        String responseStr = (String) request.getAttribute("RawMessageResponse");
        if (responseStr == null) {
            responseStr = "";
        }
        String errorStr = (String) request.getAttribute("ErrorResponse");
    %>
    <br>

    <FORM NAME="RawMessageForm">
        <TABLE class="TableStyle" cellpadding="0" cellspacing="0" border="0" width="90%" align="center">
            <TR>
                <TD class="Header" height="25">
                    <p align="left"><b>&nbsp;Response Message</b></p>
                </TD>
            </TR>
            <TR>
                <TD class="DefaultRendererStyle" colspan="2">
                    <TEXTAREA NAME="RawMessage" ROWS="20" STYLE="WIDTH: 100%;border:none"
                              readonly="true"><%=responseStr%>
                    </TEXTAREA>
                </TD>
            </TR>
            <% if (errorStr != null) { %>
            <TR>
                <TD class="Header" height="25">
                    <p align="left"><b>&nbsp;Error</b></p>
                </TD>
            </TR>
            <TR>
                <TD class="DefaultRendererStyle" colspan="2">
                    <TEXTAREA NAME="Error" ROWS="8" STYLE="WIDTH: 100%;border:none;color:red"
                              readonly="true"><%=errorStr%>
                    </TEXTAREA>
                </TD>
            </TR>
            <% } %>
        </TABLE>
    </FORM>
</center>
<center>
    <input type="button" class="LookupButtonStyle" name="Return" value="Return"
           onclick="window.open('NewRawMessage.jsp', '_self')"/>
</center>
</body>
</html>
