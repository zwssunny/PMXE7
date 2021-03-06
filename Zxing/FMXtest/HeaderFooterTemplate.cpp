//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HeaderFooterTemplate.h"
#include <string>
#include "UnicodeAndStdstring.h"
#include "ImageReaderSource.h"
#include "BufferBitmapSource.h"
#include <System.Ioutils.hpp>
/*
<AllPackageLibs>rtl.lib;fmx.lib;BigIntlib.lib;ZxingCommon.lib;Azteclib.lib;Datamatrixlib.lib;QRCodelib.lib;Multilib.lib;Onedlib.lib;Pdf417lib.lib;</AllPackageLibs>
#if defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#pragma link "libBigIntlib.a"
#pragma link "libZxingCommon.a"
#pragma link "libAzteclib.a"
#pragma link "libDatamatrixlib.a"
#pragma link "libQRCodelib.a"
#pragma link "libMultilib.a"
#pragma link "libOnedlib.a"
#pragma link "libPdf417lib.a"
#else
#pragma link "BigIntlib.lib"
#pragma link "ZxingCommon.lib"
#pragma link "Azteclib.lib"
#pragma link "Datamatrixlib.lib"
#pragma link "QRCodelib.lib"
#pragma link "Multilib.lib"
#pragma link "Onedlib.lib"
#pragma link "Pdf417lib.lib"
#endif
*/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
THeaderFooterForm *HeaderFooterForm;
vector<Ref<Result> > decode(Ref<BinaryBitmap> image, DecodeHints hints) {
  Ref<Reader> reader(new MultiFormatReader);
  return vector<Ref<Result> >(1, reader->decode(image, hints));
}

vector<Ref<Result> > decode_multi(Ref<BinaryBitmap> image, DecodeHints hints) {
  MultiFormatReader delegate;
  GenericMultipleBarcodeReader reader(delegate);
  return reader.decodeMultiple(image, hints);
}
//---------------------------------------------------------------------------
__fastcall THeaderFooterForm::THeaderFooterForm(TComponent* Owner)
	: TForm(Owner)
{
#if  defined(__ANDROID__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	 AppPath= System::Ioutils::TPath::GetDocumentsPath();
	 btFile->Visible=false;
#else
	AppPath = ExtractFilePath(ParamStr(0));
#endif
}
//---------------------------------------------------------------------------
Ref<LuminanceSource> THeaderFooterForm::BarcodePicToLuminanceSource(string filename)
{
   Ref<LuminanceSource> source;
   try {
	  source = ImageReaderSource::create(filename);
	} catch (const zxing::IllegalArgumentException &e) {
	  throw zxing::Exception(e.what());
	}
  return source;
}
Ref<LuminanceSource> THeaderFooterForm::ImageToLuminanceSource(TBitmap *Image)
{
	Ref<LuminanceSource> source;
	TMemoryStream *ms=new TMemoryStream();
   try {
	  Image->SaveToStream(ms);
	  unsigned char* inBuffer=new unsigned char[ms->Size+1];
	  ms->Position=0;
	  ms->Read(inBuffer,ms->Size);
	  inBuffer[ms->Size]=0;
	  source= ImageReaderSource::create(inBuffer,ms->Size);
	} catch (const zxing::IllegalArgumentException &e) {
	  throw zxing::Exception(e.what());
	}
  return source;
}
int THeaderFooterForm::read_image(Ref<LuminanceSource> source, bool hybrid,bool search_multi) {
  vector<Ref<Result> > results;
  string cell_result;
  AnsiString Ansi_result;
  int res = -1;

  try {
    Ref<Binarizer> binarizer;
    if (hybrid) {
      binarizer = new HybridBinarizer(source);
    } else {
      binarizer = new GlobalHistogramBinarizer(source);
    }
	DecodeHints hints(DecodeHints::DEFAULT_HINT);
	hints.setTryHarder(true);
    Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
	if (search_multi) {
	  results = decode_multi(binary, hints);
	} else {
	  results = decode(binary, hints);
	}
	res = 0;
  } catch (const ReaderException& e) {
	cell_result = "zxing::ReaderException: " + string(e.what());
    res = -2;
  } catch (const zxing::IllegalArgumentException& e) {
	cell_result = "zxing::IllegalArgumentException: " + string(e.what());
    res = -3;
  } catch (const zxing::Exception& e) {
    cell_result = "zxing::Exception: " + string(e.what());
    res = -4;
  } catch (const std::exception& e) {
	cell_result = "std::exception: " + string(e.what());
    res = -5;
  }
	edError->Text=stdStringToUnicodeString(cell_result);
  if (results.size() == 1) {
	 std::string result= results[0]->getText()->getText();
	 edResult->Text=stdStringToUnicodeString(result);
	 std::string formatresult=BarcodeFormat::barcodeFormatNames[results[0]->getBarcodeFormat()];
	 edFormat->Text=stdStringToUnicodeString(formatresult) ;
	res = -6;
  }
  return res;
}


void __fastcall THeaderFooterForm::acDecodeExecute(TObject *Sender)
{
  if(!ImageContainer->Bitmap->IsEmpty())
  {
	 Ref<LuminanceSource> Source=ImageToLuminanceSource(ImageContainer->Bitmap);
	 read_image(Source,false,false);
  }
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::TakePhotoFromLibraryAction1DidFinishTaking(TBitmap *Image)

{
 	if (Image->Width > 1024) {
		auto ScaleFactor = Image->Width / 1024;
		Image->Resize(static_cast<int>(Image->Width / ScaleFactor),
			static_cast<int>(Image->Height / ScaleFactor));
	}
	ImageContainer->Bitmap->Assign(Image);
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::TakePhotoFromCameraAction1DidFinishTaking(TBitmap *Image)

{
 	if (Image->Width > 1024) {
		auto ScaleFactor = Image->Width / 1024;
		Image->Resize(static_cast<int>(Image->Width / ScaleFactor),
			static_cast<int>(Image->Height / ScaleFactor));
	}
	ImageContainer->Bitmap->Assign(Image);
}
//---------------------------------------------------------------------------


void __fastcall THeaderFooterForm::btFileClick(TObject *Sender)
{
 // System::String picFile=System::Ioutils::TPath::Combine(AppPath, "tm1.jpg");
  System::String picFile=System::Ioutils::TPath::Combine(AppPath, "tm2.png");
  if(FileExists(picFile))
  {
	ImageContainer->Bitmap->LoadFromFile(picFile);
 /*	TMemoryStream *ms=new TMemoryStream();
   try{
   //	ms->LoadFromFile(picFile);
	ImageContainer->Bitmap->SaveToStream(ms);
 	int csize=ms->Size;
	ArrayRef<char> inBuffer=ArrayRef<char>(csize);
	ms->Position=0;
	ms->Read(&inBuffer[0],csize);
	delete ms;
   Ref<LuminanceSource> Source=Ref<LuminanceSource>(new ImageReaderSource(inBuffer,ImageContainer->Bitmap->Width,ImageContainer->Bitmap->Height, 4));
//	Ref<LuminanceSource> Source=Ref<LuminanceSource>(new BufferBitmapSource(ImageContainer->Bitmap->Width,ImageContainer->Bitmap->Height, inBuffer));
   //	Ref<LuminanceSource> Source=BarcodePicToLuminanceSource(UnicodeStringTostdString(picFile));
	read_image(Source,false,false);
   }
   catch(const zxing::IllegalArgumentException& e)
   {

	   throw zxing::Exception(e.what());
   }
    */
  }
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterForm::acCloseExecute(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

