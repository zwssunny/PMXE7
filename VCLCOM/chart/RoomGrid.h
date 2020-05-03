//---------------------------------------------------------------------------

#ifndef RoomGridH
#define RoomGridH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
const String RoomGridSettingKey="RoomGridSetting"; //默认注册key,可能影响所有应用
//---------------------------------------------------------------------------
struct TSelRange  //单元选取的范围
{
    int StartFloor;  //起始楼层
    int EndFloor;    //结束楼层
    int StartUnit;   //起始单元号
	int EndUnit;     //结束单元号
};

struct TCells
{
  TCells():Status(6){DoubleLays=0;Selected=false;LeaseStatus=6;
    Code="";Title="";Detail="";HouseType="";Direction="";
    Area="";UseArea="";RoofGargdenArea="";Sight="";Fitment="";
    UpArea="";DownArea="";ApportionArea="";UnitPrice="";TotalCost="";
    UnitLeaseCost="";LeaseCost="";CanLease="";SaleArea="";PreSaleArea="";
    RightArea="";
  };
  String Code;  //编号
  String Title;  //标题栏显示
  String Detail;  // 细节栏显示
  String HouseType;//户型
  String Direction; //朝向
  String Area;      //建筑面积
  String UseArea;   //套内面积
  String SaleArea; //销售面积
  String PreSaleArea; //预售面积
  String RightArea; //产权面积
  String RoofGargdenArea;//平台面积
  String Sight;     //景观
  String Fitment;   //装修
  String UpArea;    //上层面积
  String DownArea;  //下层面积
  String ApportionArea; //分摊面积
  String UnitPrice; //单价
  String TotalCost; //单元总价
  int DoubleLays;       //是否复式
  int Status;   //单元状态
  bool Selected; //是否选中
  String UnitLeaseCost; //单位月租金
  String LeaseCost; //月租金
  String CanLease; //是否可出租(东苑使用)
  int LeaseStatus;   //租赁状态
};

class PACKAGE TRoomGridSetting  //销控表设置，可以调用THouseGrid:Setup(key)进行设置
{
public:
    bool AutoFill;  //单元格高度自动计算
    bool DisplaySight; //显示景观
    bool DisplayFitment; //显示装修
    bool DisplayDirection; //显示朝向
    bool DisplayArea;      //显示建筑面积， 如果单元是复式将显示上下层面积
    bool DisplayUseArea;  //显示套内面积， 如果单元是复式将显示上下层面积
    bool DisplaySaleArea; //销售面积
    bool DisplayRightArea; //产权面积
    bool DisplayPreSaleArea; //预售面积

