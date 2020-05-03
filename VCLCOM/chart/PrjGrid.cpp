//---------------------------------------------------------------------------
//    File:               PrjGrid.h, PrjGrid.cpp
//    Function:           显示项目任务的列表
//    Author:             sunny
//    Last Modify:        2009-08-26
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrjGrid.h"
#include "MoveTaskDlg.h"
#include <Registry.hpp>
#pragma package(smart_init)
using namespace Zgrids;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TPrjGrid *)
{
   new TPrjGrid(NULL);
}
//---------------------------------------------------------------------------
namespace Prjgrid
{
  void __fastcall PACKAGE Register()
  {
     TComponentClass classes[1] = {__classid(TPrjGrid)};
	 RegisterComponents("ZChart", classes, 0);
  }
}
const int NameLayerInc = 20;
const int ExpandSize = 20;
//---------------------------------------------------------------------------
class TPrjGridDataChangeLink : public TPrjDataChangeLink
{
	int Updating;
public:
    TPrjGrid* FGrid;
    TPrjGridDataChangeLink(TPrjGrid*AGrid)
	   :TPrjDataChangeLink(AGrid->Project), Updating(0) { FGrid = AGrid; }

    virtual void AfterTaskDelete()
    {
       if(Updating <= 0 && FGrid->Visible)
	   {
           FGrid->Init();
       }
    }
	virtual void AfterTaskAdd(TPrjObject*ATask)
    {
	   if(Updating <= 0&&FGrid->Project->NeedEditStatus)
		   FGrid->Init();
	}
	virtual void BeginUpdate()
    {
       Updating++;
    }
    virtual void EndUpdate()
    {
       Updating--;
       if(Updating <= 0)
           FGrid->Init();
    }
    virtual void SetSelect(TPrjObject*ATask, TPrjObject*OldSelect)
    {
       if(FGrid->Gantt &&  FGrid->Gantt->TopTask)
           FGrid->TopRow = FGrid->Gantt->TopTask->EFExpandIndex+1;
       if(ATask && FGrid->RowCount > FGrid->VisibleRowCount)
       {
           if(ATask->EFExpandIndex < FGrid->TopRow-1 && ATask->EFExpandIndex > 0)
           {
               FGrid->TopRow = ATask->EFExpandIndex + 1;
           }else if(ATask->EFExpandIndex > FGrid->TopRow+FGrid->VisibleRowCount-2)
           {
               FGrid->TopRow = ATask->EFExpandIndex - FGrid->VisibleRowCount + 2;
           }
	   }
       FGrid->FixedRows = 1;
       if(Updating <= 0)
       {
           FGrid->Invalidate();
       }
    }
};
//---------------------------------------------------------------------------
__fastcall TPrjGrid::TPrjGrid(TComponent* Owner)
  : FMouseAct(maNone), TBYCustomGrid(Owner)
{
   InitCols();
   GridLineWidth = 1;
   ScrollBars =System::Uitypes::TScrollStyle::ssHorizontal;
   FEvenGridColor = clWhite;
   FOddGridColor = (TColor)0x00EFF1F1;
   FSelectColor = clBackground;
   FixedColor = clSkyBlue;
   Ctl3D = false;
   RowCount = 2;
   ColCount = 11;
   FixedCols = 1;
   FixedRows = 0;
   FGantt = NULL;
   DefaultDrawing = false;
   DoubleBuffered = true;
   FCanDragTask = true;
   Options>>Zgrids::goFixedVertLine>>Zgrids::goFixedHorzLine>>Zgrids::goVertLine>>Zgrids::goHorzLine;
   RowHeights[0]=32;
   ColWidths[0] = 80;
   ColWidths[1] = 150;
   FReadSaveWidth=false;
}
//---------------------------------------------------------------------------
__fastcall TPrjGrid::~TPrjGrid()
{
   if(FChangeLink)
      delete FChangeLink;
   try{//perhaps FGantt is Destroyed
       SaveProperty();
      if(FGantt)
      {
         FGantt->OnTopTaskChanged = NULL;
         FGantt->FBindGrid = NULL;
	  }
   }catch(...)
   {}
}
//---------------------------------------------------------------------------
void TPrjGrid::InitCols()
{
//初始化各列
   for(int i = 0; i < 30; i++)
      FShowCols[i].DataIndex = i;
   FShowCols[0].DataIndex = 31;//WBS
   FShowCols[2].DataIndex = 34;//
   FShowCols[4].DataIndex = 35;
   FShowCols[5].DataIndex = 4;
   FShowCols[6].DataIndex = 5;//
   FShowCols[7].DataIndex = 37;//TF
   FShowCols[8].DataIndex = 38;//FF
   FShowCols[9].DataIndex = 23;//TF
   FShowCols[10].DataIndex = 25;//FF
}
//---------------------------------------------------------------------------
void TPrjGrid::Init()
{
   if(!FGantt)
      return;
   if(DefaultRowHeight != FGantt->RowHeight)
      DefaultRowHeight = FGantt->RowHeight;
   if(FGantt)
      RowHeights[0] = FGantt->CalendarHeight;
   if(Project)
   {
      RowCount = Project->ExpandFoldTasks.Count() + 2;
   }else
   {
      RowCount = 2;
   }
   ColCount = 11;
   if(Project && Project->Selected)
   {
	  Zgrids::TGridRect gr;
      gr.Left = Col;
      gr.Top = Project->Selected->EFExpandIndex + 1;
      gr.Bottom = Project->Selected->EFExpandIndex + 1;
      gr.Right = Col;
      Selection = gr;
   }
   if(RowCount < 2)
      RowCount = 2;
   FixedRows = 1;
   FixedCols = 1;
   FixedColor = FGantt->CalendarBkColor;
   FGantt->OnTopTaskChanged = GanttTopTaskChanged;

   if(FSelectCol > 0 && FSelectCol < ColCount)
   {
       Col = FSelectCol;
   }else if(FSelectCol == 0)
   {
       Col = 1;
   }
   Invalidate();
   //FGantt->Invalidate();
   FGantt->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::SetProject(TProject*AProject)
{
   FProject = AProject;
   FMouseAct = maNone;
   if(FChangeLink)
      FChangeLink->SetProject(FProject);
   else
      FChangeLink = new TPrjGridDataChangeLink(this);
   Init();
}
//---------------------------------------------------------------------------
TProject* __fastcall TPrjGrid::GetProject()
{
   if(FGantt)
       return FGantt->Project;
   return FProject;
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::SetGantt(TGantt*AGantt)
{
   if(FGantt)
   {
       FGantt->OnTopTaskChanged = NULL;
       FGantt->FBindGrid = NULL;
   }
   FGantt = AGantt;
   if(FChangeLink)
       FChangeLink->SetProject(FGantt->Project);
   else
	   FChangeLink = new TPrjGridDataChangeLink(this);
   Init();
   if(FGantt)
   {
       FGantt->OnTopTaskChanged = GanttTopTaskChanged;
       FGantt->FBindGrid = this;
   }
      ReadProperty();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::ColumnMoved(int FromIndex, int ToIndex)
{
    TBYCustomGrid::ColumnMoved(FromIndex, ToIndex);
    TTaskShowCol t = FShowCols[FromIndex];
    FShowCols[FromIndex] = FShowCols[ToIndex];
    FShowCols[ToIndex] = t;
    Invalidate();
}
void __fastcall TPrjGrid::RowMoved(int FromIndex, int ToIndex)
{
}
bool __fastcall TPrjGrid::SelectCell(int ACol, int ARow)
{
   if(GetKeyState(VK_LCONTROL)&0xff00 || GetKeyState(VK_SHIFT)&0xff00)
   {
       return false;
   }else
   {
       if(!CellIsSelected(ACol, ARow))
       {
           if(FSelectCol != 0)
               FSelectCol = ACol;
           SetSelectWithRow(ARow);
       }
       return TBYCustomGrid::SelectCell(ACol, ARow);
   }
}
void __fastcall TPrjGrid::DrawCell(int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState)
{
   DrawACell(Canvas->Handle, ACol, ARow, ARect, AState, false);
}
HFONT TPrjGrid::CreateFontByTFont(TFont* AFont,int iVitalLevel)
{
  LOGFONT pFont;
  //createfont
  HFONT hFont;
  pFont.lfHeight = AFont->Height; //MulDiv (8, -GetDeviceCaps(dc,LOGPIXELSY), 72);
  pFont.lfWidth = 0;
  pFont.lfEscapement = 0;
  pFont.lfOrientation = 0;
  /*
  if(AFont->Style.Contains(fsBold))
     pFont.lfWeight = FW_BOLD;
  else
     pFont.lfWeight = FW_NORMAL;
  */
  pFont.lfItalic = AFont->Style.Contains(fsItalic);
  pFont.lfUnderline = false;
  pFont.lfWeight = FW_NORMAL;
  switch(iVitalLevel)
  {
    case 1 :
      pFont.lfUnderline = true;
      break;
    case 2 :
      pFont.lfWeight = FW_BOLD;
      break;
  }
  //pFont.lfUnderline = AFont->Style.Contains(fsUnderline);
  pFont.lfStrikeOut = AFont->Style.Contains(fsStrikeOut);
  pFont.lfCharSet = AFont->Charset;
  wcscpy(pFont.lfFaceName, AFont->Name.c_str());
  pFont.lfQuality = DEFAULT_QUALITY;
  pFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
  pFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  switch(AFont->Pitch)
  {
	 case TFontPitch::fpVariable:
        pFont.lfPitchAndFamily = VARIABLE_PITCH;
        break;
     case TFontPitch::fpFixed:
        pFont.lfPitchAndFamily = FIXED_PITCH;
        break;
     default:
        pFont.lfPitchAndFamily = DEFAULT_PITCH;
  }
  hFont = CreateFontIndirect(&pFont);
  return hFont;
}
void __fastcall TPrjGrid::DrawACell(HDC dc, int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState, bool Print)
{
   HFONT DrawFont = NULL;
   HGDIOBJ oldFont = NULL;
	   if(Print)
       {
		   HBRUSH brush = CreateSolidBrush(clWhite);
           HGDIOBJ oldbrush = SelectObject(dc, brush);
           if(ARow > 0)
           {
               Rectangle(dc, ARect.Left-1, ARect.Top-1, ARect.Right, ARect.Bottom);
           }else
           {
               Rectangle(dc, ARect.Left-1, ARect.Top, ARect.Right, ARect.Bottom);
           }
           SelectObject(dc, oldbrush);
           DeleteObject(brush);
       }else
       {
           TColor bkColor = ARow % 2 ? FEvenGridColor : FOddGridColor;
           if(CellIsSelected(ACol, ARow))
              bkColor = FSelectColor;
           if(ARow == 0)
              bkColor = FixedColor;
           HBRUSH brush = CreateSolidBrush(bkColor);
           HGDIOBJ oldbrush = SelectObject(dc, brush);
           FillRect(dc, &ARect, brush);
           SelectObject(dc, oldbrush);
           DeleteObject(brush);
       }
       SetBkMode(dc, TRANSPARENT);
       String draw_str;
	   unsigned Format = 0;

       RECT dr = ARect;
       dr.left = ARect.Left + 1;
       dr.right = ARect.Right - 1;
       if(ARow == 0)
       {
           //Font->Style = TFontStyles();
           //DrawFont = SDFunction::CreateFontByTFont(Font);
           DrawFont = CreateFontByTFont(Font,0);
           oldFont = SelectObject(dc, DrawFont);

		   draw_str = FShowCols[ACol].GetTitle();
          // if(FShowCols[ACol].DataIndex==1)
		  //   draw_str=FShowCols[2].GetTitle()+draw_str;  //在名称前面增加显示wbs
		   Format = FShowCols[ACol].GetTitleFormat();
			DrawText(dc, draw_str.c_str(), draw_str.Length(), &dr, Format);
		   SelectObject(dc, oldFont);
           DeleteObject(DrawFont);
       }else if(Project && ARow <= Project->ExpandFoldTasks.Count() && ARow >= 1)
       {
           TPrjObject* prjobject  = Project->ExpandFoldTasks[ARow-1];
		   DrawFont = CreateFontByTFont(Font,prjobject->VitalLevel);
           oldFont = SelectObject(dc, DrawFont);
           prjobject = NULL;

		   Format = FShowCols[ACol].GetDataFormat();
           draw_str = FShowCols[ACol].GetData(*(Project->ExpandFoldTasks[ARow-1]));
           if(FShowCols[ACol].DataIndex != 1)
		   {
			   DrawText(dc, draw_str.c_str(), draw_str.Length(), &dr, Format);
		   }else
           {
               TPrjObject *Obj = Project->ExpandFoldTasks[ARow-1];
               if(Obj)
               {
                    switch(Obj->GetType())
                    {
						 case ttAbstractTask:
                         case ttForeignProject:
                             DrawName(dc, dr, draw_str, Obj->Layer(), Obj->EFExpanded ? 2 : 1);
                             break;
                         case ttTask:
                             DrawName(dc, dr, draw_str, Obj->Layer(), 0);
                             break;
                         case ttProject:
                         default:
                             throw Exception("TPrjGrid::DrawName不支持此类型");
                    }
               }
           }
           SelectObject(dc, oldFont);
           DeleteObject(DrawFont);
       }
}
bool TPrjGrid::CellIsSelected(int ACol, int ARow)
{
   if(!Project || !(Project->Selected))
       return false;
   if(ARow == Project->Selected->EFExpandIndex+1)
   {
       if(FSelectCol == 0)
       {
           return true;
       }else
       {
           if(ACol == FSelectCol)
              return true;
           else
              return false;
       }
   }else
   {
       for(int i = 0; i < Project->Selections.Count(); i++)
       {
           if(Project->Selected != &(Project->Selections[i]) && ARow == Project->Selections[i].EFExpandIndex+1)
           {
                return true;
           }
       }
   }
   return false;
}
void TPrjGrid::DrawName(HDC dc, const TRect &ARect, String&AName, int Layer, int ExpandType)
{//ExpandType 0:None 1:Expanded 2:Folded
   TRect dr = ARect;
   switch(ExpandType)
   {
       case 1:
           DrawExpandFold(dc, ARect.Left + (Layer-1) * NameLayerInc + ExpandSize / 2,
                          (ARect.Top + ARect.Bottom) / 2, true);
           dr.Left = dr.Left + (Layer-1) * NameLayerInc + ExpandSize;
           break;
       case 2:
           DrawExpandFold(dc, ARect.Left + (Layer-1) * NameLayerInc + ExpandSize / 2,
                          (ARect.Top + ARect.Bottom) / 2, false);
           dr.Left = dr.Left + (Layer-1) * NameLayerInc + ExpandSize;
           break;
       case 0:
           dr.Left = dr.Left + (Layer-1) * NameLayerInc + ExpandSize;
           break;
       default:
           throw Exception("TPrjGrid::DrawName逻辑错误");
   }
   DrawText(dc, AName.c_str(), AName.Length(), &dr, DT_VCENTER | DT_LEFT | DT_SINGLELINE);
}
void __fastcall TPrjGrid::TopLeftChanged(void)
{
   TBYCustomGrid::TopLeftChanged();
   if(TopRow-1 >= 0 && TopRow-1 < Project->ExpandFoldTasks.Count())
   {
       if((TopRow != 1) ||
          Project->ExpandFoldTasks.Count() > 0)
       {
           FGantt->TopTask = Project->ExpandFoldTasks[TopRow-1];
       }
   }
}
void __fastcall TPrjGrid::GanttTopTaskChanged(TProject *AProject,
                                        TPrjObject *New, TPrjObject *Old)
{
   if(New)
      TopRow = New->EFExpandIndex+1;
}
void TPrjGrid::CellMouseDown(int ACol, int ARow, int MouseX, int MouseY,
                             bool Control, bool Shift, TMessage& AMsg)
{
   if(ACol == 0)
   {
        IndexMouseDown(ACol, ARow, MouseX, MouseY, Control, Shift, AMsg);
   }else if(ARow >= 1 && ARow <= Project->ExpandFoldTasks.Count()+1 &&
			FShowCols[ACol].DataIndex == 1)
   {
        NameMouseDown(ACol, ARow, MouseX, MouseY, Control, Shift, AMsg);
   }else
   {
        OtherMouseDown(ACol, ARow, MouseX, MouseY, Control, Shift, AMsg);
   }
   if(!Shift && !Control)
   {
        if(ACol >= FixedCols && ACol < ColCount && ARow >= FixedRows && ARow < RowCount)
        {
            Col = ACol;
            Row = ARow;
        }else if(FSelectCol == 0 && ARow >= FixedRows && ARow < RowCount)
        {
            Row = ARow;
        }
   }
}
void TPrjGrid::IndexMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg)
{
    int CurrSelectIndex = ARow - 1;
    if(FSelectCol == 0 && Control && Project->Selected)
    {
         if(CurrSelectIndex == Project->Selected->EFExpandIndex)
              return;
         if(CurrSelectIndex < Project->ExpandFoldTasks.Count() && CurrSelectIndex >= 0)
         {
              if(Project->Selections.IndexOf(*(Project->ExpandFoldTasks[CurrSelectIndex])) < 0)
              {
                   Project->Selections.Add(Project->ExpandFoldTasks[CurrSelectIndex]);
              }else
              {
                   Project->Selections.Delete(*(Project->ExpandFoldTasks[CurrSelectIndex]));
              }
         }
         Invalidate();
    }else if(FSelectCol == 0 && Shift && Project->Selected)
    {
         Project->Selections.Clear();
         if(CurrSelectIndex == Project->Selected->EFExpandIndex)
         {
              Project->Selections.Add(Project->Selected);
              return;
         }
         if(CurrSelectIndex < Project->ExpandFoldTasks.Count() && CurrSelectIndex >= 0)
         {
              int Start = CurrSelectIndex < Project->Selected->EFExpandIndex ? CurrSelectIndex : Project->Selected->EFExpandIndex;
              int End = CurrSelectIndex > Project->Selected->EFExpandIndex ? CurrSelectIndex : Project->Selected->EFExpandIndex;
              for(int i = Start; i <= End; i++)
              {
                   Project->Selections.Add(Project->ExpandFoldTasks[i]);
              }
         }
         Invalidate();
    }else
    {
        FSelectCol = ACol;
        SetSelectWithRow(ARow);
        StartDragSelect(MouseX, MouseY);
    }
}
void TPrjGrid::NameMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg)
{
    FSelectCol = ACol;
    SetSelectWithRow(ARow);
    if(Project->ExpandFoldTasks.CanExpandFold(ARow-1))//是名称
    {
         TRect r = CellRect(ACol, ARow);
         int MidX = r.Left + (Project->ExpandFoldTasks[ARow-1]->Layer()-1) *
                                 NameLayerInc + ExpandSize / 2;
         if(MouseX > MidX - ExpandSize/2 && MouseX < MidX + ExpandSize/2)
         {
              if(Project->ExpandFoldTasks[ARow-1]->EFExpanded)
              {
                   Project->ExpandFoldTasks.Fold(ARow-1);
                   Init();
              }else
              {
                   bool CanExpand(true);
                   if(FOnExpand)
                       FOnExpand(Project, Project->ExpandFoldTasks[ARow-1], CanExpand);
                   if(CanExpand)
                   {
                       TMessage Msg = AMsg;
                       Msg.Msg = WM_LBUTTONUP;
                       TBYCustomGrid::Dispatch(&Msg);
                       Project->ExpandFoldTasks.Expand(ARow-1);
                       Init();
                   }
              }
              if(FGantt && FGantt->GetTopTask())
                  TopRow = FGantt->GetTopTask()->EFExpandIndex+1;
         }
    }
}
void TPrjGrid::OtherMouseDown(int ACol, int ARow, int MouseX, int MouseY, bool Control, bool Shift, TMessage& AMsg)
{
    FSelectCol = ACol;
    SetSelectWithRow(ARow);
}
void TPrjGrid::SetSelectWithRow(int ARow)
{
   if(!Project)
      return;
   if(ARow <= Project->ExpandFoldTasks.Count() && ARow > 0)
   {
       if(Project->Selected != Project->ExpandFoldTasks[ARow-1])
       {
           Project->Selected = Project->ExpandFoldTasks[ARow-1];
           switch(FGantt->Calendar->Type)
           {
               case TCalendarDraw::gct2Hour://二小时
               case TCalendarDraw::gct6Hour://六小时
                    FGantt->LeftDay = Project->Selected->StartDate - 1;
                    break;
               case TCalendarDraw::gctDay: //日
               case TCalendarDraw::gct3Day: //三日
               case TCalendarDraw::gctWeek: //周
               case TCalendarDraw::gctMonth1: //月
               case TCalendarDraw::gctMonth2: //月
               case TCalendarDraw::gctQuarter: //季度
               case TCalendarDraw::gctHalfYear: //半年
                    FGantt->LeftDay = Project->Selected->StartDate - 3;
                    break;
           }
       }else
       {
           Project->Selections.Clear();
           Project->Selections.Add(Project->Selected);
       }
   }else
   {
       Project->Selected = NULL;
   }
   Invalidate();
}
TBYInplaceEdit* __fastcall TPrjGrid::CreateEditor(void)
{
   return new TBYInplaceEdit(this);
}
String __fastcall TPrjGrid::GetEditText(int ACol, int ARow)
{
   return "";
}
void __fastcall TPrjGrid::SetEditText(int ACol, int ARow, const String Value)
{
}
bool __fastcall TPrjGrid::CanEditShow(void)
{
   return false;
}
void __fastcall TPrjGrid::SetCanDragTask(bool AValue)
{
   FCanDragTask = AValue;
}
void __fastcall TPrjGrid::SetEvenGridColor(Graphics::TColor value)
{
   FEvenGridColor=value;
   Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::SetOddGridColor(Graphics::TColor value)
{
   FOddGridColor=value;
   Invalidate();
}
void __fastcall TPrjGrid::SetSelectColor(Graphics::TColor value)
{
  FSelectColor=value;
  Invalidate();
}
void __fastcall TPrjGrid::WMHScroll(TWMScroll &Msg)
{
  TBYCustomGrid::Dispatch(&Msg);
  DrawOutGridCell();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::WMVScroll(TWMScroll &Msg)
{
   TBYCustomGrid::Dispatch(&Msg);
   DrawOutGridCell();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::WMLButtonDown(TMessage &Msg)
{
   TBYCustomGrid::Dispatch(&Msg); 

   int MX, MY;
   MX = Msg.LParamLo;
   MY = Msg.LParamHi;
   bool ControlDown = (Msg.WParam & MK_CONTROL) != 0;
   bool ShiftDown = (Msg.WParam & MK_SHIFT) != 0;
   if(StartDragTask(MX, MY))
   {
       return;
   }else
   {//格的选中
                if(!Project)
                {
                    return;
                }

                int mCol = -1;
                int tempx = 0;
                for(int i = 0; i < FixedCols; i++)
                {
                    int ColWidth = ColWidths[i];
                    if(tempx <= MX && tempx + ColWidth >= MX)
                    {
                        mCol = i;
                        goto labelGetmRow;
                    }
                    tempx += ColWidth;
                }
                for(int i = LeftCol; i < LeftCol + VisibleColCount; i++)
                {
                    int ColWidth = ColWidths[i];
                    if(tempx <= MX && tempx + ColWidth >= MX)
                    {
                        mCol = i;
                        goto labelGetmRow;
                    }
                    tempx += ColWidth;
                }

             labelGetmRow:
                int mRow = -1;
                int tempy = 0;
                for(int i = 0; i < FixedRows; i++)
                {
                    int RowHeight = RowHeights[i];
                    if(tempy <= MY && tempy + RowHeight >= MY)
                    {
                        mRow = i;
                        goto labelGetmRowOver;
                    }
                    tempy += RowHeight;
                }
                for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
                {
                    int RowHeight = RowHeights[i];
                    if(tempy <= MY && tempy + RowHeight > MY)
                    {
                        mRow = i;
                        goto labelGetmRowOver;
                    }
                    tempy += RowHeight;
                }
             labelGetmRowOver:
                if(mCol != -1 && mRow > 0)
                {
                    CellMouseDown(mCol, mRow, MX, MY, ControlDown, ShiftDown, Msg);
                }
   }
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::WMMouseMove(TMessage &Msg)
{
   TBYCustomGrid::Dispatch(&Msg);
   int MX, MY;
   MX = Msg.LParamLo;
   MY = Msg.LParamHi;
   //get current row
                 int mRow = -1;
                 int tempy = 0;
                 for(int i = 0; i < FixedRows; i++)
                 {
                     int RowHeight = RowHeights[i];
                     if(tempy <= MY && tempy + RowHeight >= MY)
                     {
                         mRow = i;
                         goto labelGetmRowOver;
                     }
                     tempy += RowHeight;
                 }
                 for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
                 {
                     int RowHeight = RowHeights[i];
                     if(tempy <= MY && tempy + RowHeight >= MY)
                     {
                         mRow = i;
                         goto labelGetmRowOver;
                     }
                     tempy += RowHeight;
                 }
labelGetmRowOver:
   switch(FMouseAct)
   {
       case maDragTask:
            DragingTask(MX, MY);
            Msg.Result = 0;
            break;
       case maDragSelect:
            DragingSelect(MX, MY, mRow);
            Msg.Result = 0;
            break;
       case maNone:
            break;
       default:
            throw Exception("未处理此操作");
   }
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::WMLButtonUp(TMessage &Msg)
{
    TBYCustomGrid::Dispatch(&Msg);
    int MX, MY;
    MX = Msg.LParamLo;
    MY = Msg.LParamHi;
    switch(FMouseAct)
    {
        case maDragTask:
             EndDragTask(MX, MY);
             Msg.Result = 0;
             break;
        case maDragSelect:
             EndDragSelect(MX, MY);
             Msg.Result = 0;
             break;
        case maNone:
             break;
        default:
             throw Exception("未处理此操作");
    }
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::WMLButtonDblClick(TMessage &Msg)
{
   if(!Project)
   {
       TBYCustomGrid::Dispatch(&Msg);
       return;
   }
   int MX, MY;
   MX = Msg.LParamLo;
   MY = Msg.LParamHi;
   //get current row
                int mCol = -1;
                int tempx = 0;
                for(int i = 0; i < FixedCols; i++)
                {
                    int ColWidth = ColWidths[i];
                    if(tempx <= MX && tempx + ColWidth >= MX)
                    {
                        mCol = i;
                        goto labelGetmRow;
                    }
                    tempx += ColWidth;
                }
                for(int i = LeftCol; i < LeftCol + VisibleColCount; i++)
                {
                    int ColWidth = ColWidths[i];
                    if(tempx <= MX && tempx + ColWidth >= MX)
                    {
                        mCol = i;
                        goto labelGetmRow;
                    }
                    tempx += ColWidth;
                }

             labelGetmRow:
                int mRow = -1;
                int tempy = 0;
                for(int i = 0; i < FixedRows; i++)
                {
                    int RowHeight = RowHeights[i];
                    if(tempy <= MY && tempy + RowHeight >= MY)
                    {
                        mRow = i;
                        goto labelGetmRowOver;
                    }
                    tempy += RowHeight;
                }
                for(int i = TopRow; i < TopRow + VisibleRowCount; i++)
                {
                    int RowHeight = RowHeights[i];
                    if(tempy <= MY && tempy + RowHeight > MY)
                    {
                        mRow = i;
                        goto labelGetmRowOver;
                    }
                    tempy += RowHeight;
                }
 labelGetmRowOver:
    if(mCol != 1 || mRow == -1)
    {
        TBYCustomGrid::Dispatch(&Msg);
        return;
    }
    if(Project->ExpandFoldTasks.CanExpandFold(mRow-1))//是名称
    {
         TRect r = CellRect(mCol, mRow);
         int MidX = r.Left + (Project->ExpandFoldTasks[mRow-1]->Layer()-1) *
                                 NameLayerInc + ExpandSize / 2;
         if(MX > MidX - ExpandSize/2 && MX < MidX + ExpandSize/2)
         {
              FSelectCol = mCol;
              SetSelectWithRow(mRow);
              if(Project->ExpandFoldTasks[mRow-1]->EFExpanded)
              {
                   Project->ExpandFoldTasks.Fold(mRow-1);
                   Init();
                   return;
              }else
              {
                   bool CanExpand(true);
                   if(FOnExpand)
                       FOnExpand(Project, Project->ExpandFoldTasks[mRow-1], CanExpand);
                   if(CanExpand)
                   {
                       Project->ExpandFoldTasks.Expand(mRow-1);
                       Init();
                   }
                   return;
              }
         }
    }
    TBYCustomGrid::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::Paint(void)
{
  TBYCustomGrid::Paint();
  DrawOutGridCell();
}
//---------------------------------------------------------------------------
double __fastcall Mod(double x,double y)
{
  while(x>=y)
      x-=y;
  return x;
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::DrawOutGridCell(void)
{
  //Draw outof grid height
  if(TopRow + VisibleRowCount < RowCount)
  {
  }else
  {
       int LastRow = TopRow + VisibleRowCount;
       TRect LastRowRect = CellRect(0, LastRow);
       int DrawRow = LastRow;
       int DrawY = LastRowRect.Bottom + 1;

       HBRUSH evenbrush = CreateSolidBrush(FEvenGridColor);
       HBRUSH oddbrush = CreateSolidBrush(FOddGridColor);
       HGDIOBJ oldbrush = SelectObject(Canvas->Handle, evenbrush);
       TRect dr;
       dr.Left = 0;
       dr.Right = GridWidth;
       while(DrawY < ClientHeight)
       {
           HBRUSH brush = DrawRow % 2 ? evenbrush : oddbrush;
           SelectObject(Canvas->Handle, brush);
           dr.Top = DrawY;
           dr.Bottom = dr.Top + DefaultRowHeight;
           FillRect(Canvas->Handle, &dr, brush);
           DrawY += DefaultRowHeight;
           DrawRow++;
       }
       SelectObject(Canvas->Handle, oldbrush);
       DeleteObject(evenbrush);
       DeleteObject(oddbrush);
  }
  //画不固定格的竖线
  {
       const TColor LineColor = RGB(212, 208, 200);
       HPEN pen = CreatePen(PS_SOLID, 1, LineColor);
       HGDIOBJ oldpen = SelectObject(Canvas->Handle, pen);

       int TopY = RowHeights[0];
       int BottomY = ClientHeight;
       int X = ColWidths[0];
       MoveToEx(Canvas->Handle, X, TopY, NULL);
       LineTo(Canvas->Handle, X, BottomY);
       for(int i = LeftCol; i < LeftCol + VisibleColCount; i++)
       {
           X += ColWidths[i];
           MoveToEx(Canvas->Handle, X, TopY, NULL);
           LineTo(Canvas->Handle, X, BottomY);
       }
       SelectObject(Canvas->Handle, oldpen);
       DeleteObject(pen);
  }
  //画固定格的竖线
  {
       const TColor LineColor1 = RGB(192, 192, 192);
       const TColor LineColor2 = RGB(255, 255, 255);
       HPEN pen1 = CreatePen(PS_SOLID, 1, LineColor1);
       HPEN pen2 = CreatePen(PS_SOLID, 1, LineColor2);
       HGDIOBJ oldpen = SelectObject(Canvas->Handle, pen1);

       int TopY = 0;
       int BottomY = RowHeights[0];
       int X = ColWidths[0];
       SelectObject(Canvas->Handle, pen1);
       MoveToEx(Canvas->Handle, X, TopY, NULL);
       LineTo(Canvas->Handle, X, BottomY);
       SelectObject(Canvas->Handle, pen2);
       MoveToEx(Canvas->Handle, X+1, TopY, NULL);
       LineTo(Canvas->Handle, X+1, BottomY);
       for(int i = LeftCol; i < LeftCol + VisibleColCount; i++)
       {
           X += ColWidths[i];
           SelectObject(Canvas->Handle, pen1);
           MoveToEx(Canvas->Handle, X, TopY, NULL);
           LineTo(Canvas->Handle, X, BottomY);
           SelectObject(Canvas->Handle, pen2);
           MoveToEx(Canvas->Handle, X+1, TopY, NULL);
           LineTo(Canvas->Handle, X+1, BottomY);
       }
       SelectObject(Canvas->Handle, oldpen);
       DeleteObject(pen1);
       DeleteObject(pen2);
  }
}
//---------------------------------------------------------------------------
bool TPrjGrid::StartDragTask(int X, int Y)
{
    if(!FCanDragTask)
       return false;
    if(!Project || !(Project->Selected))
       return false;
    if(FSelectCol == 0 && X < ColWidths[0])
    {
        int YAtRow = (Y - RowHeights[0]) / DefaultRowHeight + TopRow;
        if(YAtRow == Project->Selected->EFExpandIndex + 1)
        {
            SetCapture(Handle);
            FMouseAct = maDragTask;
            FDragTaskOldY = 0;
            FDragOldRow = YAtRow;
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void TPrjGrid::DragingTask(int X, int Y)
{
    if(!CanDragTask||Project->Selected==NULL)
        return;
    //擦旧的
    if(FDragTaskOldY > 0)
    {
        InvestDragY(FDragTaskOldY);
    }

     //画新的
    InvestDragY(Y);
    FDragTaskOldY = Y;
}
//---------------------------------------------------------------------------
void TPrjGrid::EndDragTask(int X, int Y)
{
    ReleaseCapture();
    FMouseAct = maNone;
    if(!CanDragTask)
        return;
    //擦旧的
    if(FDragTaskOldY > 0)
    {
        InvestDragY(FDragTaskOldY);
    }

    //大于等于零，在下面，小于零，在上面
    int Direction = (Y - RowHeights[0]) % DefaultRowHeight - DefaultRowHeight / 2;
    int MoveTo;
    if(Direction >= 0)
    {
        MoveTo = (Y - RowHeights[0]) / DefaultRowHeight + TopRow;
    }else if((Y - RowHeights[0]) / DefaultRowHeight + TopRow == FDragOldRow)
    {
        return;
    }else
    {
        MoveTo = (Y - RowHeights[0]) / DefaultRowHeight + TopRow - 1;
    }
    if(FDragOldRow != MoveTo)
    {
        TPrjObject* poFrom; TPrjObject* poTo;TPrjObject* poOldParent;
        if(Project->ExpandFoldTasks[FDragOldRow-1]->IsForeign())
        {
			 MessageBox(Handle, L"外部工程的子任务不支持此操作！", L"信息", MB_OK	| MB_ICONINFORMATION);
             return;
        }
        if(MoveTo == TopRow - 1)
        {
            if(Project->ExpandFoldTasks[MoveTo]->IsForeign())
            {
				 MessageBox(Handle, L"外部工程的子任务不支持此操作！", L"信息", MB_OK	| MB_ICONINFORMATION);
                 return;
            }
            if(Project->ExpandFoldTasks[MoveTo]->GetType() == ttAbstractTask)
            {
              if(Project->UsePCWBS)
              {
                if(Project->ExpandFoldTasks[MoveTo]->Parent()!=Project->ExpandFoldTasks[FDragOldRow-1]->Parent())
                  throw Exception("只能在同一PCWBS内拖动");
                poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                poOldParent = poFrom->Parent();
                poTo = Project->ExpandFoldTasks[MoveTo];
                Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                     Project->ExpandFoldTasks[MoveTo]->Index);
                if(FOnEndDragTask)
                  FOnEndDragTask(poFrom,poTo,poOldParent);
              }
              else
              {
              //if(Project->UsePCWBS) return;
//                 switch(MessageBox(Handle, "\n您将此任务移到了任务分组上，您可以：\n\n"
//                                    "      1.选择\"是\"将任务插入分组任务所在的位置；\n"
//                                    "      2.选择\"否\"将任务加为分组任务的子任务；\n"
//                                    "      3.选择\"取消\"取消操作；\n\n"
//                                    "您要将任务插入分组任务所在的位置吗？\n"   , "信息", MB_YESNOCANCEL | MB_ICONINFORMATION))
                TfrmMoveTaskDlg *MTDlg=new TfrmMoveTaskDlg(Application);
                   switch(MTDlg->ShowModal())
                 {
                     case mrOk:
                         poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                         poOldParent = poFrom->Parent();
                         poTo = Project->ExpandFoldTasks[MoveTo];
                         Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);

                         if(FOnEndDragTask)
                           FOnEndDragTask(poFrom,poTo,poOldParent);
                         break;
                     case mrAll:
                         Project->Moving=true;
                         poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                         poOldParent = poFrom->Parent();
                         poTo = Project->ExpandFoldTasks[MoveTo];
                         Project->AddChildTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);
                         Project->Moving=false;

                         if(FOnEndDragTask)
                           FOnEndDragTask(poFrom,poTo,poOldParent);
                         break;
                     default:
                         delete MTDlg;
                         return;
                 }
                         delete MTDlg;
              }
            }else
            {
                 poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                 poOldParent = poFrom->Parent();
                 poTo = Project->ExpandFoldTasks[MoveTo];
                 if(Project->UsePCWBS)
                 {
                   if(poOldParent!=poTo->Parent())
                     throw Exception("只能在同一WBS内拖动");
                 }
                 Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);

                 if(FOnEndDragTask)
                           FOnEndDragTask(poFrom,poTo,poOldParent);
            }
        }else if(MoveTo >= TopRow &&
                 MoveTo < (TopRow + VisibleRowCount) &&
                 MoveTo < Project->ExpandFoldTasks.Count())
        {
            if(Project->ExpandFoldTasks[MoveTo]->IsForeign())
            {
				 MessageBox(Handle, L"外部工程的子任务不支持此操作！", L"信息", MB_OK	| MB_ICONINFORMATION);
                 return;
            }
            if(Project->ExpandFoldTasks[MoveTo]->GetType() == ttAbstractTask)
            {
              if(Project->UsePCWBS)
              {
                if(Project->ExpandFoldTasks[MoveTo]->Parent()!=Project->ExpandFoldTasks[FDragOldRow-1]->Parent())
                  throw Exception("只能在同一WBS内拖动");
                poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                poTo = Project->ExpandFoldTasks[MoveTo];
                poOldParent = poFrom->Parent();
                Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                     Project->ExpandFoldTasks[MoveTo]->Index);
                if(FOnEndDragTask)
                  FOnEndDragTask(poFrom,poTo,poOldParent);
              }
              else
              {
               //if(Project->UsePCWBS) return;
//                 switch(MessageBox(Handle, "\n您将此任务移到了任务分组上，您可以：\n\n"
//                                    "      1.选择\"是\"将任务插入分组任务所在的位置；\n"
//                                    "      2.选择\"否\"将任务加为分组任务的子任务；\n"
//                                    "      3.选择\"取消\"取消操作；\n\n"
//                                    "您要将任务插入分组任务所在的位置吗？\n"   , "信息", MB_YESNOCANCEL | MB_ICONINFORMATION))
                TfrmMoveTaskDlg *MTDlg=new TfrmMoveTaskDlg(Application);
                   switch(MTDlg->ShowModal())
                 {
                     case mrOk:
                          poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                          poOldParent = poFrom->Parent();
                          poTo = Project->ExpandFoldTasks[MoveTo];
                          Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);

                          if(FOnEndDragTask)
                           FOnEndDragTask(poFrom,poTo,poOldParent);
                         break;
                     case mrAll:
                         Project->Moving=true;
                         poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                         poTo = Project->ExpandFoldTasks[MoveTo];
                         poOldParent = poFrom->Parent();
                         Project->AddChildTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);
                         Project->Moving=false;

                         if(FOnEndDragTask)
                           FOnEndDragTask(poFrom,poTo,poOldParent);
                         break;
                     default:
                         delete MTDlg;
                         return;
                 }
                         delete MTDlg;
              }
            }else
            {
                 poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
                 poOldParent = poFrom->Parent();
                 poTo = Project->ExpandFoldTasks[MoveTo];
                 if(Project->UsePCWBS)
                 {
                   if(poOldParent!=poTo->Parent())
                     throw Exception("只能在同一WBS内拖动");
                 }
                 Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index,
                              Project->ExpandFoldTasks[MoveTo]->Index);
				 if(FOnEndDragTask)
                  FOnEndDragTask(poFrom,poTo,poOldParent);

            }
        }else if(MoveTo >= Project->ExpandFoldTasks.Count())
        {
             return;
             poFrom = Project->ExpandFoldTasks[FDragOldRow-1];
             poOldParent = poFrom->Parent();
             poTo = NULL;
             Project->MoveTask(Project->ExpandFoldTasks[FDragOldRow-1]->Index, -1);
			 if(FOnEndDragTask)
               FOnEndDragTask(poFrom,poTo,poOldParent);
        }
		Project->RequestUpdate();
        Paint();
    }
}
bool TPrjGrid::StartDragSelect(int X, int Y)
{
    if(Project->Selected)
    {
        FMouseAct = maDragSelect;
        return true;
    }else
    {
        return false;
    }
}
void TPrjGrid::DragingSelect(int X, int Y, int ARow)
{
    if(!CanDragTask||Project->Selected==NULL)
        return;
    Project->Selections.Clear();
    if(ARow-1 <= Project->ExpandFoldTasks.Count() && ARow-1 >= 0)
    {
         int Start = ARow-1 < Project->Selected->EFExpandIndex ? ARow-1 : Project->Selected->EFExpandIndex;
         int End = ARow-1 > Project->Selected->EFExpandIndex ? ARow-1 : Project->Selected->EFExpandIndex;
         for(int i = Start; i <= End && i < Project->ExpandFoldTasks.Count(); i++)
         {
              Project->Selections.Add(Project->ExpandFoldTasks[i]);
         }
    }
    Invalidate();
}
void TPrjGrid::EndDragSelect(int X, int Y)
{
    FMouseAct = maNone;
}
//---------------------------------------------------------------------------
void TPrjGrid::InvestDragY(int Y)
{
   int Row = (Y - RowHeights[0]) / DefaultRowHeight + 1;
   if(Row < 1 || Row == (FDragOldRow - TopRow + 1))
       return;
   //大于等于零，在下面，小于零，在上面
   int Direction = (Y - RowHeights[0]) % DefaultRowHeight
                           - DefaultRowHeight / 2;
   if(Direction >= 0)
   {
       if(Row == (FDragOldRow - TopRow))
           return;
   }else
   {
       if(Row == (FDragOldRow - TopRow + 2))
           return;
   }
   int DrawY;
   RECT InvertRect;
   InvertRect.left = 0;
   InvertRect.right = ClientWidth;
   if(Direction >= 0)
   {
       InvertRect.top = Row * DefaultRowHeight + RowHeights[0] - 1;
       InvertRect.bottom = InvertRect.top + 4;
   }else
   {
       InvertRect.top = (Row - 1) * DefaultRowHeight + RowHeights[0] - 1;
       InvertRect.bottom = InvertRect.top + 4;
   }

   HDC dc = GetDC(Handle);
   HRGN rgn = CreateRectRgn(InvertRect.left,
                            InvertRect.top,
                            InvertRect.right,
                            InvertRect.bottom);
   InvertRgn(dc, rgn);
   DeleteObject(rgn);
   ReleaseDC(Handle, dc);
}
//---------------------------------------------------------------------------
int TPrjGrid::PrintWidth()
{
   return ColWidths[0] + ColWidths[1];
}
//---------------------------------------------------------------------------
void TPrjGrid::Print(HDC dc, RECT PrintRect)
{
   if(PrintRect.right > PrintWidth())
   {
      int DrawTop(0);
      TRect dr0, dr1;
      dr0.Left = 0;
      dr0.Right = ColWidths[0];
      dr1.Left = ColWidths[0];
      dr1.Right = dr1.Left + ColWidths[1];
      dr0.Top = DrawTop;
      dr0.Bottom = RowHeights[0];
      DrawACell(dc, 0, 0, dr0, TBYGridDrawState(), true);
      dr1.Top = DrawTop;
      dr1.Bottom = RowHeights[0];
      DrawACell(dc, 1, 0, dr1, TBYGridDrawState(), true);
      DrawTop += RowHeights[0];
      for(int i = 1; DrawTop < PrintRect.bottom/*i < RowCount-1*/; i++)
      {
          dr0.Top = DrawTop;
          DrawTop += RowHeights[i];
          dr0.Bottom = DrawTop;
          if(dr0.Bottom > PrintRect.top && dr0.Top < PrintRect.bottom)
              DrawACell(dc, 0, i, dr0, TBYGridDrawState(), true);
          dr1.Top = dr0.Top;
          dr1.Bottom = dr0.Bottom;
          if(dr1.Bottom > PrintRect.top && dr1.Top < PrintRect.bottom)
              DrawACell(dc, 1, i, dr1, TBYGridDrawState(), true);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::FindTaskByName(const String TaskName)
{
  int i;
  for(i = Project->ExpandFoldTasks.Count()-1; i>=0; i--)
  {
    if(TaskName==Project->ExpandFoldTasks[i]->Name)
    {
      Project->Selected = Project->ExpandFoldTasks[i];
      SetSelectWithRow(i+1);
      break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::ExpandAllTask(bool bExpand,int iLevel)
{
  if(iLevel<=0)
  {
    ExpandAllTask(bExpand);
    return;
  }

  int i,curLevel;
  TPrjObject *tParent;
  for(i =0; i<Project->ExpandFoldTasks.Count(); i++)
  {
    if(Project->ExpandFoldTasks[i]->EFExpanded==bExpand)
      continue;

    tParent = Project->ExpandFoldTasks[i]->Parent();
    curLevel = 1;
    while(tParent!=Project)
    {
      curLevel++;
      tParent = tParent->Parent();
    }
    if(curLevel>iLevel)
      continue;

    if(bExpand)
    {
      bool CanExpand(true);
      if(FOnExpand)
        FOnExpand(Project, Project->ExpandFoldTasks[i], CanExpand);

      if(CanExpand)
      {
        Project->ExpandFoldTasks.Expand(i);
      }
    }
    else
    {
      Project->ExpandFoldTasks.Fold(i);
    }
  }//for
  Init();
}
//---------------------------------------------------------------------------
void __fastcall TPrjGrid::ExpandAllTask(bool bExpand)
{
  int i;
  for(i =0; i<Project->ExpandFoldTasks.Count(); i++)
  {
    if(Project->ExpandFoldTasks[i]->EFExpanded==bExpand)
      continue;

    if(bExpand)
    {
      bool CanExpand(true);
      if(FOnExpand)
        FOnExpand(Project, Project->ExpandFoldTasks[i], CanExpand);

      if(CanExpand)
      {
        Project->ExpandFoldTasks.Expand(i);
      }
    }
    else
    {
      Project->ExpandFoldTasks.Fold(i);
    }
  }//for
  Init();
}
void __fastcall TPrjGrid::DeleteProperty()
{
   String myKey=GridSelfID();
   if(myKey==Name)  return;
   TRegistry *Registry = new TRegistry;
   try
   {
     try
     {
         Registry->RootKey=HKEY_CURRENT_USER;
         myKey="\\Software\\HYWYDEV\\ZGRID\\"+myKey;
         if(Registry->KeyExists(myKey))
         {
           Registry->DeleteKey(myKey);
         }
         FReadSaveWidth = false;
		 MessageBox(Handle,L"下次打开该窗体时生效！",L"提示",MB_ICONWARNING);
     }
     catch(...){}
   }
   __finally
   {
    delete Registry;
   }
}
void __fastcall TPrjGrid::ReadProperty()
{
  if(!FReadSaveWidth) return;

  int iCount = ColCount;

 String myKey=GridSelfID();
 if(myKey==Name)
   return;
 int dwBuffer[100000];
 TRegistry *Registry = new TRegistry;
 try{
   try{
       Registry->RootKey=HKEY_CURRENT_USER;
       myKey="\\Software\\HYWYDEV\\ZGRID\\"+myKey;
       if(Registry->OpenKey(myKey,false))
       {
          int nCount = Registry->ReadBinaryData("ColWidths", dwBuffer, sizeof(dwBuffer)) / sizeof(int);
          if (nCount>iCount)
             nCount=iCount;
          for(int i=0;i<nCount;i++)
          {
				ColWidths[i]=dwBuffer[i];
		  }
       }
   }
   catch(...){}
 }
 __finally
 {
  delete Registry;
 }

}

void __fastcall TPrjGrid::SaveProperty()
{
  if(!FReadSaveWidth) return;

  int iCount = ColCount;

 String myKey=GridSelfID();
 if(myKey==Name)
   return;
   
 int* dwBuffer = new int[iCount];
 TRegistry *Registry = new TRegistry;
 try{
   try{
       Registry->RootKey=HKEY_CURRENT_USER;
       myKey="\\Software\\HYWYDEV\\ZGRID\\"+myKey;
       if(Registry->OpenKey(myKey,true))
       {
         for(int i=0;i<iCount;i++)
         {
			 dwBuffer[i]=ColWidths[i];

         }
       }
       Registry->WriteBinaryData("ColWidths", dwBuffer, iCount * sizeof(int));
   }
   catch(...){}
 }
 __finally
 {
  delete []dwBuffer;
  delete Registry;
 }

}

String __fastcall TPrjGrid::GridSelfID()
{
 /*  TControl *myparent=Parent;
   String myID=Name;
   while(myparent!=NULL)
   {
	 myID=myparent->Name+myID;
	 myparent=myparent->Parent;
   } */
   return "HYWYDEVGanter";
}
