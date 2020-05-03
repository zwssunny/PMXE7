using System;
using System.IO.IsolatedStorage;
using Embarcadero.Datasnap.WindowsPhone7;
using System.Diagnostics;
using System.Threading;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Navigation;

namespace Foresight.InstantMessenger
{
    static public class CTConnection
    {
        static private DSProxy.TLoginUser instance;
        static private DSCallbackChannelManager manager;
        static private String CurUserCode;
        static private String CurUserID;
        static private String CurUserName;
        static private String password;
        static private String accbook;
        static private DSRESTConnection connection;
        //static private DSCallbackChannelManager manager_cmd;
        static private IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;
        static public DSProxy.TLoginUser getLoginUserInstance(DSAdmin.ExceptionCallback ManageExceptionCallback = null)
        {
            if (instance == null)
            {
                string hostname;
                string port;
                if (!settings.TryGetValue<string>("hostname", out hostname))
                    hostname = "localhost";

                if (!settings.TryGetValue<string>("port", out port))
                    port = "8080";

                connection = new DSRESTConnection();
                    connection.setHost(hostname);
                    connection.setPort(Convert.ToInt32(port));
                    connection.setProtocol("http"); 
                    connection.setUserName(CurUserCode);
                    connection.setPassword(password);
                if (ManageExceptionCallback == null)
                    instance = new DSProxy.TLoginUser(connection, (e) => { MessageBox.Show("会话已过期，请重新登录."); });
                else
                    instance = new DSProxy.TLoginUser(connection, ManageExceptionCallback);
            }
            return instance;
        }

        public static String getCurUserCode()
        {
            return CurUserCode;
        }

        public static String getCurUserID()
        {
            return CurUserID;
        }

        public static String getCurUserName()
        {
            return CurUserName;
        }
        public static bool IsNull()
        {
            if (instance == null)
                return true;
            else return false;
        }

        public static void ResetProxy()
        {
            instance = null;
            manager = null;
            //manager_cmd = null;
        }

        private static void RegisterCallbacks()
        {
            string SMsgCallback = "FSMessageCallBack";
            //string SCMDCallback = "FSCMDCallBack";
            string SMessageChannel;
           // string SCMDChannel;
            // string managerid = Guid.NewGuid().ToString();
            string managerid = DSCallbackChannelManager.getNewManagerID();
            SMessageChannel = "FSMessage" + accbook;
           // SCMDChannel = "FSCMD" + Accbookid;
            manager = new DSCallbackChannelManager(connection, SMessageChannel, managerid,
              (ex) =>
              {
                  MessageBox.Show(ex.Message);
              });
            DBXCallback cb = new CTCallback(SynchronizationContext.Current);
            try
            {
                manager.registerCallback(SMsgCallback, cb);
                getLoginUserInstance().UpdateCurUserCallbackClientID(managerid);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.StackTrace);
            }
       /*     managerid = Guid.NewGuid().ToString();
            manager_cmd = new DSCallbackChannelManager(getCompanyTweet()
              .getConnection(), SCMDChannel, managerid,
              (ex) =>
              {
                  MessageBox.Show(ex.Message);
              });
            DBXCallback cb_cmd = new CTCMDCallback(SynchronizationContext.Current);
            try
            {
                manager_cmd.registerCallback(SCMDCallback, cb_cmd);
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.StackTrace);
            }*/
        }



        public static void LoginUser(String UserCode, String Password, Delegate OnLogin, Delegate OnExceptionLogin)
        {
            accbook = "0";
            CurUserCode = UserCode;
            password = Password;
            DSProxy.TLoginUser instance = getLoginUserInstance();
            if (instance != null)
            {
                instance.GetCurUserJSON(userobj =>
                    {
                        if (userobj != null)
                        {
                            CurUserID = userobj.getString("userid");
                            CurUserName = userobj.getString("username");
                            //CurUserCode = userobj.getString("usercode");
                            RegisterCallbacks();
                            OnLogin.DynamicInvoke();
                         }
                    },
                      e => {
                        OnExceptionLogin.DynamicInvoke(e);
                    });
               
            }
            
        }

        public static void LogOut()
        {
            if (instance != null)
            {
                CTConnection.getLoginUserInstance().Logout();
                ResetProxy();
            }
        }
    } 
}
