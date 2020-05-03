//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "VOR.h"

const int DotInterval = 100 ;       // Interval between course deviation dots.
const int DotRadius = DotInterval / 4 ; // Radius of a deviation dot.
// Inner and Outer radii of the course selection wheel
const int CourseOuterRadius = 1325 ;
const int CourseInnerRadius = 900 ;
// Logical window width and height.
const int WindowExtX = 2800 ; // 2600 ;
const int WindowExtY = - 2800 ; // -2600 ;
// Logical window origin.
const int WindowOrgX = -WindowExtX/2 ;
const int WindowOrgY = -WindowExtY/2 ;
// Length of the course indictor lines.
const int LargeLineLength = 100 ;
const int ShortLineLength = 50 ;
// Coordinates for the To/From indicator
const int HashHeight = 150 ;
const int HashWidth = HashHeight * 5 / 2 ;
const int ToFromX = -HashWidth / 2 ;
const int ToFromY = -550 ;

inline int DeviceX (TCanvas &canvas, int x)
{
  // Conversion from logical to device coordinates.
  SIZE size ;
  GetViewportExtEx (canvas.Handle, &size) ;
  return (x - WindowOrgX) * size.cx / WindowExtX  ;
}

inline int DeviceY (TCanvas &canvas, int y)
{
  // Conversion from logical to device coordinates.
  SIZE size ;
  GetViewportExtEx (canvas.Handle, &size) ;
  return (y - WindowOrgY) * size.cy / WindowExtY   ;
}
//---------------------------------------------------------------------------
static inline TVOR *ValidCtrCheck()
{
  return new TVOR(NULL);
}
//---------------------------------------------------------------------------
__fastcall TVOR::TVOR(TComponent* Owner)
  : TCustomControl(Owner)
{
  TControlStyle style = ControlStyle ;
  ControlStyle = style ;
  Width = 150 ;
  Height = 150 ;
  course = 0 ;
  radial = 0 ;
  bitmap = new Graphics::TBitmap ;
}

