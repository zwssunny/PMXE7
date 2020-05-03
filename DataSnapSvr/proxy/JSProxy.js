// 
// Created by the DataSnap proxy generator.
// 2014-07-26 14:45:39
// 

function DSAdmin(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("DSAdmin",connectionInfo);

  /*
   * @return result - Type on server: string
   */
  this.GetPlatformName = function() {
    var returnObject = this.executor.executeMethod('GetPlatformName', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: Boolean
   */
  this.ClearResources = function() {
    var returnObject = this.executor.executeMethod('ClearResources', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TDBXReader
   */
  this.FindPackages = function() {
    var returnObject = this.executor.executeMethod('FindPackages', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param PackageName [in] - Type on server: string
   * @param ClassPattern [in] - Type on server: string
   * @return result - Type on server: TDBXReader
   */
  this.FindClasses = function(PackageName, ClassPattern) {
    var returnObject = this.executor.executeMethod('FindClasses', "GET", [PackageName, ClassPattern], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.PackageName = PackageName;
        resultObject.ClassPattern = ClassPattern;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param PackageName [in] - Type on server: string
   * @param ClassPattern [in] - Type on server: string
   * @param MethodPattern [in] - Type on server: string
   * @return result - Type on server: TDBXReader
   */
  this.FindMethods = function(PackageName, ClassPattern, MethodPattern) {
    var returnObject = this.executor.executeMethod('FindMethods', "GET", [PackageName, ClassPattern, MethodPattern], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.PackageName = PackageName;
        resultObject.ClassPattern = ClassPattern;
        resultObject.MethodPattern = MethodPattern;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ClassReader [in] - Type on server: TDBXReader
   */
  this.CreateServerClasses = function(ClassReader) {
    this.executor.executeMethod('"CreateServerClasses"', "POST", [ClassReader], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param ClassReader [in] - Type on server: TDBXReader
   */
  this.DropServerClasses = function(ClassReader) {
    this.executor.executeMethod('"DropServerClasses"', "POST", [ClassReader], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param MethodReader [in] - Type on server: TDBXReader
   */
  this.CreateServerMethods = function(MethodReader) {
    this.executor.executeMethod('"CreateServerMethods"', "POST", [MethodReader], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param MethodReader [in] - Type on server: TDBXReader
   */
  this.DropServerMethods = function(MethodReader) {
    this.executor.executeMethod('"DropServerMethods"', "POST", [MethodReader], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @return result - Type on server: TDBXReader
   */
  this.GetServerClasses = function() {
    var returnObject = this.executor.executeMethod('GetServerClasses', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.ListClasses = function() {
    var returnObject = this.executor.executeMethod('ListClasses', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ClassName [in] - Type on server: string
   * @return result - Type on server: TJSONObject
   */
  this.DescribeClass = function(ClassName) {
    var returnObject = this.executor.executeMethod('DescribeClass', "GET", [ClassName], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClassName = ClassName;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ClassName [in] - Type on server: string
   * @return result - Type on server: TJSONArray
   */
  this.ListMethods = function(ClassName) {
    var returnObject = this.executor.executeMethod('ListMethods', "GET", [ClassName], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClassName = ClassName;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ServerMethodName [in] - Type on server: string
   * @return result - Type on server: TJSONObject
   */
  this.DescribeMethod = function(ServerMethodName) {
    var returnObject = this.executor.executeMethod('DescribeMethod', "GET", [ServerMethodName], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ServerMethodName = ServerMethodName;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TDBXReader
   */
  this.GetServerMethods = function() {
    var returnObject = this.executor.executeMethod('GetServerMethods', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TDBXReader
   */
  this.GetServerMethodParameters = function() {
    var returnObject = this.executor.executeMethod('GetServerMethodParameters', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TDBXReader
   */
  this.GetDatabaseConnectionProperties = function() {
    var returnObject = this.executor.executeMethod('GetDatabaseConnectionProperties', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: string
   */
  this.GetDSServerName = function() {
    var returnObject = this.executor.executeMethod('GetDSServerName', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelName [in] - Type on server: string
   * @param ClientManagerId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param ChannelNames [in] - Type on server: string
   * @param SecurityToken [in] - Type on server: string
   * @param ResponseData [in] - Type on server: TJSONValue
   * @return result - Type on server: TJSONValue
   */
  this.ConsumeClientChannel = function(ChannelName, ClientManagerId, CallbackId, ChannelNames, SecurityToken, ResponseData) {
    var returnObject = this.executor.executeMethod('"ConsumeClientChannel"', "POST", [ChannelName, ClientManagerId, CallbackId, ChannelNames, SecurityToken, ResponseData], arguments[6], true, arguments[7], arguments[8]);
    if (arguments[6] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelName = ChannelName;
        resultObject.ClientManagerId = ClientManagerId;
        resultObject.CallbackId = CallbackId;
        resultObject.ChannelNames = ChannelNames;
        resultObject.SecurityToken = SecurityToken;
        resultObject.ResponseData = ResponseData;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelName [in] - Type on server: string
   * @param ClientManagerId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param ChannelNames [in] - Type on server: string
   * @param SecurityToken [in] - Type on server: string
   * @param Timeout [in] - Type on server: Integer
   * @param ResponseData [in] - Type on server: TJSONValue
   * @return result - Type on server: TJSONValue
   */
  this.ConsumeClientChannelTimeout = function(ChannelName, ClientManagerId, CallbackId, ChannelNames, SecurityToken, Timeout, ResponseData) {
    var returnObject = this.executor.executeMethod('"ConsumeClientChannelTimeout"', "POST", [ChannelName, ClientManagerId, CallbackId, ChannelNames, SecurityToken, Timeout, ResponseData], arguments[7], true, arguments[8], arguments[9]);
    if (arguments[7] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelName = ChannelName;
        resultObject.ClientManagerId = ClientManagerId;
        resultObject.CallbackId = CallbackId;
        resultObject.ChannelNames = ChannelNames;
        resultObject.SecurityToken = SecurityToken;
        resultObject.Timeout = Timeout;
        resultObject.ResponseData = ResponseData;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelId [in] - Type on server: string
   * @param SecurityToken [in] - Type on server: string
   * @return result - Type on server: Boolean
   */
  this.CloseClientChannel = function(ChannelId, SecurityToken) {
    var returnObject = this.executor.executeMethod('CloseClientChannel', "GET", [ChannelId, SecurityToken], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelId = ChannelId;
        resultObject.SecurityToken = SecurityToken;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param ChannelNames [in] - Type on server: string
   * @param SecurityToken [in] - Type on server: string
   * @return result - Type on server: Boolean
   */
  this.RegisterClientCallbackServer = function(ChannelId, CallbackId, ChannelNames, SecurityToken) {
    var returnObject = this.executor.executeMethod('RegisterClientCallbackServer', "GET", [ChannelId, CallbackId, ChannelNames, SecurityToken], arguments[4], true, arguments[5], arguments[6]);
    if (arguments[4] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelId = ChannelId;
        resultObject.CallbackId = CallbackId;
        resultObject.ChannelNames = ChannelNames;
        resultObject.SecurityToken = SecurityToken;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param SecurityToken [in] - Type on server: string
   * @return result - Type on server: Boolean
   */
  this.UnregisterClientCallback = function(ChannelId, CallbackId, SecurityToken) {
    var returnObject = this.executor.executeMethod('UnregisterClientCallback', "GET", [ChannelId, CallbackId, SecurityToken], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelId = ChannelId;
        resultObject.CallbackId = CallbackId;
        resultObject.SecurityToken = SecurityToken;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelName [in] - Type on server: string
   * @param Msg [in] - Type on server: TJSONValue
   * @return result - Type on server: Boolean
   */
  this.BroadcastToChannel = function(ChannelName, Msg) {
    var returnObject = this.executor.executeMethod('"BroadcastToChannel"', "POST", [ChannelName, Msg], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelName = ChannelName;
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ChannelName [in] - Type on server: string
   * @param Msg [in] - Type on server: TObject
   * @return result - Type on server: Boolean
   */
  this.BroadcastObjectToChannel = function(ChannelName, Msg) {
    var returnObject = this.executor.executeMethod('"BroadcastObjectToChannel"', "POST", [ChannelName, Msg], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ChannelName = ChannelName;
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ClientId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param Msg [in] - Type on server: TJSONValue
   * @param Response [out] - Type on server: TJSONValue
   * @return result - Type on server: Boolean
   */
  this.NotifyCallback = function(ClientId, CallbackId, Msg) {
    var returnObject = this.executor.executeMethod('"NotifyCallback"', "POST", [ClientId, CallbackId, Msg], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClientId = ClientId;
        resultObject.CallbackId = CallbackId;
        resultObject.Msg = Msg;
        resultObject.Response = resultArray[0];
        resultObject.result = resultArray[1];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ClientId [in] - Type on server: string
   * @param CallbackId [in] - Type on server: string
   * @param Msg [in] - Type on server: TObject
   * @param Response [out] - Type on server: TObject
   * @return result - Type on server: Boolean
   */
  this.NotifyObject = function(ClientId, CallbackId, Msg) {
    var returnObject = this.executor.executeMethod('"NotifyObject"', "POST", [ClientId, CallbackId, Msg], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClientId = ClientId;
        resultObject.CallbackId = CallbackId;
        resultObject.Msg = Msg;
        resultObject.Response = resultArray[0];
        resultObject.result = resultArray[1];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TLoginUser(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TLoginUser",connectionInfo);

  /*
   * @return result - Type on server: String
   */
  this.GetSysConnectionString = function() {
    var returnObject = this.executor.executeMethod('GetSysConnectionString', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param UserCode [in] - Type on server: String
   * @param OldPassword [in] - Type on server: String
   * @param NewPassword [in] - Type on server: String
   * @param msg [in/out] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.ChangePassword = function(UserCode, OldPassword, NewPassword, msg) {
    var returnObject = this.executor.executeMethod('ChangePassword', "GET", [UserCode, OldPassword, NewPassword, msg], arguments[4], true, arguments[5], arguments[6]);
    if (arguments[4] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.UserCode = UserCode;
        resultObject.OldPassword = OldPassword;
        resultObject.NewPassword = NewPassword;
        resultObject.msg = resultArray[0];
        resultObject.result = resultArray[1];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Value [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.UpdateCurUserCallbackClientID = function(Value) {
    var returnObject = this.executor.executeMethod('CurUserCallbackClientID', "POST", [Value], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Value = Value;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  this.Logout = function() {
    this.executor.executeMethod('Logout', "GET", [], arguments[0], false, arguments[1], arguments[2]);
  };

  /*
   * @param Users [in] - Type on server: TJSONArray
   */
  this.SetUsersToFollow = function(Users) {
    this.executor.executeMethod('"SetUsersToFollow"', "POST", [Users], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToFollow = function(Msg) {
    var returnObject = this.executor.executeMethod('SendMessageToFollow', "GET", [Msg], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToAll = function(Msg) {
    var returnObject = this.executor.executeMethod('SendMessageToAll', "GET", [Msg], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param UserID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToUser = function(Msg, UserID) {
    var returnObject = this.executor.executeMethod('SendMessageToUser', "GET", [Msg, UserID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.UserID = UserID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param DepartmentID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToDepartment = function(Msg, DepartmentID) {
    var returnObject = this.executor.executeMethod('SendMessageToDepartment', "GET", [Msg, DepartmentID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.DepartmentID = DepartmentID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param GroupID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToGroup = function(Msg, GroupID) {
    var returnObject = this.executor.executeMethod('SendMessageToGroup', "GET", [Msg, GroupID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.GroupID = GroupID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToFollow = function(cmdStr) {
    var returnObject = this.executor.executeMethod('SendCMDToFollow', "GET", [cmdStr], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToAll = function(cmdStr) {
    var returnObject = this.executor.executeMethod('SendCMDToAll', "GET", [cmdStr], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param UserID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToUser = function(cmdStr, UserID) {
    var returnObject = this.executor.executeMethod('SendCMDToUser', "GET", [cmdStr, UserID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.UserID = UserID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param DepartmentID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToDepartment = function(cmdStr, DepartmentID) {
    var returnObject = this.executor.executeMethod('SendCMDToDepartment', "GET", [cmdStr, DepartmentID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.DepartmentID = DepartmentID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param GroupID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToGroup = function(cmdStr, GroupID) {
    var returnObject = this.executor.executeMethod('SendCMDToGroup', "GET", [cmdStr, GroupID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.GroupID = GroupID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param itype [in] - Type on server: Integer
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMgrMessage = function(itype, Msg) {
    var returnObject = this.executor.executeMethod('SendMgrMessage', "GET", [itype, Msg], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.itype = itype;
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetAccList = function() {
    var returnObject = this.executor.executeMethod('GetAccList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetCurUserInfo = function() {
    var returnObject = this.executor.executeMethod('GetCurUserInfo', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.ListOfLoginUser = function() {
    var returnObject = this.executor.executeMethod('ListOfLoginUser', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.ListOfAllLoginUser = function() {
    var returnObject = this.executor.executeMethod('ListOfAllLoginUser', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetClassList = function() {
    var returnObject = this.executor.executeMethod('GetClassList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetAutoCodeFields = function() {
    var returnObject = this.executor.executeMethod('GetAutoCodeFields', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetModuleData = function() {
    var returnObject = this.executor.executeMethod('GetModuleData', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.RefreshGlobeVar = function() {
    var returnObject = this.executor.executeMethod('RefreshGlobeVar', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetModuleRight = function() {
    var returnObject = this.executor.executeMethod('GetModuleRight', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetAccInforJSON = function() {
    var returnObject = this.executor.executeMethod('GetAccInforJSON', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetAccListJSON = function() {
    var returnObject = this.executor.executeMethod('GetAccListJSON', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetCurUserJSON = function() {
    var returnObject = this.executor.executeMethod('GetCurUserJSON', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetUserList = function() {
    var returnObject = this.executor.executeMethod('GetUserList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetAllUserList = function() {
    var returnObject = this.executor.executeMethod('GetAllUserList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetClassListJO = function() {
    var returnObject = this.executor.executeMethod('GetClassListJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetAutoCodeFieldsJO = function() {
    var returnObject = this.executor.executeMethod('GetAutoCodeFieldsJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetModuleDataJO = function() {
    var returnObject = this.executor.executeMethod('GetModuleDataJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.RefreshGlobeVarJO = function() {
    var returnObject = this.executor.executeMethod('RefreshGlobeVarJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetModuleRightJO = function() {
    var returnObject = this.executor.executeMethod('GetModuleRightJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetDepartmentAndUsersList = function() {
    var returnObject = this.executor.executeMethod('GetDepartmentAndUsersList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param UserId [in] - Type on server: String
   * @return result - Type on server: String
   */
  this.UserIdToName = function(UserId) {
    var returnObject = this.executor.executeMethod('UserIdToName', "GET", [UserId], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.UserId = UserId;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetServerInfo = function() {
    var returnObject = this.executor.executeMethod('GetServerInfo', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetFtpSetting = function() {
    var returnObject = this.executor.executeMethod('GetFtpSetting', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetMailSetting = function() {
    var returnObject = this.executor.executeMethod('GetMailSetting', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetSmsSetting = function() {
    var returnObject = this.executor.executeMethod('GetSmsSetting', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetWorkFlowServerList = function() {
    var returnObject = this.executor.executeMethod('GetWorkFlowServerList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetSmsServerList = function() {
    var returnObject = this.executor.executeMethod('GetSmsServerList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TSyAccBook(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TSyAccBook",connectionInfo);

  /*
   * @return result - Type on server: TStream
   */
  this.GetAllAccBook = function() {
    var returnObject = this.executor.executeMethod('GetAllAccBook', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TStream
   */
  this.GetActiveAccBook = function() {
    var returnObject = this.executor.executeMethod('GetActiveAccBook', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetAllAccBookJO = function() {
    var returnObject = this.executor.executeMethod('GetAllAccBookJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONObject
   */
  this.GetActiveAccBookJO = function() {
    var returnObject = this.executor.executeMethod('GetActiveAccBookJO', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TServerDataSet(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TServerDataSet",connectionInfo);

  /*
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.GetInitResult = function(ClassCode) {
    var returnObject = this.executor.executeMethod('GetInitResult', "GET", [ClassCode], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Open = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Open"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Update = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Update"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Delete = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Delete"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.DeleteDetail = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"DeleteDetail"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.CmdExec = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"CmdExec"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Check = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Check"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.CloseOff = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"CloseOff"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Revoke = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Revoke"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.Tally = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"Tally"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @return result - Type on server: TStream
   */
  this.ExecSQL = function(Stream) {
    var returnObject = this.executor.executeMethod('"ExecSQL"', "POST", [Stream], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Stream [in] - Type on server: TStream
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.ValidateData = function(Stream, ClassCode) {
    var returnObject = this.executor.executeMethod('"ValidateData"', "POST", [Stream, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Stream = Stream;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QueryOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QueryExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QuerySysOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QuerySysExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TServerQuery(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TServerQuery",connectionInfo);

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QueryOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: Integer
   */
  this.QueryExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @param Parameters [in] - Type on server: TParams
   * @return result - Type on server: Integer
   */
  this.ExecSQL = function(SQLText, Parameters) {
    var returnObject = this.executor.executeMethod('"ExecSQL"', "POST", [SQLText, Parameters], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.Parameters = Parameters;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.QuerySysOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: Integer
   */
  this.QuerySysExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @param Parameters [in] - Type on server: TParams
   * @return result - Type on server: Integer
   */
  this.SysExecSQL = function(SQLText, Parameters) {
    var returnObject = this.executor.executeMethod('"SysExecSQL"', "POST", [SQLText, Parameters], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.Parameters = Parameters;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TJServerDataSet(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TJServerDataSet",connectionInfo);

  /*
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.GetInitResult = function(ClassCode) {
    var returnObject = this.executor.executeMethod('GetInitResult', "GET", [ClassCode], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Open = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Open"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Update = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Update"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Delete = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Delete"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.DeleteDetail = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"DeleteDetail"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.ValidateData = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"ValidateData"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.CmdExec = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"CmdExec"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Check = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Check"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.CloseOff = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"CloseOff"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Revoke = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Revoke"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.Tally = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"Tally"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @return result - Type on server: TJSONObject
   */
  this.ExecSQL = function(Json) {
    var returnObject = this.executor.executeMethod('"ExecSQL"', "POST", [Json], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QueryOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QueryExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QuerySysOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QuerySysExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TJServerQuery(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TJServerQuery",connectionInfo);

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QueryOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Json [in] - Type on server: TJSONObject
   * @param ClassCode [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QueryUpdate = function(Json, ClassCode) {
    var returnObject = this.executor.executeMethod('"QueryUpdate"', "POST", [Json, ClassCode], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Json = Json;
        resultObject.ClassCode = ClassCode;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: Integer
   */
  this.QueryExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QueryExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.QuerySysOpen = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysOpen', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param SQLText [in] - Type on server: String
   * @return result - Type on server: Integer
   */
  this.QuerySysExecSQL = function(SQLText) {
    var returnObject = this.executor.executeMethod('QuerySysExecSQL', "GET", [SQLText], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.SQLText = SQLText;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TWorkFlowServer(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TWorkFlowServer",connectionInfo);

  /*
   * @param jsonValue [in] - Type on server: TJSONObject
   * @return result - Type on server: String
   */
  this.ServerWorkFlowStartJSON = function(jsonValue) {
    var returnObject = this.executor.executeMethod('"ServerWorkFlowStartJSON"', "POST", [jsonValue], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.jsonValue = jsonValue;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param FlowDefID [in] - Type on server: String
   * @param Subject [in] - Type on server: String
   * @param Content [in] - Type on server: String
   * @param BusWindow [in] - Type on server: String
   * @param BusCode [in] - Type on server: String
   * @param Rank [in] - Type on server: Integer
   * @param PrjID [in] - Type on server: String
   * @param Report [in] - Type on server: String
   * @return result - Type on server: String
   */
  this.ServerWorkFlowStart = function(FlowDefID, Subject, Content, BusWindow, BusCode, Rank, PrjID, Report) {
    var returnObject = this.executor.executeMethod('ServerWorkFlowStart', "GET", [FlowDefID, Subject, Content, BusWindow, BusCode, Rank, PrjID, Report], arguments[8], true, arguments[9], arguments[10]);
    if (arguments[8] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.FlowDefID = FlowDefID;
        resultObject.Subject = Subject;
        resultObject.Content = Content;
        resultObject.BusWindow = BusWindow;
        resultObject.BusCode = BusCode;
        resultObject.Rank = Rank;
        resultObject.PrjID = PrjID;
        resultObject.Report = Report;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param jsonValue [in] - Type on server: TJSONObject
   * @return result - Type on server: Boolean
   */
  this.ServerWorkFlowExecJSON = function(jsonValue) {
    var returnObject = this.executor.executeMethod('"ServerWorkFlowExecJSON"', "POST", [jsonValue], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.jsonValue = jsonValue;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param FlowDefID [in] - Type on server: String
   * @param WorkInsID [in] - Type on server: String
   * @param TaskInsID [in] - Type on server: String
   * @param TskStatus [in] - Type on server: String
   * @param TskComments [in] - Type on server: String
   * @param VariableList [in] - Type on server: TJSONArray
   * @return result - Type on server: Boolean
   */
  this.ServerWorkFlowExec = function(FlowDefID, WorkInsID, TaskInsID, TskStatus, TskComments, VariableList) {
    var returnObject = this.executor.executeMethod('"ServerWorkFlowExec"', "POST", [FlowDefID, WorkInsID, TaskInsID, TskStatus, TskComments, VariableList], arguments[6], true, arguments[7], arguments[8]);
    if (arguments[6] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.FlowDefID = FlowDefID;
        resultObject.WorkInsID = WorkInsID;
        resultObject.TaskInsID = TaskInsID;
        resultObject.TskStatus = TskStatus;
        resultObject.TskComments = TskComments;
        resultObject.VariableList = VariableList;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param AUserID [in] - Type on server: String
   * @param ACompletedState [in] - Type on server: Integer
   * @param AOtherCondition [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.GetTaskList = function(AUserID, ACompletedState, AOtherCondition) {
    var returnObject = this.executor.executeMethod('GetTaskList', "GET", [AUserID, ACompletedState, AOtherCondition], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.AUserID = AUserID;
        resultObject.ACompletedState = ACompletedState;
        resultObject.AOtherCondition = AOtherCondition;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ALogFilterType [in] - Type on server: Integer
   * @param AFilterKey [in] - Type on server: String
   * @return result - Type on server: String
   */
  this.GetLogList = function(ALogFilterType, AFilterKey) {
    var returnObject = this.executor.executeMethod('GetLogList', "GET", [ALogFilterType, AFilterKey], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ALogFilterType = ALogFilterType;
        resultObject.AFilterKey = AFilterKey;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param ADiagramType [in] - Type on server: Integer
   * @param ADiagramKey [in] - Type on server: String
   * @return result - Type on server: String
   */
  this.GetDiagram = function(ADiagramType, ADiagramKey) {
    var returnObject = this.executor.executeMethod('GetDiagram', "GET", [ADiagramType, ADiagramKey], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.ADiagramType = ADiagramType;
        resultObject.ADiagramKey = ADiagramKey;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param TaskInsID [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.GetTaskdefList = function(TaskInsID) {
    var returnObject = this.executor.executeMethod('GetTaskdefList', "GET", [TaskInsID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.TaskInsID = TaskInsID;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param TaskInsID [in] - Type on server: String
   * @return result - Type on server: TJSONObject
   */
  this.GetVariableList = function(TaskInsID) {
    var returnObject = this.executor.executeMethod('GetVariableList', "GET", [TaskInsID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.TaskInsID = TaskInsID;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param TaskInsID [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.GetVariableListDS = function(TaskInsID) {
    var returnObject = this.executor.executeMethod('GetVariableListDS', "GET", [TaskInsID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.TaskInsID = TaskInsID;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param TaskInsID [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.GetTaskdefListDS = function(TaskInsID) {
    var returnObject = this.executor.executeMethod('GetTaskdefListDS', "GET", [TaskInsID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.TaskInsID = TaskInsID;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param FlowID [in] - Type on server: String
   * @param isDef [in] - Type on server: Boolean
   * @return result - Type on server: TStream
   */
  this.GetWorkFlowChart = function(FlowID, isDef) {
    var returnObject = this.executor.executeMethod('GetWorkFlowChart', "GET", [FlowID, isDef], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.FlowID = FlowID;
        resultObject.isDef = isDef;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param AUserID [in] - Type on server: String
   * @param ACompletedState [in] - Type on server: Integer
   * @param AOtherCondition [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.GetTaskListDS = function(AUserID, ACompletedState, AOtherCondition) {
    var returnObject = this.executor.executeMethod('GetTaskListDS', "GET", [AUserID, ACompletedState, AOtherCondition], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.AUserID = AUserID;
        resultObject.ACompletedState = ACompletedState;
        resultObject.AOtherCondition = AOtherCondition;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param TaskInsID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.TaskCanUpdate = function(TaskInsID) {
    var returnObject = this.executor.executeMethod('TaskCanUpdate', "GET", [TaskInsID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.TaskInsID = TaskInsID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TMessageManage(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TMessageManage",connectionInfo);

  /*
   * @param GroupName [in] - Type on server: String
   * @param Description [in] - Type on server: String
   */
  this.NewMessageGroup = function(GroupName, Description) {
    this.executor.executeMethod('NewMessageGroup', "GET", [GroupName, Description], arguments[2], false, arguments[3], arguments[4]);
  };

  /*
   * @param GroupID [in] - Type on server: String
   */
  this.DelMessageGroup = function(GroupID) {
    this.executor.executeMethod('DelMessageGroup', "GET", [GroupID], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param GroupID [in] - Type on server: String
   * @param GroupName [in] - Type on server: String
   * @param Description [in] - Type on server: String
   */
  this.UpdateMessageGroup = function(GroupID, GroupName, Description) {
    this.executor.executeMethod('MessageGroup', "POST", [GroupID, GroupName, Description], arguments[3], false, arguments[4], arguments[5]);
  };

  /*
   * @param GroupID [in] - Type on server: String
   * @param GroupMemberID [in] - Type on server: String
   * @param IsAdmin [in] - Type on server: Integer
   */
  this.NewMessageMember = function(GroupID, GroupMemberID, IsAdmin) {
    this.executor.executeMethod('NewMessageMember', "GET", [GroupID, GroupMemberID, IsAdmin], arguments[3], false, arguments[4], arguments[5]);
  };

  /*
   * @param GroupID [in] - Type on server: String
   * @param GroupMemberID [in] - Type on server: String
   * @param IsAdmin [in] - Type on server: Integer
   */
  this.UpdateMessageMember = function(GroupID, GroupMemberID, IsAdmin) {
    this.executor.executeMethod('MessageMember', "POST", [GroupID, GroupMemberID, IsAdmin], arguments[3], false, arguments[4], arguments[5]);
  };

  /*
   * @param GroupID [in] - Type on server: String
   * @param GroupMemberID [in] - Type on server: String
   */
  this.DelMessageMember = function(GroupID, GroupMemberID) {
    this.executor.executeMethod('DelMessageMember', "GET", [GroupID, GroupMemberID], arguments[2], false, arguments[3], arguments[4]);
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetMessageGroupList = function() {
    var returnObject = this.executor.executeMethod('GetMessageGroupList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param GroudId [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetGroupMemberList = function(GroudId) {
    var returnObject = this.executor.executeMethod('GetGroupMemberList', "GET", [GroudId], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.GroudId = GroudId;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param GroupId [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetAllEmployee = function(GroupId) {
    var returnObject = this.executor.executeMethod('GetAllEmployee', "GET", [GroupId], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.GroupId = GroupId;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param GroupId [in] - Type on server: String
   * @param MemberId [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.IsGroupMember = function(GroupId, MemberId) {
    var returnObject = this.executor.executeMethod('IsGroupMember', "GET", [GroupId, MemberId], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.GroupId = GroupId;
        resultObject.MemberId = MemberId;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetUserList = function() {
    var returnObject = this.executor.executeMethod('GetUserList', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Value [in] - Type on server: String
   * @return result - Type on server: String
   */
  this.GetHTMLEscapedString = function(Value) {
    var returnObject = this.executor.executeMethod('GetHTMLEscapedString', "GET", [Value], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Value = Value;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Value [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.UpdateCurUserCallbackClientID = function(Value) {
    var returnObject = this.executor.executeMethod('CurUserCallbackClientID', "POST", [Value], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Value = Value;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToAll = function(Msg) {
    var returnObject = this.executor.executeMethod('SendMessageToAll', "GET", [Msg], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param UserID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToUser = function(Msg, UserID) {
    var returnObject = this.executor.executeMethod('SendMessageToUser', "GET", [Msg, UserID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.UserID = UserID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param DepartmentID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToDepartment = function(Msg, DepartmentID) {
    var returnObject = this.executor.executeMethod('SendMessageToDepartment', "GET", [Msg, DepartmentID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.DepartmentID = DepartmentID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param GroupID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToGroup = function(Msg, GroupID) {
    var returnObject = this.executor.executeMethod('SendMessageToGroup', "GET", [Msg, GroupID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.GroupID = GroupID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param JobID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToJob = function(Msg, JobID) {
    var returnObject = this.executor.executeMethod('SendMessageToJob', "GET", [Msg, JobID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.JobID = JobID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param RoleID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToRole = function(Msg, RoleID) {
    var returnObject = this.executor.executeMethod('SendMessageToRole', "GET", [Msg, RoleID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.RoleID = RoleID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMessageToFollow = function(Msg) {
    var returnObject = this.executor.executeMethod('SendMessageToFollow', "GET", [Msg], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToFollow = function(cmdStr) {
    var returnObject = this.executor.executeMethod('SendCMDToFollow', "GET", [cmdStr], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToAll = function(cmdStr) {
    var returnObject = this.executor.executeMethod('SendCMDToAll', "GET", [cmdStr], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param UserID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToUser = function(cmdStr, UserID) {
    var returnObject = this.executor.executeMethod('SendCMDToUser', "GET", [cmdStr, UserID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.UserID = UserID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param DepartmentID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToDepartment = function(cmdStr, DepartmentID) {
    var returnObject = this.executor.executeMethod('SendCMDToDepartment', "GET", [cmdStr, DepartmentID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.DepartmentID = DepartmentID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param GroupID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToGroup = function(cmdStr, GroupID) {
    var returnObject = this.executor.executeMethod('SendCMDToGroup', "GET", [cmdStr, GroupID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.GroupID = GroupID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param JobID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToJob = function(cmdStr, JobID) {
    var returnObject = this.executor.executeMethod('SendCMDToJob', "GET", [cmdStr, JobID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.JobID = JobID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param cmdStr [in] - Type on server: String
   * @param RoleID [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendCMDToRole = function(cmdStr, RoleID) {
    var returnObject = this.executor.executeMethod('SendCMDToRole', "GET", [cmdStr, RoleID], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.cmdStr = cmdStr;
        resultObject.RoleID = RoleID;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param itype [in] - Type on server: Integer
   * @param Msg [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMgrMessage = function(itype, Msg) {
    var returnObject = this.executor.executeMethod('SendMgrMessage', "GET", [itype, Msg], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.itype = itype;
        resultObject.Msg = Msg;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param UserId [in] - Type on server: String
   */
  this.SendMissMessage = function(UserId) {
    this.executor.executeMethod('SendMissMessage', "GET", [UserId], arguments[1], false, arguments[2], arguments[3]);
  };

  /*
   * @param UserId [in] - Type on server: String
   * @param ReceId [in] - Type on server: String
   * @param RecType [in] - Type on server: Integer
   * @return result - Type on server: TJSONArray
   */
  this.GetLatelyMessage = function(UserId, ReceId, RecType) {
    var returnObject = this.executor.executeMethod('GetLatelyMessage', "GET", [UserId, ReceId, RecType], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.UserId = UserId;
        resultObject.ReceId = ReceId;
        resultObject.RecType = RecType;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param FromID [in] - Type on server: String
   * @param FromName [in] - Type on server: String
   * @param MsgID [in] - Type on server: String
   * @param sendtime [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMissMessageToUser = function(Msg, FromID, FromName, MsgID, sendtime) {
    var returnObject = this.executor.executeMethod('SendMissMessageToUser', "GET", [Msg, FromID, FromName, MsgID, sendtime], arguments[5], true, arguments[6], arguments[7]);
    if (arguments[5] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.FromID = FromID;
        resultObject.FromName = FromName;
        resultObject.MsgID = MsgID;
        resultObject.sendtime = sendtime;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param FromID [in] - Type on server: String
   * @param FromName [in] - Type on server: String
   * @param DepartmentID [in] - Type on server: String
   * @param MsgID [in] - Type on server: String
   * @param sendtime [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMissMessageToDepartment = function(Msg, FromID, FromName, DepartmentID, MsgID, sendtime) {
    var returnObject = this.executor.executeMethod('SendMissMessageToDepartment', "GET", [Msg, FromID, FromName, DepartmentID, MsgID, sendtime], arguments[6], true, arguments[7], arguments[8]);
    if (arguments[6] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.FromID = FromID;
        resultObject.FromName = FromName;
        resultObject.DepartmentID = DepartmentID;
        resultObject.MsgID = MsgID;
        resultObject.sendtime = sendtime;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Msg [in] - Type on server: String
   * @param FromID [in] - Type on server: String
   * @param FromName [in] - Type on server: String
   * @param GroupID [in] - Type on server: String
   * @param MsgID [in] - Type on server: String
   * @param sendtime [in] - Type on server: String
   * @return result - Type on server: Boolean
   */
  this.SendMissMessageToGroup = function(Msg, FromID, FromName, GroupID, MsgID, sendtime) {
    var returnObject = this.executor.executeMethod('SendMissMessageToGroup', "GET", [Msg, FromID, FromName, GroupID, MsgID, sendtime], arguments[6], true, arguments[7], arguments[8]);
    if (arguments[6] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Msg = Msg;
        resultObject.FromID = FromID;
        resultObject.FromName = FromName;
        resultObject.GroupID = GroupID;
        resultObject.MsgID = MsgID;
        resultObject.sendtime = sendtime;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };
}

function TContractProject(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("TContractProject",connectionInfo);

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetContype = function() {
    var returnObject = this.executor.executeMethod('GetContype', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param userid [in] - Type on server: String
   * @param ctypeid [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetContlist = function(userid, ctypeid) {
    var returnObject = this.executor.executeMethod('GetContlist', "GET", [userid, ctypeid], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.userid = userid;
        resultObject.ctypeid = ctypeid;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param contid [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetContdata = function(contid) {
    var returnObject = this.executor.executeMethod('GetContdata', "GET", [contid], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.contid = contid;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @return result - Type on server: TJSONArray
   */
  this.GetProtype = function() {
    var returnObject = this.executor.executeMethod('GetProtype', "GET", [], arguments[0], true, arguments[1], arguments[2]);
    if (arguments[0] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param userid [in] - Type on server: String
   * @param ProTypeid [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetProlist = function(userid, ProTypeid) {
    var returnObject = this.executor.executeMethod('GetProlist', "GET", [userid, ProTypeid], arguments[2], true, arguments[3], arguments[4]);
    if (arguments[2] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.userid = userid;
        resultObject.ProTypeid = ProTypeid;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param Projectid [in] - Type on server: String
   * @return result - Type on server: TJSONArray
   */
  this.GetProdata = function(Projectid) {
    var returnObject = this.executor.executeMethod('GetProdata', "GET", [Projectid], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.Projectid = Projectid;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };
}

function THouseView(connectionInfo)
{
  this.executor = new ServerFunctionExecutor("THouseView",connectionInfo);

  /*
   * @param AKeyID [in] - Type on server: String
   * @return result - Type on server: TStream
   */
  this.GetHouseViewStream = function(AKeyID) {
    var returnObject = this.executor.executeMethod('GetHouseViewStream', "GET", [AKeyID], arguments[1], true, arguments[2], arguments[3]);
    if (arguments[1] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.AKeyID = AKeyID;
        resultObject.result = resultArray[0];
        if (returnObject.cacheId != null && returnObject.cmdIndex != null) {
          resultObject._cacheId = returnObject.cacheId;
          resultObject._cmdIndex = returnObject.cmdIndex;
        }
        return resultObject;
      }
      return returnObject;
    }
  };

  /*
   * @param AKeyID [in] - Type on server: String
   * @param AFileName [in] - Type on server: String
   * @param AStream [in] - Type on server: TStream
   * @return result - Type on server: Boolean
   */
  this.UpdateHouseViewFile = function(AKeyID, AFileName, AStream) {
    var returnObject = this.executor.executeMethod('HouseViewFile', "POST", [AKeyID, AFileName, AStream], arguments[3], true, arguments[4], arguments[5]);
    if (arguments[3] == null) {
      if (returnObject != null && returnObject.result != null && isArray(returnObject.result)) {
        var resultArray = returnObject.result;
        var resultObject = new Object();
        resultObject.AKeyID = AKeyID;
        resultObject.AFileName = AFileName;
        resultObject.AStream = AStream;
        resultObject.result = resultArray[0];
        return resultObject;
      }
      return returnObject;
    }
  };
}

var JSProxyClassList = {
  "DSAdmin": ["GetPlatformName","ClearResources","FindPackages","FindClasses","FindMethods","CreateServerClasses","DropServerClasses","CreateServerMethods","DropServerMethods","GetServerClasses","ListClasses","DescribeClass","ListMethods","DescribeMethod","GetServerMethods","GetServerMethodParameters","GetDatabaseConnectionProperties","GetDSServerName","ConsumeClientChannel","ConsumeClientChannelTimeout","CloseClientChannel","RegisterClientCallbackServer","UnregisterClientCallback","BroadcastToChannel","BroadcastObjectToChannel","NotifyCallback","NotifyObject"],
  "TLoginUser": ["GetSysConnectionString","ChangePassword","UpdateCurUserCallbackClientID","Logout","SetUsersToFollow","SendMessageToFollow","SendMessageToAll","SendMessageToUser","SendMessageToDepartment","SendMessageToGroup","SendCMDToFollow","SendCMDToAll","SendCMDToUser","SendCMDToDepartment","SendCMDToGroup","SendMgrMessage","GetAccList","GetCurUserInfo","ListOfLoginUser","ListOfAllLoginUser","GetClassList","GetAutoCodeFields","GetModuleData","RefreshGlobeVar","GetModuleRight","GetAccInforJSON","GetAccListJSON","GetCurUserJSON","GetUserList","GetAllUserList","GetClassListJO","GetAutoCodeFieldsJO","GetModuleDataJO","RefreshGlobeVarJO","GetModuleRightJO","GetDepartmentAndUsersList","UserIdToName","GetServerInfo","GetFtpSetting","GetMailSetting","GetSmsSetting","GetWorkFlowServerList","GetSmsServerList"],
  "TSyAccBook": ["GetAllAccBook","GetActiveAccBook","GetAllAccBookJO","GetActiveAccBookJO"],
  "TServerDataSet": ["GetInitResult","Open","Update","Delete","DeleteDetail","CmdExec","Check","CloseOff","Revoke","Tally","ExecSQL","ValidateData","QueryOpen","QueryExecSQL","QuerySysOpen","QuerySysExecSQL"],
  "TServerQuery": ["QueryOpen","QueryExecSQL","ExecSQL","QuerySysOpen","QuerySysExecSQL","SysExecSQL"],
  "TJServerDataSet": ["GetInitResult","Open","Update","Delete","DeleteDetail","ValidateData","CmdExec","Check","CloseOff","Revoke","Tally","ExecSQL","QueryOpen","QueryExecSQL","QuerySysOpen","QuerySysExecSQL"],
  "TJServerQuery": ["QueryOpen","QueryUpdate","QueryExecSQL","QuerySysOpen","QuerySysExecSQL"],
  "TWorkFlowServer": ["ServerWorkFlowStartJSON","ServerWorkFlowStart","ServerWorkFlowExecJSON","ServerWorkFlowExec","GetTaskList","GetLogList","GetDiagram","GetTaskdefList","GetVariableList","GetVariableListDS","GetTaskdefListDS","GetWorkFlowChart","GetTaskListDS","TaskCanUpdate"],
  "TMessageManage": ["NewMessageGroup","DelMessageGroup","UpdateMessageGroup","NewMessageMember","UpdateMessageMember","DelMessageMember","GetMessageGroupList","GetGroupMemberList","GetAllEmployee","IsGroupMember","GetUserList","GetHTMLEscapedString","UpdateCurUserCallbackClientID","SendMessageToAll","SendMessageToUser","SendMessageToDepartment","SendMessageToGroup","SendMessageToJob","SendMessageToRole","SendMessageToFollow","SendCMDToFollow","SendCMDToAll","SendCMDToUser","SendCMDToDepartment","SendCMDToGroup","SendCMDToJob","SendCMDToRole","SendMgrMessage","SendMissMessage","GetLatelyMessage","SendMissMessageToUser","SendMissMessageToDepartment","SendMissMessageToGroup"],
  "TContractProject": ["GetContype","GetContlist","GetContdata","GetProtype","GetProlist","GetProdata"],
  "THouseView": ["GetHouseViewStream","UpdateHouseViewFile"]
};

