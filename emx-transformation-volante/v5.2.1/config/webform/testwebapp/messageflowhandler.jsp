<%@ page language="java"
         import="com.tplus.transform.runtime.*, com.tplus.transform.runtime.formula.FormatFunctions, java.util.*, com.tplus.transform.util.*, test.PerfMain" %>
<%@ page errorPage="Error.jsp" %>
<%
    LookupContext lookupContext = LookupContextFactory.getLookupContext();
    String messageFlowName = request.getParameter("MessageFlowName");
    if (messageFlowName != null && !messageFlowName.equals("")) {
        MessageFlow messageFlow = lookupContext.lookupMessageFlow(messageFlowName);
        DataObject inputDataObject = messageFlow.createInputDataObject();
        for (int i = 0; i < inputDataObject.getFieldCount(); ++i) {
            String fieldName = inputDataObject.getFieldName(i);
            String fieldType = inputDataObject.getFieldType(i);
            String fieldValueStr = request.getParameter(fieldName);
            Object fieldVal;
            if (fieldType.equals(DesignerTypes.DESIGNER_BINARY_TYPE)) {
                fieldVal = fieldValueStr.getBytes();
            }
            if (fieldType.equals(DesignerTypes.DESIGNER_RAW_MESSAGE_TYPE)) {
                fieldVal = new StringInputSource(fieldValueStr);
            }
            else {
                fieldVal = Parsing.toRuntimeObject(fieldValueStr, fieldType);

            }
            inputDataObject.setField(i, fieldVal);
        }
        PerfMain client = new PerfMain();
        Map fieldAndValueMap = new SequencedHashMap();
        Map fieldAndTypeMap = new SequencedHashMap();
        client.simpleTesting(messageFlow, inputDataObject, fieldAndValueMap, fieldAndTypeMap);
%>
<HTML>
<head>
    <title>New Message</title>
    <META HTTP-EQUIV="Cache-control" CONTENT="no-cache, no-store, must-revalidate">
    <META HTTP-EQUIV="pragma" CONTENT="no-cache">
    <META HTTP-EQUIV="Expires" CONTENT="01 Apr 1995 01:10:10 GMT">
    <link rel="stylesheet" type="text/css" href="webform.css">
</head>

<BODY style='margin :5' ONLOAD='return populateOutputElements();'>
<FORM NAME='MessageFlowOutputForm'>
    <TABLE BORDER='0' ROWSPACEING='20' WIDTH='100%'>
        <%
            String perfTest = request.getParameter("PerfTest");
            if (perfTest != null && !perfTest.equals("")) {
                long transformations = 0; //client.perfTesting(messageFlow, inputDataObject);
        %>
        <TR>
            <TD WIDTH='100%'>Performance:&nbsp;<FONT COLOR="#0000FF" FACE='Courier'><%= transformations %>&nbsp;Transformations/Sec</FONT>
            </TD>
        </TR>
        <%
            }
            List outputFieldNames = new ArrayList(fieldAndTypeMap.keySet());
            for (int i = 0; i < outputFieldNames.size(); ++i) {
                String outputFieldName = ((String) outputFieldNames.get(i)).replace('.', '_');
                String outputFieldType = (String) fieldAndTypeMap.get(outputFieldName);
                if (outputFieldType == null) {
                    continue;
                }

        %>
        <TR>
            <TD WIDTH='100%' ><span class='fieldheading'><%= outputFieldName%>&nbsp;<FONT style='font-weight:normal'>(<%= outputFieldType%>)</FONT><BR></span>
                <%
                    if (outputFieldType.equals(DesignerTypes.DESIGNER_BINARY_TYPE) || outputFieldType.equals(DesignerTypes.DESIGNER_RAW_MESSAGE_TYPE)) {
                %>
                <TEXTAREA class='fieldcontent' readonly="readonly" NAME='<%= outputFieldName%>' ROWS='18' STYLE='WIDTH: 100%'></TEXTAREA>
                <%
                }
                else {
                %>
                <INPUT class='fieldcontent' readonly="readonly" NAME='<%= outputFieldName%>' TYPE='text' STYLE='WIDTH: 100%'/>
                <%
                    }
                %>
            </TD>
        </TR>
        <%
            }
        %>
    </TABLE>
</FORM>
</BODY>
<SCRIPT LANGUAGE="javascript">
    <%= "<!--"%>
    function populateOutputElements() {
    <%

                for (int i=0; i < outputFieldNames.size(); ++i) {
                    String outputFieldName = ((String)outputFieldNames.get(i)).replace('.','_');
                    String outputFieldType = (String)fieldAndTypeMap.get(outputFieldName);
                    Object outputFieldValue = fieldAndValueMap.get(outputFieldName);
                    String outputFieldValueName = outputFieldName + "Value";
                    if (outputFieldType == null) {
                        continue;
                    }
                    String outputVal="";
                    if(outputFieldValue != null ) {
                        if (outputFieldType.equals(DesignerTypes.DESIGNER_BINARY_TYPE)) {
                            outputVal = new String((byte[])outputFieldValue);
                        }
                        else if (outputFieldType.equals(DesignerTypes.DESIGNER_RAW_MESSAGE_TYPE)) {
                           outputVal = ((RawMessage)outputFieldValue).getAsString();
                        }
                        else {
                            outputVal = Parsing.runtimeObjectToString(outputFieldValue, outputFieldType);
                        }
                    }
                   outputVal = StringUtils.replace(outputVal, "\r\n", "CRLF");
                   outputVal = StringUtils.replace(outputVal, "\n", "CRLF");
    %>
        var <%= outputFieldValueName%> = '<%=outputVal%>';
        document.forms["MessageFlowOutputForm"].elements["<%= outputFieldName%>"].value =<%= outputFieldValueName%>.split('CRLF').join('\n');
    <%
                }
    %>
    }
    <%= "//-->"%>
</SCRIPT>
</HTML>
<%
}
else {
%>
<HTML>
<TITLE>Performance Test Page</TITLE>
<META HTTP-EQUIV="Cache-control" CONTENT="no-cache, no-store, must-revalidate">
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="01 Apr 1995 01:10:10 GMT">
<HEAD>

    <SCRIPT LANGUAGE="javascript">
        <!--
        function updateElements(doc, parameters) {
            for (i = 0; i < parameters.length; ++i) {
                parameter = parameters[i];
                parameterInfo = parameter.split("=");
                parameterName = parameterInfo[0];
                parameterType = parameterInfo[1];
                parameterValue = "";
                doc.writeln("<TR>");
                doc.writeln("<TD><span class='fieldheading'>");
                doc.writeln(parameterName + "<FONT style='font-weight:normal'>&nbsp;(" + parameterType + ")</FONT>" + "</span><BR>");
                if (parameterType == "Binary" || parameterType == "RawMessage") {
                    doc.writeln("<TEXTAREA class='fieldcontent' NAME='" + parameterName + "' ROWS='18' STYLE='WIDTH: 100%'>" + parameterValue + "</TEXTAREA>");
                }
                else {
                    doc.writeln("<INPUT class='fieldcontent' NAME='" + parameterName + "' TYPE='text' STYLE='WIDTH: 100%' VALUE='" + parameterValue + "' />");
                }
                doc.writeln("</TD>");
                doc.writeln("</TR>");
            }
        }

        function prepareInputPanel(messageFlowInfo) {
            messageFlowInfoItems = messageFlowInfo.split(";");
            messageFlowName = messageFlowInfoItems[0];
            inputParameters = messageFlowInfoItems[1].split(",");
            doc = top.frames["InputFrame"].document;
            doc.writeln("<HTML>");
            doc.writeln("<HEAD>");
            doc.writeln("<link rel='stylesheet' type='text/css'  href='webform.css'>");
            doc.writeln("</HEAD>");
            doc.writeln("<BODY style='margin :2px'>");
            doc.writeln("<FORM NAME='MessageFlowInputForm' METHOD='POST' ACTION='messageflowhandler.jsp' TARGET='OutputFrame'>");
            doc.writeln("<INPUT NAME='MessageFlowName' VALUE='" + messageFlowName + "' TYPE='hidden' />");
            doc.writeln("<INPUT NAME='PerfTest' TYPE='hidden' />");
            doc.writeln("<TABLE BORDER='0' ROWSPACEING='20' WIDTH='100%'>");
            updateElements(doc, inputParameters);
            doc.writeln("</TABLE>");
            doc.writeln("</FORM>");
            doc.writeln("</BODY></HTML>");
            doc.close();
        }

        function submitInputForm() {
            /*
            if (document.forms["MessageFlowHandler"].elements["PerfTest"].checked) {
                top.frames["InputFrame"].document.forms["MessageFlowInputForm"].elements["PerfTest"].value = "required";
            }
            else {
                top.frames["InputFrame"].document.forms["MessageFlowInputForm"].elements["PerfTest"].value = "";
            }*/
            return top.frames["InputFrame"].document.forms["MessageFlowInputForm"].submit();
        }
        //-->
    </SCRIPT>
</HEAD>
<BODY style='background:#ECE9D8;margin:0px' >
<%@ include file="Header.html" %>
<FORM NAME="MessageFlowHandler">
    <TABLE border="0">
        <TR>
            <TD ALIGN="left" style='padding-left:10px;padding-right:15px' class='fieldheading' >Message Flow</TD>
            <TD ALIGN="left">
                <SELECT class="fielddisplay" NAME="MessageFlowList" ONCHANGE='return prepareInputPanel(this.value);'>
                    <%
                        String[] messageFlows = lookupContext.getMessageFlows();
                        for (int i = 0; i < messageFlows.length; ++i) {
                            MessageFlow messageFlow = lookupContext.lookupMessageFlow(messageFlows[i]);
                            DataObject inputDataObject = messageFlow.createInputDataObject();
                            StringBuffer inputParameters = new StringBuffer("");
                            for (int j = 0; j < inputDataObject.getFieldCount(); ++j) {
                                String fieldName = inputDataObject.getFieldName(j);
                                String fieldType = inputDataObject.getFieldType(j);
                                if (j > 0) {
                                    inputParameters.append(",");
                                }
                                inputParameters.append(fieldName);
                                inputParameters.append("=");
                                inputParameters.append(fieldType);
                            }
                    %>
                    <OPTION VALUE='<%= (messageFlows[i] + ";" + inputParameters)%>' <%= (messageFlows[i].equals(messageFlowName) ? "SELECTED" : "")%>><%= messageFlows[i] %>
                    </OPTION>
                    <%
                        }
                    %>
                </SELECT>
            </TD>
            <TD COLSPAN="2">
                <INPUT TYPE="button" class="fielddisplay" VALUE="Submit" ONCLICK='return submitInputForm();'/>&nbsp;&nbsp;
                <!--<INPUT TYPE="checkbox"  NAME="PerfTest"><span class="fielddisplay" style='font-weight:normal;'>Performance Testing</span> -->
            </TD>
        </TR>
    </TABLE>
</FORM>
<SCRIPT LANGUAGE='javascript'>
    <!--
    prepareInputPanel(document.forms["MessageFlowHandler"].elements["MessageFlowList"].value);
    //-->
</SCRIPT>
</BODY>
</HTML>
<%
    }
%>