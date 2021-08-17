#pragma once

#include "FilterBJInterval.h"
#include "KriteriumBJPocetOsob.h"
#include "BytovaJednotka.h"

class FilterBJPocetOsob : public FilterBJInterval<unsigned int>
{
public:
	FilterBJPocetOsob(KriteriumBJPocetOsob* krit, unsigned int min, unsigned int max);
};


FilterBJPocetOsob::FilterBJPocetOsob(KriteriumBJPocetOsob* krit, unsigned int min, unsigned int max) : FilterBJInterval(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
