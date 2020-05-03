//---------------------------------------------------------------------------

#ifndef ZgridH
#define ZgridH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include "ZGrids.hpp"
#include "PubEnum.h"
#include "vclComFunc.h"
#include <winuser.h>
//---------------------------------------------------------------------------
enum TEditType{ zNone, zEdit, zComboBox, zDateTime, zComboList, zDropGrid };
enum TColHorAlign{haLeft, haRight, haCenter};
enum TRowVerAlign{vaTop, vaMiddle, vaBottom};
enum TColSort{csNone, csAsc, csDesc};

class DELPHICLASS TZColumn;
class DELPHICLASS TZColumns;
class DELPHICLASS TZFooter;
class DELPHICLASS TZFooters;
class DELPHICLASS TRowFontItem;
class DELPHICLASS TRowFonts;
class DELPHICLASS TZGrid;
class TZInplaceEdit;

typedef void __fastcall (__closure *TGetCellStringEvent)(System::TObject* Sender,
                           long ACol, long ARow, String &AString, bool &Result);
typedef void __fastcall (__closure *TColumnEvent)(TZGrid* Grid,
                           TZColumn* AColumn);
typedef void __fastcall (__closure *TButtonDownEvent)(TZGrid* Grid,
                           TZColumn* AColumn, bool &DoDefault);
typedef void __fastcall (__closure *TFormatFootText)(int ACol,int ARow, double value,String &NewValue);

typedef void __fastcall (__closure *TOnCellExitEvent)(int ACol,int ARow,String Vlaue);

typedef void __fastcall (__closure *TOnChangeEvent)(System::TObject* Sender);
class TZGridEditor : public TBYInplaceEdit
{
private:
     TSpeedButton *FButton;
     TNotifyEvent __fastcall GetOnButtonClick();
	 void __fastcall SetOnButtonClick(TNotifyEvent AEvent);
protected:
public:
     __fastcall TZGridEditor(TComponent*AOwner);
	 virtual __fastcall ~TZGridEditor();
     void InitEditor(TEditType);
     __property TNotifyEvent OnButtonClick = {read=GetOnButtonClick, write=SetOnButtonClick};
};

class TZColumn : public TCollectionItem
{
	  friend TZGrid;
private:
	  String   FValidChar;
      String   FDefaultValue;
      String FTitle;
      TFont *FTitleFont;
      TEditType FEditType;
      TZColumns *FZColumns;
      TStrings *FListItem;
	  TZGrid* FDropGrid;
	  TColHorAlign FColHorAlign;
      TRowVerAlign FRowVerAlign;
      TColSort FColSort;
      String FSortField;
      TZCharType FCharType;
      TZCharCase FCharCase;
	  TZComboBoxItemIndex FKeyItem;
	  int       FDigLen;
      int       FMaxLen;
	  bool FMerged;
      int FRowMergeCount;
      int FRowMergeOrder;
      int FColMergeCount;
      int FColMergeOrder;
      bool FColumnVisible;
      int FHideColWidth;
      TButtonDownEvent    FOnButtonDown;
      TOnChangeEvent FOnChange;

