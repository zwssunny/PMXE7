//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RoomGridSet.h"
#include <registry.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZEdit"
#pragma resource "*.dfm"
TfrmRoomGridSet *frmRoomGridSet;
//---------------------------------------------------------------------------
__fastcall TfrmRoomGridSet::TfrmRoomGridSet(TComponent* Owner,TRoomGrid *RoomGrid,String Key)
        : TForm(Owner)
{
    FRoomGrid=RoomGrid;
    RegKey=Key;
	SetData();
}
//---------------------------------------------------------------------------
void  TfrmRoomGridSet::RestoreData(TRoomGrid * RoomGrid,TRoomGridSetting * RoomGridSetting)
{
  RoomGrid->DisplayDetail=RoomGridSetting->DisplayDetail;
  RoomGrid->DisplaySight=RoomGridSetting->DisplaySight;
  RoomGrid->DisplayFitment=RoomGridSetting->DisplayFitment;
  RoomGrid->DisplayDirection=RoomGridSetting->DisplayDirection;
  RoomGrid->DisplayArea=RoomGridSetting->DisplayArea;
  RoomGrid->DisplayUseArea=RoomGridSetting->DisplayUseArea;
  RoomGrid->DisplaySaleArea=RoomGridSetting->DisplaySaleArea;
  RoomGrid->DisplayPreSaleArea=RoomGridSetting->DisplayPreSaleArea;
  RoomGrid->DisplayRightArea=RoomGridSetting->DisplayRightArea;
  RoomGrid->DisplayHouseType=RoomGridSetting->DisplayHouseType;
  RoomGrid->DisplayUnitPrice=RoomGridSetting->DisplayUnitPrice;
  RoomGrid->DisplayTotalCost=RoomGridSetting->DisplayTotalCost;
  RoomGrid->DisplayRoofGarden=RoomGridSetting->DisplayRoofGarden;
  RoomGrid->DisplayApportionArea=RoomGridSetting->DisplayApportionArea;///////
  RoomGrid->PrintAlign=RoomGridSetting->PrintAlign;
  RoomGrid->RowHeight=RoomGridSetting->RowHeight;
  RoomGrid->ColWidth=RoomGridSetting->ColWidth;
  RoomGrid->UnitAutoFill=RoomGridSetting->AutoFill;
  RoomGrid->DisplayCanLease     =RoomGridSetting->DisplayCanLease     ;
  RoomGrid->DisplayLeaseCost    =RoomGridSetting->DisplayLeaseCost    ;
  RoomGrid->DisplayUnitLeaseCost=RoomGridSetting->DisplayUnitLeaseCost;
}

void  TfrmRoomGridSet::BackupData(TRoomGrid * RoomGrid,TRoomGridSetting * RoomGridSetting)
{
  RoomGridSetting->DisplayDetail=RoomGrid->DisplayDetail;
  RoomGridSetting->DisplaySight=RoomGrid->DisplaySight;
  RoomGridSetting->DisplayFitment=RoomGrid->DisplayFitment;
  RoomGridSetting->DisplayDirection=RoomGrid->DisplayDirection;
  RoomGridSetting->DisplayUnitPrice=RoomGrid->DisplayUnitPrice;
  RoomGridSetting->DisplayTotalCost=RoomGrid->DisplayTotalCost;
  RoomGridSetting->DisplayArea=RoomGrid->DisplayArea;
  RoomGridSetting->DisplayUseArea=RoomGrid->DisplayUseArea;
  RoomGridSetting->DisplaySaleArea=RoomGrid->DisplaySaleArea;
  RoomGridSetting->DisplayPreSaleArea=RoomGrid->DisplayPreSaleArea;
  RoomGridSetting->DisplayRightArea=RoomGrid->DisplayRightArea;

  RoomGridSetting->DisplayHouseType=RoomGrid->DisplayHouseType;
  RoomGridSetting->DisplayRoofGarden=RoomGrid->DisplayRoofGarden;
  RoomGridSetting->DisplayApportionArea=RoomGrid->DisplayApportionArea;///////
  RoomGridSetting->PrintAlign=RoomGrid->PrintAlign;
  RoomGridSetting->RowHeight=RoomGrid->RowHeight;
  RoomGridSetting->ColWidth=RoomGrid->ColWidth;
  RoomGridSetting->AutoFill=RoomGrid->UnitAutoFill;

  RoomGridSetting->DisplayCanLease     =RoomGrid->DisplayCanLease;
  RoomGridSetting->DisplayLeaseCost    =RoomGrid->DisplayLeaseCost;
  RoomGridSetting->DisplayUnitLeaseCost=RoomGrid->DisplayUnitLeaseCost;

}
void  TfrmRoomGridSet::SaveToRegistry(TRoomGrid * RoomGrid, String Key )
{
  TRegistry*AReg;
   try{
      TRoomGridSetting ASet;
      BackupData(RoomGrid,&ASet);
	  AReg = new TRegistry();
      AReg->RootKey = HKEY_CURRENT_USER;
	  AReg->OpenKey("SOFTWARE", false);
	  AReg->OpenKey("CPMest", true);
      AReg->WriteBinaryData(Key, &ASet, sizeof(TRoomGridSetting));
      AReg->CloseKey();
   }__finally
   {
      delete AReg;
   }
}
void  TfrmRoomGridSet::LoadDataFromRegistry(TRoomGrid * RoomGrid, String Key)
{
   TRegistry*AReg;
   try{
      TRoomGridSetting ASet;
	  AReg = new TRegistry();
      AReg->RootKey = HKEY_CURRENT_USER;
      AReg->OpenKey("SOFTWARE", false);
      if(!AReg->KeyExists("CPMest"))
      {
         return;
      }
      AReg->OpenKey("CPMest", true);
      if(!AReg->ValueExists(Key))
         return;
      try{
         int readcount=AReg->ReadBinaryData(Key, &ASet, sizeof(TRoomGridSetting));
         if(readcount!=sizeof(TRoomGridSetting))
           {
             AReg->DeleteValue(Key);
             AReg->CloseKey();
             return;
           }
         AReg->CloseKey();
		 RestoreData(RoomGrid,&ASet);
      }catch(...)
      {
      }
   }__finally
   {
      delete AReg;
   }

}

