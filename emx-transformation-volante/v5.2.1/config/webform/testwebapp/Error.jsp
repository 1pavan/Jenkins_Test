<%@ page language="java" session="true" import="java.io.*, java.util.*, java.text.*, javax.servlet.jsp.JspException" %>

<%@ page isErrorPage="true" %>
<html>
<META HTTP-EQUIV="Cache-control" CONTENT="no-cache, no-store, must-revalidate">
<META HTTP-EQUIV="pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="01 Apr 1995 01:10:10 GMT">
<head>
<title>Error</title>
<link rel="stylesheet" href="webform.css" type="text/css">
</head>
<style>
<!--
.login-button-section {  padding: 5px; font-family: Arial,Helvetica, sans-serif;  font-weight:normal; color: #000000; background-color:#DDDDDD; } 
.noframe-framing-table  {  background-image: none; border-right: 1px solid #000000; border-bottom: 1px solid #000000; border-top: 1px solid #000000; border-left: 1px solid #000000; }
.column-head {  padding-left: .35em; padding-top: .35em; padding-bottom: .35em; font-family: Arial,Helvetica, sans-serif; font-size: 77.0%; font-weight:bold; text-align: left; color: #FFFFFF; background-color: #8691C7; background-image: none; }  
.login {  text-align: center; }
.table-text {padding-left: .5em; padding-right: .5em; font-family: Arial,Helvetica, sans-serif; font-size:70.0%; background-color: #F7F7F7; background-image: none;}
.table-text-empty {  background-color: #F7F7F7;}
-->
</style>
<title>Web Forms Error</title>

<body style="margin :0">
<%@ include file="Header.html" %>
<br><br><br><br>

<%
    String message = "";

    if (exception != null) {
		if(exception instanceof javax.servlet.jsp.JspException) {
			javax.servlet.jsp.JspException jspException = (javax.servlet.jsp.JspException)exception;
			if(jspException.getRootCause() != null) {
				exception= (Exception)jspException.getRootCause();
			} 
		}
        message = exception.getMessage();
        com.tplus.transform.util.log.Log log = com.tplus.transform.util.log.LogFactory.getLog("stm");
        if(exception instanceof RuntimeException) {
            message = "Unexpected error while processing request.<br>Detail: " + message;
            log.error("Unexpected error while processing request " + request.getRequestURI() + request.getQueryString(), exception);
        }
        else if(exception instanceof Exception) {
            message = "Unexpected error while processing request.<br>Detail: " + message;
            log.error("Unexpected error while processing request " + request.getRequestURI() + request.getQueryString(), exception);
        }
    }
    else {
        message = "<i>No message reported</i>";
    }
	if(exception != null) {
		exception.printStackTrace();
	}
%>


	<table border="0" cellpadding="0" cellspacing="0" width="100%" >
		<tr> 
			<td  class="login">   	
				<table class="noframe-framing-table" cellpadding="0" cellspacing="0" border="0" width="400" align="center">
						<tr> 
							<th colspan="2" class="column-head" scope="rowgroup"><IMG src="images/error.gif" border="0" />Error&nbsp;&nbsp;</th>
						</tr>
						<tr>
							<td class="table-text-empty" colspan="2" height="30"> 
								&nbsp;
							</td>
						</tr>
						<tr> 
							<td class="table-text" width="400" colspan="2" >
							<%= message %>
							</td>
						</tr>
						<tr>
							<td class="table-text-empty" colspan="2" height="30"> 
								&nbsp;
							</td>
						</tr>
						<tr> 
							<td class="login-button-section" valign="center" colspan="2" nowrap align="center"> 
					            <span align="center" valign="center">
									<a class="LookupButtonStyle" href= "javascript:window.history.back();">&nbsp;&nbsp;Return&nbsp;&nbsp;</a>
								</span>
							</td>
						</tr>
				</table>
			</td>
		</tr>
	</table>

<br><br>
<%@ include file="Footer.html" %>
</body>
</html>
