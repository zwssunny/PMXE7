/***************************************************************************
  Copyright (c) 2002 MBLab

  Permission to use, copy, modify, distribute and sell this software
  and its documentation for any purpose is hereby granted without fee,
  provided that the above copyright notice appear in all copies and
  that both that copyright notice and this permission notice appear
  in supporting documentation.
  MBLab makes no representations about the suitability of this software
  for any purpose. It is provided "as is" without express or implied
  warranty.
***************************************************************************/

#include <stdio.h>
#include "lexer.h"

//----------------------------------------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------------------------------------
TLexTokens AndSet, AnyCharSet;

void CreateCharSets (void)
{
  AndSet << ltEof << ltRegChar << ltTab << ltNewLine << ltCarRet <<
         ltBackSpace << ltLiteral << ltOctalValue << ltHexValue <<
         ltDecValue << ltLeftBrack << ltNot << ltLeftParen << ltLeftBrace;

  AnyCharSet << ltRegChar << ltOctalValue << ltHexValue << ltDecValue <<
             ltTab << ltNewLine << ltCarRet << ltBackSpace << ltLiteral << ltEof;
}

//#pragma startup CreateCharSets 65

//----------------------------------------------------------------------------------------------------------
static void __fastcall ErrorAction (TLexer *ALexer)
{
  ALexer->ErrorAction ();
}

//----------------------------------------------------------------------------------------------------------
void __fastcall TNodeEntries::Add (int AKey,TLexNode* ANode)
{
  if (ANode == NULL || AKey < 0 || AKey < FBase) return;

  if (start == end) FBase = AKey;

  AKey -= FBase - 1; 

  int len = end - start;

  if (AKey > finish - start)
  {
    int size = (AKey/4 + 1) * 4;
    PLexNode *ptr = new PLexNode[size];

    memcpy (ptr,start,len*sizeof (PLexNode));
    memset (&ptr[len],0,(size - len)*sizeof (PLexNode));

    finish = ptr + size;
    end = ptr + len;

    delete [] start;

    start = ptr;
  }

  if (AKey > len) end = start + AKey;

  start[AKey - 1] = ANode;
}

//----------------------------------------------------------------------------------------------------------
__fastcall TNfaRoot::TNfaRoot (void) : Node (NULL),Type (0),Action (ErrorAction)
{
}

//----------------------------------------------------------------------------------------------------------
__fastcall TLexTree::TLexTree (TTokenInfo ATokenInfos[],int ATokenInfosSize) : TLexNodes ()
{
 CreateCharSets();//zws20080211, #pragma startup 优先级控制有问题,造成构造函数时出错.
  int i,Root;
  TNfaRoots NfaRoots;

  for (i=0; i<ATokenInfosSize; i++)
  {
    Root = ATokenInfos[i].RootIndex;

    while ((int)NfaRoots.size () <= Root) NfaRoots.push_back (TNfaRoot ());

    if (ATokenInfos[i].DescStr == NULL)
    {
      NfaRoots[Root].Type = ATokenInfos[i].Type;
      NfaRoots[Root].Action = ATokenInfos[i].Action;
    }
    else
    {
      try
      {
        if (NfaRoots[Root].Node == NULL) NfaRoots[Root].Node = Rule (&ATokenInfos[i]);
        else NfaRoots[Root].Node = NewNfaNode (NfaRoots[Root].Node,Rule (&ATokenInfos[i]));
      }
      catch (EExpression& e)
      {
        throw EExpression ("Expression: \"" + TTokenString ((char *)ATokenInfos[i].DescStr) + "\" has error!");
      }
    }
  }

  for (i = 0; i< (int)NfaRoots.size (); i++)
  {
    push_back ((NfaRoots[i].Node != NULL)?NfaToDfa (NfaRoots[i]):NULL);
  }

  ClearNfaList ();
}

__fastcall TLexTree::~TLexTree (void)
{
  for (unsigned int i=0; i<FNodesList.size (); i++) delete FNodesList[i];
}

