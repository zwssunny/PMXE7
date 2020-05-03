//---------------------------------------------------------------------------

#pragma hdrstop

#include "BufferBitmapSource.h"
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace qrviddec {

BufferBitmapSource::BufferBitmapSource(int inWidth, int inHeight,  unsigned char* inBuffer)
:LuminanceSource(inWidth,inHeight)
{
	width = inWidth;
	height = inHeight;
	buffer = inBuffer;
}

BufferBitmapSource::~BufferBitmapSource()
{
}

int BufferBitmapSource::getWidth() const
{
	return width;
}

int BufferBitmapSource::getHeight() const
{
	return height;
}

ArrayRef<char> BufferBitmapSource::getRow(int y, ArrayRef<char> row) const
{
	if (y < 0 || y >= height)
	{
		fprintf(stderr, "ERROR, attempted to read row %d of a %d height image.\n", y, height);
		return NULL;
	}
	// WARNING: NO ERROR CHECKING! You will want to add some in your code.
	if (row == NULL) row =  ArrayRef<char>(width);
	for (int x = 0; x < width; x ++)
	{
		row[x] = buffer[y*width+x];
	}
	return row;
}

ArrayRef<char> BufferBitmapSource::getMatrix() const
{
  int length = getWidth() * getHeight();
  ArrayRef<char> Matrix(length);
  memcpy(&Matrix[0], &buffer[0], length);
  return Matrix;
}

}