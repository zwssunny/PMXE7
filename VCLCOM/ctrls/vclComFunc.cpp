//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "vclComFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
namespace Vclcomfunc{
void WriteInt(TStream* Stream, const int Value)
{
   Stream->Write(&Value, sizeof(int));
}
int ReadInt(TStream* Stream)
{
   int i;
   Stream->Read(&i, sizeof(int));
   return i;
}
void WriteDouble(TStream* Stream, const double Value)
{
   Stream->Write(&Value, sizeof(double));
}
double ReadDouble(TStream* Stream)
{
   double d;
   Stream->Read(&d, sizeof(double));
   return d;
}
String ReadString(TStream* Stream)
{
   int l = ReadInt(Stream);
   String r;
   r.SetLength(l);
   Stream->Read(r.c_str(), l*sizeof(Char));
   return r;
}
void WriteString(TStream* Stream, String AValue)
{
   int size= AValue.Length()*sizeof(Char);
   WriteInt(Stream, size);
   Stream->Write(AValue.c_str(), size);
}
void WriteStrings(TStream* Stream, TStrings* AValue)
{
   WriteInt(Stream, AValue->Count);
   for(int i = 0; i < AValue->Count; i++)
      WriteString(Stream, AValue->Strings[i]);
}
void ReadStrings(TStream* Stream, TStrings* AValue)
{
   AValue->Clear();
   int c = ReadInt(Stream);
   for(int i = 0; i < c; i++)
      AValue->Add(ReadString(Stream));
}
//--------------------------------------------------------------------
void Byte2ToChar3(BYTE*b, char*c)
{//byte*2 --> char*3
   c[0] = b[0] & 0x3f;
   c[1] = b[1] & 0x3f;
   c[2] = (b[0] >> 6) | ((b[1] & 0xc0) >> 4);
   c[0] = c[0] + 0x3c;
   c[1] = c[1] + 0x3c;
   c[2] = c[2] + 0x3c;
}
//char*3 --> byte*2
void Char3ToByte2(char*c, BYTE*b)
{
   c[0] = c[0] - 0x3c;
   c[1] = c[1] - 0x3c;
   c[2] = c[2] - 0x3c;
   b[0] = c[0] | ((c[2] & 0x03) << 6);
   b[1] = c[1] | ((c[2] & 0x0c) << 4);
}
//每2个字节转换为3个字符
char* StreamToString(TStream*AStream, int * R_Length)
{
   int Size = AStream->Size;
   *R_Length = (Size+Size%2)/2*3 + 6 + 1;
   BYTE* b = (unsigned char*)malloc(sizeof(BYTE)*(Size + Size % 2));
   char* c = (char*)malloc(sizeof(char)*(*R_Length));
   if(b == NULL || c == NULL)
      return "";
   char * cc = c;
   BYTE * cb = b;
   AStream->ReadBuffer(b, Size);
   //Size
   Byte2ToChar3((BYTE*)&Size, cc);
   cc += 3;
   Byte2ToChar3(((BYTE*)&Size) + 2, cc);
   cc += 3;
   //body
   for(int i = 0; i < (Size+Size%2)/2; i++)
   {
      Byte2ToChar3(cb, cc);
      cb+=2;
      cc+=3;
   }
   *cc = '\0';
   free(b);
   return c;
}
//每3个字符转换为2个字节
void StringToStream(TStream*AStream, char* AString)
{
   int Size;
   char*cc = AString;
   //Size
   Char3ToByte2(cc, ((BYTE*)(&Size)));
   cc += 3;
   Char3ToByte2(cc, ((BYTE*)(&Size)) + 2);
   cc += 3;
   //body
   BYTE* b = (BYTE*)malloc(sizeof(BYTE)*(Size+Size%2));
   if(b==NULL)
      return;
   BYTE* bc = b;
   for(int i = 0; i < (Size+Size%2)/2; i++)
   {
      Char3ToByte2(cc, bc);
      cc += 3;
      bc += 2;
   }
   AStream->WriteBuffer(b, Size);
   free(b);
}
//---------------------------------------------------------------------------
//   计算字符输出高度
//---------------------------------------------------------------------------
int  TextHeight(HDC dc, String Text)
{
   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1000;
   r.bottom = 1000;

   DrawText(dc, Text.c_str(), Text.Length(), &r, DT_CALCRECT);
   return r.bottom - r.top;
}
//---------------------------------------------------------------------------
//   计算字符输出宽度
//---------------------------------------------------------------------------
int  TextWidth(HDC dc, String Text)
{
   RECT r;
   r.top = 0;
   r.left = 0;
   r.right = 1000;
   r.bottom = 1000;
   DrawText(dc, Text.c_str(), Text.Length(), &r, DT_CALCRECT);
   return r.right - r.left;
}
//--------------------------------------------------------------------
//   画布文字输出
//---------------------------------------------------------------------------
void WarpTextOut(String Text, TRect ARect, TCanvas* ACanvas)
{
   SetTextAlign(ACanvas->Handle, TA_LEFT);
   String DText = Text;
   int TextHeight = ACanvas->TextHeight("mmm");
   if(TextHeight > ARect.Height())
	  return;
   int TextWidth;
   int DrawTop = ARect.Top;
   do{
	  for(int i = DText.Length(); i >= 1; i--)
	  {
		 if(ACanvas->TextWidth(DText.SubString(1, i)) < ARect.Width())
		 {
			ACanvas->TextOut(ARect.Left, DrawTop, DText.SubString(1, i));
			DrawTop += (TextHeight+2);
			DText.SubString(i, DText.Length()-i);
			break;
		 }
	  }
   }while(DText.Length()>0 && (DrawTop + TextHeight)< ARect.Bottom);
}
//--------------------------------------------------------------------
//   判断点是否在范围内
//---------------------------------------------------------------------------
bool MouseIn(POINT AP, TRect AR)
{
   if(AP.y < AR.Top)
	  return false;
   else if(AP.y > AR.Bottom)
	  return false;
   else if(AP.x < AR.Left)
	  return false;
   else if(AP.x > AR.Right)
	  return false;
   return true;
}
//---------------------------------------------------------------------------
//   TPointerArray
//---------------------------------------------------------------------------
TPointerArrayBase::TPointerArrayBase(PointerArrayOnDelete OnDelete, int MinCapability, int CapabilityInc)
			: FPoints(NULL)
{
 FCount=0;
 FCapability=0;
 FOnDelete=OnDelete;
 FMinCapability=MinCapability;
 FCapabilityInc=CapabilityInc;
}
//---------------------------------------------------------------------------
PointerArrayOnDelete TPointerArrayBase::SetOnDelete(PointerArrayOnDelete AValue)
{
    PointerArrayOnDelete old = FOnDelete;
    FOnDelete = AValue;
    return old;
}
//---------------------------------------------------------------------------
TPointerArrayBase::~TPointerArrayBase()
{
    Clear();
    if(FPoints)
         delete [] FPoints;
}
//---------------------------------------------------------------------------
void TPointerArrayBase::IncCapability()
{
    switch(FCapability)
    {
         case 0:
             FPoints = new void*[FMinCapability];
             FCapability = FMinCapability;
             break;
         default:
         {
             FCapability += FCapabilityInc;
             void**temp = new void*[FCapability];
             memcpy(temp, FPoints, FCount*sizeof(void*));
             delete [] FPoints;
             FPoints = temp;
             break;
         }
    }
}
//---------------------------------------------------------------------------
void TPointerArrayBase::DecCapability()
{
    if(FCapability - FCount > FCapabilityInc*2)
    {
         int NewCapability = FCapability;
         while(NewCapability - FCount > FCapabilityInc)
               NewCapability -= FCapabilityInc;
         void**temp = new void*[NewCapability];
         memcpy(temp, FPoints, FCount*sizeof(void*));
         delete [] FPoints;
         FPoints = temp;
         FCapability = NewCapability;
    }
}
//---------------------------------------------------------------------------
int TPointerArrayBase::Count()
{
     return FCount;
}
//---------------------------------------------------------------------------
int TPointerArrayBase::Add(void*AItem)
{
     if(FCapability - FCount <= 0)
         IncCapability();
     FPoints[FCount] = AItem;
     FCount++;
     return FCount-1;
}
//---------------------------------------------------------------------------
void TPointerArrayBase::Insert(void*AItem, int Index)
{
     if(Index >= 0 && Index <= FCount)
     {
          if(FCapability - FCount <= 0)
              IncCapability();
          MoveMemory(&(FPoints[Index+1]), &(FPoints[Index]),
                    sizeof(void*)*(FCount-Index));
          FPoints[Index] = AItem;
          FCount++;
     }else
     {
          throw Exception("TPointerArray::Insert 序号错误");
     }
}
//---------------------------------------------------------------------------
void TPointerArrayBase::DeleteByIndex(int Index)
{
    if(Index >= 0 && Index < FCount)
    {
         if(FOnDelete)
         {
              FOnDelete(FPoints[Index]);
         }
         MoveMemory(&(FPoints[Index]), &(FPoints[Index+1]),
                    sizeof(void*)*(FCount-Index-1));
         FCount--;
         DecCapability();
    }else
    {
         throw Exception("TPointerArray::Delete 序号错误");
    }
}
//---------------------------------------------------------------------------
int TPointerArrayBase::DeleteByItem(void*AItem)
{
    for(int i=0; i < FCount; i++)
    {
         if(FPoints[i] == AItem)
         {
              DeleteByIndex(i);
              return i;
         }
    }
    return -1;
}
//---------------------------------------------------------------------------
void TPointerArrayBase::RemoveByIndex(int Index)
{
    if(Index >= 0 && Index < FCount)
	{
         MoveMemory(&(FPoints[Index]), &(FPoints[Index+1]),
                    sizeof(void*)*(FCount-Index-1));
         FCount--;
         DecCapability();
    }else
    {
		 throw Exception("TPointerArray::Delete 序号错误");
    }
}
//---------------------------------------------------------------------------
int TPointerArrayBase::RemoveByItem(void*AItem)
{
    for(int i=0; i < FCount; i++)
    {
		 if(FPoints[i] == AItem)
         {
              RemoveByIndex(i);
              return i;
         }
    }
    return -1;
}
//---------------------------------------------------------------------------
int TPointerArrayBase::IndexOf(void*AItem)
{
    for(int i=0; i < FCount; i++)
    {
         if(FPoints[i] == AItem)
         {
              return i;
         }
    }
    return -1;
}
//---------------------------------------------------------------------------
void TPointerArrayBase::Clear()
{
   if(FOnDelete)
   {
         for(int i = 0; i < FCount; i++)
         {
			   FOnDelete(FPoints[i]);
         }
    }     
    FCount = 0;
    delete [] FPoints;
    FPoints = NULL;
    FCapability = 0;
}
//---------------------------------------------------------------------------
void TPointerArrayBase::Assign(const TPointerArrayBase&AArray)
{
    if(&AArray != this)
    {
         Clear();
         FCount = AArray.FCount;
         FCapability = AArray.FCapability;
         FPoints = new void*[FCapability];
         memcpy(FPoints, AArray.FPoints, sizeof(void*)*FCount);
         FOnDelete = AArray.FOnDelete;
    }
}
//---------------------------------------------------------------------------
__fastcall TItemObject::TItemObject()
{
     varObj= VarArrayCreate(OPENARRAY(int, (0, 6)), varVariant);
}

 __fastcall TItemObject::~TItemObject()
{
     varObj.Clear();
}

void __fastcall TItemObject::PutElement(Variant var, int index)
{
     varObj.PutElement(var,index);
}

Variant __fastcall TItemObject::GetElement(int index)
{
     return varObj.GetElement(index);
}

}