void __fastcall TLexTree::ClearNfaList (void)
{
  for (unsigned int i=0; i<FNfaList.size (); i++) delete FNfaList[i];
  FNfaList.clear ();
}

TNfaNode *__fastcall TLexTree::NewNfaNode (void)
{
  TNfaNode *ANode = new TNfaNode ();

  ANode->Action = ErrorAction;
  ANode->Index = FNfaList.size ();
  FNfaList.push_back (ANode);

  return (ANode);
}

TNfaNode *__fastcall TLexTree::NewNfaNode (TNfaNode *ALeft,TNfaNode *ARight)
{
  TNfaNode *ANode = NewNfaNode ();

  ANode->Left = ALeft;
  ANode->Right = ARight;

  return (ANode);
}

void __fastcall TLexTree::GetLexToken (void)
{
  while (true)
  {
    FText.clear ();

    switch (*FPtr)
    {
      case 0   :
           FType = ltEnd;
           return;
      case ' ' :
      case '\n':
      case '\r':
      case '\t':
           FPtr++;
           break;
      case '\\':
           FPtr++;
           switch (*FPtr)
           {
             case '0' :
                  FText.add (*FPtr++);
                  if (*FPtr == 'X' || *FPtr == 'x')
                  {
                    FText.add (*FPtr++);
                    while (isdigit (*FPtr) || (*FPtr >= 'a' && *FPtr <= 'f') ||
                           (*FPtr >= 'A' && *FPtr <= 'F')) FText.add (*FPtr++);
                    FType = ltHexValue;
                    return;
                  }
                  else
                  {
                    while (*FPtr >= '0' && *FPtr <= '7') FText.add (*FPtr++);
                    FType = ltOctalValue;
                    return;
                  }
             case 't' :
                  FText.add ('\t');
                  FType = ltTab;
                  break;
             case 'n' :
                  FText.add ('\n');
                  FType = ltNewLine;
                  break;
             case 'r' :
                  FText.add ('\r');
                  FType = ltCarRet;
                  break;
             case 'b' :
                  FText.add ('\b');
                  FType = ltBackSpace;
                  break;
             default  :
                  if (*FPtr >= '1' && *FPtr <= '9')
                  {
                    FText.add (*FPtr++);
                    while (isdigit (*FPtr)) FText.add (*FPtr++);
                    FType = ltDecValue;
                    return;
                  }
                  else
                  {
                    FText.add (*FPtr);
                    FType = ltLiteral;
                    break;
                  }
           }
           FPtr++;
           return;
      default  :
           switch (*FPtr)
           {
             case '@' : FType = ltEof; break;
             case '{' : FType = ltLeftBrace; break;
             case '}' : FType = ltRightBrace; break;
             case '(' : FType = ltLeftParen; break;
             case ')' : FType = ltRightParen; break;
             case '[' : FType = ltLeftBrack; break;
             case ']' : FType = ltRightBrack; break;
             case '*' : FType = ltZeroMore; break;
             case '+' : FType = ltOneMore; break;
             case '|' : FType = ltOr; break;
             case '-' : FType = ltRange; break;
             case '~' : FType = ltNot; break;
             default  : FType = ltRegChar; break;
           }
           FText.add (*FPtr++);
           return;
    }
  }
}

void __fastcall TLexTree::Match (TLexToken AType)
{
  if (FType != AType) throw EExpression (FText.c_str ());
}

TNfaNode *__fastcall TLexTree::Rule (TTokenInfo *AInfo)
{
  FPtr = AInfo->DescStr;
  GetLexToken ();

  TNfaPair APair = RegExpr ();

  (APair.second)->Action = AInfo->Action;
  (APair.second)->Type = AInfo->Type;

  return (APair.first);
}

TNfaPair __fastcall TLexTree::RegExpr (void)
{
  TNfaPair APair0 = AndExpr ();

  while (FType == ltOr)
  {
    GetLexToken ();

    TNfaPair APair1 = AndExpr ();

    APair0.first = NewNfaNode (APair0.first,APair1.first);

    (APair0.second)->Right = (APair1.second)->Right = NewNfaNode ();

    APair0.second = (APair0.second)->Right;
  }

  return (APair0);
}

