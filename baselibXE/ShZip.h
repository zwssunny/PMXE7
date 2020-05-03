// ---------------------------------------------------------------------------

#ifndef ShZipH
#define ShZipH
#include <System.Classes.hpp>

// ---------------------------------------------------------------------------
class PACKAGE TCompress {
public:
	TCompress(const void *buf, int size);
	~TCompress();

	int Read(void *buf, int size);
	int Size();
	int Position();
	int Seek(int Offset);

protected:
	virtual void CompressProc(const void *buf, int size);

private:
	int _dwSize;
	int _dwPosition;
	char *_szBuff;
};

class PACKAGE TDecompress {
public:
	TDecompress(const void *buf, int size);
	~TDecompress();

	int Read(void *buf, int size);
	int Size();
	int Position();
	int Seek(int Offset);

protected:
	virtual void DecompressProc(const void *buf, int size);

private:
	int _dwSize;
	int _dwPosition;
	char *_szBuff;
};

extern PACKAGE String ZDecompress(String Str);
extern PACKAGE String ZCompress(String Str);
#endif
