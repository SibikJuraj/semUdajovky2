#pragma once

#include "FilterUJInterval.h"
#include "KriteriumUJZastavanost.h"
#include "UzemnaJednotka.h"

class FilterUJZastavanost : public FilterUJInterval<double>
{
public:
	FilterUJZastavanost(KriteriumUJZastavanost* krit, double min, double max);

};


FilterUJZastavanost::FilterUJZastavanost(KriteriumUJZastavanost* krit, double min, double max) : FilterUJInterval(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