TNfaPair __fastcall TLexTree::AndExpr (void)
{
  TNfaPair APair0 = RepeatExpr ();

  while (AndSet.Contains (FType))
  {
    TNfaPair APair1 = RepeatExpr ();
    (APair0.second)->Right = APair1.first;
    APair0.second = APair1.second;
  }

  return (APair0);
}

TNfaPair __fastcall TLexTree::RepeatExpr (void)
{
  TNfaPair APair = Expr ();

  if (FType == ltZeroMore)
  {
    (APair.second)->Left = APair.first;
    APair.first = NewNfaNode (APair.first,NewNfaNode ());
    APair.second = (APair.second)->Right = (APair.first)->Right;

    GetLexToken ();
  }
  else if (FType == ltOneMore)
  {
    (APair.second)->Left = APair.first;

    GetLexToken ();
  }

  return (APair);
}

TNfaPair __fastcall TLexTree::Expr (void)
{
  TNfaPair APair0,APair1;

  APair0.first = NewNfaNode ();
  APair0.second = NewNfaNode ();

  switch (FType)
  {
    case ltLeftBrack :
         GetLexToken ();

         (APair0.first)->Left = APair0.second;
         (APair0.first)->CharSet = AtomList ();

         Match (ltRightBrack);
         GetLexToken ();
         break;
    case ltNot :
         GetLexToken ();
         Match (ltLeftBrack);
         GetLexToken ();

         (APair0.first)->Left = APair0.second;
         (APair0.first)->CharSet = ~AtomList ();

         Match (ltRightBrack);
         GetLexToken ();
         break;
    case ltLeftParen :
         GetLexToken ();
         APair1 = RegExpr ();

         (APair0.first)->Left = APair1.first;
         (APair1.second)->Right = APair0.second;

         Match (ltRightParen);
         GetLexToken ();
         break;
    case ltLeftBrace :
         GetLexToken ();
         APair1 = RegExpr ();

         (APair0.first)->Left = APair1.first;
         (APair1.second)->Right = (APair0.first)->Right = APair0.second;

         Match (ltRightBrace);
         GetLexToken ();
         break;
    default :
         (APair0.first)->Left = APair0.second;
         (APair0.first)->CharSet.set (AnyChar ());

  }

  return (APair0);
}

TCharSet __fastcall TLexTree::AtomList (void)
{
  TCharSet ASet;

  while (AnyCharSet.Contains (FType)) ASet |= NearAtom ();

  return (ASet);
}

TCharSet __fastcall TLexTree::NearAtom (void)
{
  int AEnd,i = AnyChar ();
  TCharSet ASet;

  ASet.set (i);

  if (FType == ltRange)
  {
    GetLexToken ();
    for (i++,AEnd = AnyChar (); i<=AEnd; i++) ASet.set (i);
  }

  return (ASet);
}

unsigned char __fastcall TLexTree::AnyChar (void)
{
  int ch = 0;

  switch (FType)
  {
    case ltEof:
         break;
    case ltRegChar:
    case ltTab:
    case ltNewLine:
    case ltCarRet:
    case ltBackSpace:
    case ltLiteral:
         ch = (unsigned char)FText[0] - EOF;
         break;
    case ltOctalValue:
         sscanf (FText.c_str (),"%o",&ch);
         ch -= EOF;
         break;
    case ltHexValue:
         sscanf (FText.c_str () + 2,"%x",&ch);
         ch -= EOF;
         break;
    case ltDecValue:
         sscanf (FText.c_str (),"%d",&ch);
         ch -= EOF;
         break;
    default:
         throw EExpression (FText.c_str ());
  }

  GetLexToken ();
  return ((unsigned char)ch);
}

TLexNode *__fastcall TLexTree::NewLexNode (const TNfaNodeSet &DestSet)
{
  TLexNode *ANode = new TLexNode (FTokenType,FTokenAction);

  FNodesList.push_back (ANode);
  FFindMap[DestSet] = ANode;

  return (ANode);
}

