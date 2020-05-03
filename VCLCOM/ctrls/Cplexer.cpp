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

#include "cplexer.h"

//----------------------------------------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------------------------------------
static void __fastcall EofAction (TLexer *ALexer)
{
  ALexer->Erase ();
}

static void __fastcall NewLineAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->First ();
  ALexer->SetRootIndex (criStart);
}

static void __fastcall SkipAction (TLexer *ALexer)
{
  ALexer->Skip ();
}

static void __fastcall MoreAction (TLexer *ALexer)
{
  ALexer->More ();
}

static void __fastcall EraseAction (TLexer *ALexer)
{
  ALexer->Erase ();
  ALexer->More ();
}

static void __fastcall NoFirstAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetStringsAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criStrings);
  ALexer->More ();
}

static void __fastcall SetStrErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criStrError);
  ALexer->Skip ();
}

static void __fastcall EndStrErrorAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_char () != '\n') ALexer->Erase ();
  ALexer->AddError (UnterminatedStringMsg,ALexer->GetStartLine ());
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetCharactersAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criCharacters);
  ALexer->More ();
}

static void __fastcall SetDirectiveAction (TLexer *ALexer)
{
  if (((TCPPScan *)ALexer)->GetFirst ())
  {
    ALexer->SetRootIndex (criDirective);
    ALexer->More ();
  }
}

static void __fastcall SetStartAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetDefiningAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criDefining);
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetIncludingAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criIncluding);
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetFilenamesAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criFilenames);
  ALexer->More ();
}

static void __fastcall SetDirErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criDirError);
  ALexer->More ();
}

static void __fastcall EndDirErrorAction (TLexer *ALexer)
{
  ALexer->Erase ();
  ALexer->AddError (TMsgString (&UnknownDirMsg,ALexer->GetText ().c_str()),ALexer->GetStartLine ());
  ALexer->Skip ();
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetDefErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criDefError);
  ALexer->Skip ();
}

static void __fastcall EndDefErrorAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_char () != '\n') ALexer->Erase ();
  ALexer->AddError (DefineNeedsIdMsg,ALexer->GetStartLine ());
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetIncErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criIncError);
  ALexer->Skip ();
}

static void __fastcall EndIncErrorAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_char () != '\n') ALexer->Erase ();
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetPErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criPError);
  ALexer->Skip ();
}

static void __fastcall EndPErrorAction (TLexer *ALexer)
{
  ALexer->Erase ();
  ((TCPPScan *)ALexer)->AddFatal (TMsgString (&ErrorDirectiveMsg,ALexer->GetText ().c_str()),ALexer->GetStartLine ());
  ALexer->Skip ();
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetPLineAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criPLine);
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetLineErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criLineError);
  ALexer->Skip ();
}

static void __fastcall EndLineErrorAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_char () != '\n') ALexer->Erase ();
  ALexer->AddError (BadLineDirMsg,ALexer->GetStartLine ());
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetSLCommentsAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criSLComments);
  ALexer->Erase ();
  ALexer->More ();
}

static void __fastcall SetMLCommentsAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criMLComments);
  ((TCPPScan *)ALexer)->IncComments ();
  ALexer->Erase ();
  ALexer->More ();
}

static void __fastcall EndCommentsAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->DecComments ();
  if (((TCPPScan *)ALexer)->GetComments () == 0)
  {
    ALexer->RestoreRootIndex ();
    ALexer->Erase ();
    ALexer->AddChar (' ');
  }
  ALexer->More ();
}

static void __fastcall EndCommentsErrorAction (TLexer *ALexer)
{
  ALexer->Erase ();
  ALexer->AddError (TMsgString (&UnexpectedEOFCommentMsg,ALexer->GetStartLine ()),ALexer->GetLine ());
}

static void __fastcall SetOctSuffixAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criOctSuffix);
  ALexer->More ();
}

static void __fastcall SetDecSuffixAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criDecSuffix);
  ALexer->More ();
}

static void __fastcall SetHexSuffixAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criHexSuffix);
  ALexer->More ();
}

static void __fastcall EndSuffixAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->NoFirst ();
  ALexer->SetRootIndex (criStart);
}

static void __fastcall ErrorSuffixAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_delimiter ("iI") != -1)
  {
    ALexer->AddError (IllegalNumberSuffixMsg,ALexer->GetLine ());
    ALexer->Skip ();
  }
  ((TCPPScan *)ALexer)->NoFirst ();
  ALexer->SetRootIndex (criStart);
}

