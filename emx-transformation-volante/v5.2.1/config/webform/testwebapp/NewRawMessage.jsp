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
<title>New SWIFT Message - SWIFT READER </title>
<head>
    <SCRIPT LANGUAGE="JAVASCRIPT" SRC="/scrollpos.js"></SCRIPT>
    <%@ include file="Header.html" %>
</head>

<body style="margin :0">
<center>
    <%
        String rawMessage = (String) session.getAttribute("RawMessage");
        if (rawMessage == null) {
            rawMessage = "";
        }
        String name = request.getParameter("name");
    %>

    <br>

    <FORM NAME="RawMessageForm" METHOD="POST" enctype="multipart/form-data" ACTION="NewRawMessageAction.jsp">
        <TABLE class="TableStyle" cellpadding="0" cellspacing="0" border="0" width="90%" align="center">
            <TR>
                <TD class="SwiftSequenceBackgroundStyle" style="BORDER-RIGHT: none">
                    <span class="SwiftSequenceStyle" >&nbsp;SWIFT Message</span>
                </TD>
                <TD class="SwiftSequenceBackgroundStyle" style="BORDER-Left: none;">
                    <span style="text-align:right;">&nbsp;
                    <INPUT class='LookupButtonStyle' TYPE="SUBMIT" VALUE="Submit"/>&nbsp;</span>
                </TD>
            </TR>
            <TR>
                <td colspan="2" style="padding-top:10;padding-bottom:10">
                <table  style="border:none" cellpadding="0" cellspacing="0" border="0" width="100%" align="center">
                    <tr>
                <td width="50" class="DefaultLabelColumnStyle" style="border:none"><p style="margin-left: 0px" class="DefaultLabelStyle">File</p></td>
                <td class="DefaultRendererColumnStyle" style="border:none"><input class="DefaultRendererStyle" type="file" name="InputFile" value="Browse..." size="80"/>
                </tr>
                    <tr>
                        <td style="border:none"/>
                    <td class="DefaultRendererColumnStyle" style="border:none" >
                <TEXTAREA NAME="RawMessage" class="DefaultRendererStyle" ROWS="28" STYLE="WIDTH: 100%;margin-right: 25"><%=rawMessage%></TEXTAREA><br>
                </td>
                    </tr>
                </table>
                </td>
            </TR>
            <!--
            <TR>
                <td></td>
                <TD class="DefaultRendererStyle" colspan="1">
                    <TEXTAREA style="border:none" NAME="RawMessage" ROWS="25" STYLE="WIDTH: 100%"><%=rawMessage%></TEXTAREA>
                </TD>
            </TR> -->

        </TABLE>
        <INPUT NAME="name" TYPE="HIDDEN" VALUE='<%= (name == null ? "" : name)%>'/>
    </FORM>
</center>

</body>
</html>
