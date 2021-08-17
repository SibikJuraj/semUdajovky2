#pragma once

#include "FilterBJInterval.h"
#include "KriteriumBJPocetIzieb.h"
#include "BytovaJednotka.h"

class FilterBJPocetIzieb : public FilterBJInterval<unsigned int>
{
public:
	FilterBJPocetIzieb(KriteriumBJPocetIzieb* krit, unsigned int min, unsigned int max);
};


FilterBJPocetIzieb::FilterBJPocetIzieb(KriteriumBJPocetIzieb* krit, unsigned int min, unsigned int max) : FilterBJInterval(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
