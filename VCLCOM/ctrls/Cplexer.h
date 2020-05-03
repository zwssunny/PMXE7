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

#ifndef cplexerH
#define cplexerH

#include <dinkumware\stack>
#include <dinkumware\vector>
#include <dinkumware\set>
#include "lexer.h"
#include "errmsgs.h"
#include "istream.h"
using namespace std;
//----------------------------------------------------------------------------------------------------------
enum TTokenType {
  TOK_EMPTY,
  TOK_EOF,
  TOK_AMPERSAND,
  TOK_AND,
  TOK_ASSIGNEQUAL,
  TOK_BITWISEANDEQUAL,
  TOK_BITWISEOR,
  TOK_BITWISEOREQUAL,
  TOK_BITWISEXOR,
  TOK_BITWISEXOREQUAL,
  TOK_COMMA,
  TOK_COLON,
  TOK_DIVIDE,
  TOK_DIVIDEEQUAL,
  TOK_DOT,
  TOK_DOTMBR,
  TOK_ELLIPSIS,
  TOK_EQUAL,
  TOK_GREATERTHAN,
  TOK_GREATERTHANOREQUALTO,
  TOK_LCURLY,
  TOK_LESSTHAN,
  TOK_LESSTHANOREQUALTO,
  TOK_LPAREN,
  TOK_LSQUARE,
  TOK_MINUS,
  TOK_MINUSEQUAL,
  TOK_MINUSMINUS,
  TOK_MOD,
  TOK_MODEQUAL,
  TOK_NOT,
  TOK_NOTEQUAL,
  TOK_OR,
  TOK_PLUS,
  TOK_PLUSEQUAL,
  TOK_PLUSPLUS,
  TOK_POINTERTO,
  TOK_POINTERTOMBR,
  TOK_QUESTIONMARK,
  TOK_RCURLY,
  TOK_RPAREN,
  TOK_RSQUARE,
  TOK_SCOPE,
  TOK_SEMICOLON,
  TOK_SHIFTLEFT,
  TOK_SHIFTLEFTEQUAL,
  TOK_SHIFTRIGHT,
  TOK_SHIFTRIGHTEQUAL,
  TOK_STAR,
  TOK_TILDE,
  TOK_TIMESEQUAL,

  TOK_ASM,
  TOK_AUTO,
  TOK_AUTOMATED,
  TOK_BOOL,
  TOK_BREAK,
  TOK_CASE,
  TOK_CATCH,
  TOK_CDECL,
  TOK_CHAR,
  TOK_CLASS,
  TOK_CLASSID,
  TOK_CLOSURE,
  TOK_CONST,
  TOK_CONST_CAST,
  TOK_CONTINUE,
  TOK_DECLSPEC,
  TOK_DEFAULT,
  TOK_DELETE,
  TOK_DISPID,
  TOK_DO,
  TOK_DOUBLE,
  TOK_DYNAMIC_CAST,
  TOK_ELSE,
  TOK_ENUM,
  TOK_EXCEPT,
  TOK_EXPLICIT,
  TOK_EXPORT,
  TOK_EXTERN,
  TOK_FALSE,
  TOK_FASTCALL,
  TOK_FINALLY,
  TOK_FLOAT,
  TOK_FOR,
  TOK_FRIEND,
  TOK_GOTO,
  TOK_IF,
  TOK_IMPORT,
  TOK_INLINE,
  TOK_INT,
  TOK_INT8,
  TOK_INT16,
  TOK_INT32,
  TOK_INT64,
  TOK_LONG,
  TOK_MSFASTCALL,
  TOK_MSRETURN,
  TOK_MUTABLE,
  TOK_NAMESPACE,
  TOK_NEW,
  TOK_OPERATOR,
  TOK_PASCAL,
  TOK_PRIVATE,
  TOK_PROPERTY,
  TOK_PROTECTED,
  TOK_PUBLIC,
  TOK_PUBLISHED,
  TOK_REGISTER,
  TOK_REINTERPRET_CAST,
  TOK_RETURN,
  TOK_RTTI,
  TOK_SHORT,
  TOK_SIGNED,
  TOK_SIZEOF,
  TOK_STATIC,
  TOK_STATIC_CAST,
  TOK_STDCALL,
  TOK_STRUCT,
  TOK_SWITCH,
  TOK_TEMPLATE,
  TOK_THIS,
  TOK_THREAD,
  TOK_THROW,
  TOK_TRUE,
  TOK_TRY,
  TOK_TYPEDEF,
  TOK_TYPEID,
  TOK_TYPENAME,
  TOK_UNION,
  TOK_UNSIGNED,
  TOK_USING,
  TOK_VIRTUAL,
  TOK_VOID,
  TOK_VOLATILE,
  TOK_WCHAR_T,
  TOK_WHILE,

