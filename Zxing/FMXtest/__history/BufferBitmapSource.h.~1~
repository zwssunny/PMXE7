//---------------------------------------------------------------------------

#ifndef BufferBitmapSourceH
#define BufferBitmapSourceH
//---------------------------------------------------------------------------
#include <zxing/LuminanceSource.h>
#include <stdio.h>
#include <stdlib.h>
using namespace zxing;
namespace qrviddec {

class BufferBitmapSource : public LuminanceSource {
private:
  int width, height;
  unsigned char*  buffer;

public:
  BufferBitmapSource(int inWidth, int inHeight,  unsigned char* inBuffer);
  ~BufferBitmapSource();

  int getWidth() const;
  int getHeight() const;
  ArrayRef<char> getRow(int y, ArrayRef<char> row) const;
  ArrayRef<char> getMatrix() const;
};
}
#endif
