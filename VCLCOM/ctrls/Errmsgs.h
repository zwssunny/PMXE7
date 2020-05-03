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

#ifndef ErrmsgsH
#define ErrmsgsH

#include <sysutils.hpp>
//----------------------------------------------------------------------------------------------------------
extern PACKAGE char *ErrTokenText[];

struct PACKAGE TMsgInfo
{
  int Type;
  char *Msg;
};

extern PACKAGE TMsgInfo UnterminatedStringMsg;
extern PACKAGE TMsgInfo UnknownDirMsg;
extern PACKAGE TMsgInfo DefineNeedsIdMsg;
extern PACKAGE TMsgInfo BadLineDirMsg;
extern PACKAGE TMsgInfo UnexpectedEOFCommentMsg;
extern PACKAGE TMsgInfo IllegalNumberSuffixMsg;
extern PACKAGE TMsgInfo ErrorDirectiveMsg;
extern PACKAGE TMsgInfo ConstantTooLargeMsg;
extern PACKAGE TMsgInfo InvalidCharConstMsg;
extern PACKAGE TMsgInfo IllegalUseFloatPointMsg;
extern PACKAGE TMsgInfo IllegalUsePtrMsg;
extern PACKAGE TMsgInfo NotAllowedTypeMsg;
extern PACKAGE TMsgInfo IncompatibleTypeConvMsg;
extern PACKAGE TMsgInfo LvalueRequiredMsg;
extern PACKAGE TMsgInfo InvalidPtrAddMsg;
extern PACKAGE TMsgInfo SizeTypeUnknownMsg;
extern PACKAGE TMsgInfo IllegalPtrSubMsg;
extern PACKAGE TMsgInfo ExpectedMsg;
extern PACKAGE TMsgInfo UnableOpenIncludeFileMsg;
extern PACKAGE TMsgInfo MisplacedElifMsg;
extern PACKAGE TMsgInfo MisplacedElseMsg;
extern PACKAGE TMsgInfo MisplacedEndifMsg;
extern PACKAGE TMsgInfo UnexpectedEOFConditionalMsg;
extern PACKAGE TMsgInfo BadDirSyntaxMsg;
extern PACKAGE TMsgInfo BadFilenameIncludeMsg;
extern PACKAGE TMsgInfo BadFilenameLineMsg;
extern PACKAGE TMsgInfo MacroArgumentSyntaxMsg;
extern PACKAGE TMsgInfo InvalidMacroArgSeparatorMsg;
extern PACKAGE TMsgInfo RedefinitionNotIdentMsg;
extern PACKAGE TMsgInfo ImportDirMsg;
extern PACKAGE TMsgInfo MisplacedDirMsg;
extern PACKAGE TMsgInfo WrongNumberArgMacroMsg;
extern PACKAGE TMsgInfo ConstantExpReqMsg;
extern PACKAGE TMsgInfo MultipleDeclMsg;
extern PACKAGE TMsgInfo TooManyTypesDeclMsg;
extern PACKAGE TMsgInfo AlreadyIncludedMsg;
extern PACKAGE TMsgInfo StorageNotAllowedMsg;
extern PACKAGE TMsgInfo TooManyStorageMsg;
extern PACKAGE TMsgInfo UseDeclspecMsg;
extern PACKAGE TMsgInfo ModifierAlreadyIncludedMsg;
extern PACKAGE TMsgInfo ConflictingTypeModifiersMsg;
extern PACKAGE TMsgInfo ExpressionSyntaxMsg;
extern PACKAGE TMsgInfo NoColonMsg;
extern PACKAGE TMsgInfo ArrayBoundsMsg;
extern PACKAGE TMsgInfo ArrayIsEmptyMsg;
extern PACKAGE TMsgInfo DeclarationSyntaxMsg;
extern PACKAGE TMsgInfo DeclarationExpectedMsg;
extern PACKAGE TMsgInfo BadPragmaSyntaxMsg;
extern PACKAGE TMsgInfo IllFormedPragmaMsg;
extern PACKAGE TMsgInfo StatementMissingMsg;
extern PACKAGE TMsgInfo AsmStatementMissedMsg;
extern PACKAGE TMsgInfo IncorrectCmdLineOptMsg;
extern PACKAGE TMsgInfo IncorrectPragmaDirOptMsg;
extern PACKAGE TMsgInfo AlignmentAndEnumSizeMsg;
extern PACKAGE TMsgInfo PragmaCheckFailedMsg;
extern PACKAGE TMsgInfo PragmaOptPopMsg;
extern PACKAGE TMsgInfo NotAllowedOptionPopMsg;
extern PACKAGE TMsgInfo PrevOptNotRestoredMsg;
extern PACKAGE TMsgInfo UndefSymbolMsg;
extern PACKAGE TMsgInfo CouldNotFindFileMsg;
extern PACKAGE TMsgInfo NoFileNameGivenMsg;

//----------------------------------------------------------------------------------------------------------
#endif
