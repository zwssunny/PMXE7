//---------------------------------------------------------------------------

#ifndef ZScaleH
#define ZScaleH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
enum TDirect{drTopToBottom,drBottomToTop,drLeftToRight,drRightToLeft};
enum TGraduate{gdMillimeter,gdCentimetre,gdInch};
class PACKAGE TZScale : public TGraphicControl
{
private:
  int FBeginValue;
  TDirect FDirect;
  TColor FBackColor;
  TColor FForeColor;
  TGraduate FGraduate;
  double __fastcall DataCarry(double data,int scale,int method);
  double __fastcall Mod(double x,double y);
protected:
  virtual void __fastcall WMPaint(TWMPaint &Message);
  virtual void __fastcall WMSize(TWMSize &Message);

  virtual void __fastcall SetBackColor(TColor value);
  virtual void __fastcall SetForeColor(TColor value);
  virtual void __fastcall SetDirect(TDirect value);
  virtual void __fastcall SetGraduate(TGraduate value);
  virtual void __fastcall DrawScale();
  virtual void __fastcall SetAlign(TAlign value);
  virtual TAlign __fastcall GetAlign();
  virtual void __fastcall SetBeginValue(int value);
public:
  __fastcall TZScale(TComponent* Owner);
__published:
  __property Align={read=GetAlign,write=SetAlign};
  __property TColor BackColor={read=FBackColor,write=SetBackColor};
  __property TColor ForeColor={read=FForeColor,write=SetForeColor};
  __property TDirect Direct={read=FDirect,write=SetDirect};
  __property TGraduate Graduate={read=FGraduate,write=SetGraduate};
  __property int BeginValue={read=FBeginValue,write=SetBeginValue};

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
    VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
  END_MESSAGE_MAP(TGraphicControl);
};
//---------------------------------------------------------------------------
#endif
 