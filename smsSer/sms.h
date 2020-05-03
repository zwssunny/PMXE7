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

#ifndef   smsH
#define   smsH

#include <System.hpp>
#include <InvokeRegistry.hpp>
#include <XSBuiltIns.hpp>
#include <SOAPHTTPClient.hpp>

#if !defined(SOAP_REMOTABLE_CLASS)
#define SOAP_REMOTABLE_CLASS __declspec(delphiclass)
#endif
#if !defined(IS_OPTN)
#define IS_OPTN 0x0001
#endif
#if !defined(IS_UNBD)
#define IS_UNBD 0x0002
#endif
#if !defined(IS_NLBL)
#define IS_NLBL 0x0004
#endif
#if !defined(IS_REF)
#define IS_REF 0x0080
#endif


namespace NS_sms {

// ************************************************************************ //
// The following types, referred to in the WSDL document are not being represented
// in this file. They are either aliases[@] of other types represented or were referred
// to but never[!] declared in the document. The types from the latter category
// typically map to predefined/known XML or Borland types; however, they could also 
// indicate incorrect WSDL documents that failed to declare or import a schema type.
// ************************************************************************ //
// !:string          - "http://www.w3.org/2001/XMLSchema"[Gbl]
// !:int             - "http://www.w3.org/2001/XMLSchema"[Gbl]

class SOAP_REMOTABLE_CLASS CommonReturn;
class SOAP_REMOTABLE_CLASS RepliedSMS;
class SOAP_REMOTABLE_CLASS SMSNode;
class SOAP_REMOTABLE_CLASS StockDetails;
class SOAP_REMOTABLE_CLASS SendStatus;
class SOAP_REMOTABLE_CLASS RemoteException;
class SOAP_REMOTABLE_CLASS RemoteException2;
class SOAP_REMOTABLE_CLASS Throwable;



// ************************************************************************ //
// XML       : CommonReturn, global, <complexType>
// Namespace : http://soap.sms.com
// ************************************************************************ //
class CommonReturn : public TRemotable {
private:
  WideString      Fmessage;
  bool            Fmessage_Specified;
  WideString      FretCode;
  bool            FretCode_Specified;
  void __fastcall Setmessage(int Index, WideString _prop_val)
  {  Fmessage = _prop_val; Fmessage_Specified = true;  }
  bool __fastcall message_Specified(int Index)
  {  return Fmessage_Specified;  } 
  void __fastcall SetretCode(int Index, WideString _prop_val)
  {  FretCode = _prop_val; FretCode_Specified = true;  }
  bool __fastcall retCode_Specified(int Index)
  {  return FretCode_Specified;  } 
__published:
  __property WideString    message = { index=(IS_OPTN|IS_NLBL), read=Fmessage, write=Setmessage, stored = message_Specified };
  __property WideString    retCode = { index=(IS_OPTN|IS_NLBL), read=FretCode, write=SetretCode, stored = retCode_Specified };
};


typedef DynamicArray<SMSNode*>    ArrayOfSMSNode; /* "http://soap.sms.com"[GblCplx] */


// ************************************************************************ //
// XML       : RepliedSMS, global, <complexType>
// Namespace : http://soap.sms.com
// ************************************************************************ //
class RepliedSMS : public TRemotable {
private:
  ArrayOfSMSNode  FSMSGroup;
  bool            FSMSGroup_Specified;
  int             Fcount;
  bool            Fcount_Specified;
  WideString      Fmessage;
  bool            Fmessage_Specified;
  WideString      FretCode;
  bool            FretCode_Specified;
  void __fastcall SetSMSGroup(int Index, ArrayOfSMSNode _prop_val)
  {  FSMSGroup = _prop_val; FSMSGroup_Specified = true;  }
  bool __fastcall SMSGroup_Specified(int Index)
  {  return FSMSGroup_Specified;  } 
  void __fastcall Setcount(int Index, int _prop_val)
  {  Fcount = _prop_val; Fcount_Specified = true;  }
  bool __fastcall count_Specified(int Index)
  {  return Fcount_Specified;  } 
  void __fastcall Setmessage(int Index, WideString _prop_val)
  {  Fmessage = _prop_val; Fmessage_Specified = true;  }
  bool __fastcall message_Specified(int Index)
  {  return Fmessage_Specified;  } 
  void __fastcall SetretCode(int Index, WideString _prop_val)
  {  FretCode = _prop_val; FretCode_Specified = true;  }
  bool __fastcall retCode_Specified(int Index)
  {  return FretCode_Specified;  } 

public:
  __fastcall ~RepliedSMS();
__published:
  __property ArrayOfSMSNode   SMSGroup = { index=(IS_OPTN|IS_NLBL), read=FSMSGroup, write=SetSMSGroup, stored = SMSGroup_Specified };
  __property int             count = { index=(IS_OPTN), read=Fcount, write=Setcount, stored = count_Specified };
  __property WideString    message = { index=(IS_OPTN|IS_NLBL), read=Fmessage, write=Setmessage, stored = message_Specified };
  __property WideString    retCode = { index=(IS_OPTN|IS_NLBL), read=FretCode, write=SetretCode, stored = retCode_Specified };
};




// ************************************************************************ //
// XML       : SMSNode, global, <complexType>
// Namespace : http://soap.sms.com
// ************************************************************************ //
class SMSNode : public TRemotable {
private:
  WideString      F_value;
  bool            F_value_Specified;
  WideString      Fphone;
  bool            Fphone_Specified;
  WideString      FpostFixNumber;
  bool            FpostFixNumber_Specified;
  WideString      FrecDateTime;
  bool            FrecDateTime_Specified;
  void __fastcall Set_value(int Index, WideString _prop_val)
  {  F_value = _prop_val; F_value_Specified = true;  }
  bool __fastcall _value_Specified(int Index)
  {  return F_value_Specified;  } 
  void __fastcall Setphone(int Index, WideString _prop_val)
  {  Fphone = _prop_val; Fphone_Specified = true;  }
  bool __fastcall phone_Specified(int Index)
  {  return Fphone_Specified;  } 
  void __fastcall SetpostFixNumber(int Index, WideString _prop_val)
  {  FpostFixNumber = _prop_val; FpostFixNumber_Specified = true;  }
  bool __fastcall postFixNumber_Specified(int Index)
  {  return FpostFixNumber_Specified;  } 
  void __fastcall SetrecDateTime(int Index, WideString _prop_val)
  {  FrecDateTime = _prop_val; FrecDateTime_Specified = true;  }
  bool __fastcall recDateTime_Specified(int Index)
  {  return FrecDateTime_Specified;  } 
__published:
  __property WideString     _value = { index=(IS_OPTN|IS_NLBL), read=F_value, write=Set_value, stored = _value_Specified };
  __property WideString      phone = { index=(IS_OPTN|IS_NLBL), read=Fphone, write=Setphone, stored = phone_Specified };
  __property WideString postFixNumber = { index=(IS_OPTN|IS_NLBL), read=FpostFixNumber, write=SetpostFixNumber, stored = postFixNumber_Specified };
  __property WideString recDateTime = { index=(IS_OPTN|IS_NLBL), read=FrecDateTime, write=SetrecDateTime, stored = recDateTime_Specified };
};




// ************************************************************************ //
// XML       : StockDetails, global, <complexType>
// Namespace : http://soap.sms.com
// ************************************************************************ //
class StockDetails : public TRemotable {
private:
  int             FcurDaySend;
  bool            FcurDaySend_Specified;
  WideString      Fmessage;
  bool            Fmessage_Specified;
  int             Fpoints;
  bool            Fpoints_Specified;
  WideString      FretCode;
  bool            FretCode_Specified;
  int             FsendTotal;
  bool            FsendTotal_Specified;
  int             FstockRemain;
  bool            FstockRemain_Specified;
  void __fastcall SetcurDaySend(int Index, int _prop_val)
  {  FcurDaySend = _prop_val; FcurDaySend_Specified = true;  }
  bool __fastcall curDaySend_Specified(int Index)
  {  return FcurDaySend_Specified;  } 
  void __fastcall Setmessage(int Index, WideString _prop_val)
  {  Fmessage = _prop_val; Fmessage_Specified = true;  }
  bool __fastcall message_Specified(int Index)
  {  return Fmessage_Specified;  } 
  void __fastcall Setpoints(int Index, int _prop_val)
  {  Fpoints = _prop_val; Fpoints_Specified = true;  }
  bool __fastcall points_Specified(int Index)
  {  return Fpoints_Specified;  } 
  void __fastcall SetretCode(int Index, WideString _prop_val)
  {  FretCode = _prop_val; FretCode_Specified = true;  }
  bool __fastcall retCode_Specified(int Index)
  {  return FretCode_Specified;  } 
  void __fastcall SetsendTotal(int Index, int _prop_val)
  {  FsendTotal = _prop_val; FsendTotal_Specified = true;  }
  bool __fastcall sendTotal_Specified(int Index)
  {  return FsendTotal_Specified;  } 
  void __fastcall SetstockRemain(int Index, int _prop_val)
  {  FstockRemain = _prop_val; FstockRemain_Specified = true;  }
  bool __fastcall stockRemain_Specified(int Index)
  {  return FstockRemain_Specified;  } 
__published:
  __property int        curDaySend = { index=(IS_OPTN), read=FcurDaySend, write=SetcurDaySend, stored = curDaySend_Specified };
  __property WideString    message = { index=(IS_OPTN|IS_NLBL), read=Fmessage, write=Setmessage, stored = message_Specified };
  __property int            points = { index=(IS_OPTN), read=Fpoints, write=Setpoints, stored = points_Specified };
  __property WideString    retCode = { index=(IS_OPTN|IS_NLBL), read=FretCode, write=SetretCode, stored = retCode_Specified };
  __property int         sendTotal = { index=(IS_OPTN), read=FsendTotal, write=SetsendTotal, stored = sendTotal_Specified };
  __property int        stockRemain = { index=(IS_OPTN), read=FstockRemain, write=SetstockRemain, stored = stockRemain_Specified };
};




// ************************************************************************ //
// XML       : SendStatus, global, <complexType>
// Namespace : http://soap.sms.com
// ************************************************************************ //
class SendStatus : public TRemotable {
private:
  int             FOKPhoneCounts;
  bool            FOKPhoneCounts_Specified;
  WideString      FerrPhones;
  bool            FerrPhones_Specified;
  int             FjobID;
  bool            FjobID_Specified;
  WideString      Fmessage;
  bool            Fmessage_Specified;
  WideString      FretCode;
  bool            FretCode_Specified;
  int             FstockReduced;
  bool            FstockReduced_Specified;
  void __fastcall SetOKPhoneCounts(int Index, int _prop_val)
  {  FOKPhoneCounts = _prop_val; FOKPhoneCounts_Specified = true;  }
  bool __fastcall OKPhoneCounts_Specified(int Index)
  {  return FOKPhoneCounts_Specified;  } 
  void __fastcall SeterrPhones(int Index, WideString _prop_val)
  {  FerrPhones = _prop_val; FerrPhones_Specified = true;  }
  bool __fastcall errPhones_Specified(int Index)
  {  return FerrPhones_Specified;  } 
  void __fastcall SetjobID(int Index, int _prop_val)
  {  FjobID = _prop_val; FjobID_Specified = true;  }
  bool __fastcall jobID_Specified(int Index)
  {  return FjobID_Specified;  } 
  void __fastcall Setmessage(int Index, WideString _prop_val)
  {  Fmessage = _prop_val; Fmessage_Specified = true;  }
  bool __fastcall message_Specified(int Index)
  {  return Fmessage_Specified;  } 
  void __fastcall SetretCode(int Index, WideString _prop_val)
  {  FretCode = _prop_val; FretCode_Specified = true;  }
  bool __fastcall retCode_Specified(int Index)
  {  return FretCode_Specified;  } 
  void __fastcall SetstockReduced(int Index, int _prop_val)
  {  FstockReduced = _prop_val; FstockReduced_Specified = true;  }
  bool __fastcall stockReduced_Specified(int Index)
  {  return FstockReduced_Specified;  } 
__published:
  __property int        OKPhoneCounts = { index=(IS_OPTN), read=FOKPhoneCounts, write=SetOKPhoneCounts, stored = OKPhoneCounts_Specified };
  __property WideString  errPhones = { index=(IS_OPTN|IS_NLBL), read=FerrPhones, write=SeterrPhones, stored = errPhones_Specified };
  __property int             jobID = { index=(IS_OPTN), read=FjobID, write=SetjobID, stored = jobID_Specified };
  __property WideString    message = { index=(IS_OPTN|IS_NLBL), read=Fmessage, write=Setmessage, stored = message_Specified };
  __property WideString    retCode = { index=(IS_OPTN|IS_NLBL), read=FretCode, write=SetretCode, stored = retCode_Specified };
  __property int        stockReduced = { index=(IS_OPTN), read=FstockReduced, write=SetstockReduced, stored = stockReduced_Specified };
};




// ************************************************************************ //
// XML       : RemoteException, global, <complexType>
// Namespace : http://rmi.java
// Info      : Fault
// ************************************************************************ //
class RemoteException : public ERemotableException {
private:
  Throwable*      Fcause;
  bool            Fcause_Specified;
  WideString      Fmessage;
  bool            Fmessage_Specified;
  void __fastcall Setcause(int Index, Throwable* _prop_val)
  {  Fcause = _prop_val; Fcause_Specified = true;  }
  bool __fastcall cause_Specified(int Index)
  {  return Fcause_Specified;  } 
  void __fastcall Setmessage(int Index, WideString _prop_val)
  {  Fmessage = _prop_val; Fmessage_Specified = true;  }
  bool __fastcall message_Specified(int Index)
  {  return Fmessage_Specified;  } 

public:
  __fastcall ~RemoteException();
__published:
  __property Throwable*      cause = { index=(IS_OPTN|IS_NLBL), read=Fcause, write=Setcause, stored = cause_Specified };
  __property WideString    message = { index=(IS_OPTN|IS_NLBL), read=Fmessage, write=Setmessage, stored = message_Specified };
};




// ************************************************************************ //
// XML       : RemoteException, global, <element>
// Namespace : http://soap.sms.com
// Info      : Fault
// ************************************************************************ //
class RemoteException2 : public RemoteException {
private:
__published:
};




// ************************************************************************ //
// XML       : Throwable, global, <complexType>
// Namespace : http://lang.java
// ************************************************************************ //
class Throwable : public TRemotable {
private:
__published:
};



// ************************************************************************ //
// Namespace : http://soap.sms.com
// transport : http://schemas.xmlsoap.org/soap/http
// style     : document
// binding   : smsHttpBinding
// service   : sms
// port      : smsHttpPort
// URL       : http://58.63.224.34:8000/smsweb/services/sms
// ************************************************************************ //
__interface INTERFACE_UUID("{B462590D-86C7-A55B-C741-E449A50294DB}") smsPortType : public IInvokable
{
public:
  virtual CommonReturn*   passwordChange(const WideString userID, const WideString account, const WideString password, const WideString newPSW) = 0; 
  virtual RepliedSMS*     directFetchSMS(const WideString userID, const WideString account, const WideString password, const WideString spid, const WideString commid) = 0; 
  virtual StockDetails*   directGetSubDetails(const WideString Muid, const WideString account, const WideString passwd, const WideString Nuid) = 0; 
  virtual StockDetails*   directGetStockDetails(const WideString userID, const WideString account, const WideString password) = 0; 
  virtual SendStatus*     directSend1(const WideString userID, const WideString account, const WideString password, const WideString phones, const WideString content, const WideString sendTime, const int sendType, const WideString postFixNumber, const int sign) = 0; 
  virtual WideString      AddUser(const WideString account, const WideString passwd, const WideString username, const WideString mobileid, const int usertype) = 0; 
  virtual WideString      AddSubuser(const WideString Muid, const WideString account, const WideString passwd, const WideString subaccount, const WideString subusername, const WideString mobileid, const int usertype) = 0; 
  virtual WideString      Delsend(const WideString userID, const WideString account, const WideString password, const WideString batchid) = 0; 
  virtual WideString      UserInfo(const WideString Muid, const WideString Name, const WideString mobileid, const WideString info) = 0; 
  virtual WideString      ManagerUser(const WideString Muid, const WideString account, const WideString passwd, const WideString Nuid, const WideString OperateType, const int Amount) = 0; 
  virtual SendStatus*     directSend(const WideString userID, const WideString account, const WideString password, const WideString phones, const WideString content, const WideString sendTime, const int sendType, const WideString postFixNumber, const int sign) = 0; 
};
typedef DelphiInterface<smsPortType> _di_smsPortType;

_di_smsPortType GetsmsPortType(bool useWSDL=false, AnsiString addr="", THTTPRIO* HTTPRIO=0);


};     // NS_sms

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace NS_sms;
#endif



#endif // smsH