TLexNode *__fastcall TLexTree::NfaToDfa (TNfaRoot &Start)
{
  TNfaNodeSet DestSet, SrcSet;
  TLexNode *ResNode;
  TCharSet ACharSet;

  FOpIndex = 1;

  FNfaRoot = Start;
  FTokenType = FNfaRoot.Type;
  FTokenAction = FNfaRoot.Action;

  CloseNode (FNfaRoot.Node,DestSet,ACharSet);
  ResNode = NewLexNode (DestSet);
  SetDfaNode (ResNode,DestSet,ACharSet);

  FFindMap.clear ();

  return (ResNode);
}

void __fastcall TLexTree::SetDfaNode (TLexNode *ANode,TNfaNodeSet &SrcSet,const TCharSet &SrcCharSet)
{
  for (int i=0; i<257; i++)
  {
    if (SrcCharSet.test (i))
    {
      FOpIndex++;
      FTokenType = FNfaRoot.Type;
      FTokenAction = FNfaRoot.Action;

      TNfaNodeSet DestSet;
      TCharSet DestCharSet;

      for (TNfaNodeSet::iterator PSet = SrcSet.begin (); PSet != SrcSet.end (); PSet++)
      {
        TNfaNode *ANfaNode = FNfaList [*PSet];
        if (ANfaNode->CharSet.test (i)) CloseNode (ANfaNode->Left,DestSet,DestCharSet);
      }

      TFindMap::iterator PMap = FFindMap.find (DestSet);
      TLexNode *ANewNode;

      if (PMap == FFindMap.end ())
      {
        ANewNode = NewLexNode (DestSet);
        SetDfaNode (ANewNode,DestSet,DestCharSet);
      }
      else ANewNode = (*PMap).second;

      ANode->Entries.Add (i,ANewNode);
    }
  }
}

void __fastcall TLexTree::CloseNode (TNfaNode *ANode,TNfaNodeSet &DestSet,TCharSet &DestCharSet)
{
  if (ANode != NULL && ANode->NfaSet != FOpIndex)
  {
    DestSet.insert (ANode->Index);
    ANode->NfaSet = FOpIndex;
    DestCharSet |= ANode->CharSet;

    if (FTokenAction == FNfaRoot.Action && ANode->Action != ErrorAction)
    {
      FTokenType = ANode->Type;
      FTokenAction = ANode->Action;
    }

    if (ANode->CharSet.any () == false) CloseNode (ANode->Left,DestSet,DestCharSet);

    CloseNode (ANode->Right,DestSet,DestCharSet);
  }
}

//----------------------------------------------------------------------------------------------------------
void __fastcall TTokenString::allocate (unsigned int n)
{
  char *ptr = start;

  n = ((n + 1)/16 + 1) * 16;
  start = end = new char [n];
  memset (start,0,n);
  finish = start + n - 1;

  if (ptr) delete [] ptr;
}

void __fastcall TTokenString::reallocate (unsigned int n)
{
  char *ptr = start;

  start = end = finish = 0;
  copy (ptr,n);

  if (ptr) delete [] ptr;
}

void __fastcall TTokenString::deallocate (void)
{
  if (start != 0) delete [] start;
  start = end = finish = 0;
}

void __fastcall TTokenString::copy (const char *src,unsigned int n)
{
  if (n > capacity ()) allocate (n);
  else while (end != start) *(--end) = 0;

  if (src) while (length () < n && *src != 0) *end++ = *src++;
}

void __fastcall TTokenString::cat (const char *src,unsigned int n)
{
  if (n + length () > capacity ()) reallocate (n + length ());

  if (src) for (char *ptr = end; end - ptr < (int)n && *src != 0; *end++ = *src++);
}

TTokenString __fastcall TTokenString::operator+ (const TTokenString &s) const
{
  TTokenString tmp (c_str (),length () + s.length ());
  tmp.cat (s.c_str (),s.length ());

  return tmp;
}

TTokenString &__fastcall TTokenString::operator+= (const TTokenString &s)
{
  cat (s.c_str (),s.length ());
  return *this;
}

__fastcall TTokenString::operator String () const
{
  return String (c_str ());
}

