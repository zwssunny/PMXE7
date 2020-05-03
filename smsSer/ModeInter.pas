unit ModeInter;

interface
uses
   winapi.Windows, Classes, SysUtils,Vcl.Forms;
function LoadModeDll: Boolean;
var
{
函数用来设置DLL启用线程模式执行，不受消息限制的执行，可以适合以服务方式执行的程序的调用。
参数: nMode - 1 开启线程模式
注意:一定在所有的fnInitModem函数调用之前调用这个才有效，否则可能造成程序混乱。
返回: 0-成功。
}
fnSetThreadMode: function(nMode:integer):integer stdcall;
 //函数说明
//先初始化,然后发送或者接收,退出程序前关闭Modem
{*************************************************************}
//  参数: nComNo 0~255 代表COM编号，
//        modemType 短信猫类型
//	  0 - 1口短信猫，
//        1 - 2口短信猫，
//        2 - 4口短信猫，
//        3 - 8短信猫口
//  返回: 0 - 成功， -1类型错
//        XXX -错误代码，参见代码表
{*************************************************************}
fnSetModemType: function(ComNo:integer; modemType:integer{Smallint}) :integer stdcall;

{******************************************************}
//	获取当前短信猫类型设置
//参数: nComNo 0~255 代表COM编号。
//返回 ：短信猫类型
//0 - 1口短信猫，
//1 - 2口短信猫，
//2 - 4口短信猫，
//3 - 8短信猫口
//XXX -错误代码，参见代码表
{*******************************************************}
 fnGetModemType: function(ComNo:integer):integer stdcall;

{***********************初始化函数***********************}
//参数: comx 0~7 代表端口号码， -1 表示所有端口
//返回: 0 - 成功  XXX -错误代码，参见代码表
{********************************************************}

 fnInitModem: function(comx:integer):integer;stdcall;

{***********************发送函数*************************}
//参数: comx 0~7 代表端口号码， -1 表示任意一个可用端口
//receivephone  接受手机号，sendmsg表示发送信息内容
//sendmsg(应该在70个字符以内,包含标点符号,1个汉字算1个字符)
//例如: 恭喜发财,测试成功!   长度为10
//返回: 0 - 发送成功 1 - 发送失败 XXX -错误代码，参见代码表
{********************************************************}
 fnSendMsg: function(comx:integer;receivephone,sendmsg:pchar):integer stdcall;

{********************************************************}
 // 参数: nPortNo 0~255 代表端口号码， -1 表示所有端口
//返回: 端口状态，大于等于8表示设备连接正常，可以接收和发送。
 //     状态小于8，表示测试状态。小于等于1，可能连线没有接好或者电源
 //	  没有打开，注意复位短信猫。
 //    -1 端口号指定错误或者是端口未打开

{********************************************************}
 fnGetStatus: function(nPortNo:integer):integer stdcall;
{*************************接收函数***********************}
//参数: comx 0~7 代表端口号码，
//(-1 表示任意一个可用端口,暂时不支持)
//sendphone 发送方手机号码      receivemsg 接收信息内容
//返回: 0~7 - 成功,接收端口号码  -1 -  无信息
//XXX -错误代码，参见代码表
{********************************************************}
 fnReadMsgEx: function(comx:integer;szHeader,receivemsg:pchar):integer stdcall;

 fnGetSndCount: function(nPortNo:integer):integer stdcall;
 fnGetRecCount: function(nPortNo:integer):integer stdcall;
//function fnSetReceive(nType:integer):integer stdcall;

{************************关闭函数************************}
//参数: comx 0~7 代表端口号码， -1 表示所有端口
//返回: 0 - 成功  XXX -错误代码，参见代码表
{********************************************************}

 fnCloseModem: function(comx:integer):integer stdcall;

{*******************错误代码表:**************************}
// 100: 授权错误(检测软件狗)
// 101: 授权类型错误(检测软件狗类型)
// 102: 未初始化，请先初始化

// 200: 端口号码错
// 201: 不支持的端口
// 202: 信息超长
// 203: 不能发送空信息
// 204: 手机号码错
// 205: 设备错

//5xx: 操作xx号端口错误
{********************************************************}
implementation
var
  hModeDll: THandle;

function LoadModeDll: Boolean;
var
  DLLName:String ;
begin
  Result := hModeDll > 0;
  if Result then Exit;
  DLLName:=ExtractFilePath(Application.ExeName)+'MonDem.dll';
  hModeDll := LoadLibrary(PChar(DLLName));
  Result := hModeDll > 0;
  if Result then
  begin
        fnSetThreadMode:= GetProcAddress(hModeDll, 'fnSetThreadMode');
        fnSetModemType := GetProcAddress(hModeDll, 'fnSetModemType');
        fnGetModemType := GetProcAddress(hModeDll, 'fnGetModemType');
        fnInitModem    := GetProcAddress(hModeDll, 'fnInitModem');
        fnSendMsg      := GetProcAddress(hModeDll, 'fnSendMsg');
        fnGetStatus    := GetProcAddress(hModeDll, 'fnGetStatus');
        fnReadMsgEx    := GetProcAddress(hModeDll, 'fnReadMsgEx');
        fnGetSndCount  := GetProcAddress(hModeDll, 'fnGetSndCount');
        fnGetRecCount  := GetProcAddress(hModeDll, 'fnGetRecCount');
        fnCloseModem   := GetProcAddress(hModeDll, 'fnCloseModem');
  end;
end;
procedure FreeModeDll;
begin
  if hModeDll > 0 then
  begin
        fnSetThreadMode:= nil;
        fnSetModemType := nil;
        fnGetModemType := nil;
        fnInitModem    := nil;
        fnSendMsg      := nil;
        fnGetStatus    := nil;
        fnReadMsgEx    := nil;
        fnGetSndCount  := nil;
        fnGetRecCount  := nil;
        fnCloseModem   := nil;
        FreeLibrary(hModeDll);
  end;
  hModeDll := 0;
end;
initialization
finalization
  FreeModeDll;
end.
