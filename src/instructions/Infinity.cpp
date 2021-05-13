#include "Infinity.h"

#include <limits>

Infinity::Infinity(BarrelParser &parser) : Number{std::numeric_limits<double>::infinity(), parser}
{
}
