function computeActionURI(uri, target, action) {
    var hasRefs = uri.indexOf('?') != -1;
    uri += (hasRefs ? "&" : "?");
    return uri + "webform_target=" + target + "&webform_event=" + action;
}
function postBack(uri, formName, target, event) {
    var form = document.forms[formName];
    if (uri == null) {
        uri = form.action;
    }
    form.action = computeActionURI(uri, target, event);
    form.submit();
    return 0;
}

function addSectionElement(uri, formName, sectionName) {
    saveScrollPosition();
	return postBack(uri, formName, sectionName, "AddSectionElement");
}

function deleteSectionElement(uri, formName, sectionName) {
    saveScrollPosition();
	return postBack(uri, formName, sectionName, "DeleteSectionElement");
}

function nextSectionElement(uri, formName, sectionName, index) {
    var instanceId = sectionName + "-INDX-" + (index + 1) + "-_InstanceId";
    var elm = document.getElementById(instanceId);
    if (elm != null) {
        elm.scrollIntoView();
    }
    else {
        alert("Unable to locate next instance");
    }

}
function previousSectionElement(uri, formName, sectionName, index) {
    var prevInstance = index - 1;
    var instanceId = "";
    if (prevInstance == 0) {
        instanceId = sectionName + "_Id";
    }
    else {
        instanceId = sectionName + "-INDX-" + prevInstance + "-_InstanceId";
    }
    var elm = document.getElementById(instanceId);
    if (elm != null) {
        elm.scrollIntoView();
    }
    else {
        alert("Unable to locate previous instance");
    }

}

function submitWithAction(uri, formName, event) {
	 return postBack(uri, formName, "form", event);
}


function submitForm(uri, formName) {
     var form = document.forms[formName];
    if (uri != null) {
    form.action = uri;
    }
     form.submit();
     return 0;
}

function submit(formName) {
     var form = document.forms[formName];
    form.submit();
    return 0;
}

/////////////////////////////////////////////////////////////////////

function isCollapsedStatePrivate(elmid) {
    var elm = document.getElementById(elmid);
    if (elm != null) {
        return isCollapsedStateElementPrivate(elm);
    }
    return false;
    }
