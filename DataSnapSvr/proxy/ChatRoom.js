﻿//when the web page is left (either by navigating to another page, or closing the tab/window, the session will be closed, terminating the callback
window.onbeforeunload = stopChannel;
var SMessageChannel="FSMessage";
var SMsgCallback="FSMessageCallBack";
var AccbookID = "0";
var loginCode = "";
var loginpassword = "";
var channel = null;
var userID = null;
var cachedUsers = null;
var userName = null;
//used to get the user list, as well as to notify and broadcast. NOTE: notify and broadcast functions off of DSAdmin
//are restricted so the user can not execute them. This is to enforce the message format for messages being sent,
//and to prevent one user from making it look like a message came from a different user.
var LoginUserMethods = null;
var MessageManage = null;
//var authentication=null;
//default values here aren't required, but placed here anyway for sake of showing functionality
var connectionInfo = null;
//{"dscontext":"datasnap", "restcontext":"rest"};

//wait a short time and then load the chat room. This wait prevents some browsers (Chrome, safari)
//from constantly showing the web page status as loading.
setTimeout("loadChatRoom()", 127);
//生成guid
function newGuid()
{
    var guid = "";
    for (var i = 1; i <= 32; i++){
      var n = Math.floor(Math.random()*16.0).toString(16);
      guid +=   n;
      if((i==8)||(i==12)||(i==16)||(i==20))
        guid += "-";
    }
    return guid;
}
/*
 * Set 'nullIfError' to true here if you want null to be returned on an error instead of any error
 * message the server may have send you. If you don't specify a value, it will default to false.
 */
function getUserList(nullIfError) {
  nullIfError = nullIfError == null ? false : nullIfError;

  //attempt to get the list of users. If authentication failed this call will fail
  var resultObj = LoginUserMethods.GetUserList();

  if (resultObj != null && resultObj.result != null)
  {
    //authentication passed, there is a result!
    return resultObj.result;
  }

  //authentication failed, you'll need to try another user name.
  return nullIfError ? null : resultObj;
};

/*
 * Prompt for a user name, connect to the server, populate the list of users and register the messaging callback.
 */
function loadChatRoom()
{
   //create a new isntance of the LoginUserMethods proxy to the server methods class.
    //this will use the latest connection information, with the encoded user name
  openLoginDialog();
 // connectionInfo = getAuth(loginCode, loginpassword);
 // LoginUserMethods = new TLoginUser(connectionInfo);
  //bring up a dialog for the user to choose a user name.
  //the dialog will continue to come up until the user either cancels or enters a valid user name.
  //if((connectionInfo!=null) && (LoginUserMethods!=null) )
	//Login();
}


/*
 * Internal to the 'loadChatRoom()' function, for prompting the user to enter a user name and to test the validity of that name.
 */
function Login()
{
    openLoginDialog();
}

/*
 * Internal to the 'loadChatRoom()' function, for registering the messaging callback (which will receive messages from other clients)
 * once a valid user name is chosen and a successful connection to the server has been made.
 */
