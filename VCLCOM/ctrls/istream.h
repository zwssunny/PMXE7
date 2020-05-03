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

#ifndef istreamH
#define istreamH

#include "lexer.h"
#include "errmsgs.h"
#include <classes.hpp>

//----------------------------------------------------------------------------------------------------------
class PACKAGE TIStream
{
private:

protected:
  unsigned char *FBegin;
  unsigned char *FEnd;
  unsigned char *FDataEnd;
  unsigned char *FPtr;

  virtual void __fastcall ReadData (void) = 0;

public:
  __fastcall TIStream (unsigned int capacity)
  {
    FPtr = FDataEnd = FBegin = new unsigned char[max (capacity,1u)];
    FEnd = FBegin + capacity;
  }

  virtual __fastcall ~TIStream () { delete [] FBegin; }

  int __fastcall Read (void)
  {
    if (FPtr == FDataEnd)
    {
      FPtr = FBegin;
      ReadData ();
    }

    return (FPtr < FDataEnd)? *FPtr++ : -1;
  }
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TStringIStream : public TIStream
{
private:
protected:
  virtual void __fastcall ReadData (void) { FDataEnd = FBegin; }

public:
  __fastcall TStringIStream (const TTokenString &AString) : TIStream (AString.length ())
  {
    memcpy (FBegin,AString.c_str (),AString.length ());
    FDataEnd = FEnd;
  }

  virtual __fastcall ~TStringIStream () { }
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TFileIStream : public TIStream
{
private:
  HANDLE FHandle;

protected:
  virtual void __fastcall ReadData (void)
  {
    DWORD bytes;

    if (!ReadFile (FHandle,FBegin,FEnd - FBegin,&bytes,NULL)) bytes=0;
    FDataEnd = FBegin + bytes;
  }

public:
  __fastcall TFileIStream (const TTokenString &AFileName,unsigned int capacity = 1024*16) : TIStream (max (capacity,1024u))
  {
	FHandle = CreateFileA (AFileName.c_str (),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);

	if (FHandle == INVALID_HANDLE_VALUE) throw EFOpenError (AnsiString ().sprintf (CouldNotFindFileMsg.Msg,AFileName.c_str ()),0);
  }

  virtual __fastcall ~TFileIStream () { CloseHandle (FHandle); }
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TStreamIStream : public TIStream
{
private:
  TStream *FStream;

protected:
  virtual void __fastcall ReadData (void)
  {
    DWORD bytes;

    bytes = FStream->Read (FBegin,FEnd - FBegin);
    FDataEnd = FBegin + bytes;
  }

public:
  __fastcall TStreamIStream (TStream *AStream,unsigned int capacity = 1024*16) : TIStream (max (capacity,1024u))
  {
    FStream = AStream;
  }

  virtual __fastcall ~TStreamIStream () {}
};

//----------------------------------------------------------------------------------------------------------
class PACKAGE TFileOStream
{
private:
  unsigned char *FBegin;
  unsigned char *FEnd;
  unsigned char *FDataEnd;
  HANDLE FHandle;

protected:
  virtual void __fastcall WriteData (void)
  {
    DWORD bytes;

    if (!WriteFile (FHandle,FBegin,FDataEnd - FBegin,&bytes,NULL)) bytes=0;
    FDataEnd = FBegin;
  }

public:
  __fastcall TFileOStream (const TTokenString &AFileName,unsigned int capacity = 1024*16)
  {
	FHandle = CreateFileA (AFileName.c_str (),GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,NULL);

	if (FHandle == INVALID_HANDLE_VALUE) throw EFOpenError (AnsiString ().sprintf (CouldNotFindFileMsg.Msg,AFileName.c_str ()),0);

    capacity = max (capacity,1024u);
    FDataEnd = FBegin = new unsigned char[capacity];
    FEnd = FBegin + capacity;
  }

  virtual __fastcall ~TFileOStream () { WriteData (); CloseHandle (FHandle); delete [] FBegin; }

  void __fastcall Write (const TTokenString &AString);
};

//----------------------------------------------------------------------------------------------------------
#endif
