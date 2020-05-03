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

#include "Errmsgs.h"

//----------------------------------------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------------------------------------
char *ErrTokenText[]={
  "",                   // TOK_EMPTY,
  "end of file",        // TOK_EOF,
  "&",                  // TOK_AMPERSAND,
  "&&",                 // TOK_AND,
  "=",                  // TOK_ASSIGNEQUAL,
  "&=",                 // TOK_BITWISEANDEQUAL,
  "|",                  // TOK_BITWISEOR,
  "\\|=",               // TOK_BITWISEOREQUAL,
  "^",                  // TOK_BITWISEXOR,
  "^=",                 // TOK_BITWISEXOREQUAL,
  ",",                  // TOK_COMMA,
  ":",                  // TOK_COLON,
  "/",                  // TOK_DIVIDE,
  "/=",                 // TOK_DIVIDEEQUAL,
  ".",                  // TOK_DOT,
  ".*",                 // TOK_DOTMBR,
  "...",                // TOK_ELLIPSIS,
  "==",                 // TOK_EQUAL,
  ">",                  // TOK_GREATERTHAN,
  ">=",                 // TOK_GREATERTHANOREQUALTO,
  "{",                  // TOK_LCURLY,
  "<",                  // TOK_LESSTHAN,
  "<=",                 // TOK_LESSTHANOREQUALTO,
  "(",                  // TOK_LPAREN,
  "[",                  // TOK_LSQUARE,
  "-",                  // TOK_MINUS,
  "-=",                 // TOK_MINUSEQUAL,
  "--",                 // TOK_MINUSMINUS,
  "%",                  // TOK_MOD,
  "%=",                 // TOK_MODEQUAL,
  "!",                  // TOK_NOT,
  "!=",                 // TOK_NOTEQUAL,
  "||",                 // TOK_OR,
  "+",                  // TOK_PLUS,
  "+=",                 // TOK_PLUSEQUAL,
  "++",                 // TOK_PLUSPLUS,
  "->",                 // TOK_POINTERTO,
  "->*",                // TOK_POINTERTOMBR,
  "?",                  // TOK_QUESTIONMARK,
  "}",                  // TOK_RCURLY,
  ")",                  // TOK_RPAREN,
  "]",                  // TOK_RSQUARE,
  "::",                 // TOK_SCOPE,
  ";",                  // TOK_SEMICOLON,
  "<<",                 // TOK_SHIFTLEFT,
  "<<=",                // TOK_SHIFTLEFTEQUAL,
  ">>",                 // TOK_SHIFTRIGHT,
  ">>=",                // TOK_SHIFTRIGHTEQUAL,
  "*",                  // TOK_STAR,
  "~",                  // TOK_TILDE,
  "*=",                 // TOK_TIMESEQUAL,

  "asm",                // TOK_ASM,
  "auto",               // TOK_AUTO,
  "__automated",        // TOK_AUTOMATED,
  "bool",               // TOK_BOOL,
  "break",              // TOK_BREAK,
  "case",               // TOK_CASE,
  "catch",              // TOK_CATCH,
  "cdecl",              // TOK_CDECL,
  "char",               // TOK_CHAR,
  "class",              // TOK_CLASS,
  "__classid",          // TOK_CLASSID,
  "__closure",          // TOK_CLOSURE,
  "const",              // TOK_CONST,
  "const_cast",         // TOK_CONST_CAST,
  "continue",           // TOK_CONTINUE,
  "__declspec",         // TOK_DECLSPEC,
  "default",            // TOK_DEFAULT,
  "delete",             // TOK_DELETE,
  "__dispid",           // TOK_DISPID,
  "do",                 // TOK_DO,
  "double",             // TOK_DOUBLE,
  "dynamic_cast",       // TOK_DYNAMIC_CAST,
  "else",               // TOK_ELSE,
  "enum",               // TOK_ENUM,
  "__except",           // TOK_EXCEPT,
  "explicit",           // TOK_EXPLICIT,
  "export",             // TOK_EXPORT,
  "extern",             // TOK_EXTERN,
  "false",              // TOK_FALSE,
  "_fastcall",          // TOK_FASTCALL,
  "__finally",          // TOK_FINALLY,
  "float",              // TOK_FLOAT,
  "for",                // TOK_FOR,
  "friend",             // TOK_FRIEND,
  "goto",               // TOK_GOTO,
  "if",                 // TOK_IF,
  "_import",            // TOK_IMPORT,
  "inline",             // TOK_INLINE,
  "int",                // TOK_INT,
  "__int8",             // TOK_INT8,
  "__int16",            // TOK_INT16,
  "__int32",            // TOK_INT32,
  "__int64",            // TOK_INT64,
  "long",               // TOK_LONG,
  "__msfastcall",       // TOK_MSFASTCALL,
  "__msreturn",         // TOK_MSRETURN,
  "mutable",            // TOK_MUTABLE,
  "namespace",          // TOK_NAMESPACE,
  "new",                // TOK_NEW,
  "operator",           // TOK_OPERATOR,
  "pascal",             // TOK_PASCAL,
  "private",            // TOK_PRIVATE,
  "__property",         // TOK_PROPERTY,
  "protected",          // TOK_PROTECTED,
  "public",             // TOK_PUBLIC,
  "__published",        // TOK_PUBLISHED,
  "register",           // TOK_REGISTER,
  "reinterpret_cast",   // TOK_REINTERPRET_CAST,
  "return",             // TOK_RETURN,
  "__rtti",             // TOK_RTTI,
  "short",              // TOK_SHORT,
  "signed",             // TOK_SIGNED,
  "sizeof",             // TOK_SIZEOF,
  "static",             // TOK_STATIC,
  "static_cast",        // TOK_STATIC_CAST,
  "_stdcall",           // TOK_STDCALL,
  "struct",             // TOK_STRUCT,
  "switch",             // TOK_SWITCH,
  "template",           // TOK_TEMPLATE,
  "this",               // TOK_THIS,
  "__thread",           // TOK_THREAD,
  "throw",              // TOK_THROW,
  "true",               // TOK_TRUE,
  "try",                // TOK_TRY,
  "typedef",            // TOK_TYPEDEF,
  "typeid",             // TOK_TYPEID,
  "typename",           // TOK_TYPENAME,
  "union",              // TOK_UNION,
  "unsigned",           // TOK_UNSIGNED,
  "using",              // TOK_USING,
  "virtual",            // TOK_VIRTUAL,
  "void",               // TOK_VOID,
  "volatile",           // TOK_VOLATILE,
  "wchar_t",            // TOK_WCHAR_T,
  "while",              // TOK_WHILE,

  "id",                 // TOK_ID,
  "octalint",           // TOK_OCTALINT,
  "decimalint",         // TOK_DECIMALINT,
  "hexdecimalint",      // TOK_HEXADECIMALINT,
  "floatone",           // TOK_FLOATONE,
  "floattwo",           // TOK_FLOATTWO,
  "##",                 // TOK_PNDPND,
  "#",                  // TOK_PND,
  "pp_number",          // TOK_PP_NUMBER,
  "#define",            // TOK_PNDDEFINE,
  "#if",                // TOK_PNDIF,
  "#ifdef",             // TOK_PNDIFDEF,
  "#ifndef",            // TOK_PNDIFNDEF,
  "#elif",              // TOK_PNDELIF,
  "#else",              // TOK_PNDELSE,
  "#endif",             // TOK_PNDENDIF,
  "#include",           // TOK_PNDINCLUDE,
  "#line",              // TOK_PNDLINE,
  "#pragma",            // TOK_PNDPRAGMA,
  "#undef",             // TOK_PNDUNDEF,
  "#import",            // TOK_PNDIMPORT,
  "funcid",             // TOK_FUNCID,
  "\"string\"",         // TOK_STRING,
  "'character'",        // TOK_CHARACTER,
  "filename",           // TOK_FILENAME,
  "asm statement",      // TOK_ASMSTAT,

  "alignment",          // TOK_PRGALIGNMENT,
  "anon_struct",        // TOK_PRGANON_STRUCT,
  "argsused",           // TOK_PRGARGSUSED,
  "checkoption",        // TOK_PRGCHECKOPTION,
  "defineonoption",     // TOK_PRGDEFOPTION,
  "undefineonoption",   // TOK_PRGUNDEFOPTION,
  "inline",             // TOK_PRGINLINE,
  "message",            // TOK_PRGMESSAGE,
  "nopushoptwarn",      // TOK_PRGNOPUSHOPTWARN,
  "obsolete",           // TOK_PRGOBSOLETE,
  "option",             // TOK_PRGOPTION,
  "warn",               // TOK_PRGWARN,
  "options string",     // TOK_PRGOPTSTR,
  "push",               // TOK_PRGPUSH,
  "pop",                // TOK_PRGPOP,

  "\\n",                 // TOK_NEWLINE
};

