<%@ page language="java" session="true" %>
<%@ page import="com.tplus.transform.runtime.*" %>
<%@ page import="com.tplus.transform.runtime.webforms.tag.WebFormTagHelper" %>
<%@ page import="com.tplus.transform.runtime.FileInputSource,
                 com.tplus.transform.util.IOUtil,
                 org.apache.commons.fileupload.FileItemIterator,
                 org.apache.commons.fileupload.*,
                 org.apache.commons.fileupload.servlet.ServletFileUpload,
                 javax.naming.InitialContext" %>
<%@ page import="java.io.*" %>
<%@ page import="java.io.FileOutputStream" %>
<%@ page import="java.io.InputStream" %>
<%@ page import="java.util.*" %>
<%@ taglib uri="http://www.volantetech.com/taglibs/webforms" prefix="volante" %>


<%
    boolean isMultipart = ServletFileUpload.isMultipartContent(request);
    //if (isMultipart)
    byte[] rawData = null;
    String rawMessage = null;
    String messageName = null;
 {
        ServletFileUpload upload = new ServletFileUpload();
       FileItemIterator iter = upload.getItemIterator(request);
         while (iter.hasNext()) {
            FileItemStream item = iter.next();
             String name = item.getFieldName();
             if (item.isFormField()) {
                 String fieldValue = IOUtil.readStreamAsString(item.openStream());
                 if(name.equals("RawMessage")) {
                     rawMessage = fieldValue;
                 }
                 else if(name.equals("MessageName")) {
                     messageName = fieldValue;
                 }
             }
             else {
                InputStream stream = item.openStream();
                 //importFileName = item.getName();
                 rawData = IOUtil.readStream(stream);
             }
         }
    }
    if(rawData != null && rawData.length > 0) {
        rawMessage = new String(rawData);
    }

    String forwardTo = "WebForm.jsp";
%>
<%
    Message message = LookupContextFactory.getLookupContext().lookupMessage(messageName);
    DataObject messageNormalizedObject;
    Object errors ;
    if(rawMessage == null || rawMessage.length() == 0) {
        messageNormalizedObject = message.createObject();
        errors = null;
    }
    else {
        Result result = message.parse2(new StringInputSource(rawMessage), new TransformContextImpl());
        messageNormalizedObject = (DataObject)result.getOutput();
        errors = result.getExceptions();
    }
    session.removeAttribute("externalErrors");
    session.removeAttribute("processingErrors");
    if(messageNormalizedObject != null) {
        // Parse the Normalized XML
        String internalFormat = messageName;
        String modelName = internalFormat + "model";
        request.setAttribute("format", internalFormat);
        session.setAttribute(modelName, messageNormalizedObject);
        session.setAttribute("externalErrors", errors);
        session.setAttribute("WebFormReturnPage", "NewRawMessage.jsp");
        //System.out.println(errors);
    }
    else {
        forwardTo = "RawMessageFatalErrorResponse.jsp";
        request.setAttribute("RawMessageResponse", rawMessage);
        //System.out.println("Error **** " + errors);
        if (errors != null) {
            StringBuffer errMessage = new StringBuffer();
            java.util.List errorList = (java.util.List) errors;
            for (int i = 0; i < errorList.size(); i++) {
                ExceptionObject exceptionObject = (ExceptionObject) errorList.get(i);
                errMessage.append(exceptionObject.toXMLString());
                errMessage.append("\n");
                if (exceptionObject instanceof TransformException) {
                    TransformException transformException = (TransformException) exceptionObject;
                    //transformException.printStackTrace();
                }
            }
            request.setAttribute("ErrorResponse", errMessage.toString());
            //pageContext.removeAttribute("processingErrors");
        }
    }
 %>



<jsp:forward page="<%= forwardTo%>"/>