      bool FEditButtonVisible;
      int FCurListItemIndex;
      String FFootText;
      TZCalculateType FCalType;
      TFont* FFootFont;
        bool FMultyLine;
      void __fastcall SetEditButtonVisible(bool value);
      Variant __fastcall GetComboxItems(int index);
      void __fastcall SetFootText(String value);
      void __fastcall SetCalType(TZCalculateType value);
      void __fastcall SetFootFont(TFont* value);
        void __fastcall SetMultyLine(bool value);
protected:
      void __fastcall SetDigLen(int Len);
      TColHorAlign __fastcall GetColHorAlign();
      void __fastcall SetColHorAlign(TColHorAlign ColHorAlign);
      TRowVerAlign __fastcall GetRowVerAlign();
      void __fastcall SetRowVerAlign(TRowVerAlign RowVerAlign);
      TColSort __fastcall GetColSort();
      void __fastcall SetColSort(TColSort ColSort);
      String __fastcall GetSortField();
      void __fastcall SetSortField(String ColSort);
      TZCharType __fastcall GetCharType();
      void __fastcall SetCharType(TZCharType CharType);
      TZCharCase __fastcall GetCharCase();
      void __fastcall SetCharCase(TZCharCase CharCase);
      String __fastcall GetTitle();
      void __fastcall SetTitle(String Title);
      int __fastcall GetColWidth();
      void __fastcall SetColWidth(int value);
      TFont* __fastcall GetTitleFont();
      void __fastcall SetTitleFont(TFont *value);
      TEditType __fastcall GetEditType();
      void __fastcall SetEditType(TEditType value);

      void __fastcall SetColumnVisible(bool value);

      void __fastcall SetMerged(bool value);
      void __fastcall SetRowMergeCount(int value);
      void __fastcall SetRowMergeOrder(int value);
      void __fastcall SetColMergeCount(int value);
      void __fastcall SetColMergeOrder(int value);

public:
      __fastcall virtual TZColumn(TCollection* Collection);
      __fastcall virtual ~TZColumn();
      void __fastcall AddListItem(String DispItem,String Item1="",String Item2="",String Item3="",String Item4="",String Item5="",String Item6="");
      void __fastcall DeleteListItem(int index);
      void __fastcall ClearListItem();
      virtual void __fastcall Assign(TPersistent * Source);
      int __fastcall LocateComboxByKey(Variant varValue);
      void __fastcall SetDefaultValue();
      __property TStrings* ListItem = {read=FListItem};
      __property int HideColWidth = {read=FHideColWidth,write=FHideColWidth,default=50};
      __property int CurListItemIndex  = { read=FCurListItemIndex,write=FCurListItemIndex };
      __property Variant ComboxItems[int index]  = { read=GetComboxItems};
__published:
    __property TEditType EditType={read=GetEditType,write=SetEditType};//编辑所用的构件类型
    __property TFont * ColumnFont={read=GetTitleFont,write=SetTitleFont};//列显示字体
    __property TColHorAlign ColHorAlign={read=GetColHorAlign,write=SetColHorAlign};//文字行显示排列规则，左中右
    __property TRowVerAlign RowVerAlign={read=GetRowVerAlign,write=SetRowVerAlign,default=vaMiddle};//文字列显示排列规则，上中下
    __property TColSort ColSort={read=GetColSort,write=SetColSort,default=csNone};//目前列所处的排序方式，顺序还是逆序
    __property String SortField={read=GetSortField,write=SetSortField};//排列字段，邦定数据集才有效
	__property TZCharType CharType={read=GetCharType,write=SetCharType,default=TZCharType::ctNormal}; //输入字符范围
	__property TZCharCase CharCase={read=GetCharCase,write=SetCharCase,default=ccNormal};//大小写
	__property TZComboBoxItemIndex KeyItem={read=FKeyItem,write=FKeyItem};//如果该列是多列相关填充，起定位作用的列序号