void __fastcall TfrmRoomGridSet::SetData()
{
        ckDpDetail->Checked=FRoomGrid->DisplayDetail;
        ckDpHouseType->Checked=FRoomGrid->DisplayHouseType;
        ckDpArea->Checked=FRoomGrid->DisplayArea;
        ckUseArea->Checked=FRoomGrid->DisplayUseArea;
        ckSaleArea->Checked=FRoomGrid->DisplaySaleArea;
        ckPreSaleArea->Checked=FRoomGrid->DisplayPreSaleArea;
        ckRightArea->Checked=FRoomGrid->DisplayRightArea;
        ckDpDirection->Checked=FRoomGrid->DisplayDirection;
        ckDpSight->Checked=FRoomGrid->DisplaySight;
        ckDpFitment->Checked=FRoomGrid->DisplayFitment;
        ckAutoFill->Checked=FRoomGrid->UnitAutoFill;
        ckDpUnitPrice->Checked=FRoomGrid->DisplayUnitPrice;
        ckDpTotalCost->Checked=FRoomGrid->DisplayTotalCost;
        ckDpRoofGarden->Checked=FRoomGrid->DisplayRoofGarden;
        ckApportion->Checked=FRoomGrid->DisplayApportionArea;
        seRowHeight->Text=FRoomGrid->RowHeight;
        seColWidth->Text=FRoomGrid->ColWidth;
        ckCanLease->Checked=FRoomGrid->DisplayCanLease;
        ckLeaseCost->Checked=FRoomGrid->DisplayLeaseCost;
        ckUnitLeaseCost->Checked=FRoomGrid->DisplayUnitLeaseCost;
        if(FRoomGrid->PrintAlign==0)
           rbLeft->Checked=true;
         else if(FRoomGrid->PrintAlign==2)
           rbRight->Checked=true;
         else rbCenter->Checked=true;
}

void __fastcall TfrmRoomGridSet::ckDpDetailMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     FRoomGrid->DisplayDetail=ckDpDetail->Checked;
           GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpHouseTypeMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     FRoomGrid->DisplayHouseType=ckDpHouseType->Checked;
           GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpAreaMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    FRoomGrid->DisplayArea=ckDpArea->Checked;
          GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpDirectionMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      FRoomGrid->DisplayDirection=ckDpDirection->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpSightMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        FRoomGrid->DisplaySight=ckDpSight->Checked;
        GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpFitmentMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      FRoomGrid->DisplayFitment=ckDpFitment->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckAutoFillMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      FRoomGrid->UnitAutoFill=ckAutoFill->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::seRowHeightExit(TObject *Sender)
{
      FRoomGrid->RowHeight=seRowHeight->Text.ToInt();
	  seRowHeight->Text=FRoomGrid->RowHeight;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::seColWidthExit(TObject *Sender)
{
      FRoomGrid->ColWidth=seColWidth->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::FormClose(TObject *Sender, TCloseAction &Action)
{
//      delete FRoomGridSetting;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckUseAreaMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       FRoomGrid->DisplayUseArea=ckUseArea->Checked;
             GetRowHeightAgaint();
}
//---------------------------------------------------------------------------


void __fastcall TfrmRoomGridSet::GetRowHeightAgaint()
{
      if(FRoomGrid->UnitAutoFill)
        seRowHeight->Text=FRoomGrid->RowHeight;
}
void __fastcall TfrmRoomGridSet::ckDpRoofGardenMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     FRoomGrid->DisplayRoofGarden=ckDpRoofGarden->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpUnitPriceMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        FRoomGrid->DisplayUnitPrice=ckDpUnitPrice->Checked;
         GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckDpTotalCostMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     FRoomGrid->DisplayTotalCost=ckDpTotalCost->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRoomGridSet::rbLeftClick(TObject *Sender)
{
     FRoomGrid->PrintAlign=0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::rbCenterClick(TObject *Sender)
{
     FRoomGrid->PrintAlign=1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::rbRightClick(TObject *Sender)
{
     FRoomGrid->PrintAlign=2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRoomGridSet::ckApportionMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     FRoomGrid->DisplayApportionArea=ckApportion->Checked;
      GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckUnitLeaseCostMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  FRoomGrid->DisplayUnitLeaseCost=ckUnitLeaseCost->Checked;
  GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckLeaseCostMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  FRoomGrid->DisplayLeaseCost=ckLeaseCost->Checked;
  GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckCanLeaseMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  FRoomGrid->DisplayCanLease=ckCanLease->Checked;
  GetRowHeightAgaint();
}
//---------------------------------------------------------------------------


void __fastcall TfrmRoomGridSet::ckSaleAreaMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        
  FRoomGrid->DisplaySaleArea=ckSaleArea->Checked;
  GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckPreSaleAreaMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        
  FRoomGrid->DisplayPreSaleArea=ckPreSaleArea->Checked;
  GetRowHeightAgaint();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRoomGridSet::ckRightAreaMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  FRoomGrid->DisplayRightArea=ckRightArea->Checked;
  GetRowHeightAgaint();

}
//---------------------------------------------------------------------------

