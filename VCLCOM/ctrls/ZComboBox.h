//---------------------------------------------------------------------------

#ifndef ZComboBoxH
#define ZComboBoxH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include "PubEnum.h"
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZComboBox : public TComboBox
{
private:
  TZCharType  FCharType;
  TZCharCase  FCharCase;
  TZComboBoxItemIndex FKeyItem;
  TZComboBoxItemIndex FDispItem;
  String  FDataField;
  TStringList *FDataItem1;
  TStringList *FDataItem2;
  TStringList *FDataItem3;
  TStringList *FDataItem4;
  TStringList *FDataItem5;
  TStringList *FDataItem6;
  TStringList *FDataKeyItem;
  bool FReadState;
  bool FCaseSensitive;
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FComboBoxFlat;

  void __fastcall ClearBorder(TWinControl *WinCtl,TColor clearcolor);
  void __fastcall DrawComboBoxFlat();
  void __fastcall SetReadOnly(bool Read);
  String __fastcall GetItemData(int Index);
  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetComboBoxFlat(bool value);

protected:
  void __fastcall WMPaint(TWMPaint &Message);

  DYNAMIC void __fastcall KeyPress(Char &Key);
  DYNAMIC void __fastcall Change(void);

  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
  void __fastcall WMSetFocus(TMessage &Message);
  void __fastcall WMKillFocus(TMessage &Message);
  void __fastcall CNCommand(TWMCommand &Message);
  virtual void __fastcall CreateParams(TCreateParams &Params);
  void __fastcall DoSetFocus();
  void __fastcall DoKillFocus();
public:
  __fastcall TZComboBox(TComponent* Owner);
  __fastcall ~TZComboBox();
  void __fastcall AddItems(String Item1,String Item2="",String Item3="",String Item4="",String Item5=""
      ,String Item6="",String Item7="");
  void __fastcall AssignItems(TStringList *Item1,TStringList *Item2=NULL,TStringList *Item3=NULL,TStringList *Item4=NULL
      ,TStringList *Item5=NULL,TStringList *Item6=NULL,TStringList *Item7=NULL);
  bool __fastcall LocateKey(String value);
  __property String ItemData[int i]={read=GetItemData};
  void __fastcall ClearAll();

__published:
  __property TZComboBoxItemIndex DispItem={read=FDispItem,write=FDispItem};
  __property TZComboBoxItemIndex KeyItem={read=FKeyItem,write=FKeyItem};
  __property TZCharType CharType={read=FCharType,write=FCharType};
  __property TZCharCase CharCase={read=FCharCase,write=FCharCase};
  __property bool ReadOnly={read=FReadState,write=SetReadOnly};
  __property String DataField={read=FDataField,write=FDataField};
  __property bool CaseSensitive={read=FCaseSensitive,write=FCaseSensitive,default=false};
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=clWhite};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crFocusedColor};
  __property bool Flat={read=FComboBoxFlat,write=SetComboBoxFlat};

  __property Align;

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(CBN_SETFOCUS,TMessage,WMSetFocus);
    VCL_MESSAGE_HANDLER(CBN_KILLFOCUS,TMessage,WMKillFocus);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TMessage,WMSetFocus);
    VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TMessage,WMKillFocus);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN,TMessage,WMSetFocus);
    VCL_MESSAGE_HANDLER(CN_COMMAND,TWMCommand,CNCommand);
  END_MESSAGE_MAP(TComboBox);
};
//---------------------------------------------------------------------------
#endif