    __property String TitleString={read=GetTitle,write=SetTitle};//标题
    __property int ColumnWidth={read=GetColWidth,write=SetColWidth,default=50};//该列宽度
    __property bool Merged={read=FMerged,write=SetMerged,default=false};//是否合并，结合下面四个参数一起作用
    __property int RowMergeCount={read=FRowMergeCount,write=SetRowMergeCount,default=1};//行合并数
    __property int RowMergeOrder={read=FRowMergeOrder,write=SetRowMergeOrder,default=0};//行合并起始行号
    __property int ColMergeCount={read=FColMergeCount,write=SetColMergeCount,default=1};//列合并数
    __property int ColMergeOrder={read=FColMergeOrder,write=SetColMergeOrder,default=0};//列合并起始列号
    __property bool ColumnVisible={read=FColumnVisible,write=SetColumnVisible,default=true};//是否显示或打印该列
    __property bool EditButtonVisible  = { read=FEditButtonVisible, write=SetEditButtonVisible,default=false};//是否现实按钮
    __property int DigLen={read=FDigLen,write=SetDigLen};//小数位数
    __property int MaxLen={read=FMaxLen,write=FMaxLen};    //最长字符数，为0时无限制
    __property String ValidChar = {read=FValidChar, write=FValidChar};//校验字符，控制输入
    __property TZGrid* DropGrid = {read=FDropGrid, write=FDropGrid}; //下拉显示的列表
    __property TButtonDownEvent    OnButtonDown = {read=FOnButtonDown, write=FOnButtonDown};//当按下按钮时
    __property TOnChangeEvent    OnChange = {read=FOnChange, write=FOnChange};//当内容改变后执行
    __property String FootText  = { read=FFootText, write=SetFootText };//汇总行显示内容
    __property TZCalculateType CalType  = { read=FCalType, write=SetCalType };//统计类型
    __property TFont* FootFont  = { read=FFootFont, write=SetFootFont };//汇总行字体
    __property bool MultyLine  = { read=FMultyLine, write=SetMultyLine };  //该列是否显示多行模式
};

class TZColumns : public TCollection
{
private:
      TZGrid *FGrid;
protected:
      DYNAMIC TPersistent* __fastcall GetOwner(void);
      TZColumn* __fastcall GetColumn(int Index);
      void __fastcall SetColumn(int Index, TZColumn* Value);
public:
      virtual void __fastcall Assign(TPersistent * Source);
      __fastcall TZColumns(TZGrid *mGrid,TMetaClass* ItemClass);
	  __property TZGrid *ZGRID={read=FGrid};
      __property TZColumn* Items[int Index] = {read=GetColumn, write=SetColumn};
__published:

};
class TRowFontItem : public TCollectionItem
{
private:
  TRowFonts *FRowFonts;
protected:
  TFont* FFont;
  void __fastcall SetRowFont(TFont *value);
public:
  virtual void __fastcall Assign(TPersistent * Source);
  __fastcall virtual TRowFontItem(TCollection* Collection);
  __fastcall virtual ~TRowFontItem();
__published:
  __property TFont* Font = {read=FFont, write=SetRowFont};
};
class TRowFonts:public TCollection
{
private:
      TZGrid *FGrid;
protected:
      DYNAMIC TPersistent* __fastcall GetOwner(void);
      TRowFontItem* __fastcall GetFontItem(int Index);
      void __fastcall SetFontItem(int Index, TRowFontItem* Value);
public:
      void __fastcall TRowFonts::Assign(TPersistent * Source);
      __fastcall TRowFonts(TZGrid *mGrid,TMetaClass* ItemClass);
	  __property TZGrid *ZGRID={read=FGrid};
      __property TRowFontItem* Items[int Index] = {read=GetFontItem, write=SetFontItem};
__published:
};

class TMYPopupForm;
class TZInplaceEdit : public TBYInplaceEdit
{
      friend TZGrid;
      friend TMYPopupForm;
private:
      virtual void __fastcall BoundsChanged(void);
	  TZColumn* FEditColumn;
      int        FEditRow;
      String FBackDate;

      TSpeedButton *FListButton;
      TSpeedButton *FEditButton;      
      TForm*        FDropForm;
      virtual void __fastcall ListButtonClick(TObject *Sender);

      void InitForEdit();
      void __fastcall ShowListItems(TRect ARect);

      DYNAMIC void __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
	  DYNAMIC void __fastcall KeyPress(Char &Key);
      void __fastcall WMChar(TWMKeyUp&Message);
      void __fastcall WMKeyDown(TWMKey&Message);
  BEGIN_MESSAGE_MAP
     VCL_MESSAGE_HANDLER(WM_CHAR,TWMChar,WMChar);
     VCL_MESSAGE_HANDLER(WM_KEYDOWN,TWMKey,WMKeyDown);
  END_MESSAGE_MAP(TBYInplaceEdit);