static void __fastcall SetAsmStatAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criAsmStat);
  ALexer->More ();
}

static void __fastcall EndEofAsmAction (TLexer *ALexer)
{
  ALexer->Erase ();
  ((TCPPScan *)ALexer)->First ();
  ALexer->SetRootIndex (criStart);
}

static void __fastcall SetPragmaAction  (TLexer *ALexer)
{
  if (((TCPPScan *)ALexer)->ExpandPragmas ()) ALexer->SetRootIndex (criPragma);
  else ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->NoFirst ();
}

static void __fastcall SetPragmaErrorAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criPragmaError);
  ALexer->Skip ();
}

static void __fastcall SetOptStrAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criOptStr);
}

static void __fastcall EndPragmaErrorAction (TLexer *ALexer)
{
  if (ALexer->GetText ().last_char () != '\n') ALexer->Erase ();
  ALexer->SetRootIndex (criStart);
  ((TCPPScan *)ALexer)->First ();
}

static void __fastcall SetDefOptAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criDefOpt);
}

static void __fastcall EndDefOptAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criOptStr);
  ALexer->More ();
}

static void __fastcall SetOptAction (TLexer *ALexer)
{
  ALexer->SetRootIndex (criOpt);
}

static void __fastcall NewLineIfBlockAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->First ();
  ALexer->Skip ();
}

static void __fastcall SkipNoFirstAction (TLexer *ALexer)
{
  ((TCPPScan *)ALexer)->NoFirst ();
  ALexer->Skip ();
}

static void __fastcall EndIfBlockAction (TLexer *ALexer)
{
  if (((TCPPScan *)ALexer)->GetFirst ())
  {
    ALexer->SetRootIndex (criStart);
    ((TCPPScan *)ALexer)->NoFirst ();
  }
  else ALexer->Skip ();
}

