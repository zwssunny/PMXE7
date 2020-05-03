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

#ifndef lexerH
#define lexerH

#include <string.h>
#include <stdarg.h>
#include <dinkumware\vector>
#include <dinkumware\set>
#include <dinkumware\map>
#include <dinkumware\bitset>
#include <system.hpp>
#include <sysutils.hpp>
#include <classes.hpp>
#include "Errmsgs.h"
using namespace std;
//----------------------------------------------------------------------------------------------------------
class PACKAGE TLexer;
typedef void __fastcall (*TNodeAction) (TLexer *ALexer);

struct PACKAGE TTokenInfo
{
  int RootIndex;
  int Type;
  unsigned char *DescStr;
  TNodeAction Action;
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TLexNode;
typedef TLexNode* PLexNode;

class PACKAGE TNodeEntries
{
private:
  PLexNode *start;
  PLexNode *finish;
  PLexNode *end;
  int FBase;

public:
  __fastcall TNodeEntries (void) : FBase (0)
  {
    start = end = new PLexNode[4];
    memset (start,0,4*sizeof (PLexNode));
    finish = start + 4;
  }
  __fastcall ~TNodeEntries (void) { delete [] start; }

  void __fastcall Add (int AKey,TLexNode* ANode);
  TLexNode *__fastcall Get (int ch) { ch -= FBase; return ((ch<0 || ch>= end - start)?NULL:start[ch]); }
};

class PACKAGE TLexNode
{
private:
protected:
public:
  int Type;
  TNodeAction Action;
  TNodeEntries Entries;

  __fastcall TLexNode (void) : Type (NULL),Action (NULL) {}
  __fastcall TLexNode (int AType,TNodeAction AAction) : Type (AType),Action (AAction) {}
  __fastcall ~TLexNode (void) {}

  TLexNode *__fastcall TLexNode::GetEntry (int ch) { return (Entries.Get (ch - EOF)); }
};

//----------------------------------------------------------------------------------------------------------
typedef bitset<257> TCharSet;

class PACKAGE TNfaNode
{
private:
protected:
public:
  unsigned int NfaSet;
  unsigned int Index;
  int Type;
  TNodeAction Action;
  TCharSet CharSet;
  TNfaNode *Left;
  TNfaNode *Right;

  __fastcall TNfaNode (void) : NfaSet (0),Type (0),Action (NULL),Left (NULL),Right (NULL),CharSet () {}
  __fastcall ~TNfaNode (void) { }
};

typedef vector<TNfaNode *> TNfaNodes;

//----------------------------------------------------------------------------------------------------------
class PACKAGE TNfaRoot
{
public:
  TNfaNode *Node;
  int Type;
  TNodeAction Action;

  __fastcall TNfaRoot (void);
  __fastcall TNfaRoot (TNfaNode *ANode,int AType,TNodeAction AAction) : Node (ANode),Type (AType),Action (AAction) { }
};

typedef vector<TNfaRoot> TNfaRoots;

//----------------------------------------------------------------------------------------------------------
class PACKAGE TTokenString
{
private:
protected:
  char *start;
  char *finish;
  char *end;

  void __fastcall allocate (unsigned int n);
  void __fastcall reallocate (unsigned int n);
  void __fastcall deallocate (void);
  void __fastcall copy (const char *src,unsigned int len);
  void __fastcall cat (const char *src,unsigned int len);
  int __cdecl vprintf (const char *format,va_list paramList);

public:
  virtual __fastcall ~TTokenString (void)
  {
    deallocate ();
  }
  __fastcall TTokenString (void) : start (0), end (0), finish (0) { }
  __fastcall TTokenString (const TTokenString &s) : start (0), end (0), finish (0)
  {
    copy (s.c_str (),s.length ());
  }
  __fastcall TTokenString (const TTokenString &s,unsigned int pos,unsigned int n) : start (0), end (0), finish (0)
  {
    copy (s.c_str ()+pos,n);
  }
  __fastcall TTokenString (const String &s) : start (0), end (0), finish (0)
  {
	#ifdef _DELPHI_STRING_UNICODE
	AnsiString dstr=s;
	copy (dstr.c_str (),dstr.Length ());
	#else
	copy (s.c_str (),s.Length ());
	#endif
  }
  __fastcall TTokenString (String &s) : start (0), end (0), finish (0)
  {
  	#ifdef _DELPHI_STRING_UNICODE
	AnsiString dstr=s;
	copy (dstr.c_str (),dstr.Length ());
	#else
	copy (s.c_str (),s.Length ());
	#endif
  }
  __fastcall TTokenString (const char *s) : start (0), end (0), finish (0)
  {
    copy (s,strlen (s));
  }
  __fastcall TTokenString (const char *s,unsigned int n) : start (0), end (0), finish (0)
  {
    copy (s,n);
  }
  __fastcall TTokenString (char *s) : start (0), end (0), finish (0)
  {
    copy (s,strlen (s));
  }
  __fastcall TTokenString (char *s,unsigned int n) : start (0), end (0), finish (0)
  {
    copy (s,n);
  }
  __fastcall TTokenString (int c) : start (0), end (0), finish (0)
  {
    allocate (34);
    itoa (c,start,10);
    end = strchr (start,0);
  }