      __fastcall TZInplaceEdit(Classes::TComponent* AOwner);
public:
      __fastcall ~TZInplaceEdit();
      __property Grid;
      __property Font;
};
typedef void __fastcall (__closure *TGridExpandEvent)(TObject* Sender, int ACol,int ARow, bool& CanExpand);
class PACKAGE TZGrid : public TBYStringGrid
{
  friend TZInplaceEdit;
private:
  Graphics::TColor FCurrRowColor;
  Graphics::TColor FSelectColor;
  Graphics::TColor FEvenGridColor;
  Graphics::TColor FOddGridColor;
  int FDriveBySelectCell;
        int __fastcall GetFixedRows();
        void __fastcall SetFixedRows(int value);
        int __fastcall GetFixedCols();
        void __fastcall SetFixedCols(int value);
        int __fastcall GetColCount();
        void __fastcall SetColCount(int value);
        int __fastcall GetRowCount();
        void __fastcall SetRowCount(int value);
        String __fastcall GetFormatStr();
        void __fastcall SetFormatStr(String value);
        TZColumns *FZColumns;
        TRowFonts *FRowFonts;
        void __fastcall SetColumns(TZColumns * value);
        String __fastcall GetTextMatrix(int ARow,int ACol);
        void __fastcall SetTextMatrix(int ARow,int ACol,String S);
        void __fastcall SetSelectColor(Graphics::TColor value);
        void __fastcall SetEvenGridColor(Graphics::TColor value);
        void __fastcall SetOddGridColor(Graphics::TColor value);
        void __fastcall SetReadOnly(bool value);
        TNotifyEvent FOnListClick;
        void __fastcall EventMessage(TMessage &message);
  void __fastcall SetFullFill(bool value);
  void __fastcall DrawOutGridCell(void);
  String __fastcall GetRowString(int iRow);
  void __fastcall SetRowString(int iRow,String value);

        bool FReadOnly;
        bool FHighLight;
        int  FFixedRows;
        int  FFixedCols;
        bool FFullFill;
        bool FAllowSort;
        TGetCellStringEvent FOnGetCellString;
        TColumnEvent        FOnSort;
        int  FExpandFoldColIndex;
        TGridExpandEvent FOnExpand;
        TFormatFootText FOnFormatFootText;
        TColor FFooterColor;
        TOnCellExitEvent    FOnCellExit;
        bool FReadSaveWidth;
        int __fastcall GetExpandFoldColIndex();
        void __fastcall SetExpandFoldColIndex(int ACol);
        void DrawExpandFold(HDC dc, int X, int Y, bool Expanded);
        void DrawExpandFoldCell(const TRect &ARect, String& AString, int Layer, int ExpandType, int y);
        void SetLayer(int ARow, int Value);
        int GetLayer(int ARow);
        void ExpandMouseDown(int ACol, int ARow, int MouseX, int MouseY, TMessage& AMsg);
        int ExpandGetRowIndex(int ARow);
        void ReIndexRowIndex();
        void __fastcall SetIsFilled(int __index, int value);
        int __fastcall GetIsFilled(int __index);
        void __fastcall SetRowState(int __index, int value);
        int __fastcall GetRowState(int __index);
        void __fastcall WMKeyDown(TWMKey & Message);
		double __fastcall CalcauteFootSum(int ColIndex,TZCalculateType fCalType);
        void __fastcall DrawFootText(int ColIndex, TRect ARect);
        void __fastcall SetFooterColor(TColor value);
        String __fastcall TZGrid::SetCurrRowColor(TColor AColor);
        enum TMouseAct {maNone, maDragRow, maDragSelect};
        TMouseAct FMouseAct;
        int  FDragRowOldY;
        int  FDragOldRow;
        TColor FWarningColor;
  void __fastcall SetWarningColor(TColor value);
  String __fastcall GridSelfID();

protected:
        virtual TBYInplaceEdit* __fastcall CreateEditor(void);
        DYNAMIC bool __fastcall CanEditAcceptKey(Char Key);
        DYNAMIC bool __fastcall CanEditModify(void);
        virtual bool __fastcall CanEditShow(void);
        virtual void __fastcall DrawCell(int ACol, int ARow, const TRect &ARect, TBYGridDrawState AState);
        void DrawCell(int ACol, int ARow, const TRect &ARect);
        void DrawTopFixed(int ACol, int ARow, const TRect &ARect);
        void DrawLeftFixed(int ACol, int ARow, const TRect &ARect);
        virtual bool __fastcall SelectCell(int ACol, int ARow);
        virtual int __fastcall CalculatePos(int ACol,int ARow,String s,int align);
        DYNAMIC void __fastcall TopLeftChanged(void);
        DYNAMIC void __fastcall ColWidthsChanged(void);
        DYNAMIC void __fastcall RowHeightsChanged(void);
        virtual void __fastcall Paint(void);