TTokenInfo CPPTokenInfos[]={
{criStart,TOK_EOF,
         "@",EofAction},
{criStart,TOK_NEWLINE,
         "\\n",NewLineAction},

// ANSI C++ Operator and punctuator tokens
{criStart,TOK_AMPERSAND,
         "&",NoFirstAction},
{criStart,TOK_AND,
         "&&",NoFirstAction},
{criStart,TOK_ASSIGNEQUAL,
         "=",NoFirstAction},
{criStart,TOK_BITWISEANDEQUAL,
         "&=",NoFirstAction},
{criStart,TOK_BITWISEOR,
         "\\|",NoFirstAction},
{criStart,TOK_BITWISEOREQUAL,
         "\\|=",NoFirstAction},
{criStart,TOK_BITWISEXOR,
         "^",NoFirstAction},
{criStart,TOK_BITWISEXOREQUAL,
         "^=",NoFirstAction},
{criStart,TOK_COMMA,
         ",",NoFirstAction},
{criStart,TOK_COLON,
         ":",NoFirstAction},
{criStart,TOK_DIVIDE,
         "/",NoFirstAction},
{criStart,TOK_DIVIDEEQUAL,
         "/=",NoFirstAction},
{criStart,TOK_DOT,
         ".",NoFirstAction},
{criStart,TOK_DOTMBR,
         ".\\*",NoFirstAction},
{criStart,TOK_ELLIPSIS,
         "...",NoFirstAction},
{criStart,TOK_EQUAL,
         "==",NoFirstAction},
{criStart,TOK_GREATERTHAN,
         ">",NoFirstAction},
{criStart,TOK_GREATERTHANOREQUALTO,
         ">=",NoFirstAction},
{criStart,TOK_LCURLY,
         "\\{",NoFirstAction},
{criStart,TOK_LESSTHAN,
         "<",NoFirstAction},
{criStart,TOK_LESSTHANOREQUALTO,
         "<=",NoFirstAction},
{criStart,TOK_LPAREN,
         "\\(",NoFirstAction},
{criStart,TOK_LSQUARE,
         "\\[",NoFirstAction},
{criStart,TOK_MINUS,
         "\\-",NoFirstAction},
{criStart,TOK_MINUSEQUAL,
         "\\-=",NoFirstAction},
{criStart,TOK_MINUSMINUS,
         "\\-\\-",NoFirstAction},
{criStart,TOK_MOD,
         "%",NoFirstAction},
{criStart,TOK_MODEQUAL,
         "%=",NoFirstAction},
{criStart,TOK_NOT,
         "!",NoFirstAction},
{criStart,TOK_NOTEQUAL,
         "!=",NoFirstAction},
{criStart,TOK_OR,
         "\\|\\|",NoFirstAction},
{criStart,TOK_PLUS,
         "\\+",NoFirstAction},
{criStart,TOK_PLUSEQUAL,
         "\\+=",NoFirstAction},
{criStart,TOK_PLUSPLUS,
         "\\+\\+",NoFirstAction},
{criStart,TOK_POINTERTO,
         "\\->",NoFirstAction},
{criStart,TOK_POINTERTOMBR,
         "\\->\\*",NoFirstAction},
{criStart,TOK_QUESTIONMARK,
         "?",NoFirstAction},
{criStart,TOK_RCURLY,
         "\\}",NoFirstAction},
{criStart,TOK_RPAREN,
         "\\)",NoFirstAction},
{criStart,TOK_RSQUARE,
         "\\]",NoFirstAction},
{criStart,TOK_SCOPE,
         "::",NoFirstAction},
{criStart,TOK_SEMICOLON,
         ";",NoFirstAction},
{criStart,TOK_SHIFTLEFT,
         "<<",NoFirstAction},
{criStart,TOK_SHIFTLEFTEQUAL,
         "<<=",NoFirstAction},
{criStart,TOK_SHIFTRIGHT,
         ">>",NoFirstAction},
{criStart,TOK_SHIFTRIGHTEQUAL,
         ">>=",NoFirstAction},
{criStart,TOK_STAR,
         "\\*",NoFirstAction},
{criStart,TOK_TILDE,
         "\\~",NoFirstAction},
{criStart,TOK_TIMESEQUAL,
         "\\*=",NoFirstAction},

// C++ Keywords

{criStart,TOK_ASM,
         "{_|__}asm",NoFirstAction},
{criStart,TOK_AUTO,
         "auto",NoFirstAction},
{criStart,TOK_AUTOMATED,
         "__automated",NoFirstAction},
{criStart,TOK_BOOL,
         "bool",NoFirstAction},
{criStart,TOK_BREAK,
         "break",NoFirstAction},
{criStart,TOK_CASE,
         "case",NoFirstAction},
{criStart,TOK_CATCH,
         "catch",NoFirstAction},
{criStart,TOK_CDECL,
         "{_|__}cdecl",NoFirstAction},
{criStart,TOK_CHAR,
         "char",NoFirstAction},
{criStart,TOK_CLASS,
         "class",NoFirstAction},
{criStart,TOK_CLASSID,
         "__classid",NoFirstAction},
{criStart,TOK_CLOSURE,
         "__closure",NoFirstAction},
{criStart,TOK_CONST,
         "const",NoFirstAction},
{criStart,TOK_CONST_CAST,
         "const_cast",NoFirstAction},
{criStart,TOK_CONTINUE,
         "continue",NoFirstAction},
{criStart,TOK_DECLSPEC,
         "__declspec",NoFirstAction},
{criStart,TOK_DEFAULT,
         "default",NoFirstAction},
{criStart,TOK_DELETE,
         "delete",NoFirstAction},
{criStart,TOK_DISPID,
         "__dispid",NoFirstAction},
{criStart,TOK_DO,
         "do",NoFirstAction},
{criStart,TOK_DOUBLE,
         "double",NoFirstAction},
{criStart,TOK_DYNAMIC_CAST,
         "dynamic_cast",NoFirstAction},
{criStart,TOK_ELSE,
         "else",NoFirstAction},
{criStart,TOK_ENUM,
         "enum",NoFirstAction},
{criStart,TOK_EXCEPT,
         "__except",NoFirstAction},
{criStart,TOK_EXPLICIT,
         "explicit",NoFirstAction},
{criStart,TOK_EXPORT,
         "{_|__}export",NoFirstAction},
{criStart,TOK_EXTERN,
         "extern",NoFirstAction},
{criStart,TOK_FALSE,
         "false",NoFirstAction},
{criStart,TOK_FASTCALL,
         "{_}_fastcall",NoFirstAction},
{criStart,TOK_FINALLY,
         "__finally",NoFirstAction},
{criStart,TOK_FLOAT,
         "float",NoFirstAction},
{criStart,TOK_FOR,
         "for",NoFirstAction},
{criStart,TOK_FRIEND,
         "friend",NoFirstAction},
{criStart,TOK_GOTO,
         "goto",NoFirstAction},
{criStart,TOK_IF,
         "if",NoFirstAction},
{criStart,TOK_IMPORT,
         "{_}_import",NoFirstAction},
{criStart,TOK_INLINE,
         "{__}inline",NoFirstAction},
{criStart,TOK_INT,
         "int",NoFirstAction},
{criStart,TOK_INT8,
         "__int8",NoFirstAction},
{criStart,TOK_INT16,
         "__int16",NoFirstAction},
{criStart,TOK_INT32,
         "__int32",NoFirstAction},
{criStart,TOK_INT64,
         "__int64",NoFirstAction},
{criStart,TOK_LONG,
         "long",NoFirstAction},
{criStart,TOK_MSFASTCALL,
         "__msfastcall",NoFirstAction},
{criStart,TOK_MSRETURN,
         "__msreturn",NoFirstAction},
{criStart,TOK_MUTABLE,
         "mutable",NoFirstAction},
{criStart,TOK_NAMESPACE,
         "namespace",NoFirstAction},
{criStart,TOK_NEW,
         "new",NoFirstAction},
{criStart,TOK_OPERATOR,
         "operator",NoFirstAction},
{criStart,TOK_PASCAL,
         "{_|__}pascal",NoFirstAction},
{criStart,TOK_PRIVATE,
         "private",NoFirstAction},
{criStart,TOK_PROPERTY,
         "__property",NoFirstAction},
{criStart,TOK_PROTECTED,
         "protected",NoFirstAction},
{criStart,TOK_PUBLIC,
         "public",NoFirstAction},
{criStart,TOK_PUBLISHED,
         "__published",NoFirstAction},
{criStart,TOK_REGISTER,
         "register",NoFirstAction},
{criStart,TOK_REINTERPRET_CAST,
         "reinterpret_cast",NoFirstAction},
{criStart,TOK_RETURN,
         "return",NoFirstAction},
{criStart,TOK_RTTI,
         "__rtti",NoFirstAction},
{criStart,TOK_SHORT,
         "short",NoFirstAction},
{criStart,TOK_SIGNED,
         "signed",NoFirstAction},
{criStart,TOK_SIZEOF,
         "sizeof",NoFirstAction},
{criStart,TOK_STATIC,
         "static",NoFirstAction},
{criStart,TOK_STATIC_CAST,
         "static_cast",NoFirstAction},
{criStart,TOK_STDCALL,
         "{_}_stdcall",NoFirstAction},
{criStart,TOK_STRUCT,
         "struct",NoFirstAction},
{criStart,TOK_SWITCH,
         "switch",NoFirstAction},
{criStart,TOK_TEMPLATE,
         "template",NoFirstAction},
{criStart,TOK_THIS,
         "this",NoFirstAction},
{criStart,TOK_THREAD,
         "__thread",NoFirstAction},
{criStart,TOK_THROW,
         "throw",NoFirstAction},
{criStart,TOK_TRUE,
         "true",NoFirstAction},
{criStart,TOK_TRY,
         "{__}try",NoFirstAction},
{criStart,TOK_TYPEDEF,
         "typedef",NoFirstAction},
{criStart,TOK_TYPEID,
         "typeid",NoFirstAction},
{criStart,TOK_TYPENAME,
         "typename",NoFirstAction},
{criStart,TOK_UNION,
         "union",NoFirstAction},
{criStart,TOK_UNSIGNED,
         "unsigned",NoFirstAction},
{criStart,TOK_USING,
         "using",NoFirstAction},
{criStart,TOK_VIRTUAL,
         "virtual",NoFirstAction},
{criStart,TOK_VOID,
         "void",NoFirstAction},
{criStart,TOK_VOLATILE,
         "volatile",NoFirstAction},
{criStart,TOK_WCHAR_T,
         "wchar_t",NoFirstAction},
{criStart,TOK_WHILE,
         "while",NoFirstAction},

// Complex tokens
{criStart,TOK_ID,
         "[a-zA-Z_][a-zA-Z0-9_]*",NoFirstAction},
{criStart,TOK_EMPTY,
         "0[0-7]*",SetOctSuffixAction},
{criStart,TOK_EMPTY,
         "[1-9][0-9]*",SetDecSuffixAction},
{criStart,TOK_EMPTY,
         "(0x|0X)[0-9a-fA-F]+",SetHexSuffixAction},

{criStart,TOK_FLOATONE,
         "([0-9]+.[0-9]*|[0-9]*.[0-9]+){[eE]{[\\-\\+]}[0-9]+}{[fFlL]}",NoFirstAction},
{criStart,TOK_FLOATTWO,
         "[0-9]+[eE]{[\\-\\+]}[0-9]+{[fFlL]}",NoFirstAction},
{criStart,TOK_EMPTY,
         "{L}\"",SetStringsAction},
{criStart,TOK_EMPTY,
         "{L}'",SetCharactersAction},

// Constaint int suffix tokens
{criOctSuffix,TOK_OCTALINT,
         "({[uU]} ([lL] | ([iI](8|16|32|64)))) | ({[lL]}[uU])",EndSuffixAction},
{criOctSuffix,TOK_OCTALINT,
         NULL,ErrorSuffixAction},

{criDecSuffix,TOK_DECIMALINT,
         "({[uU]} ([lL] | ([iI](8|16|32|64)))) | ({[lL]}[uU])",EndSuffixAction},
{criDecSuffix,TOK_DECIMALINT,
         NULL,ErrorSuffixAction},

{criHexSuffix,TOK_HEXADECIMALINT,
         "({[uU]} ([lL] | ([iI](8|16|32|64)))) | ({[lL]}[uU])",EndSuffixAction},
{criHexSuffix,TOK_HEXADECIMALINT,
         NULL,ErrorSuffixAction},

// Preprocessor tokens
{criStart,TOK_EMPTY,
         "[\\t\\ ]+",MoreAction},
{criStart,TOK_EMPTY,
         "\\12",MoreAction},
{criStart,TOK_PNDPND,
         "##",NoFirstAction},
{criStart,TOK_PND,
         "#",SetDirectiveAction},
{criStart,TOK_EMPTY,
         "//",SetSLCommentsAction},
{criStart,TOK_EMPTY,
         "/\\*",SetMLCommentsAction},

// Special lexical class for recognizing directives at the beginning of the line
{criDirective,TOK_EOF,
             "@",EofAction},
{criDirective,TOK_NEWLINE,
             "\\n",NewLineAction},
{criDirective,TOK_EMPTY,
             "[\\t\\ ]+",EraseAction},
{criDirective,TOK_PNDDEFINE,
             "define",SetDefiningAction},
{criDirective,TOK_PNDIF,
             "if",SetStartAction},
{criDirective,TOK_PNDIFDEF,
             "ifdef",SetStartAction},
{criDirective,TOK_PNDIFNDEF,
             "ifndef",SetStartAction},
{criDirective,TOK_PNDELIF,
             "elif",SetStartAction},
{criDirective,TOK_PNDELSE,
             "else",SetStartAction},
{criDirective,TOK_PNDENDIF,
             "endif",SetStartAction},
{criDirective,TOK_EMPTY,
             "error[\\t\\ ]*",SetPErrorAction},
{criDirective,TOK_PNDINCLUDE,
             "include",SetIncludingAction},
{criDirective,TOK_PNDLINE,
             "line",SetPLineAction},
{criDirective,TOK_PNDPRAGMA,
             "pragma",SetPragmaAction},
{criDirective,TOK_PNDUNDEF,
             "undef",SetStartAction},
{criDirective,TOK_PNDIMPORT,
             "import",SetIncludingAction},
{criDirective,TOK_EMPTY,
             "//",SetSLCommentsAction},
{criDirective,TOK_EMPTY,
             "/\\*",SetMLCommentsAction},
{criDirective,TOK_EMPTY,
             NULL,SetDirErrorAction},

// Lexical class for directive error
{criDirError,TOK_EOF,
             "@",EndDirErrorAction},
{criDirError,TOK_NEWLINE,
             "\\n",EndDirErrorAction},
{criDirError,TOK_EMPTY,
             "~[@ \\n]+",MoreAction},

// Lexical class for error directive
{criPError,TOK_EOF,
           "@",EndPErrorAction},
{criPError,TOK_NEWLINE,
           "\\n",EndPErrorAction},
{criPError,TOK_EMPTY,
           "~[@ \\n]+",MoreAction},

// Lexical class for defining
{criDefining,TOK_EMPTY,
            "[\\t\\ ]+",SkipAction},
{criDefining,TOK_ID,
            "[a-zA-Z_][a-zA-Z0-9_]*",SetStartAction},
{criDefining,TOK_FUNCID,
            "[a-zA-Z_][a-zA-Z0-9_]* \\(",SetStartAction},
{criDefining,TOK_EMPTY,
            "//",SetSLCommentsAction},
{criDefining,TOK_EMPTY,
            "/\\*",SetMLCommentsAction},
{criDefining,TOK_EMPTY,
            NULL,SetDefErrorAction},

// Lexical class for defining error
{criDefError,TOK_EOF,
             "@",EndDefErrorAction},
{criDefError,TOK_NEWLINE,
             "\\n",EndDefErrorAction},
{criDefError,TOK_EMPTY,
             "~[@ \\n]+",SkipAction},

// Lexical class for including
{criIncluding,TOK_EMPTY,
              "[\\t\\ ]+",SkipAction},
{criIncluding,TOK_ID,
              "[a-zA-Z_][a-zA-Z0-9_]*",NULL},
{criIncluding,TOK_EMPTY,
              "\"",SetStringsAction},
{criIncluding,TOK_EMPTY,
              "<",SetFilenamesAction},
{criIncluding,TOK_EMPTY,
              "//",SetSLCommentsAction},
{criIncluding,TOK_EMPTY,
              "/\\*",SetMLCommentsAction},
{criIncluding,TOK_EMPTY,
              NULL,SetIncErrorAction},

// Lexical class for including error
{criIncError,TOK_EOF,
             "@",EndIncErrorAction},
{criIncError,TOK_NEWLINE,
             "\\n",EndIncErrorAction},
{criIncError,TOK_EMPTY,
             "~[@ \\n]+",SkipAction},

// Lexical class for filenames
{criFilenames,TOK_FILENAME,
              ">",SetStartAction},
{criFilenames,TOK_EMPTY,
              "~[> @ \\n]+",MoreAction},
{criFilenames,TOK_EMPTY,
              NULL,SetIncErrorAction},

{criPLine,TOK_EMPTY,
          "[\\t\\ ]+",SkipAction},
{criPLine,TOK_PP_NUMBER,
          "[0-9][0-9]+",SetStartAction},
{criPLine,TOK_EMPTY,
          "//",SetSLCommentsAction},
{criPLine,TOK_EMPTY,
          "/\\*",SetMLCommentsAction},
{criPLine,TOK_EMPTY,
          NULL,SetLineErrorAction},

{criLineError,TOK_EOF,
             "@",EndLineErrorAction},
{criLineError,TOK_NEWLINE,
             "\\n",EndLineErrorAction},
{criLineError,TOK_EMPTY,
             "~[@ \\n]+",SkipAction},

// Lexical class for strings
{criStrings,TOK_STRING,
           "\"",SetStartAction},
{criStrings,TOK_EMPTY,
           "\\\\ {\\\\ | \"}",MoreAction},
{criStrings,TOK_EMPTY,
           "~[\\\\ \" @ \\n]+",MoreAction},
{criStrings,TOK_EMPTY,
           NULL,SetStrErrorAction},

{criStrError,TOK_EOF,
            "@",EndStrErrorAction},
{criStrError,TOK_NEWLINE,
            "\\n",EndStrErrorAction},
{criStrError,TOK_EMPTY,
            "~[@ \\n]+",SkipAction},

// Lexical class for character constants.
{criCharacters,TOK_CHARACTER,
              "'",SetStartAction},
{criCharacters,TOK_EMPTY,
              "\\\\ {\\\\ | '}",MoreAction},
{criCharacters,TOK_EMPTY,
              "~[\\\\ ' @ \\n]+",MoreAction},
{criCharacters,TOK_EMPTY,
              NULL,SetStrErrorAction},

// SLComments tokens
{criSLComments,TOK_EOF,
               "@",EofAction},
{criSLComments,TOK_NEWLINE,
               "\\n",NewLineAction},
{criSLComments,TOK_EMPTY,
               "\\\\",EraseAction},
{criSLComments,TOK_EMPTY,
               "\\\\ \\n",EraseAction},
{criSLComments,TOK_EMPTY,
               "~[@ \\n \\\\]+",EraseAction},

// MLComments tokens
{criMLComments,TOK_EOF,
               "@",EndCommentsErrorAction},
{criMLComments,TOK_EMPTY,
               "\\*/",EndCommentsAction},
{criMLComments,TOK_EMPTY,
               "/\\*",SetMLCommentsAction},
{criMLComments,TOK_EMPTY,
               "\\*",EraseAction},
{criMLComments,TOK_EMPTY,
               "/",EraseAction},
{criMLComments,TOK_EMPTY,
               "~[@ \\* /]+",EraseAction},

// Assembler tokens
{criAsm,TOK_EMPTY,
        "[\\t\\ \\n]*\\{",SetAsmStatAction},
{criAsm,TOK_ASMSTAT,
        "[\\t\\ \\n]*~[@ \\n ;]*",SetStartAction},

{criAsmStat,TOK_EMPTY,
            "~[@ \\}]*",MoreAction},
{criAsmStat,TOK_ASMSTAT,
            "\\}",SetStartAction},
{criAsmStat,TOK_ASMSTAT,
            "@",EndEofAsmAction},

// Pragma tokens
{criPragma,TOK_EMPTY,
           "[\\t\\ ]+",MoreAction},
{criPragma,TOK_EMPTY,
           "[a-zA-Z0-9_]+",SetPragmaErrorAction},
{criPragma,TOK_EMPTY,
           "//",SetSLCommentsAction},
{criPragma,TOK_EMPTY,
           "/\\*",SetMLCommentsAction},
{criPragma,TOK_PRGALIGNMENT,
           "alignment",SetStartAction},
{criPragma,TOK_PRGANON_STRUCT,
           "anon_struct",SetStartAction},
{criPragma,TOK_PRGARGSUSED,
           "argsused",SetStartAction},
{criPragma,TOK_PRGCHECKOPTION,
           "checkoption",SetOptStrAction},
{criPragma,TOK_PRGDEFOPTION,
           "defineonoption",SetDefOptAction},
{criPragma,TOK_PRGUNDEFOPTION,
           "undefineonoption",SetDefOptAction},
{criPragma,TOK_PRGINLINE,
           "inline",SetStartAction},
{criPragma,TOK_PRGMESSAGE,
           "message",SetStartAction},
{criPragma,TOK_PRGNOPUSHOPTWARN,
           "nopushoptwarn",SetStartAction},
{criPragma,TOK_PRGOBSOLETE,
           "obsolete",SetStartAction},
{criPragma,TOK_PRGOPTION,
           "option",SetOptAction},
{criPragma,TOK_PRGWARN,
           "warn",SetStartAction},
{criPragma,TOK_EMPTY,
           NULL,SetPragmaErrorAction},

{criPragmaError,TOK_EOF,
                "@",EndPragmaErrorAction},
{criPragmaError,TOK_NEWLINE,
                "\\n",EndPragmaErrorAction},
{criPragmaError,TOK_EMPTY,
                "~[@ \\n]+",SkipAction},

{criOptStr,TOK_EMPTY,
           "//",SetSLCommentsAction},
{criOptStr,TOK_EMPTY,
           "/\\*",SetMLCommentsAction},
{criOptStr,TOK_EMPTY,
           "/",MoreAction},
{criOptStr,TOK_PRGOPTSTR,
           "~[@ \\n /]*",SetStartAction},

{criDefOpt,TOK_EMPTY,
           "[\\t\\ ]+",MoreAction},
{criDefOpt,TOK_EMPTY,
           "//",SetSLCommentsAction},
{criDefOpt,TOK_EMPTY,
           "/\\*",SetMLCommentsAction},
{criDefOpt,TOK_ID,
           "[a-zA-Z_][a-zA-Z0-9_]*",SetOptStrAction},
{criDefOpt,TOK_EMPTY,
           NULL,EndDefOptAction},

{criOpt,TOK_EMPTY,
        "[\\t\\ ]+",MoreAction},
{criOpt,TOK_EMPTY,
        "//",SetSLCommentsAction},
{criOpt,TOK_EMPTY,
        "/\\*",SetMLCommentsAction},
{criOpt,TOK_PRGPUSH,
        "push",SetOptStrAction},
{criOpt,TOK_PRGPOP,
        "pop",SetOptStrAction},
{criOpt,TOK_EMPTY,
        NULL,EndDefOptAction},

// Special lexical class for missing of ifblock
{criIfBlockFalse,TOK_EOF,
                 "@",EofAction},
{criIfBlockFalse,TOK_EMPTY,
                 "\\n",NewLineIfBlockAction},
//{criIfBlockFalse,TOK_EMPTY,
//                 "[\\t\\ ]+",EraseAction},
{criIfBlockFalse,TOK_PNDIF,
                 "[\\t\\ ]*#[\\t\\ ]*if",EndIfBlockAction},
{criIfBlockFalse,TOK_PNDIFDEF,
                 "[\\t\\ ]*#[\\t\\ ]*ifdef",EndIfBlockAction},
{criIfBlockFalse,TOK_PNDIFNDEF,
                 "[\\t\\ ]*#[\\t\\ ]*ifndef",EndIfBlockAction},
{criIfBlockFalse,TOK_PNDELIF,
                 "[\\t\\ ]*#[\\t\\ ]*elif",EndIfBlockAction},
{criIfBlockFalse,TOK_PNDELSE,
                 "[\\t\\ ]*#[\\t\\ ]*else",EndIfBlockAction},
{criIfBlockFalse,TOK_PNDENDIF,
                 "[\\t\\ ]*#[\\t\\ ]*endif",EndIfBlockAction},
{criIfBlockFalse,TOK_EMPTY,
                 "~[@ \\n / #]+",SkipNoFirstAction},
{criIfBlockFalse,TOK_EMPTY,
                 "/",SkipNoFirstAction},
{criIfBlockFalse,TOK_EMPTY,
                 "#",SkipNoFirstAction},
{criIfBlockFalse,TOK_EMPTY,
                 "/\\*",SetMLCommentsAction}
};

