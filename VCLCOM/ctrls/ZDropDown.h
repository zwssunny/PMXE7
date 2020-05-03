//---------------------------------------------------------------------------

#ifndef ZDropDownH
#define ZDropDownH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include "ZEdit.h"
//---------------------------------------------------------------------------
class PACKAGE TZDropDown;
typedef void __fastcall (__closure *TDropDownEvent)(TZDropDown*ADropDown, TForm*DropForm);
typedef void __fastcall (__closure *TDropDownLoadPicture)(TZDropDown*ADropDown, Graphics::TBitmap* ABitmap);
class PACKAGE TZDropDown : public TZEdit
{
private:
	  TDropDownEvent FOnDropDownInitData;
	  TDropDownEvent FOnDropDownDropDown;
      TDropDownLoadPicture FOnLoadPicture;
      TForm*         FDropForm;
      bool           FInitedData;
      void __fastcall DropDownOnButtonClick(System::TObject* Sender);
protected:
      void LoadButtonBitmap(Graphics::TBitmap*ABitmap);
public:
      __fastcall TZDropDown(TComponent* Owner);
	  __fastcall ~TZDropDown();
	  void InitData();
__published:
      __property TDropDownEvent OnInitData = {read=FOnDropDownInitData, write=FOnDropDownInitData};
      __property TDropDownEvent OnDropDown = {read=FOnDropDownDropDown, write=FOnDropDownDropDown};
      __property TDropDownLoadPicture OnLoadPicture = {read=FOnLoadPicture, write=FOnLoadPicture};
};
//---------------------------------------------------------------------------
#endif
