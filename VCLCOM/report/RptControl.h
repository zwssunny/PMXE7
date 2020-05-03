//---------------------------------------------------------------------------

#ifndef RptControlH
#define RptControlH
//---------------------------------------------------------------------------
struct PaperInfo{
   short Width;
   short Height;                                    
   short TopMargin;
   short BottomMargin;
   short LeftMargin;
   short RightMargin;
   char Name[30];
};
extern PaperInfo PaperInfos[12];
#endif

