#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Version.h"
#include "Data_type.h"

const Ec_string  Ec_version  = ROBOT_CONTROL_VERSION;
const Ec_boolean Ec_true     = true;
const Ec_boolean Ec_false    = false;
const Ec_double  Ec_pi       = 0;
const Ec_double  Ec_2pi      = 0;
const Ec_double  Ec_half_pi  = 0;
const Ec_double  Ec_e        = 0;
const Ec_double  Ec_sqrt2    = 0;
const Ec_double  Ec_sqrt3    = 0;
const Ec_double  Ec_sqrt4    = 0;
const Ec_double  Ec_sqrt5    = 0;

const Ec_double  Ec_IN2M     = 0.02540000000000000;
const Ec_double  Ec_M2IN     = 39.37007874015748;
const Ec_double  Ec_M2FT     = 3.2808398950131235;
const Ec_double  Ec_RAD2DEG  = 57.29577951308232088;
const Ec_double  Ec_DEG2RAD  = 0.0174532925199432958;
const Ec_uint32  Ec_MAXU32   = 0xFFFFFFFF;
const Ec_uint16  Ec_MAXU16   = 0xFFFF;
const Ec_uint8   Ec_MAXU8    = 0xFF;
const Ec_int32   Ec_MAXINT32 = 0x7FFFFFFF;
const Ec_int32   Ec_MININT32 = -2147483647 - 1;
const Ec_int16   Ec_MAXINT16 = 0x7FFF;
const Ec_int16   Ec_MININT16 = -32767 - 1;
const Ec_int8    Ec_MAXINT8  = 0x7F;
const Ec_int8    Ec_MININT8  = -127 - 1;

const Ec_double  Ec_NANO     = 1e-9;
const Ec_double  Ec_MICRO    = 1e-6;
const Ec_double  Ec_MILLI    = 1e-3;
const Ec_double  Ec_KILO     = 1e3;
const Ec_double  Ec_MEGA     = 1e6;
const Ec_double  Ec_GIGA     = 1e9;

const Ec_double  Ec_KIBI     = 1 << 10;
const Ec_double  Ec_MEBI     = 1 << 20;
const Ec_double  Ec_GIBI     = 1 << 30;

#endif // CONSTANTS_H