        void __fastcall WMHScroll(TWMScroll &Msg);
        void __fastcall WMVScroll(TWMScroll &Msg);
        void __fastcall WMLButtonDown(TMessage &Msg);
        void __fastcall WMLButtonUp(TMessage &Msg);
        void __fastcall WMLButtonDblClk(TMessage &Msg);
        void __fastcall WMRButtonUp(TMessage &Msg);

        virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
        void __fastcall ReadItems(TStream* Stream);
        void __fastcall ReadVersion1(TStream*Stream);
        void __fastcall WriteItems(TStream* Stream);
public:
  __fastcall TZGrid(TComponent* Owner);
  __fastcall ~TZGrid();

  void __fastcall DeleteProperty();
  void __fastcall ReadProperty();
  void __fastcall SaveProperty();
  double __fastcall Mod(double x,double y);
  void __fastcall CopyCols(int sCol,int dCol);//复制scol列内容到dCol列
  int __fastcall LocateGrid(int pCol,String Key);  //用单列值定位
  int __fastcall LocateGrid(String KeyCols,String Key);  //用多列值定位
  virtual void __fastcall DeleteColumn(int ACol);            //删除某列，尽量少用
  virtual void __fastcall DeleteRow(int ARow);       //删除行
  void __fastcall AddItem(String S,int index=-1);    //增加行
  void __fastcall ChangeItem(String S,int index);  //改变行内容
  void __fastcall RemoveItem(int index);   //删除某行
  void __fastcall WriteTextEh(HDC dc, TRect ARect, bool FilledRect,
    String Text, TAlignment Alignment, TTextLayout Layout, bool
	  MultyL, bool EndEllipsis, int LeftMarg=0, int RightMarg=0, bool
    ARightToLeftAlignment=false, bool ARightToLeftReading=false);

  void HideEditor() { TBYStringGrid::HideEditor(); }
  
  __property String TextMatrix[int ARow][int ACol]={read=GetTextMatrix,write=SetTextMatrix};
  __property int Layer[int ARow] = {read=GetLayer, write=SetLayer};//层级，从0级开始
  __property int IsFilled[int ARow]  = { read=GetIsFilled, write=SetIsFilled}; //改行已填充，层级中有效
  __property int RowState[int ARow]  = { read=GetRowState, write=SetRowState};//行状态，为1时，该行文字颜色为WarningColor;
  __property String RowStrings[int ARow] = {read=GetRowString, write=SetRowString};
  __property RowHeights;
  __property ColWidths;

