//---------------------------------------------------------------------------

#ifndef RoomGridSetH
#define RoomGridSetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZEdit.h"
#include <Buttons.hpp>
#include "RoomGrid.h"
//---------------------------------------------------------------------------
class TfrmRoomGridSet : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *ckDpDetail;
        TCheckBox *ckDpHouseType;
        TCheckBox *ckDpArea;
        TCheckBox *ckDpDirection;
        TCheckBox *ckDpSight;
        TCheckBox *ckDpFitment;
        TGroupBox *GroupBox1;
        TBitBtn *btOk;
        TBitBtn *btCancel;
        TCheckBox *ckAutoFill;
        TZEdit *seRowHeight;
		TZEdit *seColWidth;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TCheckBox *ckUseArea;
        TCheckBox *ckDpUnitPrice;
        TCheckBox *ckDpTotalCost;
        TCheckBox *ckDpRoofGarden;
        TGroupBox *GroupBox2;
        TRadioButton *rbLeft;
        TRadioButton *rbCenter;
        TRadioButton *rbRight;
        TCheckBox *ckApportion;
        TCheckBox *ckUnitLeaseCost;
        TCheckBox *ckLeaseCost;
        TCheckBox *ckCanLease;
        TCheckBox *ckSaleArea;
        TCheckBox *ckPreSaleArea;
        TCheckBox *ckRightArea;
        void __fastcall ckDpDetailMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpHouseTypeMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpAreaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpDirectionMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpSightMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpFitmentMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckAutoFillMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall seRowHeightExit(TObject *Sender);
        void __fastcall seColWidthExit(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ckUseAreaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpRoofGardenMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpUnitPriceMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckDpTotalCostMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall rbLeftClick(TObject *Sender);
        void __fastcall rbCenterClick(TObject *Sender);
        void __fastcall rbRightClick(TObject *Sender);
        void __fastcall ckApportionMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckUnitLeaseCostMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckLeaseCostMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckCanLeaseMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckSaleAreaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckPreSaleAreaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ckRightAreaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
        String RegKey;
//        TRoomGridSetting *FRoomGridSetting;
		TRoomGrid *FRoomGrid;
		void __fastcall SetData();
        void __fastcall GetRowHeightAgaint();
public:		// User declarations
		__fastcall TfrmRoomGridSet(TComponent* Owner ,TRoomGrid *RoomGrid,String Key=RoomGridSettingKey);
        static void  RestoreData(TRoomGrid * RoomGrid,TRoomGridSetting * RoomGridSetting);
        static void  BackupData(TRoomGrid * RoomGrid,TRoomGridSetting * RoomGridSetting);
		static void  LoadDataFromRegistry(TRoomGrid * RoomGrid, String Key = RoomGridSettingKey);
		static void  SaveToRegistry(TRoomGrid * RoomGrid, String Key = RoomGridSettingKey);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRoomGridSet *frmRoomGridSet;
//---------------------------------------------------------------------------
#endif