  TTokenString &__fastcall operator= (const TTokenString &s)
  {
    if (this == &s) return *this;
    copy (s.c_str (),s.length ());
    return *this;
  }

  bool operator== (const TTokenString &s) const { return strcmp (c_str (),s.c_str ()) == 0; }
  bool operator!= (const TTokenString &s) const { return strcmp (c_str (),s.c_str ()) != 0; }
  bool operator< (const TTokenString &s) const { return strcmp (c_str (),s.c_str ()) < 0; }
  char &operator[] (unsigned int n) { return *(start + n); }
  const char &operator[] (unsigned int n) const { return *(start + n); }
  TTokenString __fastcall operator+ (const TTokenString &s) const;
  TTokenString &__fastcall operator+= (const TTokenString &s);
  __fastcall operator String () const;

  const char *__fastcall c_str (void) const { return ((start)? start : ""); }
  char *__fastcall c_str (void) { return ((start)? start : NULL); }
  unsigned int __fastcall length (void) const { return (end - start); }
  unsigned int __fastcall capacity (void) const { return (finish - start); }
  void __fastcall set_length (unsigned int len);
  bool __fastcall empty (void) const { return length () == 0; }
  void __fastcall clear (void) { set_length (0); }
  void __fastcall add (char c)
  {
    if (end == finish) reallocate (length () + 1);
    *end++ = c;
  }
  char __fastcall last_char (void) const { return ((length ())? *(end - 1): 0); }
  int __fastcall last_delimiter (const char *s) const;
  int __fastcall pos (const char* s) const;
  int __fastcall count_chars (char c) const;

  TTokenString __fastcall trim_left (void) const;
  TTokenString __fastcall trim_right (void) const;
  TTokenString __fastcall trim (void) const;
  TTokenString __fastcall sub_string (unsigned int index,unsigned int count) const;
  TTokenString __fastcall string_of_char (char ch,unsigned int count);

  int __fastcall to_int (void) const;

