/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SOFCCOLORGRADIENT_H
#define GUI_SOFCCOLORGRADIENT_H

#include "stdexport.h"
#include <Inventor/nodes/SoSeparator.h>
#include "SoFCColorBar.h"
#include "App/ColorModel.h"
#include <vector>

class SoCoordinate3;
class SoMFString;
class SbVec2s;

namespace Gui {

class GuiExport SoFCColorGradient : public SoFCColorBarBase {
  typedef SoFCColorBarBase inherited;

  SO_NODE_HEADER(Gui::SoFCColorGradient);

public:
  static void initClass(void);
  static void finish(void);
  SoFCColorGradient(void);

  /**
   * Sets the range of the colorbar from the maximum \a fMax to the minimum \a fMin.
   * \a prec indicates the post decimal positions, \a prec should be in between 0 and 6.
   */
  void setRange( float fMin, float fMax, int prec=3 );
  /**
   * Returns the associated color to the value \a fVal.
   */
  App::Color getColor (float fVal) const { return _cColGrad.getColor(fVal); }
  void setOutsideGrayed (bool bVal) { _cColGrad.setOutsideGrayed(bVal); }
  /**
   * Returns always true if the gradient is in mode to show colors to arbitrary values of \a fVal,
   * otherwise true is returned if \a fVal is within the specified parameter range, if not false is
   * returned.
   */
  bool isVisible (float fVal) const;
  /** Returns the current minimum of the parameter range. */
  float getMinValue (void) const { return _cColGrad.getMinValue(); }
  /** Returns the current maximum of the parameter range. */
  float getMaxValue (void) const { return _cColGrad.getMaxValue(); }
  /**
   * Opens a dialog to customize the current settings of the color gradient bar.
   * Returns true if the settings have been changed, false otherwise.
   */
  bool customize();
  /** Returns the name of the color bar. */
  const char* getColorBarName() const { return "Color Gradient"; }

protected:
  /**
   * Sets the current viewer size this color gradient is embedded into, to recalculate its new position.
   */
  void setViewportSize( const SbVec2s& size );

  virtual ~SoFCColorGradient();
  /**
   * Sets the color model of the underlying color gradient to \a tModel. \a tModel either can
   * be \c TRIA, \c INVERSE_TRIA, \c GRAY or \c INVERSE_GRAY
   */
  void setColorModel (App::ColorGradient::TColorModel tModel);
  /**
   * Sets the color style of the underlying color gradient to \a tStyle. \a tStyle either can
   * be \c FLOW or \c ZERO_BASED
   */
  void setColorStyle (App::ColorGradient::TStyle tStyle);
  /** Rebuild the gradient bar. */
  void rebuildGradient();
  /** Returns a list of \a count labels within the ranhe [\a fMin, \a fMax].  */
  std::vector<float> getMarkerValues(float fMin, float fMax, int count) const;

private:
  /** Sets the new labels. */
  void setMarkerLabel( const SoMFString& label );

private:
  SoCoordinate3* coords;
  SoSeparator* labels;
  float _fMaxX, _fMinX, _fMaxY, _fMinY;
  bool  _bOutInvisible;
  int _precision;
  App::ColorGradient _cColGrad;
};

} // namespace Gui


#endif // GUI_SOFCCOLORGRADIENT_H
