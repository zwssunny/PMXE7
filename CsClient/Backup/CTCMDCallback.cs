using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Embarcadero.Datasnap.WindowsPhone7;
using System.Windows.Controls;
using System.Windows.Resources;
using System.Windows;
using Microsoft.Phone.Controls;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework;

namespace Foresight.InstantMessenger
{
    class CTCMDCallback : DBXCallback
    {
        private SynchronizationContext Context;
        public CTCMDCallback(SynchronizationContext Context)
            : base()
        {
            this.Context = Context;
        }

        public override TJSONValue Execute(TJSONValue value, int JSONType)
        {
            TJSONObject obj = TJSONObject.Parse(value.ToString());
            Context.Send(new SendOrPostCallback(x =>
            {
                if (obj.getString("cmd") == "vibrate")
                {
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
            }), null);
            return null;
        }


    }
}
