// ---------------------------------------------------------------------------

//#include <fmx.h>
#pragma hdrstop

#include "ShZip.h"
#include <System.zlib.hpp>

// ---------------------------------------------------------------------------

#pragma package(smart_init)

/*************************************************
 *
 * TCompress Implement
 *
 ************************************************/
TCompress::TCompress(const void *buf, int size) {
	CompressProc(buf, size);
}

// ---------------------------------------------------------------------------
TCompress::~TCompress() {
	if (_dwSize > 0)
		delete[]_szBuff;
	_dwPosition = -1;
}

// ---------------------------------------------------------------------------
int TCompress::Read(void *buf, int size) {
	if (size <= 0)
		return 0;
	else if (_dwSize > 0) {
		if (_dwPosition + size - 1 < _dwSize) {
			memcpy(buf, _szBuff + _dwPosition, size);
			_dwPosition += size;
			return size;
		}
		else {
			memcpy(buf, _szBuff + _dwPosition, _dwSize - _dwPosition);
			_dwPosition = _dwSize;
			return _dwSize - _dwPosition;
		}
	}
	else
		return 0;
}

// ---------------------------------------------------------------------------
int TCompress::Size() {
	return _dwSize;
}

// ---------------------------------------------------------------------------
int TCompress::Position() {
	return _dwPosition;
}

// ---------------------------------------------------------------------------
int TCompress::Seek(int Offset) {
	if (_dwPosition + Offset < _dwSize) {
		_dwPosition += Offset;
		return _dwPosition;
	}
	else {
		_dwPosition = _dwSize - 1;
		return _dwPosition;
	}
}

// ---------------------------------------------------------------------------
void TCompress::CompressProc(const void *buf, int size) {
	TMemoryStream *ms = new TMemoryStream;
	ms->Write(buf, size);
	TMemoryStream *dest = new TMemoryStream;
	TCompressionStream *cs = new TCompressionStream(Zlib::clDefault, dest);
	ms->SaveToStream(cs);
	delete cs;
	delete ms;
	_dwSize = sizeof(size) + dest->Size;
	_szBuff = new char[_dwSize];
	memcpy(_szBuff, &size, sizeof(size));
	dest->Position = 0;
	memcpy(_szBuff +sizeof(size), dest->Memory, dest->Size);
	delete dest;
	_dwPosition = 0;
}

// ---------------------------------------------------------------------------
/*************************************************
 *
 * TDeCompress Implement
 *
 ************************************************/
TDecompress::TDecompress(const void *buf, int size) {
	DecompressProc(buf, size);
}

// ---------------------------------------------------------------------------
TDecompress::~TDecompress() {
	if (_dwSize > 0)
		delete[]_szBuff;
	_dwPosition = -1;
}

// ---------------------------------------------------------------------------
int TDecompress::Read(void *buf, int size) {
	if (size <= 0)
		return 0;
	else if (_dwSize > 0) {
		if (_dwPosition + size - 1 < _dwSize) {
			memcpy(buf, _szBuff + _dwPosition, size);
			_dwPosition += size;
			return size;
		}
		else {
			memcpy(buf, _szBuff + _dwPosition, _dwSize - _dwPosition);
			_dwPosition = _dwSize;
			return _dwSize - _dwPosition;
		}
	}
	else
		return 0;
}

// ---------------------------------------------------------------------------
int TDecompress::Size() {
	return _dwSize;
}

// ---------------------------------------------------------------------------
int TDecompress::Position() {
	return _dwPosition;
}

// ---------------------------------------------------------------------------
int TDecompress::Seek(int Offset) {
	if (_dwPosition + Offset < _dwSize) {
		_dwPosition += Offset;
		return _dwPosition;
	}
	else {
		_dwPosition = _dwSize - 1;
		return _dwPosition;
	}
}

// ---------------------------------------------------------------------------
void TDecompress::DecompressProc(const void *buf, int size) {
	TMemoryStream *ms = new TMemoryStream();
	ms->Write(buf, size);
	ms->Position = 0;
	ms->Read(&_dwSize, sizeof(_dwSize));
	TDecompressionStream *cs = new TDecompressionStream(ms);
	_szBuff = new char[_dwSize];
	cs->ReadBuffer(_szBuff, _dwSize);
	delete cs;
	delete ms;
	_dwPosition = 0;
}

// ---------------------------------------------------------------------------
String ZDecompress(String Str) {
	AnsiString sStr, tStr;
	sStr = AnsiString(Str);
	TDecompress *depress = new TDecompress(sStr.c_str(), sStr.Length());
	tStr.SetLength(depress->Size());
	depress->Read(tStr.c_str(), depress->Size());
	delete depress;
	return String(tStr);
}

// ---------------------------------------------------------------------------
String ZCompress(String Str) {
	AnsiString sStr, tStr;
	sStr = AnsiString(Str);
	TCompress *press = new TCompress(sStr.c_str(), sStr.Length());
	tStr.SetLength(press->Size());
	press->Read(tStr.c_str(), press->Size());
	delete press;
	return String(tStr);
}
// ---------------------------------------------------------------------------
