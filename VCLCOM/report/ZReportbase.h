//---------------------------------------------------------------------------

#ifndef ZReportbaseH
#define ZReportbaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "frxClass.hpp"
#include "frxDesgn.hpp"
#include "frxPreview.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include "frxDBSet.hpp"
#include <ADODB.hpp>
#include "ZStatusBar.h"
#include "ZComboBox.h"
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "frxExportImage.hpp"
#include "frxExportPDF.hpp"
#include "frxExportRTF.hpp"
#include "frxExportXLS.hpp"
#include <Menus.hpp>
#include "frxBarcode.hpp"
#include "frxChart.hpp"
#include "frxChBox.hpp"
#include "frxCross.hpp"
#include "frxDCtrl.hpp"
#include "frxGradient.hpp"
#include "frxOLE.hpp"
#include "frxRich.hpp"
//---------------------------------------------------------------------------
typedef  void __fastcall (__closure * TOnBeforDesig)(TfrxReport* Report);
typedef  void __fastcall (__closure * TOnGetValue)( String VarName,Variant &Value);
typedef  void __fastcall (__closure * TOnUserDefineFunction)( String MethodName, Variant &Params,Variant &retValue);
typedef  void __fastcall (__closure * TOnGetVariables)(TfrxVariables *Variables);
typedef  void __fastcall (__closure * TOnSetFieldAliases)(TfrxDBDataset *,TfrxDBDataset *);
typedef  void __fastcall (__closure * TOnSaveReport)(TMemoryStream * AMemoryStream,String AFilePath );
typedef  void __fastcall (__closure * TOnAfterExportReport)(String pFullFileName); //add by ljh at 2010.1.29
class TFRPBaseForm : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList1;
        TfrxDesigner *frxDsg;
        TfrxPreview *frxPreview;
        TZStatusBar *STBBottom;
		TToolBar *ToolBar1;
        TToolButton *TBtEdit;
        TToolButton *TBtPreview;
        TToolButton *TBtPrint;
        TToolButton *TbtFirst;
        TToolButton *TbtPre;
        TToolButton *TbtNext;
        TToolButton *TbtLast;
        TToolButton *TbtBig;
        TToolButton *TbtSmaill;
        TToolButton *TbtFact;
		TfrxReport *frxRpt;
        TDataSource *M_DataSource;
        TDataSource *D_DataSource;
        TDataSource *D_DataSource2;
        TfrxDBDataset *frxMDataSet;
        TfrxDBDataset *frxDDataSet;
        TfrxDBDataset *frxDBDataset1;
        TADODataSet *FMDataSet;
        TADODataSet *FDDataSet;
        TADODataSet *FDDataSet2;
        TPopupMenu *PopupMenu1;
        TMenuItem *Excel1;
        TMenuItem *Word1;
        TMenuItem *Jpg1;
        TMenuItem *PDF1;
        TfrxPDFExport *frxPDFExport1;
        TfrxRTFExport *frxRTFExport1;
        TfrxJPEGExport *frxJPEGExport1;
        TfrxXLSExport *frxXLSExport1;
        TToolButton *TBTImport;
        TfrxDialogControls *frxDialogControls1;
        TfrxChartObject *frxChartObject1;
        TfrxCrossObject *frxCrossObject1;
        TfrxCheckBoxObject *frxCheckBoxObject1;
        TfrxBarCodeObject *frxBarCodeObject1;
        TfrxOLEObject *frxOLEObject1;
        TfrxRichObject *frxRichObject1;
				TfrxGradientObject *frxGradientObject1;
        void __fastcall TBtEditClick(TObject *Sender);
        void __fastcall TBtPreviewClick(TObject *Sender);
        void __fastcall TBtPrintClick(TObject *Sender);
        void __fastcall TbtFirstClick(TObject *Sender);
        void __fastcall TbtPreClick(TObject *Sender);
        void __fastcall TbtNextClick(TObject *Sender);
        void __fastcall TbtLastClick(TObject *Sender);
        void __fastcall TbtBigClick(TObject *Sender);
        void __fastcall TbtSmaillClick(TObject *Sender);
        void __fastcall frxPreviewPageChanged(TfrxPreview *Sender,
          int PageNo);
        void __fastcall TbtFactClick(TObject *Sender);
        void __fastcall frxRptGetValue(const String VarName,
          Variant &Value);
        void __fastcall frxRptBeginDoc(TObject *Sender);
        Variant __fastcall frxRptUserFunction(const String MethodName,
          Variant &Params);
        void __fastcall Excel1Click(TObject *Sender);
        void __fastcall Word1Click(TObject *Sender);
        void __fastcall Jpg1Click(TObject *Sender);
        void __fastcall PDF1Click(TObject *Sender);

private:	// User declarations
   double FZoom;
   String FReportPath;      //报表存放的路径+报表名；
   String FCaption;
   String FMDLinkString;
   String FMDLinkString2;
   void __fastcall SetMDLinkStr(String ALinkStr);
   void __fastcall SetMDLinkStr2(String ALinkStr);
   void __fastcall SetReportPath(String  AReportPath);
   void __fastcall SetMDataSet(String AMDataSet);
   void __fastcall SetDDataSet(String ADDataSet);
   void __fastcall SetDDataSetOther(String ADDataSetOther);
   TColor __fastcall  GetTitleColor();
   void __fastcall SetTitleColor(TColor AColor);
   void __fastcall SetCaption(String ACaption);
   String __fastcall GetLinkString(String LinkString,int Atype);
   String __fastcall GetBigMoney(double Amount);//返回大写数字
   String __fastcall Num2Str(int ANum);
   TOnGetValue  FOnGetValue;
   TOnGetVariables FOnGetVariables;
   TOnSaveReport FOnSaveReport;
   TOnUserDefineFunction FOnUserDefineFunction;
	 TOnSetFieldAliases FOnSetFieldAliases;
	 TOnAfterExportReport FOnAfterExportReport; //add by ljh at 2010.1.29
	 TOnBeforDesig FOnBeforDesig;
public:		// User declarations
    void __fastcall ShowReport();
    __property TOnSetFieldAliases OnSetFieldAliases={write = FOnSetFieldAliases, read = FOnSetFieldAliases};
    __property String  MDLinkString2 ={write=SetMDLinkStr2,read=FMDLinkString2};
    __property String  MDLinkString ={write=SetMDLinkStr,read=FMDLinkString};
    __property String  Reportpath={write= SetReportPath,read=FReportPath};
    __property String  MDataSet={write = SetMDataSet};
    __property String  DDataSet={write = SetDDataSet};
    __property String  DDataSetOther={write = SetDDataSetOther};
	__property TOnGetValue OnGetValue={write = FOnGetValue, read = FOnGetValue};
	__property TOnUserDefineFunction OnUserDefineFunction={write = FOnUserDefineFunction, read = FOnUserDefineFunction};
	__property TOnGetVariables  OnGetVariables ={write = FOnGetVariables,read = FOnGetVariables};
	__property TColor TitleColor={write = SetTitleColor,read =GetTitleColor};
		__property  TOnBeforDesig OnBeforDesig={write=FOnBeforDesig,read=FOnBeforDesig};
		__property TOnSaveReport OnSaveReport={write = FOnSaveReport, read = FOnSaveReport};
		__property TOnAfterExportReport OnAfterExportReport={write=FOnAfterExportReport, read=FOnAfterExportReport};//add by ljh at 2010.1.29
		__property String TitleCaption={write = SetCaption,read =FCaption};
    __fastcall TFRPBaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRPBaseForm *FRPBaseForm;
//---------------------------------------------------------------------------
#endif
