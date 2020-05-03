//---------------------------------------------------------------------------

#ifndef PrjGridH
#define PrjGridH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <ZGrids.hpp>
#include "ProjectStruct.h"
#include "ZChartDraw.h"
#include "Gantt.h"
using namespace ProjectStruct;
//---------------------------------------------------------------------------
class PACKAGE TPrjGrid;
class TPrjGridDataChangeLink;
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TExpandEvent)(TProject* AProject, TPrjObject* AObj, bool& CanExpand);
typedef void __fastcall (__closure *TEndDragTaskEvent)(TPrjObject* poFrom, TPrjObject* poTo,TPrjObject* poOldParent);
class PACKAGE TPrjGrid : public TBYCustomGrid
{
private:
	enum TMouseAct {maNone, maDragTask, maDragSelect};
	TProject*FProject;
	TGantt*  FGantt;
	TExpandEvent FOnExpand;
	TEndDragTaskEvent FOnEndDragTask;
	void __fastcall SetProject(TProject*AProject);
	TProject* __fastcall GetProject();
	void __fastcall SetGantt(TGantt*AGantt);
	void __fastcall SetShowCols(int Index, TTaskShowCol AShowCol);
	TTaskShowCol __fastcall GetShowCols(int Index);
	void InitCols();
	TPrjGridDataChangeLink* FChangeLink;
	void SetIndexColWidth();

	bool             FCanDragTask;
	Graphics::TColor FEvenGridColor;
	Graphics::TColor FOddGridColor;
	Graphics::TColor FSelectColor;
	void __fastcall SetCanDragTask(bool AValue);
	void __fastcall SetEvenGridColor(Graphics::TColor value);
	void __fastcall SetOddGridColor(Graphics::TColor value);
	void __fastcall SetSelectColor(Graphics::TColor value);
	void __fastcall GanttTopTaskChanged(TProject *AProject,
										TPrjObject *New, TPrjObject *Old);
protected:
	virtual TBYInplaceEdit* __fastcall CreateEditor(void);
	DYNAMIC String __fastcall GetEditText(int ACol, int ARow);
	virtual bool __fastcall CanEditShow(void);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const String Value);

	void __fastcall DrawCell(int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState);
	void __fastcall DrawACell(HDC dc, int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState, bool Print);
	bool CellIsSelected(int ACol, int ARow);
	void DrawName(HDC dc, const TRect &ARect, String&Name, int Layer, int ExpandType);//ExpandType 0:None 1:Expanded 2:Folded
	DYNAMIC void __fastcall TopLeftChanged(void);
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	DYNAMIC void __fastcall RowMoved(int FromIndex, int ToIndex);
	void __fastcall DrawGridLine(TRect &ARect, int);
	bool __fastcall SelectCell(int ACol, int ARow);

	virtual void __fastcall Paint(void);
	void __fastcall WMHScroll(TWMScroll &Msg);
	void __fastcall WMVScroll(TWMScroll &Msg);
	void __fastcall DrawOutGridCell(void);
private://drag task
	void __fastcall WMLButtonDown(TMessage &Msg);
	void __fastcall WMMouseMove(TMessage &Msg);
	void __fastcall WMLButtonUp(TMessage &Msg);
	void __fastcall WMLButtonDblClick(TMessage &Msg);
private:

	TMouseAct FMouseAct;
	int  FDragTaskOldY;
	int  FDragOldRow;
	bool StartDragTask(int X, int Y);
	void DragingTask(int X, int Y);
	void EndDragTask(int X, int Y);
	bool StartDragSelect(int X, int Y);
	void DragingSelect(int X, int Y, int ARow);
	void EndDragSelect(int X, int Y);
	void InvestDragY(int Y);
	int  FSelectCol;
	bool FReadSaveWidth;
	void CellMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg);
	void IndexMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg);
	void NameMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg);
	void OtherMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg);
	void SetSelectWithRow(int ARow);
	HFONT CreateFontByTFont(TFont* AFont,int iVitalLevel);
	String __fastcall GridSelfID();
public:
    __fastcall TPrjGrid(TComponent* Owner);
    __fastcall ~TPrjGrid();
    void Init();
    int PrintWidth();
    void __fastcall FindTaskByName(const String TaskName);///////////
    void __fastcall ExpandAllTask(bool bExpand);
	void __fastcall ExpandAllTask(bool bExpand,int iLevel);
	void __fastcall SaveProperty();
	void __fastcall ReadProperty();
	void __fastcall DeleteProperty();
    void Print(HDC dc, RECT PrintRect);
    TTaskShowCol FShowCols[30];
	__property TProject* Project = {read=GetProject, write=SetProject};
	__property TGantt*   Gantt = {read=FGantt, write=SetGantt};
	__property TTaskShowCol ShowCols[int Index] = {read=GetShowCols, write=SetShowCols};
    __property Selection;
    __property TopRow;
	__property Row;
    __property RowHeights ;
	__property FixedRows;
#pragma option -w-inl
  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_VSCROLL, TWMScroll, WMVScroll);
    VCL_MESSAGE_HANDLER(WM_HSCROLL, TWMScroll, WMHScroll);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN, TMessage, WMLButtonDown);
    VCL_MESSAGE_HANDLER(WM_MOUSEMOVE, TMessage, WMMouseMove);
    VCL_MESSAGE_HANDLER(WM_LBUTTONUP, TMessage, WMLButtonUp);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TMessage, WMLButtonDblClick);
  END_MESSAGE_MAP(TBYCustomGrid);
#pragma option -winl
__published:
    __property bool CanDragTask = {read=FCanDragTask, write=SetCanDragTask};
    __property Graphics::TColor EvenGridColor={read=FEvenGridColor,write=SetEvenGridColor,default=clWhite};
    __property Graphics::TColor OddGridColor={read=FOddGridColor,write=SetOddGridColor,default=0x00EEF0F9};
    __property Graphics::TColor SelectColor={read=FSelectColor,write=SetSelectColor,default=clBackground};
	__property TEndDragTaskEvent OnEndDragTask = {read=FOnEndDragTask, write=FOnEndDragTask};
	__property TExpandEvent OnExpand = {read=FOnExpand, write=FOnExpand};
	__property bool ReadSaveWidth  = { read=FReadSaveWidth, write=FReadSaveWidth,default=false };
	__property FixedColor;
	__property Align;
	__property BorderStyle;
	__property ColCount;
	__property Font;
	__property Options;
	__property RowCount;
	__property PopupMenu;
	__property VisibleRowCount;
	__property OnClick;
	__property OnDblClick;
	__property OnKeyDown;
};
//---------------------------------------------------------------------------
#endif
