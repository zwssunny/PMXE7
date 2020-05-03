//---------------------------------------------------------------------------

#ifndef ZEditH
#define ZEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include "PubEnum.h"
#include "ColorDefine.h"
//---------------------------------------------------------------------------
class PACKAGE TZEdit : public TEdit
{
private:
  TColor FBkColor;
  String FDataField;       //数据字段名
  int FDigLen;               //小数位长度
  TZCharType FCharType;
  TZCharCase FCharCase;
  String   FValidChar;
  String   FBrowseNo;      //浏览器名称
  String   FFormatStr;      //数据显示格式
  String   FDateFormat;     //日期格式

  String   FDefaultValue;

  TSpeedButton *FEditButton;
  TNotifyEvent FOnButtonClick;

  TStringList *FDataItem1;
  TStringList *FDataItem2;
  TStringList *FDataItem3;
  TStringList *FDataItem4;
  TStringList *FDataItem5;
  TStringList *FDataItem6;
  TStringList *FDataItem7;
  TZComboBoxItemIndex FKeyItem;
  TZComboBoxItemIndex FDispItem;
  int FItemIndex;
  bool FMultiDisplay;
  String FSplitSymbol;
  bool FMatch;
  TColor FBorderColor;
  TColor FFocusedColor;
  TColor FHoverColor;
  bool FIsFocused;
  bool FIsHovered;
  bool FEditFlat;
  bool FIsCurrency;
  String __fastcall GetItemData(int Index);
  void __fastcall SetItemData(int Index,String value);

  void __fastcall SetCharType(TZCharType AType);
  void __fastcall ClearCtrlBorder(TWinControl* WinControl, TColor color);
  void __fastcall DrarFlatEdit();

  void __fastcall SetButtonFlat(bool value);
  bool __fastcall GetButtonFlat();
  void __fastcall SetButtonVisible(bool value);
  bool __fastcall GetButtonVisible();
  void __fastcall SetButtonTransparent(bool value);
  bool __fastcall GetButtonTransparent();
  void __fastcall SetItemIndex(int value);
  bool __fastcall GetEnabled();
  void __fastcall SetEnabled(bool value);
  String __fastcall GetSdEditText();
  void __fastcall SetSdEditText(String value);
  void __fastcall SetBorderColor(TColor value);
  void __fastcall SetFocusedColor(TColor value);
  void __fastcall SetHoverColor(TColor value);
  void __fastcall SetEditFlat(bool value);
  void __fastcall SetCurrency(bool value);
  String __fastcall GetDefaultValue();
  void __fastcall SetDefaultValue(String value);
  String __fastcall GetDoublevalue(String ResoureStr);
protected:
  void __fastcall WMPaint(TWMPaint &Message);
  void __fastcall WMSize(TWMSize &Message);
  void __fastcall WMPaste(TMessage &Message);

  DYNAMIC void __fastcall DoExit(void);
  DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
  DYNAMIC void __fastcall KeyPress(Char &Key);
  DYNAMIC void __fastcall Change(void);
  virtual void __fastcall ButtonClick(TObject *Sender);

  void __fastcall SetDigLen(int Len);
  bool Valid(String Str);

  void __fastcall McLostFocus(TObject *Sender);
  void __fastcall MCDoubleClick(TObject *Sender);
  void __fastcall CMMouseEnter(TMessage &Message);
  void __fastcall CMMouseLeave(TMessage &Message);
	void __fastcall WMSetFocus(TWMSetFocus &Message);
	void __fastcall WMKillFocus(TWMSetFocus &Message);
	void __fastcall WMLButtonDown(TMessage &Message);

  virtual void LoadButtonBitmap(Graphics::TBitmap* ABitmap);
  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
	VCL_MESSAGE_HANDLER(WM_PASTE, TMessage, WMPaste);
    VCL_MESSAGE_HANDLER(CM_MOUSELEAVE,TMessage,CMMouseLeave);
    VCL_MESSAGE_HANDLER(CM_MOUSEENTER,TMessage,CMMouseEnter);
    VCL_MESSAGE_HANDLER(WM_SETFOCUS,TWMSetFocus,WMSetFocus);
    VCL_MESSAGE_HANDLER(WM_KILLFOCUS,TWMSetFocus,WMKillFocus);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN, TMessage,WMLButtonDown);
  END_MESSAGE_MAP(TEdit);
public:
  __fastcall TZEdit(TComponent* Owner);
  virtual __fastcall ~TZEdit();
  void __fastcall AddItems(String Item1,String Item2="",String Item3="",String Item4="",String Item5=""
      ,String Item6="",String Item7="");
  void __fastcall AssignItems(TStringList *Item1,TStringList *Item2=NULL,TStringList *Item3=NULL,TStringList *Item4=NULL
      ,TStringList *Item5=NULL,TStringList *Item6=NULL,TStringList *Item7=NULL);
  bool __fastcall LocateKey(String value);
  void __fastcall ClearAll();

  __property String ItemData[int i]={read=GetItemData,write=SetItemData};
  __property int ItemIndex={read=FItemIndex,write=SetItemIndex};
__published:
  __property String DataField={read=FDataField,write=FDataField};
  __property int DigLen={read=FDigLen,write=SetDigLen,default=0};
  __property String BrowseNo={read=FBrowseNo,write=FBrowseNo};
  __property TZCharType CharType={read=FCharType,write=SetCharType};
  __property String ValidChar = {read=FValidChar, write=FValidChar};
  __property String DateFormat={read=FDateFormat,write=FDateFormat};
  __property String FormatStr={read=FFormatStr,write=FFormatStr};
  __property String DefaultValue={read=GetDefaultValue,write=SetDefaultValue};

  __property TNotifyEvent OnButtonClick={read=FOnButtonClick,write=FOnButtonClick};
  __property bool ButtonVisible={read=GetButtonVisible,write=SetButtonVisible,default=false};
  __property bool ButtonFlat={read=GetButtonFlat,write=SetButtonFlat,default=true};
  __property bool ButtonTransparent={read=GetButtonTransparent,write=SetButtonTransparent,default=true};
  __property TZComboBoxItemIndex KeyItem={read=FKeyItem,write=FKeyItem,default=cbItem1};
  __property TZComboBoxItemIndex DispItem={read=FDispItem,write=FDispItem,default=cbItem2};
  __property TZCharCase CharCase={read=FCharCase,write=FCharCase};
  __property bool MultiDisplay={read=FMultiDisplay,write=FMultiDisplay,default=false};
  __property String SplitSymbol={read=FSplitSymbol,write=FSplitSymbol};
  __property bool Match={read=FMatch,write=FMatch,default=false};
  __property bool Enabled={read=GetEnabled,write=SetEnabled,default=true};
  __property String Text={read=GetSdEditText,write=SetSdEditText};
  __property TColor BorderColor={read=FBorderColor,write=SetBorderColor,default=crBorderColor};
  __property TColor FocusedColor={read=FFocusedColor,write=SetFocusedColor,default=clWhite};
  __property TColor HoverColor={read=FHoverColor,write=SetHoverColor,default=crFocusedColor};
  __property bool Flat={read=FEditFlat,write=SetEditFlat};
  __property bool IsCurrency={read=FIsCurrency,write=SetCurrency,default = false};
};
//---------------------------------------------------------------------------
#endif
