// 
// Created by the DataSnap proxy generator.
// 2014-10-31 15:27:28
// 

using System;
using System.Threading;

namespace Embarcadero.Datasnap.WindowsPhone7
{
  public class DSProxy
  {
    public class TLoginUser : DSAdmin
    {
      public TLoginUser(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TLoginUser_GetSysConnectionString_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetSysConnectionString_Metadata()
      {
        if (TLoginUser_GetSysConnectionString_Metadata == null)
        {
          TLoginUser_GetSysConnectionString_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TLoginUser_GetSysConnectionString_Metadata;
      }

      /**
       * @return result - Type on server: String
       */
      public delegate void GetSysConnectionStringCallback(String Result);

      public void GetSysConnectionString(GetSysConnectionStringCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetSysConnectionString");
        cmd.prepare(get_TLoginUser_GetSysConnectionString_Metadata());
        InternalConnectionDelegate GetSysConnectionStringDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetSysConnectionStringDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_ChangePassword_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_ChangePassword_Metadata()
      {
        if (TLoginUser_ChangePassword_Metadata == null)
        {
          TLoginUser_ChangePassword_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("UserCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("OldPassword", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("NewPassword", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("msg", DSRESTParamDirection.InputOutput, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_ChangePassword_Metadata;
      }

      /**
       * @param UserCode [in] - Type on server: String
       * @param OldPassword [in] - Type on server: String
       * @param NewPassword [in] - Type on server: String
       * @param msg [in/out] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public class ChangePasswordReturns
      {
        public String msg;
        public bool returnValue;
      }
      public delegate void ChangePasswordCallback(ChangePasswordReturns Returns);

      public void ChangePassword(String UserCode, String OldPassword, String NewPassword, String msg, ChangePasswordCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.ChangePassword");
        cmd.prepare(get_TLoginUser_ChangePassword_Metadata());
        InternalConnectionDelegate ChangePasswordDel = () =>
        {
          if (callback != null)
          {
            try
            {
              ChangePasswordReturns ret = new ChangePasswordReturns();
              ret.msg = cmd.getParameter(3).getValue().GetAsString();
              ret.returnValue = cmd.getParameter(4).getValue().GetAsBoolean();
              callback.DynamicInvoke(ret);
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(UserCode);
        cmd.getParameter(1).getValue().SetAsString(OldPassword);
        cmd.getParameter(2).getValue().SetAsString(NewPassword);
        cmd.getParameter(3).getValue().SetAsString(msg);
        getConnection().execute(cmd, this, ChangePasswordDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_UpdateCurUserCallbackClientID_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_UpdateCurUserCallbackClientID_Metadata()
      {
        if (TLoginUser_UpdateCurUserCallbackClientID_Metadata == null)
        {
          TLoginUser_UpdateCurUserCallbackClientID_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Value", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_UpdateCurUserCallbackClientID_Metadata;
      }

      /**
       * @param Value [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void UpdateCurUserCallbackClientIDCallback(bool Result);

      public void UpdateCurUserCallbackClientID(String Value, UpdateCurUserCallbackClientIDCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.UpdateCurUserCallbackClientID");
        cmd.prepare(get_TLoginUser_UpdateCurUserCallbackClientID_Metadata());
        InternalConnectionDelegate UpdateCurUserCallbackClientIDDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Value);
        getConnection().execute(cmd, this, UpdateCurUserCallbackClientIDDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_Logout_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_Logout_Metadata()
      {
        if (TLoginUser_Logout_Metadata == null)
        {
          TLoginUser_Logout_Metadata = new DSRESTParameterMetaData[]
          {
          };
        }
        return TLoginUser_Logout_Metadata;
      }

      public delegate void LogoutCallback();

      public void Logout(LogoutCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.Logout");
        cmd.prepare(get_TLoginUser_Logout_Metadata());
        InternalConnectionDelegate LogoutDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, LogoutDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SetUsersToFollow_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SetUsersToFollow_Metadata()
      {
        if (TLoginUser_SetUsersToFollow_Metadata == null)
        {
          TLoginUser_SetUsersToFollow_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Users", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_SetUsersToFollow_Metadata;
      }

      /**
       * @param Users [in] - Type on server: TJSONArray
       */
      public delegate void SetUsersToFollowCallback();

      public void SetUsersToFollow(TJSONArray Users, SetUsersToFollowCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TLoginUser.SetUsersToFollow");
        cmd.prepare(get_TLoginUser_SetUsersToFollow_Metadata());
        InternalConnectionDelegate SetUsersToFollowDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Users);
        getConnection().execute(cmd, this, SetUsersToFollowDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMessageToFollow_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMessageToFollow_Metadata()
      {
        if (TLoginUser_SendMessageToFollow_Metadata == null)
        {
          TLoginUser_SendMessageToFollow_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMessageToFollow_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToFollowCallback(bool Result);

      public void SendMessageToFollow(String Msg, SendMessageToFollowCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMessageToFollow");
        cmd.prepare(get_TLoginUser_SendMessageToFollow_Metadata());
        InternalConnectionDelegate SendMessageToFollowDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMessageToFollowDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMessageToAll_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMessageToAll_Metadata()
      {
        if (TLoginUser_SendMessageToAll_Metadata == null)
        {
          TLoginUser_SendMessageToAll_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMessageToAll_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToAllCallback(bool Result);

      public void SendMessageToAll(String Msg, SendMessageToAllCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMessageToAll");
        cmd.prepare(get_TLoginUser_SendMessageToAll_Metadata());
        InternalConnectionDelegate SendMessageToAllDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMessageToAllDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMessageToUser_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMessageToUser_Metadata()
      {
        if (TLoginUser_SendMessageToUser_Metadata == null)
        {
          TLoginUser_SendMessageToUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("UserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMessageToUser_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param UserID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToUserCallback(bool Result);

      public void SendMessageToUser(String Msg, String UserID, SendMessageToUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMessageToUser");
        cmd.prepare(get_TLoginUser_SendMessageToUser_Metadata());
        InternalConnectionDelegate SendMessageToUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(UserID);
        getConnection().execute(cmd, this, SendMessageToUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMessageToDepartment_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMessageToDepartment_Metadata()
      {
        if (TLoginUser_SendMessageToDepartment_Metadata == null)
        {
          TLoginUser_SendMessageToDepartment_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("DepartmentID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMessageToDepartment_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param DepartmentID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToDepartmentCallback(bool Result);

      public void SendMessageToDepartment(String Msg, String DepartmentID, SendMessageToDepartmentCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMessageToDepartment");
        cmd.prepare(get_TLoginUser_SendMessageToDepartment_Metadata());
        InternalConnectionDelegate SendMessageToDepartmentDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(DepartmentID);
        getConnection().execute(cmd, this, SendMessageToDepartmentDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMessageToGroup_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMessageToGroup_Metadata()
      {
        if (TLoginUser_SendMessageToGroup_Metadata == null)
        {
          TLoginUser_SendMessageToGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMessageToGroup_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param GroupID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToGroupCallback(bool Result);

      public void SendMessageToGroup(String Msg, String GroupID, SendMessageToGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMessageToGroup");
        cmd.prepare(get_TLoginUser_SendMessageToGroup_Metadata());
        InternalConnectionDelegate SendMessageToGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(GroupID);
        getConnection().execute(cmd, this, SendMessageToGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendCMDToFollow_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendCMDToFollow_Metadata()
      {
        if (TLoginUser_SendCMDToFollow_Metadata == null)
        {
          TLoginUser_SendCMDToFollow_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendCMDToFollow_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToFollowCallback(bool Result);

      public void SendCMDToFollow(String cmdStr, SendCMDToFollowCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendCMDToFollow");
        cmd.prepare(get_TLoginUser_SendCMDToFollow_Metadata());
        InternalConnectionDelegate SendCMDToFollowDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        getConnection().execute(cmd, this, SendCMDToFollowDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendCMDToAll_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendCMDToAll_Metadata()
      {
        if (TLoginUser_SendCMDToAll_Metadata == null)
        {
          TLoginUser_SendCMDToAll_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendCMDToAll_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToAllCallback(bool Result);

      public void SendCMDToAll(String cmdStr, SendCMDToAllCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendCMDToAll");
        cmd.prepare(get_TLoginUser_SendCMDToAll_Metadata());
        InternalConnectionDelegate SendCMDToAllDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        getConnection().execute(cmd, this, SendCMDToAllDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendCMDToUser_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendCMDToUser_Metadata()
      {
        if (TLoginUser_SendCMDToUser_Metadata == null)
        {
          TLoginUser_SendCMDToUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("UserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendCMDToUser_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param UserID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToUserCallback(bool Result);

      public void SendCMDToUser(String cmdStr, String UserID, SendCMDToUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendCMDToUser");
        cmd.prepare(get_TLoginUser_SendCMDToUser_Metadata());
        InternalConnectionDelegate SendCMDToUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(UserID);
        getConnection().execute(cmd, this, SendCMDToUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendCMDToDepartment_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendCMDToDepartment_Metadata()
      {
        if (TLoginUser_SendCMDToDepartment_Metadata == null)
        {
          TLoginUser_SendCMDToDepartment_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("DepartmentID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendCMDToDepartment_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param DepartmentID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToDepartmentCallback(bool Result);

      public void SendCMDToDepartment(String cmdStr, String DepartmentID, SendCMDToDepartmentCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendCMDToDepartment");
        cmd.prepare(get_TLoginUser_SendCMDToDepartment_Metadata());
        InternalConnectionDelegate SendCMDToDepartmentDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(DepartmentID);
        getConnection().execute(cmd, this, SendCMDToDepartmentDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendCMDToGroup_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendCMDToGroup_Metadata()
      {
        if (TLoginUser_SendCMDToGroup_Metadata == null)
        {
          TLoginUser_SendCMDToGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendCMDToGroup_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param GroupID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToGroupCallback(bool Result);

      public void SendCMDToGroup(String cmdStr, String GroupID, SendCMDToGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendCMDToGroup");
        cmd.prepare(get_TLoginUser_SendCMDToGroup_Metadata());
        InternalConnectionDelegate SendCMDToGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(GroupID);
        getConnection().execute(cmd, this, SendCMDToGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_SendMgrMessage_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_SendMgrMessage_Metadata()
      {
        if (TLoginUser_SendMgrMessage_Metadata == null)
        {
          TLoginUser_SendMgrMessage_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("itype", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TLoginUser_SendMgrMessage_Metadata;
      }

      /**
       * @param itype [in] - Type on server: Integer
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMgrMessageCallback(bool Result);

      public void SendMgrMessage(int itype, String Msg, SendMgrMessageCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.SendMgrMessage");
        cmd.prepare(get_TLoginUser_SendMgrMessage_Metadata());
        InternalConnectionDelegate SendMgrMessageDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsInt32(itype);
        cmd.getParameter(1).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMgrMessageDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAccList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAccList_Metadata()
      {
        if (TLoginUser_GetAccList_Metadata == null)
        {
          TLoginUser_GetAccList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetAccList_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetAccListCallback(TStream Result);

      public void GetAccList(GetAccListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAccList");
        cmd.prepare(get_TLoginUser_GetAccList_Metadata());
        InternalConnectionDelegate GetAccListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAccListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetCurUserInfo_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetCurUserInfo_Metadata()
      {
        if (TLoginUser_GetCurUserInfo_Metadata == null)
        {
          TLoginUser_GetCurUserInfo_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetCurUserInfo_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetCurUserInfoCallback(TStream Result);

      public void GetCurUserInfo(GetCurUserInfoCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetCurUserInfo");
        cmd.prepare(get_TLoginUser_GetCurUserInfo_Metadata());
        InternalConnectionDelegate GetCurUserInfoDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetCurUserInfoDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_ListOfLoginUser_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_ListOfLoginUser_Metadata()
      {
        if (TLoginUser_ListOfLoginUser_Metadata == null)
        {
          TLoginUser_ListOfLoginUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_ListOfLoginUser_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void ListOfLoginUserCallback(TStream Result);

      public void ListOfLoginUser(ListOfLoginUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.ListOfLoginUser");
        cmd.prepare(get_TLoginUser_ListOfLoginUser_Metadata());
        InternalConnectionDelegate ListOfLoginUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, ListOfLoginUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_ListOfAllLoginUser_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_ListOfAllLoginUser_Metadata()
      {
        if (TLoginUser_ListOfAllLoginUser_Metadata == null)
        {
          TLoginUser_ListOfAllLoginUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_ListOfAllLoginUser_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void ListOfAllLoginUserCallback(TStream Result);

      public void ListOfAllLoginUser(ListOfAllLoginUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.ListOfAllLoginUser");
        cmd.prepare(get_TLoginUser_ListOfAllLoginUser_Metadata());
        InternalConnectionDelegate ListOfAllLoginUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, ListOfAllLoginUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetClassList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetClassList_Metadata()
      {
        if (TLoginUser_GetClassList_Metadata == null)
        {
          TLoginUser_GetClassList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetClassList_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetClassListCallback(TStream Result);

      public void GetClassList(GetClassListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetClassList");
        cmd.prepare(get_TLoginUser_GetClassList_Metadata());
        InternalConnectionDelegate GetClassListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetClassListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAutoCodeFields_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAutoCodeFields_Metadata()
      {
        if (TLoginUser_GetAutoCodeFields_Metadata == null)
        {
          TLoginUser_GetAutoCodeFields_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetAutoCodeFields_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetAutoCodeFieldsCallback(TStream Result);

      public void GetAutoCodeFields(GetAutoCodeFieldsCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAutoCodeFields");
        cmd.prepare(get_TLoginUser_GetAutoCodeFields_Metadata());
        InternalConnectionDelegate GetAutoCodeFieldsDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAutoCodeFieldsDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetModuleData_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetModuleData_Metadata()
      {
        if (TLoginUser_GetModuleData_Metadata == null)
        {
          TLoginUser_GetModuleData_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetModuleData_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetModuleDataCallback(TStream Result);

      public void GetModuleData(GetModuleDataCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetModuleData");
        cmd.prepare(get_TLoginUser_GetModuleData_Metadata());
        InternalConnectionDelegate GetModuleDataDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetModuleDataDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_RefreshGlobeVar_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_RefreshGlobeVar_Metadata()
      {
        if (TLoginUser_RefreshGlobeVar_Metadata == null)
        {
          TLoginUser_RefreshGlobeVar_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_RefreshGlobeVar_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void RefreshGlobeVarCallback(TStream Result);

      public void RefreshGlobeVar(RefreshGlobeVarCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.RefreshGlobeVar");
        cmd.prepare(get_TLoginUser_RefreshGlobeVar_Metadata());
        InternalConnectionDelegate RefreshGlobeVarDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, RefreshGlobeVarDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetModuleRight_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetModuleRight_Metadata()
      {
        if (TLoginUser_GetModuleRight_Metadata == null)
        {
          TLoginUser_GetModuleRight_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TLoginUser_GetModuleRight_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetModuleRightCallback(TStream Result);

      public void GetModuleRight(GetModuleRightCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetModuleRight");
        cmd.prepare(get_TLoginUser_GetModuleRight_Metadata());
        InternalConnectionDelegate GetModuleRightDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetModuleRightDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAccInforJSON_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAccInforJSON_Metadata()
      {
        if (TLoginUser_GetAccInforJSON_Metadata == null)
        {
          TLoginUser_GetAccInforJSON_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetAccInforJSON_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetAccInforJSONCallback(TJSONObject Result);

      public void GetAccInforJSON(GetAccInforJSONCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAccInforJSON");
        cmd.prepare(get_TLoginUser_GetAccInforJSON_Metadata());
        InternalConnectionDelegate GetAccInforJSONDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAccInforJSONDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAccListJSON_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAccListJSON_Metadata()
      {
        if (TLoginUser_GetAccListJSON_Metadata == null)
        {
          TLoginUser_GetAccListJSON_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetAccListJSON_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetAccListJSONCallback(TJSONObject Result);

      public void GetAccListJSON(GetAccListJSONCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAccListJSON");
        cmd.prepare(get_TLoginUser_GetAccListJSON_Metadata());
        InternalConnectionDelegate GetAccListJSONDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAccListJSONDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetCurUserJSON_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetCurUserJSON_Metadata()
      {
        if (TLoginUser_GetCurUserJSON_Metadata == null)
        {
          TLoginUser_GetCurUserJSON_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetCurUserJSON_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetCurUserJSONCallback(TJSONObject Result);

      public void GetCurUserJSON(GetCurUserJSONCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetCurUserJSON");
        cmd.prepare(get_TLoginUser_GetCurUserJSON_Metadata());
        InternalConnectionDelegate GetCurUserJSONDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetCurUserJSONDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetUserList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetUserList_Metadata()
      {
        if (TLoginUser_GetUserList_Metadata == null)
        {
          TLoginUser_GetUserList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_GetUserList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetUserListCallback(TJSONArray Result);

      public void GetUserList(GetUserListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetUserList");
        cmd.prepare(get_TLoginUser_GetUserList_Metadata());
        InternalConnectionDelegate GetUserListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetUserListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAllUserList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAllUserList_Metadata()
      {
        if (TLoginUser_GetAllUserList_Metadata == null)
        {
          TLoginUser_GetAllUserList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_GetAllUserList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetAllUserListCallback(TJSONArray Result);

      public void GetAllUserList(GetAllUserListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAllUserList");
        cmd.prepare(get_TLoginUser_GetAllUserList_Metadata());
        InternalConnectionDelegate GetAllUserListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAllUserListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetClassListJO_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetClassListJO_Metadata()
      {
        if (TLoginUser_GetClassListJO_Metadata == null)
        {
          TLoginUser_GetClassListJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetClassListJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetClassListJOCallback(TJSONObject Result);

      public void GetClassListJO(GetClassListJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetClassListJO");
        cmd.prepare(get_TLoginUser_GetClassListJO_Metadata());
        InternalConnectionDelegate GetClassListJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetClassListJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetAutoCodeFieldsJO_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetAutoCodeFieldsJO_Metadata()
      {
        if (TLoginUser_GetAutoCodeFieldsJO_Metadata == null)
        {
          TLoginUser_GetAutoCodeFieldsJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetAutoCodeFieldsJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetAutoCodeFieldsJOCallback(TJSONObject Result);

      public void GetAutoCodeFieldsJO(GetAutoCodeFieldsJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetAutoCodeFieldsJO");
        cmd.prepare(get_TLoginUser_GetAutoCodeFieldsJO_Metadata());
        InternalConnectionDelegate GetAutoCodeFieldsJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAutoCodeFieldsJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetModuleDataJO_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetModuleDataJO_Metadata()
      {
        if (TLoginUser_GetModuleDataJO_Metadata == null)
        {
          TLoginUser_GetModuleDataJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetModuleDataJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetModuleDataJOCallback(TJSONObject Result);

      public void GetModuleDataJO(GetModuleDataJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetModuleDataJO");
        cmd.prepare(get_TLoginUser_GetModuleDataJO_Metadata());
        InternalConnectionDelegate GetModuleDataJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetModuleDataJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_RefreshGlobeVarJO_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_RefreshGlobeVarJO_Metadata()
      {
        if (TLoginUser_RefreshGlobeVarJO_Metadata == null)
        {
          TLoginUser_RefreshGlobeVarJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_RefreshGlobeVarJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void RefreshGlobeVarJOCallback(TJSONObject Result);

      public void RefreshGlobeVarJO(RefreshGlobeVarJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.RefreshGlobeVarJO");
        cmd.prepare(get_TLoginUser_RefreshGlobeVarJO_Metadata());
        InternalConnectionDelegate RefreshGlobeVarJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, RefreshGlobeVarJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetModuleRightJO_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetModuleRightJO_Metadata()
      {
        if (TLoginUser_GetModuleRightJO_Metadata == null)
        {
          TLoginUser_GetModuleRightJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetModuleRightJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetModuleRightJOCallback(TJSONObject Result);

      public void GetModuleRightJO(GetModuleRightJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetModuleRightJO");
        cmd.prepare(get_TLoginUser_GetModuleRightJO_Metadata());
        InternalConnectionDelegate GetModuleRightJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetModuleRightJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetDepartmentAndUsersList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetDepartmentAndUsersList_Metadata()
      {
        if (TLoginUser_GetDepartmentAndUsersList_Metadata == null)
        {
          TLoginUser_GetDepartmentAndUsersList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_GetDepartmentAndUsersList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetDepartmentAndUsersListCallback(TJSONArray Result);

      public void GetDepartmentAndUsersList(GetDepartmentAndUsersListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetDepartmentAndUsersList");
        cmd.prepare(get_TLoginUser_GetDepartmentAndUsersList_Metadata());
        InternalConnectionDelegate GetDepartmentAndUsersListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetDepartmentAndUsersListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_UserIdToName_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_UserIdToName_Metadata()
      {
        if (TLoginUser_UserIdToName_Metadata == null)
        {
          TLoginUser_UserIdToName_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("UserId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TLoginUser_UserIdToName_Metadata;
      }

      /**
       * @param UserId [in] - Type on server: String
       * @return result - Type on server: String
       */
      public delegate void UserIdToNameCallback(String Result);

      public void UserIdToName(String UserId, UserIdToNameCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.UserIdToName");
        cmd.prepare(get_TLoginUser_UserIdToName_Metadata());
        InternalConnectionDelegate UserIdToNameDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(UserId);
        getConnection().execute(cmd, this, UserIdToNameDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetServerInfo_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetServerInfo_Metadata()
      {
        if (TLoginUser_GetServerInfo_Metadata == null)
        {
          TLoginUser_GetServerInfo_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetServerInfo_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetServerInfoCallback(TJSONObject Result);

      public void GetServerInfo(GetServerInfoCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetServerInfo");
        cmd.prepare(get_TLoginUser_GetServerInfo_Metadata());
        InternalConnectionDelegate GetServerInfoDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetServerInfoDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetFtpSetting_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetFtpSetting_Metadata()
      {
        if (TLoginUser_GetFtpSetting_Metadata == null)
        {
          TLoginUser_GetFtpSetting_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetFtpSetting_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetFtpSettingCallback(TJSONObject Result);

      public void GetFtpSetting(GetFtpSettingCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetFtpSetting");
        cmd.prepare(get_TLoginUser_GetFtpSetting_Metadata());
        InternalConnectionDelegate GetFtpSettingDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetFtpSettingDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetMailSetting_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetMailSetting_Metadata()
      {
        if (TLoginUser_GetMailSetting_Metadata == null)
        {
          TLoginUser_GetMailSetting_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetMailSetting_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetMailSettingCallback(TJSONObject Result);

      public void GetMailSetting(GetMailSettingCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetMailSetting");
        cmd.prepare(get_TLoginUser_GetMailSetting_Metadata());
        InternalConnectionDelegate GetMailSettingDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetMailSettingDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetSmsSetting_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetSmsSetting_Metadata()
      {
        if (TLoginUser_GetSmsSetting_Metadata == null)
        {
          TLoginUser_GetSmsSetting_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TLoginUser_GetSmsSetting_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetSmsSettingCallback(TJSONObject Result);

      public void GetSmsSetting(GetSmsSettingCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetSmsSetting");
        cmd.prepare(get_TLoginUser_GetSmsSetting_Metadata());
        InternalConnectionDelegate GetSmsSettingDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetSmsSettingDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetWorkFlowServerList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetWorkFlowServerList_Metadata()
      {
        if (TLoginUser_GetWorkFlowServerList_Metadata == null)
        {
          TLoginUser_GetWorkFlowServerList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_GetWorkFlowServerList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetWorkFlowServerListCallback(TJSONArray Result);

      public void GetWorkFlowServerList(GetWorkFlowServerListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetWorkFlowServerList");
        cmd.prepare(get_TLoginUser_GetWorkFlowServerList_Metadata());
        InternalConnectionDelegate GetWorkFlowServerListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetWorkFlowServerListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TLoginUser_GetSmsServerList_Metadata;
      private DSRESTParameterMetaData[] get_TLoginUser_GetSmsServerList_Metadata()
      {
        if (TLoginUser_GetSmsServerList_Metadata == null)
        {
          TLoginUser_GetSmsServerList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TLoginUser_GetSmsServerList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetSmsServerListCallback(TJSONArray Result);

      public void GetSmsServerList(GetSmsServerListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TLoginUser.GetSmsServerList");
        cmd.prepare(get_TLoginUser_GetSmsServerList_Metadata());
        InternalConnectionDelegate GetSmsServerListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetSmsServerListDel, ExCal);
      }
    }

    public class TSyAccBook : DSAdmin
    {
      public TSyAccBook(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TSyAccBook_GetAllAccBook_Metadata;
      private DSRESTParameterMetaData[] get_TSyAccBook_GetAllAccBook_Metadata()
      {
        if (TSyAccBook_GetAllAccBook_Metadata == null)
        {
          TSyAccBook_GetAllAccBook_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TSyAccBook_GetAllAccBook_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetAllAccBookCallback(TStream Result);

      public void GetAllAccBook(GetAllAccBookCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TSyAccBook.GetAllAccBook");
        cmd.prepare(get_TSyAccBook_GetAllAccBook_Metadata());
        InternalConnectionDelegate GetAllAccBookDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAllAccBookDel, ExCal);
      }
      private DSRESTParameterMetaData[] TSyAccBook_GetActiveAccBook_Metadata;
      private DSRESTParameterMetaData[] get_TSyAccBook_GetActiveAccBook_Metadata()
      {
        if (TSyAccBook_GetActiveAccBook_Metadata == null)
        {
          TSyAccBook_GetActiveAccBook_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TSyAccBook_GetActiveAccBook_Metadata;
      }

      /**
       * @return result - Type on server: TStream
       */
      public delegate void GetActiveAccBookCallback(TStream Result);

      public void GetActiveAccBook(GetActiveAccBookCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TSyAccBook.GetActiveAccBook");
        cmd.prepare(get_TSyAccBook_GetActiveAccBook_Metadata());
        InternalConnectionDelegate GetActiveAccBookDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(0).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetActiveAccBookDel, ExCal);
      }
      private DSRESTParameterMetaData[] TSyAccBook_GetAllAccBookJO_Metadata;
      private DSRESTParameterMetaData[] get_TSyAccBook_GetAllAccBookJO_Metadata()
      {
        if (TSyAccBook_GetAllAccBookJO_Metadata == null)
        {
          TSyAccBook_GetAllAccBookJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TSyAccBook_GetAllAccBookJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetAllAccBookJOCallback(TJSONObject Result);

      public void GetAllAccBookJO(GetAllAccBookJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TSyAccBook.GetAllAccBookJO");
        cmd.prepare(get_TSyAccBook_GetAllAccBookJO_Metadata());
        InternalConnectionDelegate GetAllAccBookJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetAllAccBookJODel, ExCal);
      }
      private DSRESTParameterMetaData[] TSyAccBook_GetActiveAccBookJO_Metadata;
      private DSRESTParameterMetaData[] get_TSyAccBook_GetActiveAccBookJO_Metadata()
      {
        if (TSyAccBook_GetActiveAccBookJO_Metadata == null)
        {
          TSyAccBook_GetActiveAccBookJO_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TSyAccBook_GetActiveAccBookJO_Metadata;
      }

      /**
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetActiveAccBookJOCallback(TJSONObject Result);

      public void GetActiveAccBookJO(GetActiveAccBookJOCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TSyAccBook.GetActiveAccBookJO");
        cmd.prepare(get_TSyAccBook_GetActiveAccBookJO_Metadata());
        InternalConnectionDelegate GetActiveAccBookJODel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetActiveAccBookJODel, ExCal);
      }
    }

    public class TServerDataSet : DSAdmin
    {
      public TServerDataSet(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TServerDataSet_GetInitResult_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_GetInitResult_Metadata()
      {
        if (TServerDataSet_GetInitResult_Metadata == null)
        {
          TServerDataSet_GetInitResult_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_GetInitResult_Metadata;
      }

      /**
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void GetInitResultCallback(TStream Result);

      public void GetInitResult(String ClassCode, GetInitResultCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerDataSet.GetInitResult");
        cmd.prepare(get_TServerDataSet_GetInitResult_Metadata());
        InternalConnectionDelegate GetInitResultDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, GetInitResultDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Open_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Open_Metadata()
      {
        if (TServerDataSet_Open_Metadata == null)
        {
          TServerDataSet_Open_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Open_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void OpenCallback(TStream Result);

      public void Open(TStream Stream, String ClassCode, OpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Open");
        cmd.prepare(get_TServerDataSet_Open_Metadata());
        InternalConnectionDelegate OpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, OpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Update_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Update_Metadata()
      {
        if (TServerDataSet_Update_Metadata == null)
        {
          TServerDataSet_Update_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Update_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void UpdateCallback(TStream Result);

      public void Update(TStream Stream, String ClassCode, UpdateCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Update");
        cmd.prepare(get_TServerDataSet_Update_Metadata());
        InternalConnectionDelegate UpdateDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, UpdateDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Delete_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Delete_Metadata()
      {
        if (TServerDataSet_Delete_Metadata == null)
        {
          TServerDataSet_Delete_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Delete_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void DeleteCallback(TStream Result);

      public void Delete(TStream Stream, String ClassCode, DeleteCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Delete");
        cmd.prepare(get_TServerDataSet_Delete_Metadata());
        InternalConnectionDelegate DeleteDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, DeleteDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_DeleteDetail_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_DeleteDetail_Metadata()
      {
        if (TServerDataSet_DeleteDetail_Metadata == null)
        {
          TServerDataSet_DeleteDetail_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_DeleteDetail_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void DeleteDetailCallback(TStream Result);

      public void DeleteDetail(TStream Stream, String ClassCode, DeleteDetailCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.DeleteDetail");
        cmd.prepare(get_TServerDataSet_DeleteDetail_Metadata());
        InternalConnectionDelegate DeleteDetailDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, DeleteDetailDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_CmdExec_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_CmdExec_Metadata()
      {
        if (TServerDataSet_CmdExec_Metadata == null)
        {
          TServerDataSet_CmdExec_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_CmdExec_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void CmdExecCallback(TStream Result);

      public void CmdExec(TStream Stream, String ClassCode, CmdExecCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.CmdExec");
        cmd.prepare(get_TServerDataSet_CmdExec_Metadata());
        InternalConnectionDelegate CmdExecDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CmdExecDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Check_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Check_Metadata()
      {
        if (TServerDataSet_Check_Metadata == null)
        {
          TServerDataSet_Check_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Check_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void CheckCallback(TStream Result);

      public void Check(TStream Stream, String ClassCode, CheckCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Check");
        cmd.prepare(get_TServerDataSet_Check_Metadata());
        InternalConnectionDelegate CheckDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CheckDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_CloseOff_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_CloseOff_Metadata()
      {
        if (TServerDataSet_CloseOff_Metadata == null)
        {
          TServerDataSet_CloseOff_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_CloseOff_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void CloseOffCallback(TStream Result);

      public void CloseOff(TStream Stream, String ClassCode, CloseOffCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.CloseOff");
        cmd.prepare(get_TServerDataSet_CloseOff_Metadata());
        InternalConnectionDelegate CloseOffDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CloseOffDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Revoke_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Revoke_Metadata()
      {
        if (TServerDataSet_Revoke_Metadata == null)
        {
          TServerDataSet_Revoke_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Revoke_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void RevokeCallback(TStream Result);

      public void Revoke(TStream Stream, String ClassCode, RevokeCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Revoke");
        cmd.prepare(get_TServerDataSet_Revoke_Metadata());
        InternalConnectionDelegate RevokeDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, RevokeDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_Tally_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_Tally_Metadata()
      {
        if (TServerDataSet_Tally_Metadata == null)
        {
          TServerDataSet_Tally_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_Tally_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void TallyCallback(TStream Result);

      public void Tally(TStream Stream, String ClassCode, TallyCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.Tally");
        cmd.prepare(get_TServerDataSet_Tally_Metadata());
        InternalConnectionDelegate TallyDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, TallyDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_ExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_ExecSQL_Metadata()
      {
        if (TServerDataSet_ExecSQL_Metadata == null)
        {
          TServerDataSet_ExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_ExecSQL_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @return result - Type on server: TStream
       */
      public delegate void ExecSQLCallback(TStream Result);

      public void ExecSQL(TStream Stream, ExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.ExecSQL");
        cmd.prepare(get_TServerDataSet_ExecSQL_Metadata());
        InternalConnectionDelegate ExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        getConnection().execute(cmd, this, ExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_ValidateData_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_ValidateData_Metadata()
      {
        if (TServerDataSet_ValidateData_Metadata == null)
        {
          TServerDataSet_ValidateData_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Stream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_ValidateData_Metadata;
      }

      /**
       * @param Stream [in] - Type on server: TStream
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void ValidateDataCallback(TStream Result);

      public void ValidateData(TStream Stream, String ClassCode, ValidateDataCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerDataSet.ValidateData");
        cmd.prepare(get_TServerDataSet_ValidateData_Metadata());
        InternalConnectionDelegate ValidateDataDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsStream(Stream);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, ValidateDataDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_QueryOpen_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_QueryOpen_Metadata()
      {
        if (TServerDataSet_QueryOpen_Metadata == null)
        {
          TServerDataSet_QueryOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_QueryOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QueryOpenCallback(TStream Result);

      public void QueryOpen(String SQLText, QueryOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerDataSet.QueryOpen");
        cmd.prepare(get_TServerDataSet_QueryOpen_Metadata());
        InternalConnectionDelegate QueryOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_QueryExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_QueryExecSQL_Metadata()
      {
        if (TServerDataSet_QueryExecSQL_Metadata == null)
        {
          TServerDataSet_QueryExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_QueryExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QueryExecSQLCallback(TStream Result);

      public void QueryExecSQL(String SQLText, QueryExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerDataSet.QueryExecSQL");
        cmd.prepare(get_TServerDataSet_QueryExecSQL_Metadata());
        InternalConnectionDelegate QueryExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_QuerySysOpen_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_QuerySysOpen_Metadata()
      {
        if (TServerDataSet_QuerySysOpen_Metadata == null)
        {
          TServerDataSet_QuerySysOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_QuerySysOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QuerySysOpenCallback(TStream Result);

      public void QuerySysOpen(String SQLText, QuerySysOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerDataSet.QuerySysOpen");
        cmd.prepare(get_TServerDataSet_QuerySysOpen_Metadata());
        InternalConnectionDelegate QuerySysOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerDataSet_QuerySysExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerDataSet_QuerySysExecSQL_Metadata()
      {
        if (TServerDataSet_QuerySysExecSQL_Metadata == null)
        {
          TServerDataSet_QuerySysExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerDataSet_QuerySysExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QuerySysExecSQLCallback(TStream Result);

      public void QuerySysExecSQL(String SQLText, QuerySysExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerDataSet.QuerySysExecSQL");
        cmd.prepare(get_TServerDataSet_QuerySysExecSQL_Metadata());
        InternalConnectionDelegate QuerySysExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysExecSQLDel, ExCal);
      }
    }

    public class TServerQuery : DSAdmin
    {
      public TServerQuery(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TServerQuery_QueryOpen_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_QueryOpen_Metadata()
      {
        if (TServerQuery_QueryOpen_Metadata == null)
        {
          TServerQuery_QueryOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerQuery_QueryOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QueryOpenCallback(TStream Result);

      public void QueryOpen(String SQLText, QueryOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerQuery.QueryOpen");
        cmd.prepare(get_TServerQuery_QueryOpen_Metadata());
        InternalConnectionDelegate QueryOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerQuery_QueryExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_QueryExecSQL_Metadata()
      {
        if (TServerQuery_QueryExecSQL_Metadata == null)
        {
          TServerQuery_QueryExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TServerQuery_QueryExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: Integer
       */
      public delegate void QueryExecSQLCallback(int Result);

      public void QueryExecSQL(String SQLText, QueryExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerQuery.QueryExecSQL");
        cmd.prepare(get_TServerQuery_QueryExecSQL_Metadata());
        InternalConnectionDelegate QueryExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerQuery_ExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_ExecSQL_Metadata()
      {
        if (TServerQuery_ExecSQL_Metadata == null)
        {
          TServerQuery_ExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Parameters", DSRESTParamDirection.Input, DBXDataTypes.TableType, "TParams"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TServerQuery_ExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @param Parameters [in] - Type on server: TParams
       * @return result - Type on server: Integer
       */
      public delegate void ExecSQLCallback(int Result);

      public void ExecSQL(String SQLText, TParams Parameters, ExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerQuery.ExecSQL");
        cmd.prepare(get_TServerQuery_ExecSQL_Metadata());
        InternalConnectionDelegate ExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        cmd.getParameter(1).getValue().SetAsTable(Parameters);
        getConnection().execute(cmd, this, ExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerQuery_QuerySysOpen_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_QuerySysOpen_Metadata()
      {
        if (TServerQuery_QuerySysOpen_Metadata == null)
        {
          TServerQuery_QuerySysOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TServerQuery_QuerySysOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void QuerySysOpenCallback(TStream Result);

      public void QuerySysOpen(String SQLText, QuerySysOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerQuery.QuerySysOpen");
        cmd.prepare(get_TServerQuery_QuerySysOpen_Metadata());
        InternalConnectionDelegate QuerySysOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerQuery_QuerySysExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_QuerySysExecSQL_Metadata()
      {
        if (TServerQuery_QuerySysExecSQL_Metadata == null)
        {
          TServerQuery_QuerySysExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TServerQuery_QuerySysExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: Integer
       */
      public delegate void QuerySysExecSQLCallback(int Result);

      public void QuerySysExecSQL(String SQLText, QuerySysExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TServerQuery.QuerySysExecSQL");
        cmd.prepare(get_TServerQuery_QuerySysExecSQL_Metadata());
        InternalConnectionDelegate QuerySysExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TServerQuery_SysExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TServerQuery_SysExecSQL_Metadata()
      {
        if (TServerQuery_SysExecSQL_Metadata == null)
        {
          TServerQuery_SysExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Parameters", DSRESTParamDirection.Input, DBXDataTypes.TableType, "TParams"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TServerQuery_SysExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @param Parameters [in] - Type on server: TParams
       * @return result - Type on server: Integer
       */
      public delegate void SysExecSQLCallback(int Result);

      public void SysExecSQL(String SQLText, TParams Parameters, SysExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TServerQuery.SysExecSQL");
        cmd.prepare(get_TServerQuery_SysExecSQL_Metadata());
        InternalConnectionDelegate SysExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        cmd.getParameter(1).getValue().SetAsTable(Parameters);
        getConnection().execute(cmd, this, SysExecSQLDel, ExCal);
      }
    }

    public class TJServerDataSet : DSAdmin
    {
      public TJServerDataSet(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TJServerDataSet_GetInitResult_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_GetInitResult_Metadata()
      {
        if (TJServerDataSet_GetInitResult_Metadata == null)
        {
          TJServerDataSet_GetInitResult_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_GetInitResult_Metadata;
      }

      /**
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetInitResultCallback(TJSONObject Result);

      public void GetInitResult(String ClassCode, GetInitResultCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerDataSet.GetInitResult");
        cmd.prepare(get_TJServerDataSet_GetInitResult_Metadata());
        InternalConnectionDelegate GetInitResultDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, GetInitResultDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Open_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Open_Metadata()
      {
        if (TJServerDataSet_Open_Metadata == null)
        {
          TJServerDataSet_Open_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Open_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void OpenCallback(TJSONObject Result);

      public void Open(TJSONObject Json, String ClassCode, OpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Open");
        cmd.prepare(get_TJServerDataSet_Open_Metadata());
        InternalConnectionDelegate OpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, OpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Update_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Update_Metadata()
      {
        if (TJServerDataSet_Update_Metadata == null)
        {
          TJServerDataSet_Update_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Update_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void UpdateCallback(TJSONObject Result);

      public void Update(TJSONObject Json, String ClassCode, UpdateCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Update");
        cmd.prepare(get_TJServerDataSet_Update_Metadata());
        InternalConnectionDelegate UpdateDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, UpdateDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Delete_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Delete_Metadata()
      {
        if (TJServerDataSet_Delete_Metadata == null)
        {
          TJServerDataSet_Delete_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Delete_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void DeleteCallback(TJSONObject Result);

      public void Delete(TJSONObject Json, String ClassCode, DeleteCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Delete");
        cmd.prepare(get_TJServerDataSet_Delete_Metadata());
        InternalConnectionDelegate DeleteDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, DeleteDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_DeleteDetail_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_DeleteDetail_Metadata()
      {
        if (TJServerDataSet_DeleteDetail_Metadata == null)
        {
          TJServerDataSet_DeleteDetail_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_DeleteDetail_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void DeleteDetailCallback(TJSONObject Result);

      public void DeleteDetail(TJSONObject Json, String ClassCode, DeleteDetailCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.DeleteDetail");
        cmd.prepare(get_TJServerDataSet_DeleteDetail_Metadata());
        InternalConnectionDelegate DeleteDetailDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, DeleteDetailDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_ValidateData_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_ValidateData_Metadata()
      {
        if (TJServerDataSet_ValidateData_Metadata == null)
        {
          TJServerDataSet_ValidateData_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_ValidateData_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void ValidateDataCallback(TJSONObject Result);

      public void ValidateData(TJSONObject Json, String ClassCode, ValidateDataCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.ValidateData");
        cmd.prepare(get_TJServerDataSet_ValidateData_Metadata());
        InternalConnectionDelegate ValidateDataDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, ValidateDataDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_CmdExec_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_CmdExec_Metadata()
      {
        if (TJServerDataSet_CmdExec_Metadata == null)
        {
          TJServerDataSet_CmdExec_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_CmdExec_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void CmdExecCallback(TJSONObject Result);

      public void CmdExec(TJSONObject Json, String ClassCode, CmdExecCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.CmdExec");
        cmd.prepare(get_TJServerDataSet_CmdExec_Metadata());
        InternalConnectionDelegate CmdExecDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CmdExecDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Check_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Check_Metadata()
      {
        if (TJServerDataSet_Check_Metadata == null)
        {
          TJServerDataSet_Check_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Check_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void CheckCallback(TJSONObject Result);

      public void Check(TJSONObject Json, String ClassCode, CheckCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Check");
        cmd.prepare(get_TJServerDataSet_Check_Metadata());
        InternalConnectionDelegate CheckDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CheckDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_CloseOff_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_CloseOff_Metadata()
      {
        if (TJServerDataSet_CloseOff_Metadata == null)
        {
          TJServerDataSet_CloseOff_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_CloseOff_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void CloseOffCallback(TJSONObject Result);

      public void CloseOff(TJSONObject Json, String ClassCode, CloseOffCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.CloseOff");
        cmd.prepare(get_TJServerDataSet_CloseOff_Metadata());
        InternalConnectionDelegate CloseOffDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, CloseOffDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Revoke_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Revoke_Metadata()
      {
        if (TJServerDataSet_Revoke_Metadata == null)
        {
          TJServerDataSet_Revoke_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Revoke_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void RevokeCallback(TJSONObject Result);

      public void Revoke(TJSONObject Json, String ClassCode, RevokeCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Revoke");
        cmd.prepare(get_TJServerDataSet_Revoke_Metadata());
        InternalConnectionDelegate RevokeDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, RevokeDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_Tally_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_Tally_Metadata()
      {
        if (TJServerDataSet_Tally_Metadata == null)
        {
          TJServerDataSet_Tally_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_Tally_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void TallyCallback(TJSONObject Result);

      public void Tally(TJSONObject Json, String ClassCode, TallyCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.Tally");
        cmd.prepare(get_TJServerDataSet_Tally_Metadata());
        InternalConnectionDelegate TallyDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, TallyDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_ExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_ExecSQL_Metadata()
      {
        if (TJServerDataSet_ExecSQL_Metadata == null)
        {
          TJServerDataSet_ExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_ExecSQL_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @return result - Type on server: TJSONObject
       */
      public delegate void ExecSQLCallback(TJSONObject Result);

      public void ExecSQL(TJSONObject Json, ExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerDataSet.ExecSQL");
        cmd.prepare(get_TJServerDataSet_ExecSQL_Metadata());
        InternalConnectionDelegate ExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        getConnection().execute(cmd, this, ExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_QueryOpen_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_QueryOpen_Metadata()
      {
        if (TJServerDataSet_QueryOpen_Metadata == null)
        {
          TJServerDataSet_QueryOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_QueryOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QueryOpenCallback(TJSONObject Result);

      public void QueryOpen(String SQLText, QueryOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerDataSet.QueryOpen");
        cmd.prepare(get_TJServerDataSet_QueryOpen_Metadata());
        InternalConnectionDelegate QueryOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_QueryExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_QueryExecSQL_Metadata()
      {
        if (TJServerDataSet_QueryExecSQL_Metadata == null)
        {
          TJServerDataSet_QueryExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_QueryExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QueryExecSQLCallback(TJSONObject Result);

      public void QueryExecSQL(String SQLText, QueryExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerDataSet.QueryExecSQL");
        cmd.prepare(get_TJServerDataSet_QueryExecSQL_Metadata());
        InternalConnectionDelegate QueryExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_QuerySysOpen_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_QuerySysOpen_Metadata()
      {
        if (TJServerDataSet_QuerySysOpen_Metadata == null)
        {
          TJServerDataSet_QuerySysOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_QuerySysOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QuerySysOpenCallback(TJSONObject Result);

      public void QuerySysOpen(String SQLText, QuerySysOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerDataSet.QuerySysOpen");
        cmd.prepare(get_TJServerDataSet_QuerySysOpen_Metadata());
        InternalConnectionDelegate QuerySysOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerDataSet_QuerySysExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TJServerDataSet_QuerySysExecSQL_Metadata()
      {
        if (TJServerDataSet_QuerySysExecSQL_Metadata == null)
        {
          TJServerDataSet_QuerySysExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerDataSet_QuerySysExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QuerySysExecSQLCallback(TJSONObject Result);

      public void QuerySysExecSQL(String SQLText, QuerySysExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerDataSet.QuerySysExecSQL");
        cmd.prepare(get_TJServerDataSet_QuerySysExecSQL_Metadata());
        InternalConnectionDelegate QuerySysExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysExecSQLDel, ExCal);
      }
    }

    public class TJServerQuery : DSAdmin
    {
      public TJServerQuery(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TJServerQuery_QueryOpen_Metadata;
      private DSRESTParameterMetaData[] get_TJServerQuery_QueryOpen_Metadata()
      {
        if (TJServerQuery_QueryOpen_Metadata == null)
        {
          TJServerQuery_QueryOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerQuery_QueryOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QueryOpenCallback(TJSONObject Result);

      public void QueryOpen(String SQLText, QueryOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerQuery.QueryOpen");
        cmd.prepare(get_TJServerQuery_QueryOpen_Metadata());
        InternalConnectionDelegate QueryOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerQuery_QueryUpdate_Metadata;
      private DSRESTParameterMetaData[] get_TJServerQuery_QueryUpdate_Metadata()
      {
        if (TJServerQuery_QueryUpdate_Metadata == null)
        {
          TJServerQuery_QueryUpdate_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Json", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("ClassCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerQuery_QueryUpdate_Metadata;
      }

      /**
       * @param Json [in] - Type on server: TJSONObject
       * @param ClassCode [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QueryUpdateCallback(TJSONObject Result);

      public void QueryUpdate(TJSONObject Json, String ClassCode, QueryUpdateCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TJServerQuery.QueryUpdate");
        cmd.prepare(get_TJServerQuery_QueryUpdate_Metadata());
        InternalConnectionDelegate QueryUpdateDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(Json);
        cmd.getParameter(1).getValue().SetAsString(ClassCode);
        getConnection().execute(cmd, this, QueryUpdateDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerQuery_QueryExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TJServerQuery_QueryExecSQL_Metadata()
      {
        if (TJServerQuery_QueryExecSQL_Metadata == null)
        {
          TJServerQuery_QueryExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TJServerQuery_QueryExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: Integer
       */
      public delegate void QueryExecSQLCallback(int Result);

      public void QueryExecSQL(String SQLText, QueryExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerQuery.QueryExecSQL");
        cmd.prepare(get_TJServerQuery_QueryExecSQL_Metadata());
        InternalConnectionDelegate QueryExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QueryExecSQLDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerQuery_QuerySysOpen_Metadata;
      private DSRESTParameterMetaData[] get_TJServerQuery_QuerySysOpen_Metadata()
      {
        if (TJServerQuery_QuerySysOpen_Metadata == null)
        {
          TJServerQuery_QuerySysOpen_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TJServerQuery_QuerySysOpen_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void QuerySysOpenCallback(TJSONObject Result);

      public void QuerySysOpen(String SQLText, QuerySysOpenCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerQuery.QuerySysOpen");
        cmd.prepare(get_TJServerQuery_QuerySysOpen_Metadata());
        InternalConnectionDelegate QuerySysOpenDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysOpenDel, ExCal);
      }
      private DSRESTParameterMetaData[] TJServerQuery_QuerySysExecSQL_Metadata;
      private DSRESTParameterMetaData[] get_TJServerQuery_QuerySysExecSQL_Metadata()
      {
        if (TJServerQuery_QuerySysExecSQL_Metadata == null)
        {
          TJServerQuery_QuerySysExecSQL_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("SQLText", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TJServerQuery_QuerySysExecSQL_Metadata;
      }

      /**
       * @param SQLText [in] - Type on server: String
       * @return result - Type on server: Integer
       */
      public delegate void QuerySysExecSQLCallback(int Result);

      public void QuerySysExecSQL(String SQLText, QuerySysExecSQLCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TJServerQuery.QuerySysExecSQL");
        cmd.prepare(get_TJServerQuery_QuerySysExecSQL_Metadata());
        InternalConnectionDelegate QuerySysExecSQLDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsInt32());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(SQLText);
        getConnection().execute(cmd, this, QuerySysExecSQLDel, ExCal);
      }
    }

    public class TWorkFlowServer : DSAdmin
    {
      public TWorkFlowServer(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TWorkFlowServer_ServerWorkFlowStartJSON_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_ServerWorkFlowStartJSON_Metadata()
      {
        if (TWorkFlowServer_ServerWorkFlowStartJSON_Metadata == null)
        {
          TWorkFlowServer_ServerWorkFlowStartJSON_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("jsonValue", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TWorkFlowServer_ServerWorkFlowStartJSON_Metadata;
      }

      /**
       * @param jsonValue [in] - Type on server: TJSONObject
       * @return result - Type on server: String
       */
      public delegate void ServerWorkFlowStartJSONCallback(String Result);

      public void ServerWorkFlowStartJSON(TJSONObject jsonValue, ServerWorkFlowStartJSONCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TWorkFlowServer.ServerWorkFlowStartJSON");
        cmd.prepare(get_TWorkFlowServer_ServerWorkFlowStartJSON_Metadata());
        InternalConnectionDelegate ServerWorkFlowStartJSONDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(jsonValue);
        getConnection().execute(cmd, this, ServerWorkFlowStartJSONDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_ServerWorkFlowStart_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_ServerWorkFlowStart_Metadata()
      {
        if (TWorkFlowServer_ServerWorkFlowStart_Metadata == null)
        {
          TWorkFlowServer_ServerWorkFlowStart_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("FlowDefID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Subject", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Content", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("BusWindow", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("BusCode", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Rank", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("PrjID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Report", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TWorkFlowServer_ServerWorkFlowStart_Metadata;
      }

      /**
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
      public delegate void ServerWorkFlowStartCallback(String Result);

      public void ServerWorkFlowStart(String FlowDefID, String Subject, String Content, String BusWindow, String BusCode, int Rank, String PrjID, String Report, ServerWorkFlowStartCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.ServerWorkFlowStart");
        cmd.prepare(get_TWorkFlowServer_ServerWorkFlowStart_Metadata());
        InternalConnectionDelegate ServerWorkFlowStartDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(8).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(FlowDefID);
        cmd.getParameter(1).getValue().SetAsString(Subject);
        cmd.getParameter(2).getValue().SetAsString(Content);
        cmd.getParameter(3).getValue().SetAsString(BusWindow);
        cmd.getParameter(4).getValue().SetAsString(BusCode);
        cmd.getParameter(5).getValue().SetAsInt32(Rank);
        cmd.getParameter(6).getValue().SetAsString(PrjID);
        cmd.getParameter(7).getValue().SetAsString(Report);
        getConnection().execute(cmd, this, ServerWorkFlowStartDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_ServerWorkFlowExecJSON_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_ServerWorkFlowExecJSON_Metadata()
      {
        if (TWorkFlowServer_ServerWorkFlowExecJSON_Metadata == null)
        {
          TWorkFlowServer_ServerWorkFlowExecJSON_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("jsonValue", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONObject"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TWorkFlowServer_ServerWorkFlowExecJSON_Metadata;
      }

      /**
       * @param jsonValue [in] - Type on server: TJSONObject
       * @return result - Type on server: Boolean
       */
      public delegate void ServerWorkFlowExecJSONCallback(bool Result);

      public void ServerWorkFlowExecJSON(TJSONObject jsonValue, ServerWorkFlowExecJSONCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TWorkFlowServer.ServerWorkFlowExecJSON");
        cmd.prepare(get_TWorkFlowServer_ServerWorkFlowExecJSON_Metadata());
        InternalConnectionDelegate ServerWorkFlowExecJSONDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsJSONValue(jsonValue);
        getConnection().execute(cmd, this, ServerWorkFlowExecJSONDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_ServerWorkFlowExec_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_ServerWorkFlowExec_Metadata()
      {
        if (TWorkFlowServer_ServerWorkFlowExec_Metadata == null)
        {
          TWorkFlowServer_ServerWorkFlowExec_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("FlowDefID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("WorkInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("TskStatus", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("TskComments", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("VariableList", DSRESTParamDirection.Input, DBXDataTypes.JsonValueType, "TJSONArray"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TWorkFlowServer_ServerWorkFlowExec_Metadata;
      }

      /**
       * @param FlowDefID [in] - Type on server: String
       * @param WorkInsID [in] - Type on server: String
       * @param TaskInsID [in] - Type on server: String
       * @param TskStatus [in] - Type on server: String
       * @param TskComments [in] - Type on server: String
       * @param VariableList [in] - Type on server: TJSONArray
       * @return result - Type on server: Boolean
       */
      public delegate void ServerWorkFlowExecCallback(bool Result);

      public void ServerWorkFlowExec(String FlowDefID, String WorkInsID, String TaskInsID, String TskStatus, String TskComments, TJSONArray VariableList, ServerWorkFlowExecCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("TWorkFlowServer.ServerWorkFlowExec");
        cmd.prepare(get_TWorkFlowServer_ServerWorkFlowExec_Metadata());
        InternalConnectionDelegate ServerWorkFlowExecDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(6).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(FlowDefID);
        cmd.getParameter(1).getValue().SetAsString(WorkInsID);
        cmd.getParameter(2).getValue().SetAsString(TaskInsID);
        cmd.getParameter(3).getValue().SetAsString(TskStatus);
        cmd.getParameter(4).getValue().SetAsString(TskComments);
        cmd.getParameter(5).getValue().SetAsJSONValue(VariableList);
        getConnection().execute(cmd, this, ServerWorkFlowExecDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetTaskList_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetTaskList_Metadata()
      {
        if (TWorkFlowServer_GetTaskList_Metadata == null)
        {
          TWorkFlowServer_GetTaskList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("AUserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("ACompletedState", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("AOtherCondition", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TWorkFlowServer_GetTaskList_Metadata;
      }

      /**
       * @param AUserID [in] - Type on server: String
       * @param ACompletedState [in] - Type on server: Integer
       * @param AOtherCondition [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetTaskListCallback(TJSONObject Result);

      public void GetTaskList(String AUserID, int ACompletedState, String AOtherCondition, GetTaskListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetTaskList");
        cmd.prepare(get_TWorkFlowServer_GetTaskList_Metadata());
        InternalConnectionDelegate GetTaskListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(3).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(AUserID);
        cmd.getParameter(1).getValue().SetAsInt32(ACompletedState);
        cmd.getParameter(2).getValue().SetAsString(AOtherCondition);
        getConnection().execute(cmd, this, GetTaskListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetLogList_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetLogList_Metadata()
      {
        if (TWorkFlowServer_GetLogList_Metadata == null)
        {
          TWorkFlowServer_GetLogList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("ALogFilterType", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("AFilterKey", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TWorkFlowServer_GetLogList_Metadata;
      }

      /**
       * @param ALogFilterType [in] - Type on server: Integer
       * @param AFilterKey [in] - Type on server: String
       * @return result - Type on server: String
       */
      public delegate void GetLogListCallback(String Result);

      public void GetLogList(int ALogFilterType, String AFilterKey, GetLogListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetLogList");
        cmd.prepare(get_TWorkFlowServer_GetLogList_Metadata());
        InternalConnectionDelegate GetLogListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsInt32(ALogFilterType);
        cmd.getParameter(1).getValue().SetAsString(AFilterKey);
        getConnection().execute(cmd, this, GetLogListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetDiagram_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetDiagram_Metadata()
      {
        if (TWorkFlowServer_GetDiagram_Metadata == null)
        {
          TWorkFlowServer_GetDiagram_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("ADiagramType", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("ADiagramKey", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TWorkFlowServer_GetDiagram_Metadata;
      }

      /**
       * @param ADiagramType [in] - Type on server: Integer
       * @param ADiagramKey [in] - Type on server: String
       * @return result - Type on server: String
       */
      public delegate void GetDiagramCallback(String Result);

      public void GetDiagram(int ADiagramType, String ADiagramKey, GetDiagramCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetDiagram");
        cmd.prepare(get_TWorkFlowServer_GetDiagram_Metadata());
        InternalConnectionDelegate GetDiagramDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsInt32(ADiagramType);
        cmd.getParameter(1).getValue().SetAsString(ADiagramKey);
        getConnection().execute(cmd, this, GetDiagramDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetTaskdefList_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetTaskdefList_Metadata()
      {
        if (TWorkFlowServer_GetTaskdefList_Metadata == null)
        {
          TWorkFlowServer_GetTaskdefList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TWorkFlowServer_GetTaskdefList_Metadata;
      }

      /**
       * @param TaskInsID [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetTaskdefListCallback(TJSONObject Result);

      public void GetTaskdefList(String TaskInsID, GetTaskdefListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetTaskdefList");
        cmd.prepare(get_TWorkFlowServer_GetTaskdefList_Metadata());
        InternalConnectionDelegate GetTaskdefListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(TaskInsID);
        getConnection().execute(cmd, this, GetTaskdefListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetVariableList_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetVariableList_Metadata()
      {
        if (TWorkFlowServer_GetVariableList_Metadata == null)
        {
          TWorkFlowServer_GetVariableList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONObject"),
          };
        }
        return TWorkFlowServer_GetVariableList_Metadata;
      }

      /**
       * @param TaskInsID [in] - Type on server: String
       * @return result - Type on server: TJSONObject
       */
      public delegate void GetVariableListCallback(TJSONObject Result);

      public void GetVariableList(String TaskInsID, GetVariableListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetVariableList");
        cmd.prepare(get_TWorkFlowServer_GetVariableList_Metadata());
        InternalConnectionDelegate GetVariableListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONObject)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(TaskInsID);
        getConnection().execute(cmd, this, GetVariableListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetVariableListDS_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetVariableListDS_Metadata()
      {
        if (TWorkFlowServer_GetVariableListDS_Metadata == null)
        {
          TWorkFlowServer_GetVariableListDS_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TWorkFlowServer_GetVariableListDS_Metadata;
      }

      /**
       * @param TaskInsID [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void GetVariableListDSCallback(TStream Result);

      public void GetVariableListDS(String TaskInsID, GetVariableListDSCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetVariableListDS");
        cmd.prepare(get_TWorkFlowServer_GetVariableListDS_Metadata());
        InternalConnectionDelegate GetVariableListDSDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(TaskInsID);
        getConnection().execute(cmd, this, GetVariableListDSDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetTaskdefListDS_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetTaskdefListDS_Metadata()
      {
        if (TWorkFlowServer_GetTaskdefListDS_Metadata == null)
        {
          TWorkFlowServer_GetTaskdefListDS_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TWorkFlowServer_GetTaskdefListDS_Metadata;
      }

      /**
       * @param TaskInsID [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void GetTaskdefListDSCallback(TStream Result);

      public void GetTaskdefListDS(String TaskInsID, GetTaskdefListDSCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetTaskdefListDS");
        cmd.prepare(get_TWorkFlowServer_GetTaskdefListDS_Metadata());
        InternalConnectionDelegate GetTaskdefListDSDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(TaskInsID);
        getConnection().execute(cmd, this, GetTaskdefListDSDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetWorkFlowChart_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetWorkFlowChart_Metadata()
      {
        if (TWorkFlowServer_GetWorkFlowChart_Metadata == null)
        {
          TWorkFlowServer_GetWorkFlowChart_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("FlowID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("isDef", DSRESTParamDirection.Input, DBXDataTypes.BooleanType, "Boolean"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TWorkFlowServer_GetWorkFlowChart_Metadata;
      }

      /**
       * @param FlowID [in] - Type on server: String
       * @param isDef [in] - Type on server: Boolean
       * @return result - Type on server: TStream
       */
      public delegate void GetWorkFlowChartCallback(TStream Result);

      public void GetWorkFlowChart(String FlowID, bool isDef, GetWorkFlowChartCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetWorkFlowChart");
        cmd.prepare(get_TWorkFlowServer_GetWorkFlowChart_Metadata());
        InternalConnectionDelegate GetWorkFlowChartDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(FlowID);
        cmd.getParameter(1).getValue().SetAsBoolean(isDef);
        getConnection().execute(cmd, this, GetWorkFlowChartDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_GetTaskListDS_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_GetTaskListDS_Metadata()
      {
        if (TWorkFlowServer_GetTaskListDS_Metadata == null)
        {
          TWorkFlowServer_GetTaskListDS_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("AUserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("ACompletedState", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("AOtherCondition", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return TWorkFlowServer_GetTaskListDS_Metadata;
      }

      /**
       * @param AUserID [in] - Type on server: String
       * @param ACompletedState [in] - Type on server: Integer
       * @param AOtherCondition [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void GetTaskListDSCallback(TStream Result);

      public void GetTaskListDS(String AUserID, int ACompletedState, String AOtherCondition, GetTaskListDSCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.GetTaskListDS");
        cmd.prepare(get_TWorkFlowServer_GetTaskListDS_Metadata());
        InternalConnectionDelegate GetTaskListDSDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(3).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(AUserID);
        cmd.getParameter(1).getValue().SetAsInt32(ACompletedState);
        cmd.getParameter(2).getValue().SetAsString(AOtherCondition);
        getConnection().execute(cmd, this, GetTaskListDSDel, ExCal);
      }
      private DSRESTParameterMetaData[] TWorkFlowServer_TaskCanUpdate_Metadata;
      private DSRESTParameterMetaData[] get_TWorkFlowServer_TaskCanUpdate_Metadata()
      {
        if (TWorkFlowServer_TaskCanUpdate_Metadata == null)
        {
          TWorkFlowServer_TaskCanUpdate_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("TaskInsID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TWorkFlowServer_TaskCanUpdate_Metadata;
      }

      /**
       * @param TaskInsID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void TaskCanUpdateCallback(bool Result);

      public void TaskCanUpdate(String TaskInsID, TaskCanUpdateCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TWorkFlowServer.TaskCanUpdate");
        cmd.prepare(get_TWorkFlowServer_TaskCanUpdate_Metadata());
        InternalConnectionDelegate TaskCanUpdateDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(TaskInsID);
        getConnection().execute(cmd, this, TaskCanUpdateDel, ExCal);
      }
    }

    public class TMessageManage : DSAdmin
    {
      public TMessageManage(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TMessageManage_NewMessageGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_NewMessageGroup_Metadata()
      {
        if (TMessageManage_NewMessageGroup_Metadata == null)
        {
          TMessageManage_NewMessageGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Description", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_NewMessageGroup_Metadata;
      }

      /**
       * @param GroupName [in] - Type on server: String
       * @param Description [in] - Type on server: String
       */
      public delegate void NewMessageGroupCallback();

      public void NewMessageGroup(String GroupName, String Description, NewMessageGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.NewMessageGroup");
        cmd.prepare(get_TMessageManage_NewMessageGroup_Metadata());
        InternalConnectionDelegate NewMessageGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupName);
        cmd.getParameter(1).getValue().SetAsString(Description);
        getConnection().execute(cmd, this, NewMessageGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_DelMessageGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_DelMessageGroup_Metadata()
      {
        if (TMessageManage_DelMessageGroup_Metadata == null)
        {
          TMessageManage_DelMessageGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_DelMessageGroup_Metadata;
      }

      /**
       * @param GroupID [in] - Type on server: String
       */
      public delegate void DelMessageGroupCallback();

      public void DelMessageGroup(String GroupID, DelMessageGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.DelMessageGroup");
        cmd.prepare(get_TMessageManage_DelMessageGroup_Metadata());
        InternalConnectionDelegate DelMessageGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupID);
        getConnection().execute(cmd, this, DelMessageGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_UpdateMessageGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_UpdateMessageGroup_Metadata()
      {
        if (TMessageManage_UpdateMessageGroup_Metadata == null)
        {
          TMessageManage_UpdateMessageGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("Description", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_UpdateMessageGroup_Metadata;
      }

      /**
       * @param GroupID [in] - Type on server: String
       * @param GroupName [in] - Type on server: String
       * @param Description [in] - Type on server: String
       */
      public delegate void UpdateMessageGroupCallback();

      public void UpdateMessageGroup(String GroupID, String GroupName, String Description, UpdateMessageGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.UpdateMessageGroup");
        cmd.prepare(get_TMessageManage_UpdateMessageGroup_Metadata());
        InternalConnectionDelegate UpdateMessageGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupID);
        cmd.getParameter(1).getValue().SetAsString(GroupName);
        cmd.getParameter(2).getValue().SetAsString(Description);
        getConnection().execute(cmd, this, UpdateMessageGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_NewMessageMember_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_NewMessageMember_Metadata()
      {
        if (TMessageManage_NewMessageMember_Metadata == null)
        {
          TMessageManage_NewMessageMember_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupMemberID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("IsAdmin", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TMessageManage_NewMessageMember_Metadata;
      }

      /**
       * @param GroupID [in] - Type on server: String
       * @param GroupMemberID [in] - Type on server: String
       * @param IsAdmin [in] - Type on server: Integer
       */
      public delegate void NewMessageMemberCallback();

      public void NewMessageMember(String GroupID, String GroupMemberID, int IsAdmin, NewMessageMemberCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.NewMessageMember");
        cmd.prepare(get_TMessageManage_NewMessageMember_Metadata());
        InternalConnectionDelegate NewMessageMemberDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupID);
        cmd.getParameter(1).getValue().SetAsString(GroupMemberID);
        cmd.getParameter(2).getValue().SetAsInt32(IsAdmin);
        getConnection().execute(cmd, this, NewMessageMemberDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_UpdateMessageMember_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_UpdateMessageMember_Metadata()
      {
        if (TMessageManage_UpdateMessageMember_Metadata == null)
        {
          TMessageManage_UpdateMessageMember_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupMemberID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("IsAdmin", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
          };
        }
        return TMessageManage_UpdateMessageMember_Metadata;
      }

      /**
       * @param GroupID [in] - Type on server: String
       * @param GroupMemberID [in] - Type on server: String
       * @param IsAdmin [in] - Type on server: Integer
       */
      public delegate void UpdateMessageMemberCallback();

      public void UpdateMessageMember(String GroupID, String GroupMemberID, int IsAdmin, UpdateMessageMemberCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.UpdateMessageMember");
        cmd.prepare(get_TMessageManage_UpdateMessageMember_Metadata());
        InternalConnectionDelegate UpdateMessageMemberDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupID);
        cmd.getParameter(1).getValue().SetAsString(GroupMemberID);
        cmd.getParameter(2).getValue().SetAsInt32(IsAdmin);
        getConnection().execute(cmd, this, UpdateMessageMemberDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_DelMessageMember_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_DelMessageMember_Metadata()
      {
        if (TMessageManage_DelMessageMember_Metadata == null)
        {
          TMessageManage_DelMessageMember_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupMemberID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_DelMessageMember_Metadata;
      }

      /**
       * @param GroupID [in] - Type on server: String
       * @param GroupMemberID [in] - Type on server: String
       */
      public delegate void DelMessageMemberCallback();

      public void DelMessageMember(String GroupID, String GroupMemberID, DelMessageMemberCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.DelMessageMember");
        cmd.prepare(get_TMessageManage_DelMessageMember_Metadata());
        InternalConnectionDelegate DelMessageMemberDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupID);
        cmd.getParameter(1).getValue().SetAsString(GroupMemberID);
        getConnection().execute(cmd, this, DelMessageMemberDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetMessageGroupList_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetMessageGroupList_Metadata()
      {
        if (TMessageManage_GetMessageGroupList_Metadata == null)
        {
          TMessageManage_GetMessageGroupList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TMessageManage_GetMessageGroupList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetMessageGroupListCallback(TJSONArray Result);

      public void GetMessageGroupList(GetMessageGroupListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetMessageGroupList");
        cmd.prepare(get_TMessageManage_GetMessageGroupList_Metadata());
        InternalConnectionDelegate GetMessageGroupListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetMessageGroupListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetGroupMemberList_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetGroupMemberList_Metadata()
      {
        if (TMessageManage_GetGroupMemberList_Metadata == null)
        {
          TMessageManage_GetGroupMemberList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroudId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TMessageManage_GetGroupMemberList_Metadata;
      }

      /**
       * @param GroudId [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetGroupMemberListCallback(TJSONArray Result);

      public void GetGroupMemberList(String GroudId, GetGroupMemberListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetGroupMemberList");
        cmd.prepare(get_TMessageManage_GetGroupMemberList_Metadata());
        InternalConnectionDelegate GetGroupMemberListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroudId);
        getConnection().execute(cmd, this, GetGroupMemberListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetAllEmployee_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetAllEmployee_Metadata()
      {
        if (TMessageManage_GetAllEmployee_Metadata == null)
        {
          TMessageManage_GetAllEmployee_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TMessageManage_GetAllEmployee_Metadata;
      }

      /**
       * @param GroupId [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetAllEmployeeCallback(TJSONArray Result);

      public void GetAllEmployee(String GroupId, GetAllEmployeeCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetAllEmployee");
        cmd.prepare(get_TMessageManage_GetAllEmployee_Metadata());
        InternalConnectionDelegate GetAllEmployeeDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupId);
        getConnection().execute(cmd, this, GetAllEmployeeDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_IsGroupMember_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_IsGroupMember_Metadata()
      {
        if (TMessageManage_IsGroupMember_Metadata == null)
        {
          TMessageManage_IsGroupMember_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("GroupId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("MemberId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_IsGroupMember_Metadata;
      }

      /**
       * @param GroupId [in] - Type on server: String
       * @param MemberId [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void IsGroupMemberCallback(bool Result);

      public void IsGroupMember(String GroupId, String MemberId, IsGroupMemberCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.IsGroupMember");
        cmd.prepare(get_TMessageManage_IsGroupMember_Metadata());
        InternalConnectionDelegate IsGroupMemberDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(GroupId);
        cmd.getParameter(1).getValue().SetAsString(MemberId);
        getConnection().execute(cmd, this, IsGroupMemberDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetUserList_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetUserList_Metadata()
      {
        if (TMessageManage_GetUserList_Metadata == null)
        {
          TMessageManage_GetUserList_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TMessageManage_GetUserList_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetUserListCallback(TJSONArray Result);

      public void GetUserList(GetUserListCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetUserList");
        cmd.prepare(get_TMessageManage_GetUserList_Metadata());
        InternalConnectionDelegate GetUserListDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetUserListDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetHTMLEscapedString_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetHTMLEscapedString_Metadata()
      {
        if (TMessageManage_GetHTMLEscapedString_Metadata == null)
        {
          TMessageManage_GetHTMLEscapedString_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Value", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_GetHTMLEscapedString_Metadata;
      }

      /**
       * @param Value [in] - Type on server: String
       * @return result - Type on server: String
       */
      public delegate void GetHTMLEscapedStringCallback(String Result);

      public void GetHTMLEscapedString(String Value, GetHTMLEscapedStringCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetHTMLEscapedString");
        cmd.prepare(get_TMessageManage_GetHTMLEscapedString_Metadata());
        InternalConnectionDelegate GetHTMLEscapedStringDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsString());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Value);
        getConnection().execute(cmd, this, GetHTMLEscapedStringDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_UpdateCurUserCallbackClientID_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_UpdateCurUserCallbackClientID_Metadata()
      {
        if (TMessageManage_UpdateCurUserCallbackClientID_Metadata == null)
        {
          TMessageManage_UpdateCurUserCallbackClientID_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Value", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_UpdateCurUserCallbackClientID_Metadata;
      }

      /**
       * @param Value [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void UpdateCurUserCallbackClientIDCallback(bool Result);

      public void UpdateCurUserCallbackClientID(String Value, UpdateCurUserCallbackClientIDCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.UpdateCurUserCallbackClientID");
        cmd.prepare(get_TMessageManage_UpdateCurUserCallbackClientID_Metadata());
        InternalConnectionDelegate UpdateCurUserCallbackClientIDDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Value);
        getConnection().execute(cmd, this, UpdateCurUserCallbackClientIDDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToAll_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToAll_Metadata()
      {
        if (TMessageManage_SendMessageToAll_Metadata == null)
        {
          TMessageManage_SendMessageToAll_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToAll_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToAllCallback(bool Result);

      public void SendMessageToAll(String Msg, SendMessageToAllCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToAll");
        cmd.prepare(get_TMessageManage_SendMessageToAll_Metadata());
        InternalConnectionDelegate SendMessageToAllDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMessageToAllDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToUser_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToUser_Metadata()
      {
        if (TMessageManage_SendMessageToUser_Metadata == null)
        {
          TMessageManage_SendMessageToUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("UserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToUser_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param UserID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToUserCallback(bool Result);

      public void SendMessageToUser(String Msg, String UserID, SendMessageToUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToUser");
        cmd.prepare(get_TMessageManage_SendMessageToUser_Metadata());
        InternalConnectionDelegate SendMessageToUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(UserID);
        getConnection().execute(cmd, this, SendMessageToUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToDepartment_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToDepartment_Metadata()
      {
        if (TMessageManage_SendMessageToDepartment_Metadata == null)
        {
          TMessageManage_SendMessageToDepartment_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("DepartmentID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToDepartment_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param DepartmentID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToDepartmentCallback(bool Result);

      public void SendMessageToDepartment(String Msg, String DepartmentID, SendMessageToDepartmentCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToDepartment");
        cmd.prepare(get_TMessageManage_SendMessageToDepartment_Metadata());
        InternalConnectionDelegate SendMessageToDepartmentDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(DepartmentID);
        getConnection().execute(cmd, this, SendMessageToDepartmentDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToGroup_Metadata()
      {
        if (TMessageManage_SendMessageToGroup_Metadata == null)
        {
          TMessageManage_SendMessageToGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToGroup_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param GroupID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToGroupCallback(bool Result);

      public void SendMessageToGroup(String Msg, String GroupID, SendMessageToGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToGroup");
        cmd.prepare(get_TMessageManage_SendMessageToGroup_Metadata());
        InternalConnectionDelegate SendMessageToGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(GroupID);
        getConnection().execute(cmd, this, SendMessageToGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToJob_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToJob_Metadata()
      {
        if (TMessageManage_SendMessageToJob_Metadata == null)
        {
          TMessageManage_SendMessageToJob_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("JobID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToJob_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param JobID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToJobCallback(bool Result);

      public void SendMessageToJob(String Msg, String JobID, SendMessageToJobCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToJob");
        cmd.prepare(get_TMessageManage_SendMessageToJob_Metadata());
        InternalConnectionDelegate SendMessageToJobDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(JobID);
        getConnection().execute(cmd, this, SendMessageToJobDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToRole_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToRole_Metadata()
      {
        if (TMessageManage_SendMessageToRole_Metadata == null)
        {
          TMessageManage_SendMessageToRole_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("RoleID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToRole_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param RoleID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToRoleCallback(bool Result);

      public void SendMessageToRole(String Msg, String RoleID, SendMessageToRoleCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToRole");
        cmd.prepare(get_TMessageManage_SendMessageToRole_Metadata());
        InternalConnectionDelegate SendMessageToRoleDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(RoleID);
        getConnection().execute(cmd, this, SendMessageToRoleDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMessageToFollow_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMessageToFollow_Metadata()
      {
        if (TMessageManage_SendMessageToFollow_Metadata == null)
        {
          TMessageManage_SendMessageToFollow_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMessageToFollow_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMessageToFollowCallback(bool Result);

      public void SendMessageToFollow(String Msg, SendMessageToFollowCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMessageToFollow");
        cmd.prepare(get_TMessageManage_SendMessageToFollow_Metadata());
        InternalConnectionDelegate SendMessageToFollowDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMessageToFollowDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToFollow_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToFollow_Metadata()
      {
        if (TMessageManage_SendCMDToFollow_Metadata == null)
        {
          TMessageManage_SendCMDToFollow_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToFollow_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToFollowCallback(bool Result);

      public void SendCMDToFollow(String cmdStr, SendCMDToFollowCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToFollow");
        cmd.prepare(get_TMessageManage_SendCMDToFollow_Metadata());
        InternalConnectionDelegate SendCMDToFollowDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        getConnection().execute(cmd, this, SendCMDToFollowDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToAll_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToAll_Metadata()
      {
        if (TMessageManage_SendCMDToAll_Metadata == null)
        {
          TMessageManage_SendCMDToAll_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToAll_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToAllCallback(bool Result);

      public void SendCMDToAll(String cmdStr, SendCMDToAllCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToAll");
        cmd.prepare(get_TMessageManage_SendCMDToAll_Metadata());
        InternalConnectionDelegate SendCMDToAllDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        getConnection().execute(cmd, this, SendCMDToAllDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToUser_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToUser_Metadata()
      {
        if (TMessageManage_SendCMDToUser_Metadata == null)
        {
          TMessageManage_SendCMDToUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("UserID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToUser_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param UserID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToUserCallback(bool Result);

      public void SendCMDToUser(String cmdStr, String UserID, SendCMDToUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToUser");
        cmd.prepare(get_TMessageManage_SendCMDToUser_Metadata());
        InternalConnectionDelegate SendCMDToUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(UserID);
        getConnection().execute(cmd, this, SendCMDToUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToDepartment_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToDepartment_Metadata()
      {
        if (TMessageManage_SendCMDToDepartment_Metadata == null)
        {
          TMessageManage_SendCMDToDepartment_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("DepartmentID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToDepartment_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param DepartmentID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToDepartmentCallback(bool Result);

      public void SendCMDToDepartment(String cmdStr, String DepartmentID, SendCMDToDepartmentCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToDepartment");
        cmd.prepare(get_TMessageManage_SendCMDToDepartment_Metadata());
        InternalConnectionDelegate SendCMDToDepartmentDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(DepartmentID);
        getConnection().execute(cmd, this, SendCMDToDepartmentDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToGroup_Metadata()
      {
        if (TMessageManage_SendCMDToGroup_Metadata == null)
        {
          TMessageManage_SendCMDToGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToGroup_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param GroupID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToGroupCallback(bool Result);

      public void SendCMDToGroup(String cmdStr, String GroupID, SendCMDToGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToGroup");
        cmd.prepare(get_TMessageManage_SendCMDToGroup_Metadata());
        InternalConnectionDelegate SendCMDToGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(GroupID);
        getConnection().execute(cmd, this, SendCMDToGroupDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToJob_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToJob_Metadata()
      {
        if (TMessageManage_SendCMDToJob_Metadata == null)
        {
          TMessageManage_SendCMDToJob_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("JobID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToJob_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param JobID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToJobCallback(bool Result);

      public void SendCMDToJob(String cmdStr, String JobID, SendCMDToJobCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToJob");
        cmd.prepare(get_TMessageManage_SendCMDToJob_Metadata());
        InternalConnectionDelegate SendCMDToJobDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(JobID);
        getConnection().execute(cmd, this, SendCMDToJobDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendCMDToRole_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendCMDToRole_Metadata()
      {
        if (TMessageManage_SendCMDToRole_Metadata == null)
        {
          TMessageManage_SendCMDToRole_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("cmdStr", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("RoleID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendCMDToRole_Metadata;
      }

      /**
       * @param cmdStr [in] - Type on server: String
       * @param RoleID [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendCMDToRoleCallback(bool Result);

      public void SendCMDToRole(String cmdStr, String RoleID, SendCMDToRoleCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendCMDToRole");
        cmd.prepare(get_TMessageManage_SendCMDToRole_Metadata());
        InternalConnectionDelegate SendCMDToRoleDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(cmdStr);
        cmd.getParameter(1).getValue().SetAsString(RoleID);
        getConnection().execute(cmd, this, SendCMDToRoleDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMgrMessage_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMgrMessage_Metadata()
      {
        if (TMessageManage_SendMgrMessage_Metadata == null)
        {
          TMessageManage_SendMgrMessage_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("itype", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMgrMessage_Metadata;
      }

      /**
       * @param itype [in] - Type on server: Integer
       * @param Msg [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMgrMessageCallback(bool Result);

      public void SendMgrMessage(int itype, String Msg, SendMgrMessageCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMgrMessage");
        cmd.prepare(get_TMessageManage_SendMgrMessage_Metadata());
        InternalConnectionDelegate SendMgrMessageDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(2).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsInt32(itype);
        cmd.getParameter(1).getValue().SetAsString(Msg);
        getConnection().execute(cmd, this, SendMgrMessageDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMissMessage_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMissMessage_Metadata()
      {
        if (TMessageManage_SendMissMessage_Metadata == null)
        {
          TMessageManage_SendMissMessage_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("UserId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TMessageManage_SendMissMessage_Metadata;
      }

      /**
       * @param UserId [in] - Type on server: String
       */
      public delegate void SendMissMessageCallback();

      public void SendMissMessage(String UserId, SendMissMessageCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMissMessage");
        cmd.prepare(get_TMessageManage_SendMissMessage_Metadata());
        InternalConnectionDelegate SendMissMessageDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(UserId);
        getConnection().execute(cmd, this, SendMissMessageDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_GetLatelyMessage_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_GetLatelyMessage_Metadata()
      {
        if (TMessageManage_GetLatelyMessage_Metadata == null)
        {
          TMessageManage_GetLatelyMessage_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("UserId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("ReceId", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("RecType", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TMessageManage_GetLatelyMessage_Metadata;
      }

      /**
       * @param UserId [in] - Type on server: String
       * @param ReceId [in] - Type on server: String
       * @param RecType [in] - Type on server: Integer
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetLatelyMessageCallback(TJSONArray Result);

      public void GetLatelyMessage(String UserId, String ReceId, int RecType, GetLatelyMessageCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.GetLatelyMessage");
        cmd.prepare(get_TMessageManage_GetLatelyMessage_Metadata());
        InternalConnectionDelegate GetLatelyMessageDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(3).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(UserId);
        cmd.getParameter(1).getValue().SetAsString(ReceId);
        cmd.getParameter(2).getValue().SetAsInt32(RecType);
        getConnection().execute(cmd, this, GetLatelyMessageDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMissMessageToUser_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMissMessageToUser_Metadata()
      {
        if (TMessageManage_SendMissMessageToUser_Metadata == null)
        {
          TMessageManage_SendMissMessageToUser_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("MsgID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("sendtime", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMissMessageToUser_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param FromID [in] - Type on server: String
       * @param FromName [in] - Type on server: String
       * @param MsgID [in] - Type on server: String
       * @param sendtime [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMissMessageToUserCallback(bool Result);

      public void SendMissMessageToUser(String Msg, String FromID, String FromName, String MsgID, String sendtime, SendMissMessageToUserCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMissMessageToUser");
        cmd.prepare(get_TMessageManage_SendMissMessageToUser_Metadata());
        InternalConnectionDelegate SendMissMessageToUserDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(5).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(FromID);
        cmd.getParameter(2).getValue().SetAsString(FromName);
        cmd.getParameter(3).getValue().SetAsString(MsgID);
        cmd.getParameter(4).getValue().SetAsString(sendtime);
        getConnection().execute(cmd, this, SendMissMessageToUserDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMissMessageToDepartment_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMissMessageToDepartment_Metadata()
      {
        if (TMessageManage_SendMissMessageToDepartment_Metadata == null)
        {
          TMessageManage_SendMissMessageToDepartment_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("DepartmentID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("MsgID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("sendtime", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMissMessageToDepartment_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param FromID [in] - Type on server: String
       * @param FromName [in] - Type on server: String
       * @param DepartmentID [in] - Type on server: String
       * @param MsgID [in] - Type on server: String
       * @param sendtime [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMissMessageToDepartmentCallback(bool Result);

      public void SendMissMessageToDepartment(String Msg, String FromID, String FromName, String DepartmentID, String MsgID, String sendtime, SendMissMessageToDepartmentCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMissMessageToDepartment");
        cmd.prepare(get_TMessageManage_SendMissMessageToDepartment_Metadata());
        InternalConnectionDelegate SendMissMessageToDepartmentDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(6).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(FromID);
        cmd.getParameter(2).getValue().SetAsString(FromName);
        cmd.getParameter(3).getValue().SetAsString(DepartmentID);
        cmd.getParameter(4).getValue().SetAsString(MsgID);
        cmd.getParameter(5).getValue().SetAsString(sendtime);
        getConnection().execute(cmd, this, SendMissMessageToDepartmentDel, ExCal);
      }
      private DSRESTParameterMetaData[] TMessageManage_SendMissMessageToGroup_Metadata;
      private DSRESTParameterMetaData[] get_TMessageManage_SendMissMessageToGroup_Metadata()
      {
        if (TMessageManage_SendMissMessageToGroup_Metadata == null)
        {
          TMessageManage_SendMissMessageToGroup_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Msg", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("FromName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("GroupID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("MsgID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("sendtime", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return TMessageManage_SendMissMessageToGroup_Metadata;
      }

      /**
       * @param Msg [in] - Type on server: String
       * @param FromID [in] - Type on server: String
       * @param FromName [in] - Type on server: String
       * @param GroupID [in] - Type on server: String
       * @param MsgID [in] - Type on server: String
       * @param sendtime [in] - Type on server: String
       * @return result - Type on server: Boolean
       */
      public delegate void SendMissMessageToGroupCallback(bool Result);

      public void SendMissMessageToGroup(String Msg, String FromID, String FromName, String GroupID, String MsgID, String sendtime, SendMissMessageToGroupCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TMessageManage.SendMissMessageToGroup");
        cmd.prepare(get_TMessageManage_SendMissMessageToGroup_Metadata());
        InternalConnectionDelegate SendMissMessageToGroupDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(6).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Msg);
        cmd.getParameter(1).getValue().SetAsString(FromID);
        cmd.getParameter(2).getValue().SetAsString(FromName);
        cmd.getParameter(3).getValue().SetAsString(GroupID);
        cmd.getParameter(4).getValue().SetAsString(MsgID);
        cmd.getParameter(5).getValue().SetAsString(sendtime);
        getConnection().execute(cmd, this, SendMissMessageToGroupDel, ExCal);
      }
    }

    public class TContractProject : DSAdmin
    {
      public TContractProject(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TContractProject_GetContype_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetContype_Metadata()
      {
        if (TContractProject_GetContype_Metadata == null)
        {
          TContractProject_GetContype_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetContype_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetContypeCallback(TJSONArray Result);

      public void GetContype(GetContypeCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetContype");
        cmd.prepare(get_TContractProject_GetContype_Metadata());
        InternalConnectionDelegate GetContypeDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetContypeDel, ExCal);
      }
      private DSRESTParameterMetaData[] TContractProject_GetContlist_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetContlist_Metadata()
      {
        if (TContractProject_GetContlist_Metadata == null)
        {
          TContractProject_GetContlist_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("userid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("ctypeid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetContlist_Metadata;
      }

      /**
       * @param userid [in] - Type on server: String
       * @param ctypeid [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetContlistCallback(TJSONArray Result);

      public void GetContlist(String userid, String ctypeid, GetContlistCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetContlist");
        cmd.prepare(get_TContractProject_GetContlist_Metadata());
        InternalConnectionDelegate GetContlistDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(userid);
        cmd.getParameter(1).getValue().SetAsString(ctypeid);
        getConnection().execute(cmd, this, GetContlistDel, ExCal);
      }
      private DSRESTParameterMetaData[] TContractProject_GetContdata_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetContdata_Metadata()
      {
        if (TContractProject_GetContdata_Metadata == null)
        {
          TContractProject_GetContdata_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("contid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetContdata_Metadata;
      }

      /**
       * @param contid [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetContdataCallback(TJSONArray Result);

      public void GetContdata(String contid, GetContdataCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetContdata");
        cmd.prepare(get_TContractProject_GetContdata_Metadata());
        InternalConnectionDelegate GetContdataDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(contid);
        getConnection().execute(cmd, this, GetContdataDel, ExCal);
      }
      private DSRESTParameterMetaData[] TContractProject_GetProtype_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetProtype_Metadata()
      {
        if (TContractProject_GetProtype_Metadata == null)
        {
          TContractProject_GetProtype_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetProtype_Metadata;
      }

      /**
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetProtypeCallback(TJSONArray Result);

      public void GetProtype(GetProtypeCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetProtype");
        cmd.prepare(get_TContractProject_GetProtype_Metadata());
        InternalConnectionDelegate GetProtypeDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(0).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        getConnection().execute(cmd, this, GetProtypeDel, ExCal);
      }
      private DSRESTParameterMetaData[] TContractProject_GetProlist_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetProlist_Metadata()
      {
        if (TContractProject_GetProlist_Metadata == null)
        {
          TContractProject_GetProlist_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("userid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("ProTypeid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetProlist_Metadata;
      }

      /**
       * @param userid [in] - Type on server: String
       * @param ProTypeid [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetProlistCallback(TJSONArray Result);

      public void GetProlist(String userid, String ProTypeid, GetProlistCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetProlist");
        cmd.prepare(get_TContractProject_GetProlist_Metadata());
        InternalConnectionDelegate GetProlistDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(2).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(userid);
        cmd.getParameter(1).getValue().SetAsString(ProTypeid);
        getConnection().execute(cmd, this, GetProlistDel, ExCal);
      }
      private DSRESTParameterMetaData[] TContractProject_GetProdata_Metadata;
      private DSRESTParameterMetaData[] get_TContractProject_GetProdata_Metadata()
      {
        if (TContractProject_GetProdata_Metadata == null)
        {
          TContractProject_GetProdata_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("Projectid", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.JsonValueType, "TJSONArray"),
          };
        }
        return TContractProject_GetProdata_Metadata;
      }

      /**
       * @param Projectid [in] - Type on server: String
       * @return result - Type on server: TJSONArray
       */
      public delegate void GetProdataCallback(TJSONArray Result);

      public void GetProdata(String Projectid, GetProdataCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TContractProject.GetProdata");
        cmd.prepare(get_TContractProject_GetProdata_Metadata());
        InternalConnectionDelegate GetProdataDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke((TJSONArray)cmd.getParameter(1).getValue().GetAsJSONValue());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(Projectid);
        getConnection().execute(cmd, this, GetProdataDel, ExCal);
      }
    }

    public class THouseView : DSAdmin
    {
      public THouseView(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] THouseView_GetHouseViewStream_Metadata;
      private DSRESTParameterMetaData[] get_THouseView_GetHouseViewStream_Metadata()
      {
        if (THouseView_GetHouseViewStream_Metadata == null)
        {
          THouseView_GetHouseViewStream_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("AKeyID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BinaryBlobType, "TStream"),
          };
        }
        return THouseView_GetHouseViewStream_Metadata;
      }

      /**
       * @param AKeyID [in] - Type on server: String
       * @return result - Type on server: TStream
       */
      public delegate void GetHouseViewStreamCallback(TStream Result);

      public void GetHouseViewStream(String AKeyID, GetHouseViewStreamCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("THouseView.GetHouseViewStream");
        cmd.prepare(get_THouseView_GetHouseViewStream_Metadata());
        InternalConnectionDelegate GetHouseViewStreamDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(1).getValue().GetAsStream());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(AKeyID);
        getConnection().execute(cmd, this, GetHouseViewStreamDel, ExCal);
      }
      private DSRESTParameterMetaData[] THouseView_UpdateHouseViewFile_Metadata;
      private DSRESTParameterMetaData[] get_THouseView_UpdateHouseViewFile_Metadata()
      {
        if (THouseView_UpdateHouseViewFile_Metadata == null)
        {
          THouseView_UpdateHouseViewFile_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("AKeyID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("AFileName", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
            new DSRESTParameterMetaData("AStream", DSRESTParamDirection.Input, DBXDataTypes.BinaryBlobType, "TStream"),
            new DSRESTParameterMetaData("", DSRESTParamDirection.ReturnValue, DBXDataTypes.BooleanType, "Boolean"),
          };
        }
        return THouseView_UpdateHouseViewFile_Metadata;
      }

      /**
       * @param AKeyID [in] - Type on server: String
       * @param AFileName [in] - Type on server: String
       * @param AStream [in] - Type on server: TStream
       * @return result - Type on server: Boolean
       */
      public delegate void UpdateHouseViewFileCallback(bool Result);

      public void UpdateHouseViewFile(String AKeyID, String AFileName, TStream AStream, UpdateHouseViewFileCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.POST);
        cmd.setText("THouseView.UpdateHouseViewFile");
        cmd.prepare(get_THouseView_UpdateHouseViewFile_Metadata());
        InternalConnectionDelegate UpdateHouseViewFileDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke(cmd.getParameter(3).getValue().GetAsBoolean());
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsString(AKeyID);
        cmd.getParameter(1).getValue().SetAsString(AFileName);
        cmd.getParameter(2).getValue().SetAsStream(AStream);
        getConnection().execute(cmd, this, UpdateHouseViewFileDel, ExCal);
      }
    }

    public class TSendUserMessage : DSAdmin
    {
      public TSendUserMessage(DSRESTConnection Connection, ExceptionCallback ExCal)
          : base(Connection, ExCal)
      {
      }

      private DSRESTParameterMetaData[] TSendUserMessage_SendUserMessage_Metadata;
      private DSRESTParameterMetaData[] get_TSendUserMessage_SendUserMessage_Metadata()
      {
        if (TSendUserMessage_SendUserMessage_Metadata == null)
        {
          TSendUserMessage_SendUserMessage_Metadata = new DSRESTParameterMetaData[]
          {
            new DSRESTParameterMetaData("type", DSRESTParamDirection.Input, DBXDataTypes.Int32Type, "Integer"),
            new DSRESTParameterMetaData("AID", DSRESTParamDirection.Input, DBXDataTypes.WideStringType, "String"),
          };
        }
        return TSendUserMessage_SendUserMessage_Metadata;
      }

      /**
       * @param type [in] - Type on server: Integer
       * @param AID [in] - Type on server: String
       */
      public delegate void SendUserMessageCallback();

      public void SendUserMessage(int type, String AID, SendUserMessageCallback callback = null, ExceptionCallback ExCal = null)
      {
        DSRESTCommand cmd = getConnection().CreateCommand();
        cmd.setRequestType(DSHTTPRequestType.GET);
        cmd.setText("TSendUserMessage.SendUserMessage");
        cmd.prepare(get_TSendUserMessage_SendUserMessage_Metadata());
        InternalConnectionDelegate SendUserMessageDel = () =>
        {
          if (callback != null)
          {
            try
            {
              callback.DynamicInvoke();
            }
            catch (Exception ex)
            {
              if (ExCal != null) getConnection().syncContext.Send(new SendOrPostCallback(x => ExCal.DynamicInvoke(ex.InnerException)), null);
              else getConnection().syncContext.Send(new SendOrPostCallback(x => BaseExCal.DynamicInvoke(ex.InnerException)), null);
            }
          }
        };
        cmd.getParameter(0).getValue().SetAsInt32(type);
        cmd.getParameter(1).getValue().SetAsString(AID);
        getConnection().execute(cmd, this, SendUserMessageDel, ExCal);
      }
    }

  }
}
