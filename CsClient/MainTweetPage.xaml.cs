using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using Microsoft.Phone.Controls;
using System.Collections.ObjectModel;
using Newtonsoft.Json.Linq;
using Embarcadero.Datasnap.WindowsPhone7;
using System.IO.IsolatedStorage;

namespace Foresight.InstantMessenger
{
    public partial class MainTweetPage : PhoneApplicationPage
    {
        public MainTweetPage()
        {
            InitializeComponent();
        }
        private delegate void OnSend();
        private void btnSendTweet_Click(object sender, RoutedEventArgs e)
        {
            CTConnection.getLoginUserInstance().SendMessageToAll(txtMsg.Text.ToString(),OnSendCallback,ManageExceptionCallback);
        }
        protected void OnSendCallback(bool Result)
        {
            if(Result==true) 
               this.Dispatcher.BeginInvoke(() =>
                   {
                   /*    listBox1.Items.Add("你 " + DateTime.Now.ToString("yyy-mm-dd hh:mm:ss") );
                       int txtPos = 0;
                       int txtLen = 22;
                       string msgText = txtMsg.Text;
                       if (msgText.Length > txtLen)
                       {
                           while (txtPos < msgText.Length)
                           {
                               string dipTxt = msgText.Substring(txtPos, txtLen);
                               listBox1.Items.Add(dipTxt);
                               txtPos = txtPos + txtLen;
                               if (txtPos + txtLen > msgText.Length)
                                   txtLen = msgText.Length - txtPos;
                           }
                       }
                       else
                           listBox1.Items.Add(msgText);*/
                       txtMsg.Text = "";
                   });
        }
        protected void ManageExceptionCallback(Exception e)
        {
            this.Dispatcher.BeginInvoke(() => MessageBox.Show("会话已过期，请重新登录."));
            this.NavigationService.Navigate(new Uri("/MainPage.xaml", UriKind.Relative));
        }
        private void ApplicationBarBackButton_Click(object sender, EventArgs e)
        {
            this.Dispatcher.BeginInvoke(() =>
            {
                this.NavigationService.Navigate(new Uri("/UsersList.xaml", UriKind.Relative));
                this.NavigationService.RemoveBackEntry();
            });
        }
        private void ApplicationBarIconButton_Click(object sender, EventArgs e)
        {
            CTConnection.LogOut();
            this.Dispatcher.BeginInvoke(() =>
            {
                this.NavigationService.Navigate(new Uri("/MainPage.xaml", UriKind.Relative));
            });
        }

        private void btnVibrate_Click(object sender, RoutedEventArgs e)
        {
            CTConnection.getLoginUserInstance().SendCMDToAll("vibrate");
        }

        private void btnRing_Click(object sender, RoutedEventArgs e)
        {
            CTConnection.getLoginUserInstance().SendCMDToAll("ring");
        }

    }
}