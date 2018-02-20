function getElementState(elmId) {
	var elm = document.getElementById(elmId);
	if(elm != null) {
		return elm.style.nodestate;
	}
	return "notexist";
}
function isCollapsedState(elmId) {
	return getElementState(elmId) == "collapsed";
}

function setCollapsedState(elmId, collapsed) {
	var elm = document.getElementById(elmId);
	if(elm != null) {
		elm.style.nodestate = (collapsed ? "collapsed" : "expanded");
	}
	return false;
}

function ShowHide(elmId) {
	var collapsed = isCollapsedState(elmId);
    var newState = !collapsed;
	var hasChild = expandCollapseElementWithID(elmId, newState);
	if(!hasChild) {
		return true;
	}
	
	var imageNode = document.getElementById("img" + elmId);
	if(imageNode != null) {
		if(collapsed) {
			imageNode.src = imageNode.src.replace("expand", "collapse");
		}
		else {
			imageNode.src = imageNode.src.replace("collapse", "expand");
		}
	}
	
	setCollapsedState(elmId, newState);
	return false;
}

function expandCollapseElementWithID(elmId, collapse) {
	var hasChild = false;
	var toSet = collapse? "none" : "";
	for (var i=1; i <= 10000; ++i) {
		var childElmId = elmId + "." + i;
		var childElm = document.getElementById(childElmId);
		if(childElm != null) {
			childElm.style.display=toSet;
			if(!isCollapsedState(childElmId)) {
				expandCollapseElementWithID(childElmId, collapse);
			}
			hasChild = true;
		}
		else {
			break;
		}
	}
	return hasChild;
}


function collapseExpandSection(sectionName) {
	ShowHide(sectionName + "Id");
}
