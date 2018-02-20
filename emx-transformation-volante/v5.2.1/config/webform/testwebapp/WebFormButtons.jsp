<TABLE width="100%">
  <TBODY>
    <TR>
      <TD>
        <DIV align="center">
		 <% if(readOnly != true) { %>
            <volante:action name="Submit" style="ButtonStyle"  params="task=save"> Save </volante:action>
            <volante:action name="Submit" style="ButtonStyle"  params="task=validateAndSave"> Validate and Save </volante:action>
         <% } %>
            <A class="ButtonStyle" href= "<%= returnPage%>">&nbsp;&nbsp;Return&nbsp;&nbsp;</A> 
        </DIV>
	  </TD>
	</TR>
  </TBODY>
</TABLE>

