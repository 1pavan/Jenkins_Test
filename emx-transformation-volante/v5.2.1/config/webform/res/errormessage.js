function newErrorMessageWindow(formName, errorMessage) {
    //alert(errorMessage);
    mywindow = open('errormessage.html', formName, 'resizable=yes,width=500,height=300,top=100 left=100');
    mywindow.location.href = 'errormessage.html';
    if (mywindow.open) {
        mywindow.focus();
    }
    while(errorMessage.search(' ') != -1) {
    	errorMessage = errorMessage.replace(" ", "&nbsp;");
	}
    var modifiedErrorMessage = "";
    var errors = errorMessage.split("<br>");
    for (var i = 0; i < errors.length; i++) {
        modifiedErrorMessage = modifiedErrorMessage + errors[i] + "\r\n";
    }

    while(modifiedErrorMessage.search('<') != -1) {
    	modifiedErrorMessage = modifiedErrorMessage.replace("<", "&lt;");
	}
    while(modifiedErrorMessage.search('>') != -1) {
        modifiedErrorMessage = modifiedErrorMessage.replace(">", "&gt;");
    }
    while(modifiedErrorMessage.search('&apos;') != -1) {
        modifiedErrorMessage = modifiedErrorMessage.replace("&apos;", "'");
    }
    mywindow.document.write('<HTML><BODY leftmargin="0" topmargin="0" marginwidth="0" marginheight="0">')
    mywindow.document.write('<TITLE> Error Message </TITLE>')
    //mywindow.document.write('<TEXTAREA NAME="ErrorMessage"  readOnly="true" STYLE="HEIGHT: 100%; WIDTH: 100%;color: red">'+modifiedErrorMessage+'</TEXTAREA>');
    //alert(modifiedErrorMessage);
    mywindow.document.write('<pre>');
    mywindow.document.write('<font color="red">');
    mywindow.document.write(modifiedErrorMessage);
    mywindow.document.write('</pre>');
	mywindow.document.write('</font>');
    mywindow.document.write('</BODY></HTML>')
}

