//---------------------------------------------------------------------------

#ifndef fpanelH
#define fpanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class PACKAGE TFloatPanel : public TCustomControl
{
private:
	TBorderWidth FBorderWidth;
	Classes::TNotifyEvent FOnResize;
	TAlignment FAlignment;
	void __fastcall SetAlignment(Classes::TAlignment Value);
	void __fastcall SetBorderWidth(TBorderWidth Value);
  void __fastcall ShadeLine(TRect Rect, TColor Color);

protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall AlignControls(Controls::TControl* AControl, TRect &Rect);
	virtual void __fastcall Paint(void);
	DYNAMIC void __fastcall Resize(void);

  void __fastcall WMWindowPosChanged(TWMWindowPosChanged &Message);

public:
  __fastcall TFloatPanel(TComponent* Owner);
  __fastcall virtual ~TFloatPanel(void){};
  
__published:
	__property TBorderWidth BorderWidth = {read=FBorderWidth, write=SetBorderWidth, default=8};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, default=2};
	__property Classes::TNotifyEvent OnResize = {read=FOnResize, write=FOnResize};
	__property Align ;
	__property Color ;
	__property DragCursor ;
	__property DragMode ;
	__property Enabled ;
	__property Caption ;
	__property Font ;
	__property ParentColor ;
	//__property ParentShowHint ;
	__property PopupMenu ;
	//__property ShowHint ;
	__property TabOrder ;
	__property TabStop ;
	__property Visible ;
	__property OnClick ;
	__property OnDblClick ;
	__property OnDragDrop ;
	__property OnDragOver ;
	__property OnEndDrag ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
	__property OnStartDrag ;

  BEGIN_MESSAGE_MAP
    //MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
    VCL_MESSAGE_HANDLER(WM_WINDOWPOSCHANGED, TWMWindowPosChanged, WMWindowPosChanged);
  END_MESSAGE_MAP(TCustomControl);
};
//---------------------------------------------------------------------------
#endif
 