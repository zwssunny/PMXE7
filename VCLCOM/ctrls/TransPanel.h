//---------------------------------------------------------------------------

#ifndef TransPanelH
#define TransPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TTransPanel : public TCustomPanel
{
private:
        bool FTransParent;
        void __fastcall SetTransParent(bool value);
protected:
        virtual void __fastcall Paint();
public:
        __fastcall TTransPanel(TComponent* Owner);
        __property DockManager;
__published:
        __property Align;
        __property Alignment;
        __property Anchors;
        __property AutoSize;
        __property BevelInner;
        __property BevelOuter;
        __property BevelWidth;
        __property BiDiMode;
        __property BorderWidth;
        __property BorderStyle;
        __property Caption;
        __property Color;
        __property Constraints;
        __property Ctl3D;
        __property UseDockManager;
        __property DockSite;
        __property DragCursor;
        __property DragKind;
        __property DragMode;
        __property Enabled;
        __property FullRepaint;
        __property Font;
        __property Locked;
        __property ParentBiDiMode;
        __property ParentColor;
        __property ParentCtl3D;
        __property ParentFont;
        __property ParentShowHint;
        __property PopupMenu;
        __property ShowHint;
        __property TabOrder;
        __property TabStop;
        __property Visible;
        __property OnCanResize;
        __property OnClick;
        __property OnConstrainedResize;
        __property OnContextPopup;
        __property OnDockDrop;
        __property OnDockOver;
        __property OnDblClick;
        __property OnDragDrop;
        __property OnDragOver;
        __property OnEndDock;
        __property OnEndDrag;
        __property OnEnter;
        __property OnExit;
        __property OnGetSiteInfo;
        __property OnMouseDown;
        __property OnMouseMove;
        __property OnMouseUp;
        __property OnResize;
        __property OnStartDock;
        __property OnStartDrag;
        __property OnUnDock;
        __property bool TransParent  = { read=FTransParent, write=SetTransParent };
};
//---------------------------------------------------------------------------
#endif