//----------------------------------------------------------------------------------------------------------
TLexTree *CPPLexTree;
TErrorList *ErrorList;

void CreateLexTree (void)
{
  CPPLexTree = new TLexTree (CPPTokenInfos,sizeof(CPPTokenInfos)/sizeof(TTokenInfo));
  ErrorList = new TErrorList (25);
}

void DestroyLexTree (void)
{
  delete CPPLexTree;
  delete ErrorList;
}

#pragma startup CreateLexTree 70
#pragma exit    DestroyLexTree

//----------------------------------------------------------------------------------------------------------
void __fastcall TPreScan::NextChar (void)
{
  if (LastChar == '\n') FLine++;
  LastChar = FChar;

  do
  {
    FChar = (FStream != NULL)? FStream->Read () : EOF;
  }
  while (iscntrl (FChar) && FChar != '\n' && FChar != '\t');
}

int __fastcall TPreScan::NextToken (void)
{
  while (1)
  {
    NextChar ();

    if (LastChar == '\\' && FChar == '\n') NextChar ();
    else break;
  }

  return FLine;
}

//----------------------------------------------------------------------------------------------------------
__fastcall TCPPScan::TCPPScan (TIStream *AStream,const TTokenString &AStreamDesc,
                     TErrorList *AErrorList) : TPreScans (), TLexer (CPPLexTree), FStreamDesc (AStreamDesc),
                     FErrorList (AErrorList), FFirst (true), FComments (0), FOffsetLine (0)
{
  Push (AStream,"",1);
}

