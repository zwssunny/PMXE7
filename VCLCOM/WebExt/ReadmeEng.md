TWebBrowserEx

This class provides an opportunity to use a unified manner 
WebBrowser FireMonkey applications in Windows/OSx/iOS/Android.

A web browser that has been done with the help of this class 
will use a web browser to the default management, which are 
mounted on the platform, as shown below.

|Platform|Component       |
|--------|----------------|
|Windows |IWebBrowser(IE) |
|OSx     |WebView(Safari) |
|iOS     |WebView         |
|Android |WebView         |

Operating environment:

Delphi/C++Builder/RAD Studio XE6, XE7.

It is necessary to have available the following files:

 FMX.WebBrowser.Mac.pas    OSx for WebBrowser class
 FMX.WebBrowser.Win.pas    For Windows WebBrowser class
   FMX.WebBrowserEx.pas    Class that works in a unified manner WebBrowser of multi-platform
     Macapi.WebView.pas    Units that were transplanted into the definition of the Delphi WebView of OSx

How to use:

As described below, I will use in the same way as TWebBrowser of iOS/Android.

uses
  FMX.WebBrowserEx;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Button1: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    FWebBrowser: TWebBrowserEx;
  end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  FWebBrowser := TWebBrowserEx.Create(Self);
  FWebBrowser.Parent := Panel1;
  FWebBrowser.Align := TAlignLayout.Client;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  FWebBrowser.URL := 'http://www.embarcadero.com/';

  // It is also possible to read a String like this
  FWebBrowser.LoadFromStrings('<html><body>Hello WebBrowser!</body></html>', '');
end;

In addition, as described below, I can also use JavaScript.

procedure TForm1.Button2Click(Sender: TObject);
var
  Value: String;
begin
  // The call by passing two arguments to the JavaScript function foo that is defined in the HTML
  FWebBrowser.CallJS('foo', [Param1, Param2]);
  
  // I call in a standard way of TWebBrowser
  FWebBrowser.EvaluteJavascript('alert("Delphi!")');
  
  // I want to get the value of the HTML tags
  // If there is a tag called <input type = "text" id = "bar" value = ""/>
  // I can get the value of the attribute values id of bar in this
  Value := FWebBrowser.GetTagValue('bar', 'value'); 
end;

Specifications bug like known.

You can not move the focus to the TWebBrowserEx the Tab key:

You can not move the focus to other controls in the Tab key if TWebBrowserEx 
has the focus as well.
You think and granting the focus in the direction of TWebBrowser -> FMX Control 
if the implementation of DocHostTranslateAccelerator IDocHostUIHandler.
It might be the focus and granting also FMX Control -> TWebBrowser direction 
if you override the SetFocus of TWebBrowserEx.

Copyright.

It does not matter using freely regardless of the commercial and non-commercial.
The Feel free to also modified.
In addition, it does not have abandoned copyright, "This I over! / Our I made"