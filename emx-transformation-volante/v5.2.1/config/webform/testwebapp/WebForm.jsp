<%@ page pageEncoding="UTF-8" language="java" session="true" contentType="text/html; charset=UTF-8" %>
<%@ page import="com.tplus.transform.runtime.LookupContext,
                 com.tplus.transform.runtime.*,
                 com.tplus.transform.runtime.webforms.LookupHelper" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ taglib uri="http://www.volantetech.com/taglibs/webforms" prefix="volante" %>
<%
    request.setCharacterEncoding("UTF-8");
    %>
<html>
<head>
    <title>WebForm </title>
<META HTTP-EQUIV="Cache-control" CONTENT="no-cache, no-store, must-revalidate">
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="01 Apr 1995 01:10:10 GMT">
    <META http-equiv="Content-Type" content="text/html;charset=UTF-8">  

    <SCRIPT LANGUAGE="JAVASCRIPT" type="text/javascript" SRC="scrollpos.js"></SCRIPT>
    <SCRIPT LANGUAGE="JAVASCRIPT" type="text/javascript" SRC="volantescripts.js"></SCRIPT>
    <SCRIPT LANGUAGE="JAVASCRIPT" type="text/javascript" SRC="datescripts.js"></SCRIPT>
    <style type="text/css">
        <!--
        .ButtonStyle {
            font-family: Verdana, Arial, sans-serif;
            font-weight: bold;
            font-size: 10px;
            color: white;
            padding: 3px;
            text-decoration: none;
            BACKGROUND-COLOR: #006699;
            border-style: double;
        }


        .LegendStyle {
            font-family: Arial, sans-serif;
            font-weight: bold;
            font-size: 11px;
            color: white;
            padding: 2px;
            text-decoration: none;
            border-style: hidden;
            BACKGROUND-COLOR: #006699;
        }

        -->
    </style>

</head>

<body onload="restoreScrollPosition();" style="margin :0">
<center>

<%
    String requestURI = "WebForm.jsp";
    boolean readOnly = false;
    boolean newMessage = false;
    //session.removeAttribute("externalErrors");
    //session.removeAttribute("processingErrors");
    String format = request.getParameter("format");
    if(format == null) {
        format = (String)request.getAttribute("format");        
    }
    String returnPage = "";
    try {
        String modelName = format + "model";
        LookupContext cxt = LookupHelper.getLookupContext();
        DataObject obj = (DataObject) session.getAttribute(modelName);
        Message message = cxt.lookupMessage(format);
        if (obj == null) {
            obj = message.createObject();
            session.setAttribute(modelName, obj);
        }
%>
<br>
<volante:webform format="<%= format %>" checkMandatoryFields="false" errorStyle="tooltippopup"
                 modelRef="<%= modelName%>" requestURI="<%= requestURI%>"
                 readOnly="<%= readOnly%>" hideNullFields="<%= readOnly%>">


    <% if (!completed.booleanValue()) { %>
    <volante:adderrors errorRef="externalErrors" scope="session"/>
    <% }
    else {
        //System.out.println("Submitting NO");
    %>
    <volante:clearerrors errorRef="externalErrors" scope="session"/>
    <volante:clearerrors errorRef="processingErrors" scope="session"/>
    <%
        List validationErrors = new ArrayList();
        DataObject dataObject = (DataObject) session.getAttribute(modelName);
        Result res = message.validate2(dataObject, new TransformContextImpl());
        validationErrors.addAll(res.getExceptions());
        res = message.serializeMessage2(dataObject, new TransformContextImpl());
        RawMessage mes = (RawMessage)res.getOutput();
        if(mes != null) {
            request.setAttribute("RawMessageResponse", mes.getAsString());
            System.out.println(mes.getAsString());
        }
        validationErrors.addAll(res.getExceptions());
        if(validationErrors.size() > 0) {
            request.setAttribute("ErrorResponse", validationErrors.toString());
            session.setAttribute("processingErrors", validationErrors);
        }
        else {
            session.removeAttribute("processingErrors");
        }
       %>

    <% if("validateAndSave".equals(request.getParameter("task"))) {
        if (session.getAttribute("processingErrors") == null) {
    %>
    <jsp:forward page="TestRawMessageResponse.jsp"/>
    <% }
    }
    else  { %>
        <jsp:forward page="TestRawMessageResponse.jsp"/>
    <% }
    }
    %>

    <volante:adderrors errorRef="processingErrors" scope="session"/>

    <!--- Using table for laying out buttons, tabs, error messages & form -->
    <table width="90%" cellspacing="0" cellpadding="0" border="0">

        <!--- display button at top -->
        <!--- display a row of tabs-->

        <!--- display top level errors -->
        <tr>
            <td>
                <volante:displayerrors/>
            </td>
        </tr>
        <!--- display the  form -->
        <tr>
            <td>
                <br>
                <%@ include file="WebFormTabs.jsp" %>
            </td>
        </tr>
        <tr>
            <td style="BORDER:#000000 1px solid;">

                    <volante:display/>
            </td>
        </tr>
        <!--- display button at bottom -->
        <tr>
            <td>
                <br>
                <%@ include file="WebFormButtons.jsp" %>
            </td>
        </tr>

    </table>

</volante:webform>
<%
    }
    catch (Throwable e) {
        e.printStackTrace();
    }
    //System.out.println(((NormalizedObject)session.getAttribute(modelName)).toXMLString());
%>
</center>

</body>
</html>