__fastcall TCPPScan::~TCPPScan (void)
{
  while (!empty ()) Pop ();
}

int __fastcall TCPPScan::GetChar (void)
{
  int AChar;

  while (!empty ())
  {
    AChar = back ()->LastChar;

    if (AChar != EOF) return AChar;
    else Pop ();
  }

  return EOF;
}

void __fastcall TCPPScan::NextChar (void)
{
  if (!empty ()) FLine = back ()->NextToken ();
}

void __fastcall TCPPScan::BeforeFillText (void)
{
  if (FDescSetChanged)
  {
    StartDescSet = FDescSet;
    FDescSetChanged = false;
  }
}

void __fastcall TCPPScan::Push (TIStream *AStream,const TTokenString &ADesc,int ALine)
{
  push_back (new TPreScan (AStream,ADesc,ALine));
  if (!ADesc.empty ())
  {
    FDescSet.insert (ADesc);
    FDescSetChanged = true;
  }
  NextChar ();
}

void __fastcall TCPPScan::Pop (void)
{
  if (!(back ()->Descriptor ().empty ()))
  {
    FDescSet.erase (back ()->Descriptor ());
    FDescSetChanged = true;
  }

  delete back ();
  pop_back ();
}

void __fastcall TCPPScan::SetLine (int ALine)
{
  FOffsetLine = ALine - FLine;
}

void __fastcall TCPPScan::AddError (const TMsgString &AErrorString,int ALine)
{
  GetErrorList ()->AddError (StreamDesc (),ALine,AErrorString);
}

void __fastcall TCPPScan::AddFatal (const TMsgString &AFatalString,int ALine)
{
  GetErrorList ()->AddFatal (StreamDesc (),ALine,AFatalString);
}

void __fastcall TCPPScan::PushString (const TTokenString &AString,const TTokenString &ADesc)
{
  if (!AString.empty ()) Push (new TStringIStream (AString),ADesc,FLine - AString.count_chars ('\n'));
}
//----------------------------------------------------------------------------------------------------------

