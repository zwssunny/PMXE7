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

#include "istream.h"

//----------------------------------------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------------------------------------
void __fastcall TFileOStream::Write (const TTokenString &AString)
{
  unsigned int bytes,n;

  for (bytes=0; bytes < AString.length (); bytes += n)
  {
    n = min (FEnd - FDataEnd,(int)(AString.length () - bytes));
    memcpy (FDataEnd,AString.c_str () + bytes,n);
    FDataEnd += n;

    if (FEnd == FDataEnd) WriteData ();
  }
}

//----------------------------------------------------------------------------------------------------------
