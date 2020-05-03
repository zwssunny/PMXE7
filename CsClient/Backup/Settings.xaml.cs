using System;
using System.Windows;
using System.Windows.Input;
using Microsoft.Phone.Controls;
using System.IO.IsolatedStorage;

namespace Foresight.InstantMessenger
{
    public partial class Page1 : PhoneApplicationPage
    {
        IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

        public Page1()
        {
            InitializeComponent();

            if (!settings.Contains("hostname"))
                settings.Add("hostname", "localhost");

            if (!settings.Contains("port")) 
                settings.Add("port", "8080");

             txt_hostname.Text = settings["hostname"].ToString();
             txt_port.Text = settings["port"].ToString();
            

            InputScopeNameValue digitInputScopeNameValue = InputScopeNameValue.TelephoneNumber;
            txt_port.InputScope = new InputScope()
            {
                Names = {new InputScopeName() { NameValue = digitInputScopeNameValue}}
            };  
        }

        private void SaveSettings(object sender, EventArgs e)
        {
            this.Dispatcher.BeginInvoke(() => 
            {
                settings["hostname"] = txt_hostname.Text.ToString();
                settings["port"] = txt_port.Text.ToString();

                settings.Save();
                CTConnection.ResetProxy();

                try
                {
                    Convert.ToInt32(txt_port.Text.ToString());
                    this.NavigationService.Navigate(new Uri("/MainPage.xaml", UriKind.Relative)); 
                }
                catch (Exception)
                {
                    MessageBox.Show("Invalid port number!");
                } 
            });
        }
    }
}