function isCollapsedStateElementPrivate(elm) {
    var imageNode = getExpandCollapseImageNode(elm);
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
function getExpandCollapseImageNode(elm) {
    var imgElms = elm.getElementsByTagName("IMG");
    if(imgElms.length > 0) {
        var imageNode = imgElms[0];
        return imageNode;
    }
    return null;
}
function setCollapsedStateElementPrivate(elm, collapsed) {
    if (elm != null) {
        var id = elm.id;
        if(id.substring(id.length-3) == "_Id") {
            var imageNode = getExpandCollapseImageNode(elm);
            if (imageNode != null) {
                if (collapsed) {
                    imageNode.src = imageNode.src.replace("collapse", "expand");
                }
                else {
                    imageNode.src = imageNode.src.replace("expand", "collapse");
                }
            }
        }
    }
    return false;
}

/*
function isCollapsedStatePrivate(elmId) {
    return getElementStatePrivate(elmId) == "collapsed";
}
function setCollapsedStatePrivate(elmId, collapsed) {
    var elm = document.getElementById(elmId);
    if (elm != null) {
        elm.style.nodestate = (collapsed ? "collapsed" : "expanded");
    }
    return false;
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

function ShowHidePrivate(sectionName) {
    var allElements = findSectionElementsPrivate(sectionName)
    var secElms = allElements[0];
    var childElms = allElements[1];
    var collapsed = false;
    for (var i = 0; i < secElms.length; ++i) {
        if (isCollapsedStateElementPrivate(secElms[i])) {
            collapsed = true;
        }
        break;
    }
    var collapse = !collapsed;
    if(!collapse) {
        ExpandCollapseElementAtLevelPrivate(sectionName, childElms,  1, collapse);
    }
    else {
        var hasChild = expandCollapseChildElementsPrivate(sectionName, childElms, collapse);
    }
    //if (!hasChild) {
    //    return true;
    //}
    for (var i = 0; i < secElms.length; ++i) {
        setCollapsedStateElementPrivate(secElms[i], collapse);
    }
    return false;
}

var tdElements = new Array(); // chached td elements
function cacheTds() {
    var tdElms = document.getElementsByTagName("td");
    var length = tdElms.length;
    if(tdElements.length == 0) {
        for (var i = 0; i < length; ++i) {
            tdElements.push(tdElms[i]);
            }
            }
        }
function findSectionElementsPrivate(sectionName) {
    var mainElements = new Array();
    var subElements = new Array();
    cacheTds();
    var secNameLength = sectionName.length;
    for (var i = 0; i < tdElements.length; ++i) {
        var tdElm = tdElements[i];
        var childElmId = tdElm.id;
        if (childElmId != null && childElmId.length > secNameLength && childElmId.indexOf(sectionName) == 0) {
            var nextChar = childElmId.charAt(secNameLength);
            if (nextChar == '-') {
                subElements[subElements.length] = tdElm;
                subElements.push(tdElm);
    }
            else if(nextChar == '_') {
                mainElements.push(tdElm);
}
            }
            }
    var allElements = new Array();
    allElements.push(mainElements);
    allElements.push(subElements);
    return allElements;
        }

function expandCollapseChildElementsPrivate(sectionName, childElements, collapse) {
    var hasChild = childElements.length > 0;
    for (var i = 0; i < childElements.length; ++i) {
        var tdElm = childElements[i];
        setElementVisiblePrivate(tdElm, !collapse);
        setCollapsedStateElementPrivate(tdElm, collapse);
    }
    return hasChild;
}

function setElementVisiblePrivate(elm, visible)
{
    var toSet = visible ? '' : 'none';
    elm.parentNode.style.display = toSet;
    elm.style.display = toSet;
}


function collapseExpandSection(uri, form, sectionName) {
    initToolTip();
        ShowHidePrivate(sectionName);
}

function collapseChildSections(uri, form, sectionName) {
    ExpandCollapseElementAtLevel(sectionName, 1, true);
}

function ExpandCollapseElementAtLevel(sectionName, level, collapse) {
    if(level == 0) {
        return ShowHidePrivate(sectionName);
    }
    var allElements = findSectionElementsPrivate(sectionName);
    var childElms = allElements[1];
    ExpandCollapseElementAtLevelPrivate(sectionName, childElms, level, collapse);
    return false;
}
function ExpandCollapseElementAtLevelPrivate(sectionName, childElms, level, collapse) {
    for (var i = 0; i < childElms.length; ++i) {
        var tdElm = childElms[i];
        var childElmId = tdElm.id;
        var foundLevel = countIndexPrivate(childElmId, sectionName.length);
        if (foundLevel > level) {
            //above this level all elements are collapsed and invisible
            setElementVisiblePrivate(tdElm, false);
            setCollapsedStateElementPrivate(tdElm, true);
        }
        else if (foundLevel == level) {
            //at this level elements are collapsed but visible
            setElementVisiblePrivate(tdElm, true);
            setCollapsedStateElementPrivate(tdElm, true);
        }
    }
    return false;
}


function ExpandCollapseElementAtLevelPrivate(sectionName, childElms, level, collapse) {
    for (var i = 0; i < childElms.length; ++i) {
        var tdElm = childElms[i];
        var childElmId = tdElm.id;
        var foundLevel = countIndexPrivate(childElmId, sectionName.length);
        if (foundLevel > level) {
            //above this level all elements are collapsed and invisible
            setElementVisiblePrivate(tdElm, false);
            setCollapsedStateElementPrivate(tdElm, true);
        }
        else if (foundLevel == level) {
            //at this level elements are collapsed but visible
            setElementVisiblePrivate(tdElm, true);
            setCollapsedStateElementPrivate(tdElm, true);
        }
    }
    return false;
}

function countIndexPrivate(childElmId, startPos) {
    var index = 0;
    while (true) {
        var matchIndex = childElmId.indexOf("-INDX", startPos);
    if(matchIndex != -1) {
            ++index;
            startPos += 5;
    }
        else {
            break;
        }
    }
    return index;
}

function expandToView(fieldName) {
    expandToViewPrivate(fieldName, false)
}
function expandToViewPrivate(fieldName, expandThis) {
    lastDollar = fieldName.lastIndexOf('-INDX');
    if (lastDollar != -1) {
        expandToViewPrivate(fieldName.substr(0, lastDollar), true);
    }
    if (expandThis) {
        var elm = document.getElementById(fieldName + "_Id");
        if (elm != null) {
            if (isCollapsedStateElementPrivate(elm)) {
                ShowHidePrivate(fieldName)
            }
            return;
        }
    }
}

function scrollToFieldOrSection(fieldName) {
    expandToView(fieldName);
    var elm = document.getElementById(fieldName);
    if (elm != null) {
        elm.scrollIntoView();
        elm.focus();
        return;
    }
    var elm = document.getElementById(fieldName + "_Id");
    if (elm != null) {
        elm.scrollIntoView();
        return;
    }
    var elm = document.getElementById(fieldName + "_RendererId");
    if (elm != null) {
        elm.scrollIntoView();
        var inputBox = elm.getElementsByTagName("input");
        if(inputBox != null && inputBox.length > 0) {
            try {
                inputBox[0].focus();
            }
            catch(e) { alert("EX")}
        }
        return;
    }
    var elm = document.getElementById(fieldName + "_LabelId");
    if (elm != null) {
        elm.scrollIntoView();
        return;
    }
    var elm = document.getElementById(fieldName + "_InstanceId");
    if (elm != null) {
        elm.scrollIntoView();
        return;
    }
    alert("Unable to locate field " + fieldName);
}

var inited = false;
function initToolTip() {
    cacheTds();
    if (!inited) {
        inited = true;
        for (var i = 0; i < tdElements.length; ++i) {
            var tdElm = tdElements[i];
            var childElmId = tdElm.id;
            childElmId = childElmId.replace("_Id", "");
            childElmId = childElmId.replace("_LabelId", "");
            childElmId = childElmId.replace("_RendererId", "");
            childElmId = childElmId.replace("FLD-", "");
            childElmId = childElmId.replace("-INDX", "");
            childElmId = childElmId.replace("-INDX", "");
            childElmId = childElmId.replace("-INDX", "");
            childElmId = childElmId.replace("-INDX", "");
            childElmId = childElmId.replace("-INDX", "");
            childElmId = childElmId.replace("-0-", ".");
            childElmId = childElmId.replace("-0-", ".");
            childElmId = childElmId.replace("-0-", ".");
            childElmId = childElmId.replace("-0-", ".");
            childElmId = childElmId.replace("-0-", ".");
            tdElm.title = childElmId;
        }
    }
}
/*
function displayFullPath(elm) {
    var matchNode = elm;
    while (matchNode != null && (matchNode.id == null || matchNode.id.substr(0,4) != "FLD$")) {
        matchNode = matchNode.parentNode;
    }
    if(matchNode.id.length > 0) {
        return matchNode.id;
    }
    else {
    }
    return "";
}
function onImageMouseDown(e) {
    var id = displayFullPath(e.target);
    if(id.substring(id.length - 3) == "_Id") {
        alert("SECTION  = " + id);
    }
}*/
var gotoFieldName;
var initCustomComponents;
function restoreScrollPosition() {
    initToolTip();
    if (undefined == gotoFieldName) {
    }
    else {
        scrollToFieldOrSection(gotoFieldName);
        //return;
    }
    if (undefined == initCustomComponents) {
    }
	else {
		initCustomComponents();
	}
}

function saveScrollPosition() {
}