function startChannel()
{
  if (userID == null)
  {
    throw new Error("还没登录!");
  }

  //use the user name as the Client Channel unique ID, so that other clients know what ID to use for messaging you.
  var channelid=newGuid();
  var channeName=SMessageChannel+AccbookID;
  channel = new ClientChannel(channelid,channeName, connectionInfo);
  //create the messaging callback, to handle messages from the server and from other clients
  var callback = new ClientCallback(channel, SMsgCallback, function(jsonValue,dataType) {
    if (jsonValue != null)
    {
      if (jsonValue.notificationType != null)
      {
        var type = jsonValue.notificationType;
        var from = jsonValue.fromusrname;
        var datetimestr=jsonValue.datetime;
        //the list of users has changed, so update it on the page
        if (type == "user_login" || type == "user_logout")
        {
          loadUsers();
          var msgtext=null;
          if(type == "user_login")
             msgtext= "登录了！";
           else
             msgtext= "退出了！";
          addMessage(from, msgtext,datetimestr, false);
        }
        //you received a public or private message, so add it to the message area
        else if (type == "message" )
        {
            var message = jsonValue.message;
          var msgtype=jsonValue.msgtype;
          var isPrivate = msgtype == "2";
          addMessage(from, message,datetimestr, isPrivate);
        }
        else if ( type == "cmd")
        {
          var cmdStr=jsonValue.cmd;
          var msgtype=jsonValue.msgtype;
          var isPrivate = msgtype == "2";
          var cmdType=null;
          if(cmdStr=="ring")
          {
           cmdType="响铃" ;
          }
          else if(cmdStr="vibrate")
          {
            cmdType="震动";
          }
          addMessage(from, cmdType,datetimestr, isPrivate);
        }
      }
      //your session has expired!
      else if(jsonValue.SessionExpired != null)
      {
        addMessage(null, jsonValue.SessionExpired,null, null, true);

        //NOTE: you don't need to call stopChannel here, because the session has expired and therefore
        //this is the last message you will receive before the tunnel closes.
      }
    }
    return true;
  },channeName);
  if(channel.callbacks.length==0)
    channel.connect(callback);
  else
    channel.registerCallback(callback);
  LoginUserMethods.UpdateCurUserCallbackClientID(channelid);
}

/*
 * Closes the session on the server, which will in turn terminate the client channel.
 */
function stopChannel()
{
  if(LoginUserMethods!=null)
     LoginUserMethods.Logout();
  if (channel != null && channel.callbackLoop != null)
  {
     // channel.disconnect(); Not required because clearing the session will terminate the tunnel!
      channel.closeSession();
    }
}

/*
 * Adds a message to the message area. This message will either be a message from another user, from yourself, or an error message.
 */
function addMessage(from, message, datetimestr,isPrivate, isError)
{
  if (isPrivate == null)
  {
    isPrivate = false;
  }
  if (isError == null)
  {
    isError = false;
  }

  if ((from != null || isError) && message != null)
  {
    var newDiv = document.createElement("div");
    newDiv.classname = "entry";

    if ( isError )
    {
      newDiv.innerHTML = "<span class=\"messagefail\">" + message + "</span>"; 
    }
    else
    {
            newDiv.innerHTML = "<b>" + from + "></b> " + datetimestr + "<br/>"+
                (isPrivate ? "<small><i>(单独说)</i></small> " : "") + message;


    }

    var chatBox = document.getElementById("chatarea");
    chatBox.appendChild(newDiv);
    newDiv.scrollIntoView(false);
  }
}

function loadUsers()
{
  var users = getUserList();
  var userListObj = document.getElementById("userlist");

  if (users == null)
  {
    addMessage(null, 'Connection to the server could not be established.', null, true);
    stopChannel();
    userListObj.innerHTML = "[没有用户]";

    return false;    
  }

  if(users.SessionExpired != null)
  {
    addMessage(null, users.SessionExpired,null, null, true);
    stopChannel();
    userListObj.innerHTML = "[没有用户]";

    return false;
  }

  if (users != null && userListObj != null)
  {
    //cache the users for later, like when sending private messages
    cachedUsers = users;
    //alert(JSON.stringify(users));
    //alert(users.length);
    if (users.length > 0)
    {
      var newContent = new Array("");
      for (var i = 0; i < users.length; i++){ 
        newContent.push(users[i].username);
        newContent.push("<br />\n");
      } 
      userListObj.innerHTML = newContent.join("");
    }
    else
    {
      userListObj.innerHTML = "[没有用户]";
    }
  }
}

function sendOnEnter(e)
{
  if (e) {
    var ev = e;
  } else {
    var ev = window.event;
  }

  if(ev.which) { 
    var keycode = ev.which;
  } else {
    var keycode = ev.keyCode;
  }

  if (keycode == 13) {
    sendMessage();
  }
}