  TOK_ID,
  TOK_OCTALINT,
  TOK_DECIMALINT,
  TOK_HEXADECIMALINT,
  TOK_FLOATONE,
  TOK_FLOATTWO,
  TOK_PNDPND,
  TOK_PND,
  TOK_PP_NUMBER,
  TOK_PNDDEFINE,
  TOK_PNDIF,
  TOK_PNDIFDEF,
  TOK_PNDIFNDEF,
  TOK_PNDELIF,
  TOK_PNDELSE,
  TOK_PNDENDIF,
  TOK_PNDINCLUDE,
  TOK_PNDLINE,
  TOK_PNDPRAGMA,
  TOK_PNDUNDEF,
  TOK_PNDIMPORT,
  TOK_FUNCID,
  TOK_STRING,
  TOK_CHARACTER,
  TOK_FILENAME,
  TOK_ASMSTAT,

  TOK_PRGALIGNMENT,
  TOK_PRGANON_STRUCT,
  TOK_PRGARGSUSED,
  TOK_PRGCHECKOPTION,
  TOK_PRGDEFOPTION,
  TOK_PRGUNDEFOPTION,
  TOK_PRGINLINE,
  TOK_PRGMESSAGE,
  TOK_PRGNOPUSHOPTWARN,
  TOK_PRGOBSOLETE,
  TOK_PRGOPTION,
  TOK_PRGWARN,
  TOK_PRGOPTSTR,
  TOK_PRGPUSH,
  TOK_PRGPOP,

  TOK_NEWLINE};

typedef Set<TTokenType,TOK_EMPTY,TOK_NEWLINE> TTokenTypeSet;

extern PACKAGE TErrorList *ErrorList;

//----------------------------------------------------------------------------------------------------------
class PACKAGE TPreScan
{
private:
  TIStream *FStream;
  TTokenString FDesc;
  int FChar;
  int FLine;

  void __fastcall NextChar (void);
protected:
public:
  int LastChar;

  __fastcall TPreScan (TIStream *AStream,const TTokenString &ADesc,int ALine) :
                       FLine (ALine), FStream (AStream), FDesc (ADesc), LastChar (0), FChar (0) { NextChar (); }
  __fastcall ~TPreScan (void) { delete FStream; }

  int __fastcall NextToken (void);
  TTokenString &__fastcall Descriptor (void) { return FDesc; }
};

//----------------------------------------------------------------------------------------------------------
typedef vector<TPreScan *> TPreScans;
class PACKAGE TDescriptionSet : public set<TTokenString, less<TTokenString> >
{
public:
  bool __fastcall Contains (const TTokenString &ADesc) { return (find (ADesc) != end ()); }
};

enum TCPPRootsIndex {criStart,criDirective,criDefining,criIncluding,criStrings,criStrError,criCharacters,
                     criFilenames,criDirError,criDefError,criIncError,criPError,criPLine,criLineError,
                     criSLComments,criMLComments,criOctSuffix,criDecSuffix,criHexSuffix,criAsm,criAsmStat,
                     criPragma,criPragmaError,criOptStr,criDefOpt,criOpt,criIfBlockFalse};

class PACKAGE TCPPScan : public TPreScans, public TLexer
{
private:
  TErrorList *FErrorList;
  TTokenString FStreamDesc;
  bool FFirst;
  int FComments;
  int FOffsetLine;
  TDescriptionSet FDescSet;
  bool FDescSetChanged;

  bool __fastcall NestedComments (void) { return true; }

protected:
  virtual int __fastcall GetChar (void);
  virtual void __fastcall NextChar (void);
  virtual void __fastcall BeforeFillText (void);
  void __fastcall Push (TIStream *AStream,const TTokenString &ADesc,int ALine);
  void __fastcall Pop (void);
  TErrorList *__fastcall GetErrorList (void) { return ((FErrorList==NULL)?ErrorList:FErrorList); }

public:
  TDescriptionSet StartDescSet;

  __fastcall TCPPScan (TIStream *AStream,const TTokenString &AStreamDesc,TErrorList *AErrorList = NULL);
  __fastcall ~TCPPScan (void);

  void __fastcall First (void) { FFirst = true; }
  void __fastcall NoFirst (void) { FFirst = false; }
  bool __fastcall GetFirst (void) { return FFirst; }
  void __fastcall IncComments (void) { if (NestedComments ()) FComments ++; }
  void __fastcall DecComments (void) { if (FComments > 0) FComments --; }
  int  __fastcall GetComments (void) { return FComments; }
  void __fastcall SetLine (int ALine);
  virtual int __fastcall GetLine (void) { return FLine + FOffsetLine; }
  virtual int __fastcall GetStartLine (void) { return FStartLine + FOffsetLine; }
  virtual void __fastcall AddError (const TMsgString &AErrorString,int ALine);
  void __fastcall AddFatal (const TMsgString &AFatalString,int ALine);
  TTokenString &__fastcall StreamDesc (void) { return FStreamDesc; }
  void __fastcall PushString (const TTokenString &AString,const TTokenString &ADesc);
  bool __fastcall ExpandPragmas (void) { return false; }
};

//----------------------------------------------------------------------------------------------------------
#endif
