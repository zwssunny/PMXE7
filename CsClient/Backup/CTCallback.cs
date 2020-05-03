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
                    if (notificationtype == "message")
                    {
                        PhoneApplicationFrame frame = Application.Current.RootVisual as PhoneApplicationFrame;
                        PhoneApplicationPage mp = frame.Content as PhoneApplicationPage;
                        if (mp is MainTweetPage)
                        {
                            System.Windows.Controls.ListBox listbox = ((MainTweetPage)mp).listBox1;
                            listbox.Items.Add(obj.getString("fromusrname") + " " + obj.getString("datetime"));
                            string msgText = obj.getString("message");
                            int txtPos=0;
                            int txtLen = 22;
                            while (txtPos < msgText.Length)
                            {
                                string dipTxt = msgText.Substring(txtPos, txtLen);
                                listbox.Items.Add(dipTxt);
                                txtPos = txtPos + txtLen;
                                if (txtPos + txtLen > msgText.Length)
                                    txtLen = msgText.Length - txtPos;
                            }
                            SoundEffect.MasterVolume = 1.0f;
                            SoundEffect sfx = SoundEffect.FromStream(TitleContainer.OpenStream("tweet.wav"));
                            SoundEffectInstance sfxInstance = sfx.CreateInstance();
                            sfxInstance.Play();
                        }
                    }
                    else if(notificationtype =="cmd")
                    {
                        if (obj.getString("cmd") == "vibrate")
                        {
                           /* SoundEffect.MasterVolume = 1.0f;
                            SoundEffect sfx = SoundEffect.FromStream(TitleContainer.OpenStream("cmd.wav"));
                            SoundEffectInstance sfxInstance = sfx.CreateInstance();
                            sfxInstance.Play();*/

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
                        if (obj.getString("cmd") == "ring")
                        {
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
