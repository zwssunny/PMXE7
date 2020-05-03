// ************************************************************************ //
// The types declared in this file were generated from data read from the
// WSDL File described below:
// WSDL     : http://58.63.224.34:8000/smsweb/services/sms?wsdl
//  >Import : http://58.63.224.34:8000/smsweb/services/sms?wsdl:0
//  >Import : http://58.63.224.34:8000/smsweb/services/sms?wsdl:1
//  >Import : http://58.63.224.34:8000/smsweb/services/sms?wsdl:2
// Encoding : UTF-8
// Version  : 1.0
// (2010-11-17 15:34:06 - - $Rev: 10138 $)
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#if !defined(smsH)
#include "sms.h"
#endif



namespace NS_sms {

_di_smsPortType GetsmsPortType(bool useWSDL, AnsiString addr, THTTPRIO* HTTPRIO)
{
  static const char* defWSDL= "http://58.63.224.34:8000/smsweb/services/sms?wsdl";
  static const char* defURL = "http://58.63.224.34:8000/smsweb/services/sms";
  static const char* defSvc = "sms";
  static const char* defPrt = "smsHttpPort";
  if (addr=="")
    addr = useWSDL ? defWSDL : defURL;
  THTTPRIO* rio = HTTPRIO ? HTTPRIO : new THTTPRIO(0);
  if (useWSDL) {
    rio->WSDLLocation = addr;
    rio->Service = defSvc;
    rio->Port = defPrt;
  } else {
    rio->URL = addr;
  }
  _di_smsPortType service;
  rio->QueryInterface(service);
  if (!service && !HTTPRIO)
    delete rio;
  return service;
}


__fastcall RepliedSMS::~RepliedSMS()
{
  for(int i=0; i<FSMSGroup.Length; i++)
    if (FSMSGroup[i])
      delete FSMSGroup[i];
}

__fastcall RemoteException::~RemoteException()
{
  delete Fcause;
}

// ************************************************************************ //
// This routine registers the interfaces and types exposed by the WebService.
// ************************************************************************ //
static void RegTypes()
{
  /* smsPortType */
  InvRegistry()->RegisterInterface(__interfaceTypeinfo(smsPortType), L"http://soap.sms.com", L"UTF-8");
  InvRegistry()->RegisterDefaultSOAPAction(__interfaceTypeinfo(smsPortType), L"");
  InvRegistry()->RegisterInvokeOptions(__interfaceTypeinfo(smsPortType), ioDocument);
  /* CommonReturn */
  RemClassRegistry()->RegisterXSClass(__classid(CommonReturn), L"http://soap.sms.com", L"CommonReturn");
  /* ArrayOfSMSNode */
  RemClassRegistry()->RegisterXSInfo(__arrayTypeinfo(ArrayOfSMSNode), L"http://soap.sms.com", L"ArrayOfSMSNode");
  /* RepliedSMS */
  RemClassRegistry()->RegisterXSClass(__classid(RepliedSMS), L"http://soap.sms.com", L"RepliedSMS");
  /* SMSNode */
  RemClassRegistry()->RegisterXSClass(__classid(SMSNode), L"http://soap.sms.com", L"SMSNode");
  /* StockDetails */
  RemClassRegistry()->RegisterXSClass(__classid(StockDetails), L"http://soap.sms.com", L"StockDetails");
  /* SendStatus */
  RemClassRegistry()->RegisterXSClass(__classid(SendStatus), L"http://soap.sms.com", L"SendStatus");
  /* RemoteException */
  RemClassRegistry()->RegisterXSClass(__classid(RemoteException), L"http://rmi.java", L"RemoteException");
  /* RemoteException */
  RemClassRegistry()->RegisterXSClass(__classid(RemoteException2), L"http://soap.sms.com", L"RemoteException2", L"RemoteException");
  /* Throwable */
  RemClassRegistry()->RegisterXSClass(__classid(Throwable), L"http://lang.java", L"Throwable");
}
#pragma startup RegTypes 32

};     // NS_sms

