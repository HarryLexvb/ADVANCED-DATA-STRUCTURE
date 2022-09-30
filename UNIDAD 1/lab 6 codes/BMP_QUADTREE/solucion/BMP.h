//
// Created by win 10 on 29/09/2022.
//


#ifdef _MSC_VER
// MS Visual Studio gives warnings when using
// fopen. But fopen_s is not going to work well
// with most compilers, and fopen_s uses different
// syntax than fopen. (i.e., a macro won't work)
// So, we'lll use this:
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <iostream>
#include <cmath>
#include <cctype>
#include <cstring>

#ifndef SOLUCION_BMP_H
#define SOLUCION_BMP_H

#ifdef __BCPLUSPLUS__
// The Borland compiler must use this because something
// is wrong with their cstdio file.
#include <stdio.h>
#else
#include <cstdio>
#endif

#ifdef __GNUC__
// If g++ specific code is ever required, this is
// where it goes.
#endif

#ifdef __INTEL_COMPILER
// If Intel specific code is ever required, this is
// where it goes.
#endif

#ifndef _DefaultXPlsPerMeter_
#define _DefaultXPlsPerMeter_
#define DefaultXPlsPerMeter 3780
// set to a default of 96 dpi
#endif

#ifndef _DefaultYPlsPerMeter_
#define _DefaultYPlsPerMeter_
#define DefaultYPlsPerMeter 3780
// set to a default of 96 dpi
#endif

#include "BMP_DataStructures.h"
#include "BMP_BMP.h"
#include "BMP_VariousBMPutilities.h"

#ifndef _BMP_Version_
#define _BMP_Version_ 1.06
#define _BMP_Version_Integer_ 106
#define _BMP_Version_String_ "1.06"
#endif

#ifndef _BMP_warnings_
#define _BMP_warnings_
#endif

void SetBMPwarningsOff(); // turns off warnings
void Set_BMPwarningsOn(); // turns on warnings
bool GetBMPwarningState(); // returns true if warnings are on

#endif //SOLUCION_BMP_H
