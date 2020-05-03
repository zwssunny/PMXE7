//---------------------------------------------------------------------------

#include <basepch.h>

#pragma hdrstop

#include "JBCommentBinding.h"
#include <Dialogs.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------

namespace Jbcommentbinding
{
        void __fastcall PACKAGE Register()
        {
          IOTAKeyboardServices*  services;
          HRESULT  hr = BorlandIDEServices->QueryInterface (__uuidof (IOTAKeyboardServices), (void
					   **) &services);
//         if (FAILED (hr))
//          {
//            MessageBox(NULL,"创建不成功", "内部提示", MB_OK|MB_ICONERROR);
//            return;
//          }
		 services->AddKeyboardBinding(new TJBCommentBinding());
		}
}

//---------------------------------------------------------------------------


TBindingType __fastcall TJBCommentBinding::GetBindingType()
{
        return btPartial;
}

String __fastcall TJBCommentBinding::GetDisplayName()
{
        return "Multiline Commenting";
}

String __fastcall TJBCommentBinding::GetName()
{
        return "jbcomment";
}
HRESULT STDMETHODCALLTYPE TJBCommentBinding::QueryInterface(REFIID riid,
                               void __RPC_FAR *__RPC_FAR *ppvObject)
{
  if (IsEqualIID (riid, __uuidof (IUnknown)))
    *ppvObject = static_cast < IUnknown * >(this);
  else if (IsEqualIID (riid, __uuidof (IOTANotifier)))
    *ppvObject = static_cast < IOTANotifier * >(this);
  else if (IsEqualIID (riid, __uuidof (IOTAKeyboardBinding)))
    *ppvObject = static_cast < IOTAKeyboardBinding * >(this);

  if (*ppvObject != NULL)
    {
      reinterpret_cast < IUnknown * >(*ppvObject)->AddRef ();
      return S_OK;
    }

  return E_NOINTERFACE;
}
ULONG STDMETHODCALLTYPE TJBCommentBinding::AddRef()
{
  return InterlockedIncrement (&m_Count);
}
ULONG STDMETHODCALLTYPE TJBCommentBinding::Release()
{
  if (InterlockedDecrement (&m_Count) == 0)
    {
      delete this;
      return 0;
    }
  return m_Count;

}
void __fastcall TJBCommentBinding::BindKeyboard(const _di_IOTAKeyBindingServices BindingServices)
{
        BindingServices->SetDefaultKeyProc(DefaultKeyProc, NULL, "");
}
void __fastcall TJBCommentBinding::myCommentUncomment(IOTAEditPosition* iEditPos,int Row,int &startCol,int &startRow,int &endCol,int &endRow)
{
  iEditPos->Move(Row, 1);
  if (iEditPos->Read(2) == "//") // if commented then uncomment the line
   {
    //somehow, independent on the parameter, the .Delete() method only deletes
    //a single character, so we need to call it twice here. (Another IOTA bug ?)}
    iEditPos->Delete(1);
    iEditPos->Delete(1);
    //now move the selection to the left}
    if ((Row == startRow)&& (startCol != 1))
      startCol-=2;
    if ((Row == endRow)&& (endCol != 1))
      endCol-= 2;
   }
  else                          // otherwise comment the line
   {
     iEditPos->InsertText("//");
    //now move the selection to the right}
    if ((Row == startRow) && (startCol != 1))
         startCol+= 2;
    if ((Row == endRow)&&(endCol!= 1))
         endCol+= 2;
  }
}
void __fastcall TJBCommentBinding::JBComment(const _di_IOTAKeyContext Context, TShortCut KeyCode,TKeyBindingResult &BindingResult)
{
  _di_IOTAEditPosition iEditPos;
  _di_IOTAEditBlock iEditBlock;
  int startCol, endCol, startRow, endRow;
  int topViewRow, topViewColumn;
  int i;
  bool cursorAtStart;// is our cursor at the beginning of the selection
  BindingResult = krHandled;

  iEditBlock = Context->EditBuffer->EditBlock;
  if (!iEditBlock->IsValid) // do nothing if there is no selection
    return;

  //store the EditBlock's parameters:}
  startCol= iEditBlock->StartingColumn;
  endCol= iEditBlock->EndingColumn;
  startRow= iEditBlock->StartingRow;
  endRow= iEditBlock->EndingRow;

  iEditPos= Context->EditBuffer->EditPosition;
  //remember which side of the selection the cursor is at
  if ((iEditPos->Row == startRow) && (iEditPos->Column == startCol))
    cursorAtStart= true;
  else
    cursorAtStart= false;

  //and remember the top line viewed in the editor}
  topViewRow= Context->EditBuffer->TopView->TopRow;
  topViewColumn= Context->EditBuffer->TopView->LeftColumn;

  for(i= startRow; i<endRow;i++)
    myCommentUncomment(iEditPos,i,startCol,startRow,endCol,endRow);

  //process only if there is non-empty selection in the last row
  if ((endRow != startRow) && (endCol > 1))
    myCommentUncomment(iEditPos,endRow,startCol,startRow,endCol,endRow);
  //process anyway if the selection doesn't span more than a single row
  else if (endRow == startRow)
    myCommentUncomment(iEditPos,endRow,startCol,startRow,endCol,endRow);

  //now restore the selection and the cursor position
  if (cursorAtStart)
  {
    iEditPos->Move(endRow, endCol);
    iEditBlock->EndBlock();
    iEditPos->Move(startRow, startCol);
    iEditBlock->BeginBlock();
  }
  else
  {
    iEditPos->Move(startRow, startCol);
    iEditBlock->BeginBlock();
    iEditPos->Move(endRow, endCol);
    iEditBlock->EndBlock();
  }
  //restore the top row and left column - necessary for cases when you have
  //selections spanning more than a single page}
  Context->EditBuffer->TopView->SetTopLeft(topViewRow, topViewColumn);

}
TKeyboardState ArrayKeysState;
bool AreCorrectKeysPressed()
{
  int i;
  bool ctrlPressed,  slashPressed,  otherKeysPressed;
  ctrlPressed= false;
  slashPressed= false;
  otherKeysPressed= false;
  if (GetKeyboardState(ArrayKeysState))
  {
    for (i=0 ;i<= 255;i++)
    {
      //if the highest bit is set - see 'win32.hlp' for details on GetKeyboardState()}
      if ((ArrayKeysState[i] & 0x80) > 0)
      {
        switch(i)
        {
          case VK_CONTROL:
          case VK_LCONTROL:
          case VK_RCONTROL:
              ctrlPressed= true;
              break;
          case 191:
              slashPressed= true;
              break;
          default:
            otherKeysPressed= true;
            return false;

        } //end case
      }
    } //end for
    if (!otherKeysPressed && ctrlPressed && slashPressed)
      return  true;
  }
  return false;
}

void __fastcall TJBCommentBinding::DefaultKeyProc(const _di_IOTAKeyContext Context, TShortCut KeyCode, TKeyBindingResult &BindingResult)
{
 if (AreCorrectKeysPressed())
  {
    JBComment(Context, KeyCode, BindingResult);
    BindingResult= krHandled;
  }
  else
    BindingResult= krUnhandled;

}

__fastcall TJBCommentBinding::TJBCommentBinding()
    :IOTAKeyboardBinding()
{
          m_Count = 0;
}