void __fastcall TTokenString::set_length (unsigned int len)
{
  if (len < length ()) while (length () > len) *(--end) = 0;
  else if (len > capacity ()) reallocate (len);
}

TTokenString __fastcall TTokenString::trim_left (void) const
{
  const char *ptr;

  for (ptr = c_str (); *ptr != 0 && (*ptr == ' ' || *ptr == '\t'); ptr++);

  return TTokenString (ptr);
}

TTokenString __fastcall TTokenString::trim_right (void) const
{
  const char *ptr;

  for (ptr = end; ptr != start && (*(ptr-1) == ' ' || *(ptr-1) == '\t'); ptr--);

  return TTokenString (c_str (),ptr - start);
}

TTokenString __fastcall TTokenString::trim (void) const
{
  const char *bptr, *eptr;

  if (length () == 0) return TTokenString ();

  for (bptr = start; *bptr != 0 && (*bptr == ' ' || *bptr == '\t'); bptr++);
  for (eptr = end; eptr != bptr && (*(eptr-1) == ' ' || *(eptr-1) == '\t'); eptr--);

  return TTokenString (start,eptr - bptr);
}

int __fastcall TTokenString::last_delimiter (const char *s) const
{
  const char *ptr;

  for (ptr = end; ptr != start; ptr--)
  {
    for (const char *sptr=s; *sptr != 0; sptr++)
    {
      if (*(ptr - 1) == *sptr) return (ptr - start - 1);
    }
  }

  return (-1);
}

int __fastcall TTokenString::pos (const char* s) const
{
  const char *ptr = strstr (c_str (),s);

  return ((ptr == NULL)? -1 : ptr - c_str ());
}

int __fastcall TTokenString::count_chars (char c) const
{
  int nchars = 0;

  for (const char *ptr = c_str (); (ptr = strchr (ptr,c)) != NULL; ptr++, nchars++);

  return nchars;
}

TTokenString __fastcall TTokenString::sub_string (unsigned int index,unsigned int count) const
{
  if (index >= length ()) return TTokenString ();

  return TTokenString (*this,index,count);
}

TTokenString __fastcall TTokenString::string_of_char (char ch,unsigned int count)
{
  TTokenString tmp;

  tmp.set_length (count);
  while (count-- != 0) tmp.add (ch);

  return tmp;
}

int __fastcall TTokenString::to_int (void) const
{
  return atoi (c_str ());
}

int __cdecl TTokenString::vprintf (const char *format,va_list paramList)
{
  int len = vsnprintf (NULL,0,format,paramList);

  set_length (len);

  if (len)
  {
    vsnprintf (start,len,format,paramList);
    end = start + len;
  }

  return len;
}

int __cdecl TTokenString::printf (const char *format,...)
{
  int rc;
  va_list paramList;

  va_start (paramList,format);
  rc = TTokenString::vprintf (format,paramList);
  va_end (paramList);

  return rc;
}

TTokenString &__cdecl TTokenString::sprintf (const char *format,...)
{
  va_list paramList;

  va_start (paramList,format);
  TTokenString::vprintf (format,paramList);
  va_end (paramList);

  return *this;
}

//----------------------------------------------------------------------------------------------------------
__cdecl TMsgString::TMsgString (const TMsgInfo *m,...) : TTokenString (), Type (m->Type)
{
  va_list paramList;

  va_start (paramList,m);
  TTokenString::vprintf (m->Msg,paramList);
  va_end (paramList);
}

//----------------------------------------------------------------------------------------------------------
void __fastcall TTokenList::allocate (unsigned int n)
{
  TToken *ptr = start;

  n = (n + 4)/4*4;
  start = enddata = new TToken [n];
  finish = start + n;

  if (ptr) delete [] ptr;
}

void __fastcall TTokenList::reallocate (unsigned int n)
{
  TToken *ptr = start;
  unsigned int oldsize = size ();

  start = enddata = finish = 0;
  allocate (n);
  copy (ptr,oldsize);

  if (ptr) delete [] ptr;
}

