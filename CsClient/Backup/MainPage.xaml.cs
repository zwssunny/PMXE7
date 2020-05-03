using System;
using System.IO.IsolatedStorage;
using System.Threading;
using System.Windows;
using Embarcadero.Datasnap.WindowsPhone7;
using Microsoft.Phone.Controls;
using System.Windows.Navigation;

namespace Foresight.InstantMessenger
{
    public partial class MainPage : PhoneApplicationPage
    {
        protected DSRESTConnection Connection;
        private IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;
        // Constructor
        public System.Collections.ObjectModel.ObservableCollection<AccBook> AccBookArray =
       new System.Collections.ObjectModel.ObservableCollection<AccBook>();
        public MainPage()
        {
            InitializeComponent();
            LoadAccBookList();
            if (settings.Contains("UserCode")) txtName.Text = settings["UserCode"].ToString();
            if (settings.Contains("Password")) txtPassword.Password = settings["Password"].ToString();
          //  if (settings.Contains("AccbookID")) lbAccBook.Items. = settings["AccbookID"].ToString();
        }

        private delegate void OnLogin();
        private delegate void OnException(Exception e);
        private void btn_Login(object sender, EventArgs e)
        {
            OnLogin LoginDelegate = () =>
                 Dispatcher.BeginInvoke(() => NavigationService.Navigate(new Uri("/UsersList.xaml", UriKind.Relative)));
            OnException ExceptionDelegate = (ex) =>
                 Dispatcher.BeginInvoke(() => MessageBox.Show(ex.Message));
            CTConnection.ResetProxy();
            String retmsg = "";
            String AccCode="";
            int sindex = lbAccBook.SelectedIndex;
            if(sindex>-1)
                AccCode = AccBookArray[sindex].AccBookID;
            CTConnection.LoginUser(txtName.Text, txtPassword.Password, AccCode, retmsg, LoginDelegate, ExceptionDelegate);
        }
        private void LoadAccBookList()
        {
            CTConnection.getLoginUserInstance().GetAccListJSON(result =>
            {
                this.Dispatcher.BeginInvoke(() =>
                {
                    lbAccBook.Items.Clear();
                    AccBookArray.Clear();
                    TJSONArray accbooks = result.getJSONArray("accbooks");
                    int i = 0;
                    for (i = 0; i < accbooks.size(); i++)
                    {
                        TJSONObject AccItem = accbooks.getJSONObject(i);
                        AccBookArray.Add(new AccBook(AccItem.getString("syaccbookcode"), AccItem.getString("syaccbookname")));
                        lbAccBook.Items.Add(AccItem.getString("syaccbookname"));
                    }
                    if (lbAccBook.Items.Count > 0)
                        lbAccBook.SelectedIndex = 0;
                });
            }, ManageExceptionCallback);
        }
        protected void ManageExceptionCallback(Exception e)
        {
            this.Dispatcher.BeginInvoke(() => MessageBox.Show(e.Message));
        }

        private void mnuSetHost_Click(object sender, EventArgs e)
        {
            this.Dispatcher.BeginInvoke(() => { this.NavigationService.Navigate(new Uri("/Settings.xaml", UriKind.Relative)); });
        }
    }
}