function sendMessage()
{
  var fieldObj = document.getElementById("messageField");
 
  if (channel != null && fieldObj != null)
  {
    var messageText = fieldObj.value.trim();
   // alert(messageText.length);
    if (messageText.length > 0)
    {
      var broadcastResult = LoginUserMethods.SendMessageToAll(messageText);
     // alert(broadcastResult);
      if (broadcastResult == null || broadcastResult.result == null || broadcastResult.result != true)
      {
        var errMsg = "ERROR: your message could not be sent to one or more users. Please try again.";
        if ((broadcastResult != null && broadcastResult.SessionExpired != null))
        {
          stopChannel();
          errMsg = broadcastResult.SessionExpired;
        }
        addMessage(null, errMsg,null, null, true);
      }
      else
          fieldObj.value = "";
     // addMessage(userName, messageText, false);
   }
  }
}

function openPrivateMessageDialog()
{
  var fieldObj = document.getElementById("messageField");
  if (fieldObj != null)
  {
    var messageText = fieldObj.value.trim();
    if (messageText != "")
    {
      populatePrivateMessageUserList();
      toggleModal();
    }
  }
}

function toggleModal()
{
  var userDialog = document.getElementById("modal");
  userDialog.style.visibility = (userDialog.style.visibility == "visible") ? "hidden" : "visible";
}
function sendPrivateMessage()
{
  var chosenUserName = document.getElementById("chosenuser").value.trim();
 
  if (chosenUserName != "" && chosenUserName != userID)
  {
    toggleModal();

    var fieldObj = document.getElementById("messageField");
    var messageText = fieldObj.value.trim();

    if (messageText.length > 0)
    {
      var notifyResult = LoginUserMethods.SendMessageToUser(messageText, chosenUserName);
      if (notifyResult = null || notifyResult.result == null || notifyResult.result !== true) {
          var errMsg = "ERROR: your message could not be sent. Please try again.";
          if ((notifyResult != null && notifyResult.SessionExpired != null)) {
              stopChannel();
              errMsg = notifyResult.SessionExpired;
          }
          addMessage(null, errMsg, null,null, true);
      }
      else {
          //var dt = new Date();
          //var dtstr = dt.pattern("yyyy-MM-dd hh:mm:ss")+" ";
          //addMessage(userName, messageText,dtstr, true);
            fieldObj.value = "";
      }
    }
  }
}

function updateChosenUser()
{
  var chosenUserField = document.getElementById("chosenuser");
  var chosenUserSelect = document.getElementById("privateusers");

  chosenUserField.value = chosenUserSelect.value;
}
function populatePrivateMessageUserList()
{
  var privateUserList = document.getElementById("privateusers");

  //clear the list
  for (var x = privateUserList.length; x >= 0; x--){
    privateUserList[x] = null;
  }

  privateUserList[privateUserList.length] = new Option("选择一个用户", "");
  for (var i = 0; i < cachedUsers.length; i++){
    var thisUser = cachedUsers[i];
    //can't send private messages to yourself
    if (thisUser.userid != userID)
    {
      privateUserList[privateUserList.length] = new Option(thisUser.username, thisUser.userid);
    }
  }
}
function toggleMlogin() {
    var userDialog = document.getElementById("mlogin");
    userDialog.style.visibility = (userDialog.style.visibility == "visible") ? "hidden" : "visible";
}

