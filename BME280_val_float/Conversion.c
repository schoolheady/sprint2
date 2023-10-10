#include "Conversion.h"
float conversion(int een, int twee)
{
    int decimal = log10(twee) + 1;
    return een + twee*pow(10.0, -decimal);
}
