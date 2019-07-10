/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Swap.h"

unsigned short Base::SwapOrder (void)
{
  unsigned short usDummy = 1;
  return *((char*) &usDummy) == 1 ? LOW_ENDIAN : HIGH_ENDIAN;
}

void Base::SwapVar (char&)
{
}

void Base::SwapVar (unsigned char&)
{
}

void Base::SwapVar (short& s)
{
  short sTmp = s;
  int i;

  for (i = 0; i < (int)sizeof (short); i++)
    *(((char*) &sTmp) + i) = *(((char*) &s) + sizeof (short) - i - 1);
  s = sTmp;
}

void Base::SwapVar (unsigned short& s)
{
  short sTmp = s;
  int i;

  for (i = 0; i < (int)sizeof (short); i++)
    *(((char*) &sTmp) + i) = *(((char*) &s) + sizeof (short) - i - 1);
  s = sTmp;
}

void Base::SwapVar (long& l)
{
  long lTmp = l;
  int i;

  for (i = 0; i < (int)sizeof (long); i++)
    *(((char*) &lTmp) + i) = *(((char*) &l) + sizeof (long) - i - 1);
  l = lTmp;
}

void Base::SwapVar (unsigned long& l)
{
  long lTmp = l;
  int i;

  for (i = 0; i < (int)sizeof (long); i++)
    *(((char*) &lTmp) + i) = *(((char*) &l) + sizeof (long) - i - 1);
  l = lTmp;
}

void Base::SwapVar (float& f)
{
  float fTmp = f;
  int i;

  for (i = 0; i < (int)sizeof (float); i++)
    *(((char*) &fTmp) + i) = *(((char*) &f) + sizeof (float) - i - 1);
  f = fTmp;
}

void Base::SwapVar (double& d)
{
  double dTmp = d;
  int i;

  for (i = 0; i < (int)sizeof (double); i++)
    *(((char*) &dTmp) + i) = *(((char*) &d) + sizeof (double) - i - 1);
  d = dTmp;
}