function updateChosenAcc() {
    var chosenAccField = document.getElementById("chosenacc");
    var chosenAccSelect = document.getElementById("selectaccs");

    chosenAccField.value = chosenAccSelect.value;
}
function updateLoginUser() {
  //  var chosenAccField = document.getElementById("chosenacc");
    var logincodeField = document.getElementById("logincode");
    var loginpasswordField = document.getElementById("loginpassword");
    AccbookID = "0";
    loginCode = logincodeField.value.trim();
    loginpassword = loginpasswordField.value.trim();
    if ( loginCode != "") {
        toggleMlogin();
    }
  	connectionInfo = getAuth(loginCode, loginpassword);
  	LoginUserMethods = new TLoginUser(connectionInfo);    
    var msg = null;
   // var returnObject = LoginUserMethods.IsValidUser(loginCode, loginpassword, msg);
   // if (returnObject.result == true) {
        var UserObject = LoginUserMethods.GetCurUserJSON();
        //UserObject=JSON.stringify(UserObject);
        //alert(JSON.stringify(UserObject));
        userName = UserObject.result.username;
        userID = UserObject.result.userid;
        if (userID != null) {
            //the user entered a valid user name, so load the list of users
            loadUsers();

            //start the callback, so that the user can receive messages from other clients
            startChannel();

        }
 //   }
 //   else {
//        addMessage(null, returnObject.msg,null, null, true);
 //       stopChannel();
 //   }
    var userLabel = document.getElementById("loginlabel");
    if (userName != null) {
        userLabel.innerHTML = "<b>登录为:</b> " + userName;
    }
    else {
        userLabel.innerHTML = "<b>没有登录!</b>";
    }
}
function cancelLogin() {
    //AccbookID = "";
    loginCode = "";
    loginpassword = "";
    stopChannel();
    toggleMlogin();
}
function populateAccbookList() {
    var AccbookList = document.getElementById("selectaccs");

    //clear the list
  //  for (var x = AccbookList.length; x >= 0; x--) {
  //      AccbookList[x] = null;
    //  }
    var cachedAccs = LoginUserMethods.GetAccListJSON().result.accbooks;
    AccbookList[AccbookList.length] = new Option("选择登录账套", "");
    for (var i = 0; i < cachedAccs.length; i++) {
        var thisAcc = cachedAccs[i];
        AccbookList[AccbookList.length] = new Option(thisAcc.syaccbookname, thisAcc.syaccbookcode);
        
    }
}
function openLoginDialog() 
{
        toggleMlogin();
}
if (!String.prototype.trim)
{
  String.prototype.trim = function () { return this.replace(/^\s*/, "").replace(/\s*$/, ""); }
}
/**     
* 对Date的扩展，将 Date 转化为指定格式的String     
* 月(M)、日(d)、12小时(h)、24小时(H)、分(m)、秒(s)、周(E)、季度(q) 可以用 1-2 个占位符     
* 年(y)可以用 1-4 个占位符，毫秒(S)只能用 1 个占位符(是 1-3 位的数字)     
* eg:     
* (new Date()).pattern("yyyy-MM-dd hh:mm:ss.S") ==> 2006-07-02 08:09:04.423     
* (new Date()).pattern("yyyy-MM-dd E HH:mm:ss") ==> 2009-03-10 二 20:09:04     
* (new Date()).pattern("yyyy-MM-dd EE hh:mm:ss") ==> 2009-03-10 周二 08:09:04     
* (new Date()).pattern("yyyy-MM-dd EEE hh:mm:ss") ==> 2009-03-10 星期二 08:09:04     
* (new Date()).pattern("yyyy-M-d h:m:s.S") ==> 2006-7-2 8:9:4.18     
*/

Date.prototype.pattern = function (fmt) {
    var o = {
        "M+": this.getMonth() + 1, //月份        
        "d+": this.getDate(), //日        
        "h+": this.getHours() % 12 == 0 ? 12 : this.getHours() % 12, //小时        
        "H+": this.getHours(), //小时        
        "m+": this.getMinutes(), //分        
        "s+": this.getSeconds(), //秒        
        "q+": Math.floor((this.getMonth() + 3) / 3), //季度        
        "S": this.getMilliseconds() //毫秒        
    };
    var week = {
        "0": "/u65e5",
        "1": "/u4e00",
        "2": "/u4e8c",
        "3": "/u4e09",
        "4": "/u56db",
        "5": "/u4e94",
        "6": "/u516d"
    };
    if (/(y+)/.test(fmt)) {
        fmt = fmt.replace(RegExp.$1, (this.getFullYear() + "").substr(4 - RegExp.$1.length));
    }
    if (/(E+)/.test(fmt)) {
        fmt = fmt.replace(RegExp.$1, ((RegExp.$1.length > 1) ? (RegExp.$1.length > 2 ? "/u661f/u671f" : "/u5468") : "") + week[this.getDay() + ""]);
    }
    for (var k in o) {
        if (new RegExp("(" + k + ")").test(fmt)) {
            fmt = fmt.replace(RegExp.$1, (RegExp.$1.length == 1) ? (o[k]) : (("00" + o[k]).substr(("" + o[k]).length)));
        }
    }
    return fmt;
}      