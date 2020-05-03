//---------------------------------------------------------------------------
#ifndef VORH
#define VORH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TVOR : public TCustomControl
{
private:
  void SetCoordinateSystem (TCanvas &canvas) ;
  void DrawDot (TCanvas &canvas, int x, int y) ;
  void DrawIndicator (TCanvas &canvas) ;
  void DrawCourseDeviation (TCanvas &canvas) ;
  void DrawCourseWheel (TCanvas &canvas) ;
  void DrawCourseIndex (TCanvas &canvas) ;
  void DrawReciprocalCourseIndex (TCanvas &canvas) ;
  void DrawToFrom (TCanvas &canvas) ;
  void DrawGlideSlope (TCanvas &canvas) ;
  void DrawHash (TCanvas &canvas, int X, int y) ;

  Graphics::TBitmap *bitmap ;

  // Property Functions
  void __fastcall SetCourse (int newcourse) ;
  void __fastcall SetRadial (int newradial) ;

  // Property Values
  int course ;
  int radial ;
  // Event Property Values
  TNotifyEvent oncoursechanged ;

protected:
  // Message Procedures
  virtual void __fastcall WMEraseBkgnd (TWMEraseBkgnd &) ;
  // Overridden Procedures.
  DYNAMIC void __fastcall KeyDown(Word &Key,  TShiftState Shift) ;
  DYNAMIC void __fastcall MouseDown (TMouseButton button,
                                     TShiftState shift,
                                     int x, int y) ;
  virtual void __fastcall Paint () ;

BEGIN_MESSAGE_MAP
   MESSAGE_HANDLER(WM_ERASEBKGND,TWMEraseBkgnd,WMEraseBkgnd)
END_MESSAGE_MAP (TCustomControl) ;

public:
  __fastcall TVOR(TComponent* Owner);
  virtual __fastcall ~TVOR() ;

__published:
  __property int Course = { read=course, write=SetCourse } ;
  __property int Radial = { read=radial, write=SetRadial } ;
  __property TabStop ;
  __property TNotifyEvent OnCourseChanged = { read=oncoursechanged,
                                              write=oncoursechanged} ;
};
//---------------------------------------------------------------------------
#endif
