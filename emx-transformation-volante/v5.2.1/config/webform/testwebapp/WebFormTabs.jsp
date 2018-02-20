<link rel="stylesheet" type="text/css" href="tabs.css">   

<div id="tabs11">
	<ul>
	 <% { 
	    int currentPage = ((java.lang.Integer)pageContext.getAttribute("formpage")).intValue();
		String[] pageNames = (String[])pageContext.getAttribute("pagenames");
		int startPage = 1; //Don't show first page in tab
		 for (int i=startPage;i<=pageNames.length;i++){
			String pageName = pageNames[i-1];
			String pageId = "Page" + i;
		%>
			<li>
			<%	if(i == currentPage) {%>
				<div>
					<span><%= pageName%></span>
				</div>
	        <% } else {%>
	
				<volante:action name= "<%= pageId%>" >
					<span><%= pageName%></span>
				</volante:action>		
	        <% } %>
			</li>
	  <% } }%>
	</ul>
</div>