  TFont* __fastcall RowStateFont(int ARow);
  void Expand(int ARow);//展开该行
  void Fold(int ARow);//合龙该行
  //ExpandType 0:None 1:Expanded 2:Folded
  int ExpandFoldMark(int ARow); //返回该行的类型
  void __fastcall ReCalculate(int ACol,int ARow);//根据每列的统计类型重新运算
  TRichEdit *RichEdit;
  TForm* DropDownForm;

  BEGIN_MESSAGE_MAP
    VCL_MESSAGE_HANDLER(WM_USER+110, TMessage, EventMessage);
    VCL_MESSAGE_HANDLER(WM_VSCROLL, TWMScroll, WMVScroll);
    VCL_MESSAGE_HANDLER(WM_HSCROLL, TWMScroll, WMHScroll);
    VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN, TMessage, WMLButtonDown);
    VCL_MESSAGE_HANDLER(WM_LBUTTONUP, TMessage, WMLButtonUp);
	VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TMessage, WMLButtonDblClk);
    VCL_MESSAGE_HANDLER(WM_RBUTTONUP, TMessage, WMRButtonUp);
    VCL_MESSAGE_HANDLER(WM_KEYDOWN, TWMKey, WMKeyDown);
  END_MESSAGE_MAP(TBYStringGrid);
__published:
  __property bool ReadSaveWidth={read=FReadSaveWidth,write=FReadSaveWidth};
  __property Graphics::TColor SelectColor={read=FSelectColor,write=SetSelectColor,default=clGreen};
  __property Graphics::TColor EvenGridColor={read=FEvenGridColor,write=SetEvenGridColor,default=clWhite};
  __property Graphics::TColor OddGridColor={read=FOddGridColor,write=SetOddGridColor,default=clSkyBlue};
  __property int FixedRows={read=GetFixedRows,write=SetFixedRows,default=1};
  __property int FixedCols={read=GetFixedCols,write=SetFixedCols,default=1};
  __property int ColCount = {read=GetColCount, write=SetColCount, default=5};
  __property String FormatStr={read=GetFormatStr,write=SetFormatStr};  //格式显示单元内容 ，未实现
  __property TZColumns * Columns={read=FZColumns,write=SetColumns}; //
  __property bool ReadOnly={read=FReadOnly,write=SetReadOnly,default=true};//
  __property bool HighLight={read=FHighLight,write=FHighLight,default=false};//未实现
  __property TNotifyEvent OnListClick={read=FOnListClick,write=FOnListClick};//当该列下拉选中时
  __property bool FullFill={read=FFullFill,write=SetFullFill,default=true};  //是否要画额外的行和列
  __property bool AllowSort={read=FAllowSort,write=FAllowSort};//是否允许排序

  __property TRowFonts *RowFonts = {read=FRowFonts,write=FRowFonts};
  __property TGetCellStringEvent OnGetCellString = {read=FOnGetCellString, write=FOnGetCellString};//获取cells[][]内容时
  __property TColumnEvent        OnSort = {read=FOnSort, write=FOnSort};//排序时
  __property int ExpandFoldColIndex = {read=GetExpandFoldColIndex, write=SetExpandFoldColIndex, default=-1};//层级显示的列位置
  __property TGridExpandEvent OnExpand  = { read=FOnExpand, write=FOnExpand };//有层级的节点展开时
  __property TFormatFootText OnFormatFootText  = { read=FOnFormatFootText, write=FOnFormatFootText };
  __property TColor FooterColor  = { read=FFooterColor, write=SetFooterColor };//汇总行颜色
  __property TColor CurrRowColor = {  read= FCurrRowColor, write=SetCurrRowColor}; //
	__property HasFooter;//显示汇总行
	__property FootHeight;//汇总行高度
	__property FixedRowHeight;  //固定行高度，与默认行高区分
	__property AutoCal;     //自动运算标志
	__property OnEditControlChange;//当cells[][]里内容改变时触发
  __property TColor WarningColor  = { read=FWarningColor, write=SetWarningColor }; //警告颜色，当该行RowState[ARow]=1时用该颜色画文字
  
};
#endif
