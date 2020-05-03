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
    public partial class AccBook
    {
        public AccBook() { }
        public AccBook(string accbookid, string accbookname)
        {
            AccBookID = accbookid;
            AccBookName = accbookname;
        }
        public string AccBookID{set;get;}
        public string AccBookName { set; get; }
    }
}
