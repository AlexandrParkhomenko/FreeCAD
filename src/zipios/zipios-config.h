#ifndef ZIPIOS_CONFIG_H
#define ZIPIOS_CONFIG_H

#include "stdexport.h"

#define HAVE_STD_IOSTREAM 1
// gcc and others
#ifndef S_ISSOCK
#define S_ISSOCK(mode)	0
#endif
#include <stdint.h>

#endif // ZIPIOS_CONFIG_H