//----------------------------------------------------------------------------------------------------------
TMsgInfo UnterminatedStringMsg={0,"Unterminated string or character constant"};
TMsgInfo UnknownDirMsg={0,"Unknown preprocessor directive : '%s'"};
TMsgInfo DefineNeedsIdMsg={0,"Define directive needs an identifier"};
TMsgInfo BadLineDirMsg={0,"Bad line directive syntax"};
TMsgInfo UnexpectedEOFCommentMsg={0,"Unexpected end of file in comment started on line %d"};
TMsgInfo IllegalNumberSuffixMsg={0,"Illegal number suffix"};
TMsgInfo ErrorDirectiveMsg={0,"Error directive : '%s'"};
TMsgInfo ConstantTooLargeMsg={0,"Numeric constant too large"};
TMsgInfo InvalidCharConstMsg={0,"Invalid character constant"};
TMsgInfo IllegalUseFloatPointMsg={0,"Illegal use of floating point"};
TMsgInfo IllegalUsePtrMsg={0,"Illegal use of pointer"};
TMsgInfo NotAllowedTypeMsg={0,"Not an allowed type"};
TMsgInfo IncompatibleTypeConvMsg={0,"Incompatible type conversion"};
TMsgInfo LvalueRequiredMsg={0,"Lvalue required"};
TMsgInfo InvalidPtrAddMsg={0,"Invalid pointer addition"};
TMsgInfo SizeTypeUnknownMsg={0,"Size of the type is unknown or zero"};
TMsgInfo IllegalPtrSubMsg={0,"Illegal pointer subtraction"};
TMsgInfo ExpectedMsg={0,"'%s' expected"};
TMsgInfo UnableOpenIncludeFileMsg={0,"Unable to open include file '%s'"};
TMsgInfo MisplacedElifMsg={0,"Misplaced elif directive"};
TMsgInfo MisplacedElseMsg={0,"Misplaced else directive"};
TMsgInfo MisplacedEndifMsg={0,"Misplaced endif directive"};
TMsgInfo UnexpectedEOFConditionalMsg={0,"Unexpected end of file in conditional started on line %d"};
TMsgInfo BadDirSyntaxMsg={0,"Bad %s directive syntax"};
TMsgInfo BadFilenameIncludeMsg={0,"Bad file name format in include directive"};
TMsgInfo BadFilenameLineMsg={0,"Bad file name format in line directive"};
TMsgInfo MacroArgumentSyntaxMsg={0,"Macro argument syntax error"};
TMsgInfo InvalidMacroArgSeparatorMsg={0,"Invalid macro argument separator"};
TMsgInfo RedefinitionNotIdentMsg={0,"Redefinition of '%s' is not identical"};
TMsgInfo ImportDirMsg={0,"Use of the #import directive is not recommended. You should use TLIBIMP.EXE"};
TMsgInfo MisplacedDirMsg={0,"Misplaced '%s' directive"};
TMsgInfo WrongNumberArgMacroMsg={0,"Wrong number of arguments in call of macro '%s'"};
TMsgInfo ConstantExpReqMsg={0,"Constant expression required"};
TMsgInfo MultipleDeclMsg={0,"Multiple declaration for '%s'"};
TMsgInfo TooManyTypesDeclMsg={0,"Too many types in declaration"};
TMsgInfo AlreadyIncludedMsg={0,"'%s' has already been included"};
TMsgInfo StorageNotAllowedMsg={0,"Storage class '%s' is not allowed here"};
TMsgInfo TooManyStorageMsg={0,"Too many storage classes in declaration"};
TMsgInfo UseDeclspecMsg={0,"Use __declspec(spec1[, spec2]) to combine multiple __declspec's"};
TMsgInfo ModifierAlreadyIncludedMsg={0,"'%s' modifier has already been included"};
TMsgInfo ConflictingTypeModifiersMsg={0,"Conflicting type modifiers"};
TMsgInfo ExpressionSyntaxMsg={0,"Expression syntax"};
TMsgInfo NoColonMsg={0,"No : following the ?"};
TMsgInfo ArrayBoundsMsg={0,"Array bounds missing ]"};
TMsgInfo ArrayIsEmptyMsg={0,"Array must have at least one element"};
TMsgInfo DeclarationSyntaxMsg={0,"Declaration syntax error"};
TMsgInfo DeclarationExpectedMsg={0,"Declaration was expected"};
TMsgInfo BadPragmaSyntaxMsg={0,"Bad pragma directive syntax"};
TMsgInfo IllFormedPragmaMsg={0,"Ill-formed pragma"};
TMsgInfo StatementMissingMsg={0,"Compound statement missing '}'"};
TMsgInfo AsmStatementMissedMsg={0,"ASM statement will be missed"};
TMsgInfo IncorrectCmdLineOptMsg={0,"Incorrect command line option: %s"};
TMsgInfo IncorrectPragmaDirOptMsg={0,"Incorrect pragma directive option: %s"};
TMsgInfo AlignmentAndEnumSizeMsg={0,"The alignment is %d bytes, the enum size is %d bytes"};
TMsgInfo PragmaCheckFailedMsg={0,"Pragma checkoption failed: options are not as expected"};
TMsgInfo PragmaOptPopMsg={0,"Pragma option pop with no matching option push"};
TMsgInfo NotAllowedOptionPopMsg={0,"Nothing allowed after pragma option pop"};
TMsgInfo PrevOptNotRestoredMsg={0,"Previous options and warnings not restored"};
TMsgInfo UndefSymbolMsg={0,"Undefined symbol '%s'"};
TMsgInfo CouldNotFindFileMsg={0,"Could not find file '%s'"};
TMsgInfo NoFileNameGivenMsg={0,"No file name given"};

//----------------------------------------------------------------------------------------------------------

