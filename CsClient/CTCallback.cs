using Embarcadero.Datasnap.WindowsPhone7;
using Microsoft.Phone.Controls;
using System.Windows;
using System;
using System.Threading;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework;
using System.Collections.Generic;
using System.Collections.ObjectModel;


namespace Foresight.InstantMessenger
{
    public class CTCallback : DBXCallback
    {
        private SynchronizationContext Context;
        public CTCallback(SynchronizationContext contxt)
            : base()
        {
            Context = contxt;
        }

        public override TJSONValue Execute(TJSONValue value, int JSONType)
        {
            TJSONObject obj = TJSONObject.Parse(value.ToString());
            Context.Send(new SendOrPostCallback(x =>
                {
                    string notificationtype = obj.getString("notificationType");
                    string fromusrname = obj.getString("fromusrname");
                    string datetimestr = obj.getString("datetime");
                    if (notificationtype == "user_login" || notificationtype == "user_logout")
                    {
                        string userid = obj.getString("from");
                        string msgText;
                        if (notificationtype == "user_login")
                            msgText = "登录了！";
                        else
                            msgText = "退出了！";
                        if (CTConnection.getCurUserID() == userid)
                            return;
                        MessageBox.Show(fromusrname + msgText + datetimestr  );

                        PhoneApplicationFrame frame = Application.Current.RootVisual as PhoneApplicationFrame;
                        PhoneApplicationPage mp = frame.Content as PhoneApplicationPage;
                        if(mp is UsersList)
                        {
                            UsersList userp=(UsersList)mp;
                            userp.RefreshListBox();
                        }
   
                          /*  SoundEffect.MasterVolume = 1.0f;
                            SoundEffect sfx = SoundEffect.FromStream(TitleContainer.OpenStream("tweet.wav"));
                            SoundEffectInstance sfxInstance = sfx.CreateInstance();
                            sfxInstance.Play();*/
                    }
                    else if (notificationtype == "message")
                    {
                        PhoneApplicationFrame frame = Application.Current.RootVisual as PhoneApplicationFrame;
                        PhoneApplicationPage mp = frame.Content as PhoneApplicationPage;
                        if (mp is MainTweetPage)
                        {
                            System.Windows.Controls.ListBox listbox = ((MainTweetPage)mp).listBox1;
                            listbox.Items.Add(fromusrname + " " + datetimestr);
                            string msgText = obj.getString("message");
                            int txtPos = 0;
                            int txtLen = 22;
                            if (msgText.Length > txtLen)
                            {
                                while (txtPos < msgText.Length)
                                {
                                    string dipTxt = msgText.Substring(txtPos, txtLen);
                                    listbox.Items.Add(dipTxt);
                                    txtPos = txtPos + txtLen;
                                    if (txtPos + txtLen > msgText.Length)
                                        txtLen = msgText.Length - txtPos;
                                }
                            }
                            else
                                listbox.Items.Add(msgText);

                        }
                    }
                    else if(notificationtype =="cmd")
                    {

                        if (obj.getString("cmd") == "vibrate")
                        {
                            PhoneApplicationFrame frame = Application.Current.RootVisual as PhoneApplicationFrame;
                            PhoneApplicationPage mp = frame.Content as PhoneApplicationPage;
                            if (mp is MainTweetPage)
                            {
                                System.Windows.Controls.ListBox listbox = ((MainTweetPage)mp).listBox1;
                                listbox.Items.Add(fromusrname + " " + datetimestr);
                                listbox.Items.Add("发送：震动");

                            }

                            Microsoft.Devices.VibrateController.Default.Start(TimeSpan.FromMilliseconds(50));
                            System.Windows.Threading.DispatcherTimer timer = new System.Windows.Threading.DispatcherTimer();
                            timer.Interval = new TimeSpan(0, 0, 0, 0, 200);
                            timer.Tick += (tsender, tevt) =>
                            {
                                var t = tsender as System.Windows.Threading.DispatcherTimer;
                                t.Stop();
                                Microsoft.Devices.VibrateController.Default.Stop();

                            };
                            timer.Start();
                        }
                        else
                        if (obj.getString("cmd") == "ring")
                        {
                            PhoneApplicationFrame frame = Application.Current.RootVisual as PhoneApplicationFrame;
                            PhoneApplicationPage mp = frame.Content as PhoneApplicationPage;
                            if (mp is MainTweetPage)
                            {
                                System.Windows.Controls.ListBox listbox = ((MainTweetPage)mp).listBox1;
                                listbox.Items.Add(fromusrname + " " + datetimestr);
                                listbox.Items.Add("发送：响铃");

                            }                            
                            SoundEffect.MasterVolume = 1.0f;
                            SoundEffect sfx = SoundEffect.FromStream(TitleContainer.OpenStream("cmd.wav"));
                            SoundEffectInstance sfxInstance = sfx.CreateInstance();
                            sfxInstance.Play();
                        }
                    }
                }), null);
            return null;
        }
    }
}