void __fastcall TTokenList::deallocate (void)
{
  if (start != 0) delete [] start;
  start = enddata = finish = 0;
}

void __fastcall TTokenList::copy (const TToken *src,unsigned int n)
{
  if (n > capacity ()) allocate (n);
  else while (size () > n) (--enddata)->~TToken ();

  if (src) while (size () < n) *enddata++ = *src++;
}

bool __fastcall TTokenList::equal (const TTokenList &rhs) const
{
  for (unsigned int i=0; i<size (); i++) if (at (i) != rhs [i]) return false;

  return true;
}

//----------------------------------------------------------------------------------------------------------
void __fastcall TErrorList::CheckLimit (const TTokenString &Desc,int ALine)
{
  if (FErrorCount >= FLimit)
  {
    FErrorCount ++;
    Add ("Error " + Desc + " " + ALine + ": Too many error or warning messages");
    throw ELexer ();
  }
}

void __fastcall TErrorList::AddError (const TTokenString &AErrorString)
{
  if (Enabled)
  {
    FErrorCount ++;
    Add ("Error : " + AErrorString);
  }
}

void __fastcall TErrorList::AddFatal (const TTokenString &Desc,int ALine,const TTokenString &AErrorString)
{
  if (Enabled)
  {
    if (FIgnoreFatal) Add ("Message " + Desc + " " + ALine + ": " + AErrorString);
    else
    {
      FErrorCount ++;
      Add ("Fatal " + Desc + " " + ALine + ": " + AErrorString);
      throw ELexer ();
    }
  }
}

void __fastcall TErrorList::AddError (const TTokenString &Desc,int ALine,const TTokenString &AErrorString)
{
  if (Enabled)
  {
    FErrorCount ++;
    Add ("Error " + Desc + " " + ALine + ": " + AErrorString);
    CheckLimit (Desc,ALine);
  }
}

void __fastcall TErrorList::AddWarning (const TTokenString &Desc,int ALine,const TTokenString &AString)
{
  if (Enabled)
  {
    Add ("Warning " + Desc + " " + ALine + ": " + AString);
  }
}

void __fastcall TErrorList::AddMessage (const TTokenString &Desc,int ALine,const TTokenString &AString)
{
  if (Enabled)
  {
    Add ("Message " + Desc + " " + ALine + ": " + AString);
  }
}

void __fastcall TErrorList::OutMessages (TStream *AStream)
{
  for (int i=0; i<Count; i++)
  {
    AStream->Write (Strings[i].c_str(),Strings[i].Length ());
    AStream->Write ("\n",1);
  }

  if (FErrorCount > 0)
  {
	String AStr ("*** " + String (FErrorCount) + " errors in Parsing ***\n");
    AStream->Write (AStr.c_str(),AStr.Length ());
  }
}

//----------------------------------------------------------------------------------------------------------
void __fastcall TLexer::ErrorAction (void)
{
  unsigned char ch = GetChar ();

  AddError ("Illegal character '" + ((ch != '\n')?TTokenString ((char *)&ch,1):TTokenString ("\\n")) +
            "' (0x" + IntToHex (ch,2) + ")",FLine);

  AddChar (ch);
  NextChar ();
  Skip ();
}

TTokenString &__fastcall TLexer::GetText (void)
{
  return FToken.text;
}

TToken &__fastcall TLexer::NextToken (void)
{
  TLexNode *ANode,*Entry;

  FStartLine = FLine;
  FMode = lmSkip;

  while (FMode != lmReturn)
  {
    if (FMode == lmSkip) FToken.text.clear ();
    FLastSize = FToken.text.length ();

    BeforeFillText ();

    for (ANode=(*FLexTree)[FRootIndex]; ANode!=NULL && (Entry=ANode->GetEntry (GetChar ()))!=NULL; NextChar ())
    {
      AddChar ();
      ANode = Entry;
    }

    FMode = lmReturn;
    if (ANode->Action != NULL) ANode->Action (this);
  }

  FToken.type = ANode->Type;
  FToken.line = GetStartLine ();

  return FToken;
}
//----------------------------------------------------------------------------------------------------------
