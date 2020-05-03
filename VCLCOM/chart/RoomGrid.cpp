//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RoomGrid.h"
#include "RoomGridSet.h"
#pragma package(smart_init)
static const String None=" 无 ";
static const int SaleStatueCount = 5;
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TRoomGrid *)
{
        new TRoomGrid(NULL);
}
//---------------------------------------------------------------------------
__fastcall TRoomGrid::TRoomGrid(TComponent* Owner)
        : TCustomGrid(Owner)
{
  //Buffer = new TBufferDataSet();
  UnitRecord = NULL;
  Options<<goDrawFocusSelected<<goRowSizing<<goColSizing;
  DefaultDrawing = false;
  FixedColor = TColor(0x00B8D9E8); 
  Ctl3D = false;
  BorderStyle = bsNone;
  FFloorCount = 0;
  FUnitCount = 0;
  TCustomGrid::RowCount = 5;
  ColCount = 1;
  DefaultColWidth = 60;
  DefaultRowHeight = 40;
  RowHeights[0] = 18;
  FFloorNameWidth=50;
  ColWidths[0] = FFloorNameWidth;
  FIsUnit = true;
  FTitleFont = new TFont();
  FDetailFont = new TFont();
  FTitleFont->Assign(Font);
  FDetailFont->Assign(Font);
  FFloorNames=new TStringList();
  FDisplaySight=false; //显示景观
  FDisplayFitment=false; //显示装修
  FDisplayDirection=false; //显示朝向
  FDisplayArea=false;      //显示建筑面积， 如果单元是复式将显示上下层面积
  FDisplayUseArea=false;  //显示套内面积， 如果单元是复式将显示上下层面积
  FDisplaySaleArea=false;  //显示销售
  FDisplayPreSaleArea=false;  //显示预售
  FDisplayRightArea=false;  //显示产权
  FDisplayRoofGarden=false;//显示平台面积
  FDisplayHouseType=false; //显示户型
  FDisplayUnitPrice=false;  //单元单价
  FDisplayTotalCost=false;  //单元总价
  FDisplayDetail=true;    //显示功能（以前的细节栏）
  FDisplayApportionArea = false; //分摊面积
  FDisplayUnitLeaseCost = false; //单位月租金　
  FDisplayLeaseCost = false; //月租金　
  FDisplayCanLease = false;
  FDisplaySale = true;

  FPrintAlign=1;
  UnitTitleHeight=14;
  StepLineHeight=16;

  TitleColor = TColor(0x00B8D9E8);
  DispColor[0] = clWhite;
  DispColor[1] = TColor(0x000082FF);
  DispColor[2] = TColor(0x00848200);
  DispColor[3] = TColor(0x00FF8284);
  DispColor[4] = TColor(0x00FF82FF);
  DispColor[5] = TColor(0x00C08080);
  DispColor[6] = TColor(0x00FFFF80);
  DispColor[7] = TColor(0x0080FFFF);
  DispColor[8] = TColor(0x00FF8000);
  DispColor[9] = TColor(0x00008080);
}
//---------------------------------------------------------------------------
__fastcall TRoomGrid::~TRoomGrid()
{
  if(UnitRecord)
    delete [] UnitRecord;
  delete FTitleFont;
  delete FDetailFont;
}
//---------------------------------------------------------------------------
namespace Roomgrid
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TRoomGrid)};
				 RegisterComponents("ZChart", classes, 0);
        }
}
void __fastcall TRoomGrid::WMEraseBkGnd(Messages::TMessage &Message)
{
 Message.Result=0;
}
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::GetStatus(TCells * cell)
{
  if(FDisplaySale)
     return cell->Status;
  else
  {
    return cell->LeaseStatus;
  }
}
//---------------------------------------------------------------------------
TColor __fastcall TRoomGrid::GetDisplayColor(Status)
{
   if(Status==6)
     return DispColor[9];//删除

   if(FDisplaySale)
     return DispColor[Status-1];
   else
   {
     return DispColor[Status-1+SaleStatueCount];
   }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayColor(int Status,TColor newColor)
{
   if(Status==6)
     DispColor[8] = newColor;//删除

   if(FDisplaySale)
     DispColor[Status-1] = newColor;
   else
   {
     DispColor[Status-1+SaleStatueCount] = newColor;
   }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::DrawCellItem(HDC CanvasHandle,String sDrawText
      ,TRect &DrawRect,UINT dpAlign)
{
  if(sDrawText!=NULL && (!sDrawText.Trim().IsEmpty()))
  {
    DrawRect.Top=DrawRect.Bottom;
	DrawRect.Bottom=DrawRect.Top+StepLineHeight;

	DrawText(CanvasHandle,sDrawText.c_str(),sDrawText.Length(),&DrawRect,dpAlign);
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::DrawCell(int ACol, int ARow, const TRect &ARect, Grids::
                                         TGridDrawState AState)
{
  Canvas->Font->Assign(Font);
  if((ACol==0)||(ARow==0))
  {
    Canvas->Brush->Color = FixedColor;
	Canvas->FillRect(ARect);
  }
  if((ACol==0)&&(ARow==0))
  {
    Canvas->Brush->Color = TColor(0x008396A0);
    Canvas->MoveTo(ARect.left,ARect.top);
    Canvas->LineTo(ARect.right,ARect.top);
    Canvas->MoveTo(ARect.left,ARect.top);
    Canvas->LineTo(ARect.left,ARect.bottom);
    return;
  }
  if((ACol==0)&&(ARow!=0))
  {
    if(FIsUnit)
    {
      Canvas->Brush->Color = TColor(0x008396A0);
      Canvas->MoveTo(ARect.left,ARect.top);
      Canvas->LineTo(ARect.left,ARect.bottom);
      Canvas->Brush->Color = TColor(0x00B8D9E8);
      String sFloor =GetCellString(ACol,ARow);
      SetBkMode(Canvas->Handle, TRANSPARENT);
	  TRect UnitRect = ARect;
	  DrawText(Canvas->Handle,sFloor.c_str(),sFloor.Length(),&UnitRect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}
    return;
  }
  if((ARow==0)&&(ACol!=0))
  {
    Canvas->Brush->Color = TColor(0x008396A0);
    Canvas->MoveTo(ARect.left,ARect.top);
    Canvas->LineTo(ARect.right,ARect.top);
    Canvas->Brush->Color = TColor(0x00B8D9E8);
    TRect UnitRect = ARect;
    String sUnit = IntToStr(ACol);
	SetBkMode(Canvas->Handle, TRANSPARENT);
	DrawText(Canvas->Handle,sUnit.c_str(),sUnit.Length(),&UnitRect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	return;
  }
  //下面显示单元信息
  TCells *CellData=GetCellData(ACol,ARow);
  if(CellData==NULL)
    return;
  if(!AState.Contains(gdFixed))  //不为FixCell时
  {
    TRect Toprect,Downrect;
    Toprect = ARect;
    Downrect = ARect;
    int StepHeight=StepLineHeight;//ARect.Height()*0.6;
    Toprect.bottom =ARect.Top+UnitTitleHeight;//bottomheight;
    Downrect.top = Toprect.Bottom;
   if(GetStatus(CellData)!=6)
   {
      Canvas->Font = FTitleFont;
      Canvas->Brush->Color = TitleColor;
      Canvas->FillRect(Toprect);  //填充title
      String TitleText=CellData->Title;
      if(CellData->DoubleLays!=0)
		 TitleText+="(复)";
	  DrawText(Canvas->Handle,TitleText.c_str(),TitleText.Length(),&Toprect,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	  Canvas->Brush->Color = DisplayColor[GetStatus(CellData)];
      Canvas->FillRect(Downrect);     //填充detail
      Canvas->Font = FDetailFont;
      SetBkMode(Canvas->Handle, TRANSPARENT);
      //对齐方式
      UINT dpAlign=DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS;
      if(FPrintAlign==0)
         dpAlign|=DT_LEFT;
       else if(FPrintAlign==2)
          dpAlign|=DT_RIGHT;
       else
          dpAlign|=DT_CENTER;

      String ProText=CellData->Detail;
      Downrect.Bottom=Downrect.Top;
      if(FDisplayDetail)//画功能
      {
		DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      //显示单元属性
      ProText=CellData->HouseType;
      if(FDisplayHouseType) //画户型
      {
        DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->Sight;
      if(FDisplaySight)//画景观
      {
        DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->Fitment;
      if(FDisplayFitment) //画装修
      {
        DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->Direction;
      if(FDisplayDirection) //朝向
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->UseArea;
      if(FDisplayUseArea) //套内面积
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      /////////////////////////////////////////
      ProText=CellData->ApportionArea;
      if(FDisplayApportionArea) //分摊面积
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }


      ProText=CellData->RoofGargdenArea;  //平台面积
      if(FDisplayRoofGarden)
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->Area;
      if( FDisplayArea)   //建筑面积
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText = CellData->UpArea+"/"+CellData->DownArea;
      if((FDisplayArea||FDisplayUseArea)&&(CellData->DoubleLays!=0)&&ProText!="/") //上下层面积
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->SaleArea;
      if(FDisplaySaleArea) //销售面积
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->PreSaleArea;
      if(FDisplayPreSaleArea) //预售面积
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->RightArea;
      if(FDisplayRightArea) //产权面积
      {
       DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }

      ProText=CellData->UnitPrice;
      if( FDisplayUnitPrice)  //单价
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->TotalCost;
      if( FDisplayTotalCost ) //总价
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->UnitLeaseCost;
      if( FDisplayUnitLeaseCost ) //单位月租金
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }
      ProText=CellData->LeaseCost;
      if( FDisplayLeaseCost ) //月租金
      {
         DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      }

      //ProText=CellData->CanLease;
      //if( FDisplayCanLease) //能否出租
      //{
      //   DrawCellItem(Canvas->Handle,ProText,Downrect,dpAlign);
      //}

      Canvas->MoveTo(ARect.left,Toprect.bottom); //画中线
      Canvas->LineTo(ARect.right,Toprect.bottom);

    }
    else
    {
      Canvas->Brush->Color = clWhite;
      Canvas->FillRect(ARect);  //填充整个单元
    }
    //if(AState.Contains(gdSelected))
    if(CellData->Selected)
    {  //当为选中状态时
      if(GetStatus(CellData)!=6)
      {
        Canvas->Brush->Color = clRed;
        Canvas->FrameRect(ARect);
      }
      else
      {
          InvertRect(Canvas->Handle, &ARect);
      }

    }
  }
}
//---------------------------------------------------------------------------
/*void __fastcall TRoomGrid::Paint()
{
  TCustomGrid::Paint();
  HDC hdc;
  HBRUSH brush;
  hdc = GetWindowDC(Handle);
  brush = CreateSolidBrush(0x008396A0);
  HBRUSH oldbrush = ::SelectObject(hdc,brush);
  TRect R;
  GetWindowRect(Handle, &R);
  OffsetRect(&R, -R.Left, -R.Top);
  FrameRect(hdc, &R, brush);
  SelectObject(hdc, oldbrush);
  DeleteObject(brush);
  ReleaseDC(Handle, hdc);
}     */
//---------------------------------------------------------------------------
/*void __fastcall TRoomGrid::Click(void)
{
  TCustomGrid::Click();
  if(IsUnit)
    if(Buffer->LocateByKey(IntToStr(GetFloor())+"\t"+IntToStr(GetUnit())))
      FValid = true;
    else
      FValid = false;
  else
    if(Buffer->LocateByKey(IntToStr((Row-1)*FUnitCount+Col)))
      FValid = true;
    else
      FValid = false;
}   */
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::RowToFloor(int ARow)
{
  if(ARow>0)
    return FloorCount-ARow+1;
  else
    return 0;
}
//---------------------------------------------------------------------------
/*TPoint __fastcall TRoomGrid::CenterPos(TRect ARect, String ShowText)
{
  int Textwidth,Textheight,left,top;
  Textwidth = Canvas->TextWidth(ShowText);
  Textheight = Canvas->TextHeight(ShowText);
  if(Textwidth<=(ARect.right-ARect.left))
    left = ((ARect.right-ARect.left-Textwidth) /2)+ARect.left;
  else
    left = ARect.left+1;;
  top = ((ARect.bottom-ARect.top-Textheight) / 2)+ARect.top;
  return Point(left,top);
}  */
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetFloorCount(int Value)
{
	FFloorCount = Value;
	RowCount = Value+1;
	if(RowCount>1)
	{
	  FixedRows = 1;
	  if(UnitRecord)
	  {
		delete [] UnitRecord;
		UnitRecord = NULL;
	  }
	  if((FFloorCount>0)&&(FUnitCount>0))
		UnitRecord = new TCells[FFloorCount*FUnitCount];
	}
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetUnitCount(int Value)
{
	FUnitCount = Value;
	ColCount = Value+1;
	if(ColCount>1)
	{
	  FixedCols = 1;
	  if(UnitRecord)
	  {
		delete [] UnitRecord;
		UnitRecord = NULL;
	  }
	  if((FFloorCount>0)&&(FUnitCount>0))
		UnitRecord = new TCells[FFloorCount*FUnitCount];
	}
}
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::GetFloor()
{
  if(IsUnit)
    return RowToFloor(Row);
  else
    return Row;
}
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::GetUnit()
{
  return Col;
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetFloor(int Value)
{
  int ARow;
  ARow = FloorCount-Value+1;
  if(Row!=ARow)
    Row = ARow;
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetUnit(int Value)
{
  if(Col!=Value)
    Col = Value;
}
//---------------------------------------------------------------------------
/*void __fastcall TRoomGrid::SetKeyField(String Value)
{
  //if(FKeyField!=Value)
  //{
    FKeyField = Value;
    Buffer->KeyField = Value;
  //}
}   */
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetIsUnit(bool Value)
{
  if(FIsUnit!=Value)
  {
    FIsUnit = Value;
    if(FIsUnit)
      ColWidths[0] = FFloorNameWidth;
    else
      ColWidths[0] = 1;
  }
}
//---------------------------------------------------------------------------
TSelRange __fastcall TRoomGrid::GetSelRange()
{
  TSelRange sr;
  if(FIsUnit)
  {
    sr.StartFloor = RowToFloor(Selection.TopLeft.Y);
    sr.EndFloor = RowToFloor(Selection.BottomRight.Y);
  }
  else
  {
    sr.StartFloor = Selection.TopLeft.Y;
    sr.EndFloor = Selection.BottomRight.Y;
  }
  sr.StartUnit = Selection.TopLeft.X;
  sr.EndUnit = Selection.BottomRight.X;
  if(sr.StartFloor>sr.EndFloor)
  {
    int i=sr.StartFloor;
    sr.StartFloor = sr.EndFloor;
    sr.EndFloor = i;
  }
  if(sr.StartUnit>sr.EndUnit)
  {
    int j=sr.StartUnit;
    sr.StartUnit = sr.EndUnit;
    sr.EndUnit = j;
  }
  return sr;
}
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::GetColWidth()
{
  return DefaultColWidth;
}
//---------------------------------------------------------------------------
int __fastcall TRoomGrid::GetRowHeight()
{
  return DefaultRowHeight;
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetColWidth(int Value)
{
  DefaultColWidth = Value;
  if(FIsUnit)
    ColWidths[0] = FFloorNameWidth;
  else
    ColWidths[0] = 1;
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetRowHeight(int Value)
{
 if(Value<30)
    Value=30;
 if(!FUnitAutoFill)
    DefaultRowHeight = Value;
  RowHeights[0] = 18;
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetTitleFont(TFont *Value)
{
  if(FTitleFont!=Value)
  {
    FTitleFont->Assign(Value);
    Invalidate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDetailFont(TFont *Value)
{
  if(FDetailFont!=Value)
  {
    FDetailFont->Assign(Value);
    Invalidate();
  }
}
//---------------------------------------------------------------------------
/*void __fastcall TRoomGrid::LocateGrid()
{
  if(FIsUnit)
  {
    String floorfield,unitfield;
    int pos,ifloor,iunit;
    pos = FKeyField.Pos("\t");
    floorfield = FKeyField.SubString(1,pos-1);
    unitfield = FKeyField.SubString(pos+1,FKeyField.Length()-pos);
    ifloor = StrToInt(Buffer->FieldValues[floorfield]);
    iunit =  StrToInt(Buffer->FieldValues[unitfield]);
    Floor = ifloor;
    Unit =  iunit;
  }
  else
  {
    int id;
    id = StrToInt(Buffer->FieldValues[FKeyField]);
    div_t x = div(id,FUnitCount);
    if(x.rem>0)
    {
      Row = x.quot+1;
      Col = x.rem;
    }
    else
    {
      Row = x.quot;
      Col = FUnitCount;
    }
  }
  Invalidate(); 
}                      */
//---------------------------------------------------------------------------
/*bool __fastcall TRoomGrid::LocateBuffer()
{
  bool locate;
  if(FIsUnit)
  {
    String keyvalue;
    keyvalue = IntToStr(GetFloor())+"\t"+IntToStr(GetUnit());
    locate = Buffer->LocateByKey(keyvalue);
  }
  else
  {
    int id;
    id = (Row-1)*FUnitCount+Col;
    locate = Buffer->LocateByKey(IntToStr(id));
  }
  if(!locate)
    LocateGrid();
  return locate;
}      */
//---------------------------------------------------------------------------
TCells* TRoomGrid::GetCellData(int ACol, int ARow)
{
    if(ACol <= 0 || ARow <= 0 || ACol >= ColCount || ARow >= RowCount)
        return NULL;
    int UnitIndex;
    if(FIsUnit)
	   UnitIndex = (RowToFloor(ARow)-1)*UnitCount+ACol-1;
    else
       UnitIndex = (ARow-1)*UnitCount+ACol-1;
    return &(UnitRecord[UnitIndex]);
}
//---------------------------------------------------------------------------
String TRoomGrid::GetCellString(int ACol, int ARow)
{
    if(ACol == 0)
    {
         if(ARow == 0)
             return "";
      int iFloor=RowToFloor(ARow);
      String sFloor="第"+IntToStr(iFloor)+"层";
	  if((iFloor<=FloorNames->Count)&&FloorNames->Count>0)
         sFloor=FloorNames->Strings[iFloor-1];
      return sFloor;
    }else if(ARow == 0)
    {
		 return IntToStr(ACol);
    }else
    {
		 TCells* Cell = GetCellData(ACol, ARow);
		 if(Cell)
             return Cell->Title;
		 else
			 return "";
    }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::ReadSetting(String Key)
{
  if(this->Parent!=NULL)
    Key = Key+this->Parent->Name+this->Name;
  frmRoomGridSet->LoadDataFromRegistry(this,Key);
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SaveSetting(String Key)
{
  if(this->Parent!=NULL)
    Key = Key+this->Parent->Name+this->Name;
  frmRoomGridSet->SaveToRegistry(this,Key);
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::Setup(String Key)
{
  if(this->Parent!=NULL)
    Key = Key+this->Parent->Name+this->Name;

  TRoomGridSetting *ASet=new TRoomGridSetting();
  TfrmRoomGridSet* p=new TfrmRoomGridSet(this,this);
  try
  {
    p->BackupData(this,ASet);
	if(p->ShowModal()==mrOk)
	   p->SaveToRegistry(this,Key);
    else
       p->RestoreData(this,ASet);
  }
  __finally
  {
    delete p;
    delete ASet;
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplaySight(bool value)
{
        if(FDisplaySight != value) {
                FDisplaySight = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayFitment(bool value)
{
        if(FDisplayFitment != value) {
                FDisplayFitment = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayDirection(bool value)
{
        if(FDisplayDirection != value) {
                FDisplayDirection = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayArea(bool value)
{
        if(FDisplayArea != value) {
                FDisplayArea = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayHouseType(bool value)
{
        if(FDisplayHouseType != value) {
                FDisplayHouseType = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayDetail(bool value)
{
        if(FDisplayDetail != value) {
                FDisplayDetail = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetUnitAutoFill(bool value)
{
        if(FUnitAutoFill != value) {
                FUnitAutoFill = value;
                if(value)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayUseArea(bool value)
{
        if(FDisplayUseArea != value) {
                FDisplayUseArea = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplaySaleArea(bool value)
{
  if(FDisplaySaleArea != value)
  {
    FDisplaySaleArea = value;
    if(FUnitAutoFill)
      SetGridHeightAndWidth();
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayPreSaleArea(bool value)
{
  if(FDisplayPreSaleArea != value)
  {
    FDisplayPreSaleArea = value;
    if(FUnitAutoFill)
      SetGridHeightAndWidth();
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayRightArea(bool value)
{
  if(FDisplayRightArea != value)
  {
    FDisplayRightArea = value;
    if(FUnitAutoFill)
      SetGridHeightAndWidth();
  }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetGridHeightAndWidth()
{
        if(FUnitAutoFill)
        {
           int UnitTotalHeight=UnitTitleHeight;
           if(FDisplayDetail)
              UnitTotalHeight+=StepLineHeight;
           if(FDisplaySight)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayFitment)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayDirection)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayUnitPrice)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayTotalCost)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayApportionArea)
               UnitTotalHeight+=StepLineHeight;     /////
           if(FDisplayArea)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayRoofGarden)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayUseArea)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplaySaleArea)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayPreSaleArea)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayRightArea)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayHouseType)
               UnitTotalHeight+=StepLineHeight;
            if(FDisplayArea||FDisplayUseArea) //显示上下层面积
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayUnitLeaseCost)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayLeaseCost)
               UnitTotalHeight+=StepLineHeight;
           if(FDisplayCanLease)
               UnitTotalHeight+=StepLineHeight;

            DefaultRowHeight=UnitTotalHeight;
            RowHeight=UnitTotalHeight;
        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayUnitPrice(bool value)
{
        if(FDisplayUnitPrice != value) {
                FDisplayUnitPrice = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();

        }
}
//---------------------------------------------------------------------------
void __fastcall TRoomGrid::SetDisplayTotalCost(bool value)
{
        if(FDisplayTotalCost != value) {
                FDisplayTotalCost = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
void __fastcall TRoomGrid::SetDisplayUnitLeaseCost(bool value)
{
  if(FDisplayUnitLeaseCost != value){
                FDisplayUnitLeaseCost = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();
        }
}
void __fastcall TRoomGrid::SetDisplayLeaseCost(bool value)
{
  if(FDisplayLeaseCost != value)
  {
    FDisplayLeaseCost = value;
    if(FUnitAutoFill)
        SetGridHeightAndWidth();         
    Invalidate();
  }
}
void __fastcall TRoomGrid::SetDisplaySale(bool value)
{
  if(FDisplaySale != value)
  {
    FDisplaySale = value;
    Invalidate();
  }
}

void __fastcall TRoomGrid::SetDisplayCanLease(bool value)
{
  if(FDisplayCanLease != value)
  {
    FDisplayCanLease = value;
    if(FUnitAutoFill)
        SetGridHeightAndWidth();
    Invalidate();
  }
}

void __fastcall TRoomGrid::SetDisplayRoofGarden(bool value)
{
        if(FDisplayRoofGarden != value) {
                FDisplayRoofGarden = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();

        }
}
void __fastcall TRoomGrid::SetDisplayApportionArea(bool value)
{
        if(FDisplayApportionArea != value) {
                FDisplayApportionArea = value;
                if(FUnitAutoFill)
                    SetGridHeightAndWidth();
                Invalidate();

        }
}

void __fastcall TRoomGrid::SetPrintAlign(int Value)
{
        if(FPrintAlign!=Value)
        {
            FPrintAlign=Value;
            Invalidate();
        }
}

void __fastcall TRoomGrid::SetFloorNameWidth(int value)
{
        if(FFloorNameWidth != value) {
           if(value<0)
              value=1;
           FFloorNameWidth = value;
           if(FIsUnit)
              ColWidths[0] = FFloorNameWidth;

        }
}
int __fastcall TRoomGrid::GetFloorNameWidth()
{
        return FFloorNameWidth;
}
void __fastcall TRoomGrid::ClearSelected()
{
  if(UnitRecord)
  {
    for(int i=FFloorCount*FUnitCount-1; i>=0; i--)
      UnitRecord[i].Selected = false;
    Invalidate();
  }
}
void __fastcall TRoomGrid::SelectCells(int StartR, int EndR, int StartC,int EndC)
{
  int temp;
  if(StartR>EndR)
  {
    temp = EndR;
    EndR =  StartR;
    StartR = temp;
  }
  if(StartC>EndC)
  {
    temp = EndC;
    EndC =  StartC;
    StartC = temp;
  }
  for(int i=StartR; i<=EndR; i++)
  {
    for(int k=StartC; k<=EndC; k++)
      CellSelected[k][i] = true;
  }
}
bool __fastcall TRoomGrid::GetCellSelected(int ACol, int ARow)
{
  TCells* Cell = GetCellData(ACol, ARow);
  if(Cell)
    return Cell->Selected;
  else
    return false;
}
void __fastcall TRoomGrid::SetCellSelected(int ACol, int ARow,bool Selected)
{
  TCells* Cell = GetCellData(ACol, ARow);
  if(Cell)
  {
    Cell->Selected = Selected;
    InvalidateCell(ACol,ARow);
  }
}
void __fastcall TRoomGrid::KeyDown(Word &Key, Classes::TShiftState Shift)
{
  TCustomGrid::KeyDown(Key, Shift);
}
void __fastcall TRoomGrid::MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
  TCustomGrid::MouseDown(Button,Shift,X,Y);
  if(Options.Contains(goRangeSelect))
  {
      if(Shift.Contains(ssShift))
      {
        TGridRect CurSelection = Selection;
        ClearSelected();
        SelectCells(CurSelection.Top,CurSelection.Bottom,CurSelection.Left,CurSelection.Right);
      }
      else if(Shift.Contains(ssCtrl))
      {
        CellSelected[Col][Row] = !CellSelected[Col][Row];//反选
      }
      else
      {
        ClearSelected();
        CellSelected[Col][Row] = true;
      }
  }
  else
  {
    ClearSelected();
    CellSelected[Col][Row] = true;
  }

}
void __fastcall TRoomGrid::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
  if(FGridState==gsSelecting && (!Shift.Contains(ssCtrl)))
  {
    TGridRect OSelection = Selection;
    TCustomGrid::MouseMove(Shift,X,Y);
    TGridRect NSelection = Selection;
    if(OSelection.Top!=NSelection.Top || OSelection.Left!=NSelection.Left
     || OSelection.Bottom!=NSelection.Bottom || OSelection.Right!=NSelection.Right)
    {
        ClearSelected();
        SelectCells(NSelection.Top,NSelection.Bottom,NSelection.Left,NSelection.Right);
    }
  }
  else
  {
    TCustomGrid::MouseMove(Shift,X,Y);
  }
}
void __fastcall TRoomGrid::MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
  TCustomGrid::MouseUp(Button,Shift,X,Y);
}

