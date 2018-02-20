/*function getElementState(elmId) {
	var elm = document.getElementById(elmId);
	if(elm != null) {
		return elm.style.nodestate;
	}
	return "notexist";
}


function isCollapsedState(elmId) {
	return getElementState(elmId) == "collapsed";
}
*/
function isCollapsedState(elmId) {
    var imageNode = getExpandCollapseImageNode(elmId);
    if(imageNode != null) {
        if(imageNode.src.indexOf("expand") != -1) {
            return true;
        }
        if(imageNode.src.indexOf("collapse")!= -1) {
            return false;
        }
    }
    return false;
}


function getExpandCollapseImageNode(elmId) {
	var imageNode = document.getElementById("img" + elmId);
	if(imageNode != null) {
	    return imageNode;
	}
    var elm = document.getElementById(elmId);
    if (elm != null) {
        var imgElms = elm.getElementsByTagName("IMG");
        if(imgElms.length > 0) {
            var imageNode = imgElms[0];
            return imageNode;
        }
    }
    return null;
}
function setCollapsedState(elmId, collapsed) {

}
/*
function setCollapsedState(elmId, collapsed) {
	var elm = document.getElementById(elmId);
	if(elm != null) {
		elm.style.nodestate = (collapsed ? "collapsed" : "expanded");
	}
	return false;
}*/

function ShowHide(elmId) {
	var collapsed = isCollapsedState(elmId);
    //alert(elmId + "=" + collapsed);
    var newState = !collapsed;
	var hasChild = expandCollapseElementWithID(elmId, newState);
	if(!hasChild) {
		return false;
	}
	var imageNode = getExpandCollapseImageNode(elmId);
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

