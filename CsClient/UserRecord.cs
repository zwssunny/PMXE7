using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace Foresight.InstantMessenger
{
    public partial class UserRecord
    {
        public UserRecord() { }
        public UserRecord(string userid, string username)
        {
            UserID=userid;
            UserName = username;
        }
        public string UserID{set;get;}
        public string UserName { set; get; }
    }
}