__fastcall TVOR::~TVOR()
{
  delete bitmap ;
  return ;
}
//---------------------------------------------------------------------------
namespace Vor
{
  void __fastcall Register()
  {
    TComponentClass classes[1] = {__classid(TVOR)};
    RegisterComponents("ZOther", classes, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TVOR::Paint ()
{
  // Set the bitmap to the correct size.
  bitmap->Height = Height ;
  bitmap->Width = Width ;
  // Draw the VOR on the bitmap.
  SetCoordinateSystem (*bitmap->Canvas) ;
  DrawIndicator (*bitmap->Canvas) ;
  DrawToFrom (*bitmap->Canvas) ;
  DrawGlideSlope (*bitmap->Canvas) ;
  DrawCourseDeviation (*bitmap->Canvas) ;
  // Copy from the bitmap to the window.
  // The TCanvas/TBitmap methods for drawing do not work well when
  // the coordinate system has been changed.
  StretchBlt(Canvas->Handle, 0, 0, Width, Height, bitmap->Canvas->Handle,
             WindowOrgX, WindowOrgY,
             WindowExtX, WindowExtY, SRCCOPY) ;
}

void __fastcall TVOR::KeyDown(Word &Key,  TShiftState Shift)
{
  // We use the +/- keys to change the course. CTRL-+/- changes course by
  // 10 degress.
  TCustomControl::KeyDown (Key, Shift) ;
  if (Key == 187) // +/= Key
  {
    if (Shift.Contains (ssCtrl))
      SetCourse (course + 10) ;
    else
      SetCourse (course + 1) ;

    if (oncoursechanged != NULL)
      oncoursechanged (this) ;
  }
  else if (Key == 189)  // _/- Key
  {
    if (Shift.Contains (ssCtrl))
      SetCourse (course - 10) ;
    else
      SetCourse (course - 1) ;

    if (oncoursechanged != NULL)
      oncoursechanged (this) ;
  }
}

void __fastcall TVOR::MouseDown (TMouseButton Button, TShiftState Shift, int X, int Y)
{
  // When the user clicks on the mouse we want to shift input focus to the VOR
  // so that the user can use the +/- keys to change the course.
  TCustomControl::MouseDown (Button, Shift,X, Y) ;
  if (TabStop)
    SetFocus () ;
}

void __fastcall TVOR::WMEraseBkgnd (TWMEraseBkgnd &msg)
{
  // Ignoring the WM_ERASEBKGND messages eliminates flicker.
  msg.Result = 1 ;
  return ;
}

void __fastcall TVOR::SetCourse (int newcourse)
{
  // This function sets the value of the Course property.

  // Normalize within the range 1-360
  course = (newcourse + 359) % 360 + 1 ;
  if (course < 0)
    course += 360 ;
  Invalidate () ;
}

void __fastcall TVOR::SetRadial (int newradial)
{
  // This function sets the value of the Radial property.

  // Normalize the value to the range 0..3599
  radial = newradial % 3600 ;
  if (radial < 0)
    radial += 3600 ;

  Invalidate () ; // Force a control repaint.
}

void TVOR::SetCoordinateSystem (TCanvas &canvas)
{
  // This function sets the coordinate system up so that the origin is
  // at the center of the VOR and so that values increase from bottom to top
  // and left to right.

  // This sets the map mode so that the axes are scaled the same amount.
  SetMapMode (canvas.Handle, MM_ISOTROPIC) ;
  // This sets the logical extent of the axes.
  SetWindowExtEx (canvas.Handle, WindowExtX, WindowExtY, NULL) ;
  // This sets the physical extent of the axes.
  SetViewportExtEx (canvas.Handle, Width, Height, NULL) ;
  // This should be the default. Place the physical origin at the
  // top left.
  SetViewportOrgEx (canvas.Handle, 0, 0, NULL) ;
  // More the logical origin to the center of the VOR.
  SetWindowOrgEx (canvas.Handle, WindowOrgX, WindowOrgY, NULL) ;
}

void TVOR::DrawIndicator (TCanvas &canvas)
{
  // This function draws the VOR.

  // Fill in the background.
  canvas.Brush->Style = bsSolid ;
  canvas.Brush->Color = clBlack ;
  canvas.Rectangle (-WindowExtX/2, WindowExtY/2, WindowExtX/2, -WindowExtY/2) ;

  // Draw the "On Course" circle
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;
  canvas.Brush->Style = bsClear ;
  canvas.Ellipse (- DotInterval / 2, - DotInterval / 2,
                  DotInterval / 2, DotInterval / 2) ;

  // Draw the course deviation dots
  for (int ii = -5 ; ii <= -1 ; ++ ii)
    DrawDot (canvas, DotInterval * ii, 0) ;

  for (int ii = 1 ; ii <= 5 ; ++ ii)
    DrawDot (canvas, DotInterval * ii, 0) ;

  for (int ii = -5 ; ii <= -1 ; ++ ii)
    DrawDot (canvas, 0, DotInterval * ii) ;

  for (int ii = 1 ; ii <= 5 ; ++ ii)
    DrawDot (canvas, 0, DotInterval * ii) ;

  // Draw the circle around the indicator.
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;
  canvas.Brush->Style = bsClear ;
  canvas.Ellipse (- CourseOuterRadius, - CourseOuterRadius,
                  CourseOuterRadius, CourseOuterRadius) ;
  // Draw the two course indicator triangles.
  DrawCourseIndex (canvas) ;
  DrawReciprocalCourseIndex (canvas) ;
  // Draw the numbers around the course wheel.
  DrawCourseWheel (canvas) ;
}

void TVOR::DrawDot (TCanvas &canvas, int x, int y)
{
  // This function draws a single course deviation dot.
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;
  canvas.Brush->Style = bsSolid ;
  canvas.Brush->Color = clWhite ;
  canvas.Ellipse (x - DotRadius, y - DotRadius, x + DotRadius, y + DotRadius) ;
}

void TVOR::DrawCourseDeviation (TCanvas &canvas)
{
  // This function draws the vertical line that indicates the course deviation.

  int deviation ;

  int difference = (3600 + (10 * course - radial)) % 3600  ;
  if (difference > 1800)
    difference = difference - 3600 ;
  if (difference < -900 || difference > 900)
  { // Inbound tracking
    deviation = (3600 - difference ) % 3600 - 1800  ;
  }
  else
  { // Outbound tracking
    deviation = difference ;
  }

  canvas.Brush->Style = bsSolid ;
  canvas.Brush->Color = clWhite ;
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;

  // The course deviation indicator should appear from beneath the course
  // well. Use a clip region to keep from going over the wheel. The trick
  // here is that clip regions use device coordinates rather than logical
  // coordinates.
  HRGN region = CreateEllipticRgn (DeviceX(canvas, - CourseInnerRadius) + 2,
                                   DeviceY(canvas, CourseInnerRadius) + 2,
                                   DeviceX(canvas, CourseInnerRadius) - 1,
                                   DeviceY(canvas, -CourseInnerRadius) - 1) ;
  try
  {
    SelectClipRgn (canvas.Handle, region) ;
    canvas.Rectangle (10 * deviation/2 - DotRadius, 525,
                      10 * deviation/2 + DotRadius, -525) ;
  }
  catch (...)
  {
    SelectClipRgn (canvas.Handle, 0) ;
    DeleteObject (region) ;
    throw ;
  }
  SelectClipRgn (canvas.Handle, 0) ;
  DeleteObject (region) ;
}

void TVOR::DrawCourseWheel (TCanvas &canvas)
{
  // This function draws the course selection wheel. Large ticks are placed
  // every 10 degrees and small ticks are placed every 5 degrees. A label is
  // placed every 30 degrees. The text on the label must be rotated so that
  // the bottom of the label faces the center of the VOR.

  // Labels for the 10 degree marks.
  static const String headings [] = {"N", "", "",  "3", "", "",  "6", "", "",
                                     "E", "", "", "12", "", "", "15", "", "",
                                     "S", "", "", "21", "", "", "24", "", "",
                                     "W", "", "", "30", "", "", "33", "", "",
                                    } ;
  // Draw the 10 degree marks
  for (int ii = 0 ; ii < 360 ; ii += 10)
  {
    int angle = (90 - ii + course) ;
    double x = cos (2.0 * M_PI * angle / 360.0) ;
    double y = sin (2.0 * M_PI * angle / 360.0) ;

    // Create some "smudges" so that wheel does not look too perfect.
    if ((ii + 4) % 7 == 0)
      canvas.Pen->Color = clGray ;
    else
      canvas.Pen->Color = clWhite ;
    canvas.Pen->Style = psSolid ;

    canvas.MoveTo (CourseInnerRadius * x, CourseInnerRadius * y) ;
    canvas.LineTo ((CourseInnerRadius + LargeLineLength) * x,
                   (CourseInnerRadius + LargeLineLength) * y) ;

    // Not all of the headings have labels.
    if (headings [ii/10] != "")
    {
      // Create a font that is rotated to fit the wheel.
      LOGFONT lf ;
      memset (&lf, 0, sizeof (lf)) ;
      wcscpy(lf.lfFaceName, L"Arial") ;
      lf.lfHeight = 200 ;
      lf.lfWeight = FW_NORMAL ;
      lf.lfEscapement = ii * 10 - course  * 10 ;
      canvas.Font->Handle = CreateFontIndirect (&lf) ;
      canvas.Font->Color = clWhite ;

      // Position and draw the text on the wheel.
      int textwidth = canvas.TextWidth (headings [ii/10]) ;
      int textheight = canvas.TextHeight (headings [ii/10]) ;
      canvas.Brush->Style = bsClear ;
      canvas.TextOut ((CourseInnerRadius + LargeLineLength) * x
                       - y * textwidth/2 + x * textheight,
                      (CourseInnerRadius + LargeLineLength) * y
                       + y * textheight + x * textwidth/2,
                      headings [ii/10]) ;
    }
  }

  // Draw the 5 degree marks
  for (int ii = 5 ; ii < 360 ; ii += 10)
  {
    int angle = (90 - ii + course) ;
    double x = cos (2 * M_PI * angle / 360) ;
    double y = sin (2 * M_PI * angle / 360) ;
    canvas.Pen->Style = psSolid ;
    canvas.Pen->Color = clWhite ;
    canvas.MoveTo (CourseInnerRadius * x, CourseInnerRadius * y) ;
    canvas.LineTo ((CourseInnerRadius + ShortLineLength) * x,
                   (CourseInnerRadius + ShortLineLength) * y) ;
  }
  return ;
}

void TVOR::DrawCourseIndex (TCanvas &canvas)
{
  // This function draws the course index on the VOR. This is a triangle that
  // points to the selected course on the wheel.
  const int pointcount = 4 ;
  TPoint points [pointcount] = { 
                                 TPoint(0, CourseInnerRadius),
                                 TPoint(50, CourseInnerRadius - 100),
                                 TPoint(-50, CourseInnerRadius - 100),
                                 TPoint(0, CourseInnerRadius)
                               } ;
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;
  canvas.Brush->Style = bsSolid ;
  canvas.Brush->Color = clWhite ;
  BeginPath (canvas.Handle) ;
  canvas.Polyline (points, pointcount - 1) ;
  EndPath (canvas.Handle) ;
  FillPath (canvas.Handle) ;
  return ;
}

void TVOR::DrawReciprocalCourseIndex (TCanvas &canvas)
{
  // This function draws the reciprocal course indicator on the VOR.  This
  // is a triangle at the bottom pointing to the course wheel.
  const int pointcount = 4 ;
  TPoint points [pointcount] = { TPoint(0, -CourseInnerRadius),
                                 TPoint(40, -CourseInnerRadius + 80),
                                 TPoint(-40, -CourseInnerRadius + 80),
                                 TPoint(0, -CourseInnerRadius)} ;
  canvas.Pen->Style = psSolid ;
  canvas.Pen->Color = clWhite ;
  canvas.Brush->Style = bsSolid ;
  canvas.Brush->Color = clWhite ;

  BeginPath (canvas.Handle) ;
  canvas.Polyline (points, pointcount - 1) ;
  EndPath (canvas.Handle) ;
  FillPath (canvas.Handle) ;
  return ;
}

void TVOR::DrawHash (TCanvas &canvas, int X, int Y)
{
  // This function draws the red and white has marks when the an indicator
  // is not receiving a clear signal.

  canvas.Brush->Color = clRed ;
  canvas.Pen->Color = clRed ;
  // Each of these blocks draws the outline of a diagonal red hash mark
  // then fills it it.
  BeginPath (canvas.Handle) ;
  canvas.MoveTo (X, Y - HashHeight/2) ;
  canvas.LineTo (X, Y - HashHeight) ;
  canvas.LineTo (X + HashHeight, Y) ;
  canvas.LineTo (X + HashHeight/2, Y) ;
  canvas.LineTo (X, Y - HashHeight/2) ;
  EndPath (canvas.Handle) ;
  FillPath (canvas.Handle) ;

  BeginPath (canvas.Handle) ;
  canvas.MoveTo (X + HashHeight/2, Y - HashHeight) ;
  canvas.LineTo (X + HashHeight, Y - HashHeight) ;
  canvas.LineTo (X + 2 * HashHeight, Y) ;
  canvas.LineTo (X + 3 * HashHeight/2, Y) ;
  canvas.LineTo (X + HashHeight/2, Y - HashHeight) ;
  EndPath (canvas.Handle) ;
  FillPath (canvas.Handle) ;

  BeginPath (canvas.Handle) ;
  canvas.MoveTo (X + 3 * HashHeight/2, Y - HashHeight) ;
  canvas.LineTo (X + 2 * HashHeight, Y - HashHeight) ;
  canvas.LineTo (X + 5 * HashHeight/2, Y - HashHeight/2) ;
  canvas.LineTo (X + 5 * HashHeight/2, Y) ;
  canvas.LineTo (X + 3 * HashHeight/2, Y - HashHeight) ;
  EndPath (canvas.Handle) ;
  FillPath (canvas.Handle) ;

  return ;
}

void TVOR::DrawToFrom (TCanvas &canvas)
{
  // This function draws the To/From indicator on the VOR.

  canvas.Font->Height = HashHeight ;
  canvas.Font->Name = "Arial" ;
  canvas.Brush->Style = bsClear ;
  canvas.Font->Color = clWhite ;

  // Position and draw the text on the wheel.
  static const String label = "NAV" ;
  canvas.TextOut (ToFromX - canvas.TextWidth (label + " "), ToFromY, label) ;

  // Create a "window" for the To/From indictor to appear from.
  HRGN region = CreateRectRgn (DeviceX(canvas, ToFromX),
                               DeviceY(canvas, ToFromY),
                               DeviceX(canvas, ToFromX + HashWidth),
                               DeviceY(canvas, ToFromY - HashHeight)) ;
  try
  {
    // To clearly see how the To/From indicator is implemented, try commenting
    // out the following SelectClipRgn call.
    SelectClipRgn (canvas.Handle, region) ;

    int difference = (3600 + (10 * course - radial)) % 3600  ;
    if (difference > 1800)
      difference = difference - 3600 ;
    if (difference < 0)
      difference = -difference ;

    // Initially set the top to the location of the "From" indicator.
    int top = ToFromY ;
    const int delta = 200 ;
    if (difference > 900 + delta )
    {
      // We are clearly on the "TO" side of the VOR so display "TO".
      top = top + 2 * HashHeight ;
    }
    else if (difference > 900 - delta)
    {
      // We are in the area where the TO/FROM indictor is in between.
      // Scale to the approximate position.
      top += (double) HashHeight *(difference - 900 + 2 * delta) /
                            (double) (2 * delta)  ;
    }

    static const String FROM = "FROM" ;
    canvas.Brush->Color = clRed ;
    canvas.Rectangle (-HashWidth / 2, top, HashWidth / 2, top - HashHeight) ;
    canvas.TextOut (- canvas.TextWidth (FROM)/2, top, FROM) ;

    canvas.Brush->Color = clWhite ;
    canvas.Rectangle (-HashWidth / 2, top - HashHeight, HashWidth / 2, top - 2 * HashHeight) ;
    DrawHash (canvas, -HashWidth / 2, top - HashHeight) ;

    canvas.Brush->Color = clBlack ;
    canvas.Pen->Color = clBlack ;
    static const String TO = "TO" ;
    canvas.Rectangle (-HashWidth / 2, top - 2 * HashHeight, 
                      HashWidth / 2, top - 3 * HashHeight) ; // FROM
    canvas.TextOut (- canvas.TextWidth (TO)/2, top - 2 * HashHeight, TO) ;
  }
  catch (...)
  {
    SelectClipRgn (canvas.Handle, 0) ;
    DeleteObject (region) ;
    throw ;
  }
  // Clean up.
  SelectClipRgn (canvas.Handle, 0) ;
  DeleteObject (region) ;

  // Draw a light outline for the To/From indicator.
  canvas.Pen->Color = clGray ;
  canvas.Brush->Style = bsClear ;
  canvas.Rectangle (ToFromX, ToFromY, ToFromX + HashWidth,
                    ToFromY - HashHeight) ;

}

void TVOR::DrawGlideSlope (TCanvas &canvas)
{
  // Glideslop deviation has not been implemented (It would make no sense
  // without implementing localizer deviation as well). Draw a glideslope
  // active indicator but always show the hashmarks to indicate that
  // a glideslope signal is not being received.
  canvas.Font->Height = HashHeight ;
  canvas.Font->Name = "Arial" ;
  canvas.Brush->Style = bsClear ;
  canvas.Font->Color = clWhite ;
  static const int labelx = DotInterval ;
  static const String GS = "GS" ;
  static const int labely = DotInterval * 3 ;
  canvas.TextOut (labelx, labely, GS) ;
  canvas.Brush->Color = clWhite ;
  int textspace = canvas.TextWidth (GS + " ") ;
  int hashtop = labely - (canvas.TextHeight (GS) - HashHeight) / 2 ;
  canvas.Rectangle (labelx + textspace, hashtop,
                    labelx + HashWidth + textspace, hashtop - HashHeight) ;
  DrawHash (canvas, labelx + textspace, hashtop) ;
}