    bool DisplayRoofGarden;//显示平台面积
    bool DisplayApportionArea; //分摊面积
    bool DisplayHouseType; //显示户型
    bool DisplayUnitPrice;  //单元单价
    bool DisplayTotalCost;  //单元总价
    bool DisplayDetail;    //显示功能（以前的细节栏）
    int  PrintAlign;       //文字排列方式
    int  RowHeight;        //单元格高度，当AutoFill=false时有效
    int  ColWidth;         //单元格宽度
    bool DisplayUnitLeaseCost; //单位月租金
    bool DisplayLeaseCost; //月租金
    bool DisplayCanLease; //是否可出租
};
class PACKAGE TRoomGrid : public TCustomGrid
{
private:
        int FFloorCount;  //楼层数
        int FUnitCount;   //每层户数
        //String FKeyField;  //数据缓存的关键字段
        bool FIsUnit;  //是否是单元间
        int __fastcall RowToFloor(int ARow); //将行数转为楼层数
        TFont *FTitleFont;  //标题栏的字体
        TFont *FDetailFont; //细节栏的字体
        TStringList* FFloorNames;
        bool FDisplaySight;
        bool FDisplayFitment;
        bool FDisplayDirection;
        bool FDisplayArea;
        bool FDisplayHouseType;
        bool FDisplayDetail;
        bool FUnitAutoFill;
        bool FDisplayUseArea;
        bool FDisplaySaleArea;
        bool FDisplayRightArea;
        bool FDisplayPreSaleArea;
        bool FDisplayUnitPrice;
        bool FDisplayTotalCost;
        bool FDisplayRoofGarden;
        bool FDisplayApportionArea;
        bool FDisplayUnitLeaseCost; //单位月租金
        bool FDisplayLeaseCost; //月租金
        bool FDisplaySale; //true显示销售状态,false显示租赁状态
        bool FDisplayCanLease;
        int FPrintAlign;
        int FFloorNameWidth;
        //bool FValid;  //选中的单元格是否有效
        //TPoint __fastcall CenterPos(TRect ARect, String ShowText);
        void __fastcall SetFloorCount(int Value);
        void __fastcall SetUnitCount(int Value);
        int __fastcall GetFloor();
        int __fastcall GetUnit();
        void __fastcall SetFloor(int Value);
        void __fastcall SetUnit(int Value);
        void __fastcall SetKeyField(String Value);
        void __fastcall SetIsUnit(bool Value);
        TSelRange __fastcall GetSelRange();
        int __fastcall GetColWidth();
        int __fastcall GetRowHeight();
        void __fastcall SetColWidth(int Value);
        void __fastcall SetRowHeight(int Value);
        void __fastcall SetTitleFont(TFont *Value);
        void __fastcall SetDetailFont(TFont *Value);
        void __fastcall SetDisplaySight(bool value);
        void __fastcall SetDisplayFitment(bool value);
        void __fastcall SetDisplayDirection(bool value);
        void __fastcall SetDisplayArea(bool value);
        void __fastcall SetDisplayHouseType(bool value);
        void __fastcall SetDisplayDetail(bool value);
        void __fastcall SetUnitAutoFill(bool value);
        void __fastcall SetGridHeightAndWidth();
        void __fastcall SetDisplayUseArea(bool value);
        void __fastcall SetDisplaySaleArea(bool value);
        void __fastcall SetDisplayPreSaleArea(bool value);
        void __fastcall SetDisplayRightArea(bool value);
        void __fastcall SetDisplayUnitPrice(bool value);
        void __fastcall SetDisplayTotalCost(bool value);
        void __fastcall SetDisplayRoofGarden(bool value);
        void __fastcall SetDisplayApportionArea(bool value);
        void __fastcall SetDisplayUnitLeaseCost(bool value);
        void __fastcall SetDisplayLeaseCost(bool value);
        void __fastcall SetDisplaySale(bool value);
        void __fastcall SetDisplayCanLease(bool value);
        void __fastcall SetPrintAlign(int Value);
        void __fastcall SetFloorNameWidth(int value);
        int __fastcall GetFloorNameWidth();
        bool __fastcall GetCellSelected(int ACol, int ARow);
        void __fastcall SetCellSelected(int ACol, int ARow,bool Selected);
        TColor __fastcall GetDisplayColor(int Status);
        void __fastcall SetDisplayColor(int Status,TColor newColor);

protected:
        virtual void __fastcall DrawCell(int ACol, int ARow, const TRect &ARect, Grids::
                                         TGridDrawState AState);
		void __fastcall DrawCellItem(HDC CanvasHandle,String sDrawText
                          ,TRect &DrawRect,UINT dpAlign);
        MESSAGE void __fastcall WMEraseBkGnd(Messages::TMessage &Message);
        DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
        DYNAMIC void __fastcall MouseDown(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
        DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
        DYNAMIC void __fastcall MouseUp(TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
public:

        __fastcall TRoomGrid(TComponent* Owner);
       __fastcall ~TRoomGrid();
        TCells *UnitRecord;  //第个单元格的数据
        TCells *GetCellData(int ACol, int ARow);
        String GetCellString(int ACol, int ARow);
        void __fastcall ReadSetting(String Key = RoomGridSettingKey);  //程序员可以初始化自己的设置
        void __fastcall SaveSetting(String Key = RoomGridSettingKey);  //保存自己的设置，可以在每个窗体设
                                                                     //不同的注册表key值
        void __fastcall SelectCells(int StartR, int EndR, int StartC,int EndC);
        void __fastcall ClearSelected();
        int __fastcall GetStatus(TCells * cell);
        __property TColor DisplayColor[int]={read=GetDisplayColor,write=SetDisplayColor};

        __property bool CellSelected[int][int]={read=GetCellSelected,write=SetCellSelected};

        //TBufferDataSet *Buffer;  //保存数据缓存
        __property int Floor={read=GetFloor,write=SetFloor}; //当前单元的楼层
        __property int Unit={read=GetUnit,write=SetUnit};  //当前单元的序号
        //__property String KeyField={read=FKeyField,write=SetKeyField};  //数据集的关键字段
        __property TSelRange SelRange={read=GetSelRange};
        __property bool IsUnit={read=FIsUnit,write=SetIsUnit,default=true};//是否是显示单元间
        //__property bool Valid={read=FValid};
        //String DetailField; //当前数据行应显示的字段
        //String TitleField;  //当前标题行应显示的字段
        //String StateField;  //当前每个单元格应显示的状态
        TColor TitleColor;    //标题栏的颜色
        TColor DispColor[10];  //单元格的颜色；1-未订、2-预留、3-已订、4-已售、5-出租、6-11不存在
		void __fastcall Setup(String Key = RoomGridSettingKey); //启动设置窗体,并把设置参数以Key为关键值保存到注册表；
        int UnitTitleHeight;//打印要访问，房号编号要用
        int StepLineHeight; //打印要访问，打印其他属性每行高度
        __property ColWidths;
        __property RowHeights;
        __property FixedRows;
        __property FixedCols;
        __property ColCount;
        __property RowCount;
        __property TStringList *FloorNames  = { read=FFloorNames, write=FFloorNames };//楼层自命名列表，从第1层排好序加入
        __property bool DisplaySight  = { read=FDisplaySight, write=SetDisplaySight };
        __property bool DisplayFitment  = { read=FDisplayFitment, write=SetDisplayFitment };
        __property bool DisplayDirection  = { read=FDisplayDirection, write=SetDisplayDirection };
        __property bool DisplayArea  = { read=FDisplayArea, write=SetDisplayArea };
        __property bool DisplayHouseType  = { read=FDisplayHouseType, write=SetDisplayHouseType };
        __property bool DisplayDetail  = { read=FDisplayDetail, write=SetDisplayDetail };
        __property bool UnitAutoFill  = { read=FUnitAutoFill, write=SetUnitAutoFill };
        __property bool DisplayUseArea  = { read=FDisplayUseArea, write=SetDisplayUseArea };
        __property bool DisplaySaleArea  =    { read=FDisplaySaleArea, write=SetDisplaySaleArea };
        __property bool DisplayPreSaleArea  = { read=FDisplayPreSaleArea, write=SetDisplayPreSaleArea };
        __property bool DisplayRightArea  =   { read=FDisplayRightArea, write=SetDisplayRightArea };
        __property bool DisplayUnitPrice  = { read=FDisplayUnitPrice, write=SetDisplayUnitPrice };
        __property bool DisplayTotalCost  = { read=FDisplayTotalCost, write=SetDisplayTotalCost };
        __property bool DisplayRoofGarden  = { read=FDisplayRoofGarden, write=SetDisplayRoofGarden };
        __property bool DisplayApportionArea  = { read=FDisplayApportionArea, write=SetDisplayApportionArea };

        __property bool DisplayUnitLeaseCost  = { read=FDisplayUnitLeaseCost, write=SetDisplayUnitLeaseCost };
        __property bool DisplayLeaseCost = { read=FDisplayLeaseCost, write=SetDisplayLeaseCost };
        __property bool DisplaySale = { read=FDisplaySale, write=SetDisplaySale };
        __property bool DisplayCanLease = { read=FDisplayCanLease, write=SetDisplayCanLease };

        __property int PrintAlign  = { read=FPrintAlign, write=SetPrintAlign };
        __property int FloorNameWidth  = { read=GetFloorNameWidth, write=SetFloorNameWidth };

BEGIN_MESSAGE_MAP
      VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TMessage, WMEraseBkGnd);
END_MESSAGE_MAP(TWinControl);
__published:
        __property int FloorCount={read=FFloorCount,write=SetFloorCount};
        __property int UnitCount={read=FUnitCount,write=SetUnitCount};
        __property int ColWidth={read=GetColWidth,write=SetColWidth};
        __property int RowHeight={read=GetRowHeight,write=SetRowHeight};
        __property TFont *TitleFont={read=FTitleFont,write=SetTitleFont};
        __property TFont *DetailFont={read=FDetailFont,write=SetDetailFont};
        __property Align;
        __property Anchors;
        __property BiDiMode;
        __property Color;
        __property DragCursor;
        __property DragKind;
        __property DragMode;
        __property Enabled;
        __property FixedColor;
        __property Font;
        __property Options;
        __property Visible;
        __property OnClick;
        __property OnDblClick;
        __property OnContextPopup;
        __property OnDragDrop;
        __property OnDragOver;
        __property OnEndDock;
        __property OnEndDrag;
        __property OnEnter;
        __property OnExit;
        __property OnKeyDown;
        __property OnKeyPress;
        __property OnKeyUp;
        __property OnMouseDown;
        __property OnMouseMove;
        __property OnMouseUp;
        __property OnMouseWheelDown;
        __property OnMouseWheelUp;
        __property OnStartDock;
        __property OnStartDrag;

};
//---------------------------------------------------------------------------
#endif
