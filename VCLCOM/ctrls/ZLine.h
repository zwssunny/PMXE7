//---------------------------------------------------------------------------

#ifndef ZLineH
#define ZLineH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
enum TDir{ldLeftToRight,ldRightToLeft};
class PACKAGE TLine : public TGraphicControl
{
private:
  int  FLineWidth;
  TColor FColor;
  bool ButtonIsDown;
  TDir FDirect;

protected:
  virtual void __fastcall WMPaint(TWMPaint &Message);
  virtual void __fastcall WMSize(TWMSize &Message);
  virtual void __fastcall SetLeft(int value);
  virtual int  __fastcall GetLeft();
  virtual void __fastcall SetHeight(int value);
  virtual int  __fastcall GetHeight();
  virtual void __fastcall SetTop(int value);
  virtual int  __fastcall GetTop();
  virtual void __fastcall SetWidth(int value);
  virtual int  __fastcall GetWidth();
  virtual void __fastcall SetLineWidth(int value);
  virtual void __fastcall SetColor(TColor value);
  virtual void __fastcall SetDirect(TDir value);

public:
  __fastcall TLine(TComponent* Owner);

__published:
  __property int LineWidth={read=FLineWidth,write=SetLineWidth,default=1};
  __property TColor Color={read=FColor,write=SetColor,default=clBlack};
  __property Visible;
  __property Name;
  __property int Left={read=GetLeft,write=SetLeft};
  __property int Height={read=GetHeight,write=SetHeight};
  __property int Width={read=GetWidth,write=SetWidth};
  __property int Top={read=GetTop,write=SetTop};
  __property TDir Direct={read=FDirect,write=SetDirect};
  __property Align;

  __property PopupMenu;
  __property OnClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
  END_MESSAGE_MAP(TGraphicControl);
};
//---------------------------------------------------------------------------
#endif