  int __cdecl printf (const char *format,...);
  TTokenString &__cdecl sprintf (const char *format,...);
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TMsgString : public TTokenString
{
private:
protected:
public:
  int Type;

  __fastcall TMsgString (void) : TTokenString (), Type (0) { }
  __fastcall TMsgString (const TTokenString &s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (const TMsgString &s) : TTokenString (s), Type (s.Type) { }
  __fastcall TMsgString (TTokenString &s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (const String &s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (String &s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (const char *s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (char *s) : TTokenString (s), Type (0) { }
  __fastcall TMsgString (const TMsgInfo &m) : TTokenString (m.Msg), Type (m.Type) { }
  __fastcall TMsgString (TMsgInfo &m) : TTokenString (m.Msg), Type (m.Type) { }
  __cdecl TMsgString (const TMsgInfo *m,...);
  __fastcall TMsgString (int AType,const TTokenString &s) : TTokenString (s), Type (AType) { }
  __fastcall TMsgString (int AType,TTokenString &s) : TTokenString (s), Type (AType) { }
};

//----------------------------------------------------------------------------------------------------------
enum TLexToken {ltEnd,         // '\0'
                ltEof,         // @
                ltRegChar,     // ~[\]
                ltOctalValue,  // \0[0-7]*
                ltHexValue,    // \0[Xx][0-9a-fA-F]+
                ltDecValue,    // \[1-9][0-9]*
                ltTab,         // \t
                ltNewLine,     // \n
                ltCarRet,      // \r
                ltBackSpace,   // \b
                ltLiteral,     // \~[tnrb]
                ltLeftBrace,   // {
                ltRightBrace,  // }
                ltLeftParen,   // (
                ltRightParen,  // )
                ltLeftBrack,   // [
                ltRightBrack,  // ]
                ltZeroMore,    // *
                ltOneMore,     // +
                ltOr,          // |
                ltRange,       // -
                ltNot          // ~
               };

typedef Set <TLexToken,ltEnd,ltNot> TLexTokens;
typedef vector<TLexNode *> TLexNodes;
typedef pair<TNfaNode *,TNfaNode *> TNfaPair;
typedef set<unsigned int,less<unsigned int> > TNfaNodeSet;
typedef map<TNfaNodeSet,TLexNode *,less<TNfaNodeSet> > TFindMap;

class PACKAGE EExpression : public Exception
{
public:
  __fastcall EExpression (const TTokenString &Msg) : Exception (Msg) { }
};

class PACKAGE TLexTree : public TLexNodes
{
private:
  TLexNodes FNodesList;
  TLexToken FType;
  TTokenString FText;
  unsigned char *FPtr;
  TNfaNodes FNfaList;
  unsigned int FOpIndex;
  TFindMap FFindMap;
  int FTokenType;
  TNodeAction FTokenAction;
  TNfaRoot FNfaRoot;

  void __fastcall ClearNfaList (void);
  void __fastcall GetLexToken (void);
  TNfaNode *__fastcall NewNfaNode (void);
  TNfaNode *__fastcall NewNfaNode (TNfaNode *ALeft,TNfaNode *ARight);
  void __fastcall Match (TLexToken AType);
  TNfaNode *__fastcall Rule (TTokenInfo *AInfo);
  TNfaPair __fastcall RegExpr (void);
  TNfaPair __fastcall AndExpr (void);
  TNfaPair __fastcall RepeatExpr (void);
  TNfaPair __fastcall Expr (void);
  TCharSet __fastcall AtomList (void);
  TCharSet __fastcall NearAtom (void);
  unsigned char __fastcall AnyChar (void);
  TLexNode *__fastcall NewLexNode (const TNfaNodeSet &DestSet);
  TLexNode *__fastcall NfaToDfa (TNfaRoot &Start);
  void __fastcall SetDfaNode (TLexNode *ANode,TNfaNodeSet &SrcSet,const TCharSet &SrcCharSet);
  void __fastcall CloseNode (TNfaNode *ANode,TNfaNodeSet &DestSet,TCharSet &DestCharSet);

protected:
public:
  __fastcall TLexTree (TTokenInfo ATokenInfos[],int ATokenInfosSize);
  __fastcall ~TLexTree (void);
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TToken
{
public:
  int type;
  int line;
  TTokenString text;

  TToken (void) : type(0), text (""), line (0) {}
  TToken (int AType,const char *AText,int ALine) : type(AType), text (AText), line (ALine) {}
  TToken (int AType,const TTokenString &AText,int ALine) : type(AType), text (AText), line (ALine) {}
  virtual ~TToken () {}

  bool operator== (const TToken& AToken) const { return (type == AToken.type && text.trim_left () == AToken.text.trim_left ());}
  bool operator!= (const TToken& AToken) const { return !operator==(AToken);}
  bool operator< (const TToken& AToken) const { return (text.trim_left () < AToken.text.trim_left ()); }
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TTokenList
{
private:
  TToken *start;
  TToken *finish;
  TToken *enddata;

protected:
  void __fastcall allocate (unsigned int n);
  void __fastcall reallocate (unsigned int n);
  void __fastcall deallocate (void);
  void __fastcall copy (const TToken *src,unsigned int n);
  bool __fastcall equal (const TTokenList &rhs) const;

public:
  __fastcall TTokenList (void) : start (0), finish (0), enddata (0) { }
  __fastcall TTokenList (const TTokenList &rhs) : start (0), finish (0), enddata (0)
  {
    if (rhs.size ())
    {
      allocate (rhs.size ());
      copy (rhs.begin (),rhs.size ());
    }
  }
  virtual __fastcall ~TTokenList (void) { deallocate (); }

  TTokenList &__fastcall operator= (const TTokenList &rhs)
  {
    if (this == &rhs) return *this;
    copy (rhs.begin (),rhs.size ());
    return *this;
  }
  TToken &operator[] (unsigned int n) { return *(start + n); }
  const TToken &operator[] (unsigned int n) const { return *(start + n); }
  bool operator== (const TTokenList &rhs) const
  {
    return (size () == rhs.size () && equal (rhs));
  }
  bool operator!= (const TTokenList &rhs) const { return (!operator== (rhs)); }

  unsigned int size (void) const { return (enddata - start); }
  unsigned int capacity (void) const { return (finish - start); }
  TToken *__fastcall begin (void) { return start; }
  const TToken *__fastcall begin (void) const { return start; }
  TToken *__fastcall end (void) { return enddata; }
  const TToken *__fastcall end (void) const { return enddata; }
  TToken &__fastcall at (unsigned int index) { return *(start + index); }
  const TToken &__fastcall at (unsigned int index) const { return *(start + index); }
  bool __fastcall empty (void) const { return size () == 0; }
  void __fastcall clear (void) { deallocate (); }
  void __fastcall push_back (const TToken &c)
  {
    if (enddata == finish) reallocate (size () + 1);
    *enddata++ = c;
  }
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TErrorList : public TStringList
{
private:
  int FLimit;
  int FErrorCount;
  bool FIgnoreFatal;

  void __fastcall CheckLimit (const TTokenString &Desc,int ALine);

public:
  bool Enabled;

  __fastcall TErrorList (int ALimit,bool AIgnoreFatal=false) : TStringList (), FLimit (max (ALimit,1)),
                         Enabled (true), FIgnoreFatal (AIgnoreFatal) {};

  void __fastcall AddError (const TTokenString &AErrorString);
  void __fastcall AddFatal (const TTokenString &Desc,int ALine,const TTokenString &AErrorString);
  void __fastcall AddError (const TTokenString &Desc,int ALine,const TTokenString &AErrorString);
  void __fastcall AddWarning (const TTokenString &Desc,int ALine,const TTokenString &AString);
  void __fastcall AddMessage (const TTokenString &Desc,int ALine,const TTokenString &AString);
  int __fastcall ErrorCount (void) { return (FErrorCount); }
  int __fastcall WarningCount (void) { return (Count - FErrorCount); }
  int __fastcall GetLimit (void) { return FLimit; }
  void __fastcall SetLimit (int ALimit) { FLimit = max (ALimit,1); }
  void __fastcall OutMessages (TStream *AStream);
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE ELexer : public Exception
{
public:
  __fastcall ELexer (void) : Exception ("") { }
  __fastcall ELexer (const TTokenString &AString) : Exception (AString) { }
};

//----------------------------------------------------------------------------------------------------------
enum TLexMode {lmReturn,lmSkip,lmMore};

class PACKAGE TLexer
{
protected:
  TLexTree *FLexTree;
  TToken FToken;
  int FStartLine;
  int FLine;
  TLexMode FMode;
  int FRootIndex;
  int FPrevIndex;
  int FLastSize;

  virtual void __fastcall NextChar (void) = 0;
  virtual int __fastcall GetChar (void) = 0;
  virtual void __fastcall BeforeFillText (void) { }

public:
  __fastcall TLexer (TLexTree *ALexTree,int ALine=1) : FLexTree (ALexTree), FLine (ALine), FRootIndex (0) {}
  virtual __fastcall ~TLexer (void) {}

  void __fastcall AddChar (int AChar) { if (AChar == '\n') FLine++; FToken.text.add (AChar); }
  void __fastcall AddChar (void) { AddChar (GetChar ()); }
  void __fastcall Skip (void) { FMode = lmSkip; }
  void __fastcall More (void) { FMode = lmMore; }
  void __fastcall Erase (void) { FToken.text.set_length (FLastSize); }
  void __fastcall SetRootIndex (int AIndex) { if (FRootIndex != AIndex) { FPrevIndex = FRootIndex; FRootIndex = AIndex; } }
  void __fastcall RestoreRootIndex (void) { FRootIndex = FPrevIndex; }
  int  __fastcall GetRootIndex (void) { return FRootIndex; }
  virtual TToken &__fastcall Token (void) { return FToken; }
  virtual int __fastcall GetLine (void) { return FLine; }
  virtual int __fastcall GetStartLine (void) { return FStartLine; }
  TTokenString &__fastcall GetText (void);
  void __fastcall ErrorAction (void);
  virtual TToken &__fastcall NextToken (void);
  virtual void __fastcall AddError (const TMsgString &AErrorString,int ALine) = 0;
};

//----------------------------------------------------------------------------------------------------------
#endif

