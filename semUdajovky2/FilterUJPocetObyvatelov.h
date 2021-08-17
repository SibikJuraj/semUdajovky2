#pragma once

#include "FilterUJInterval.h"
#include "KriteriumUJPocetObyv.h"
#include "UzemnaJednotka.h"

class FilterUJPocetObyvatelov : public FilterUJInterval<unsigned int>
{
public:
	FilterUJPocetObyvatelov(KriteriumUJPocetObyv* krit, unsigned int min, unsigned int max);
};


FilterUJPocetObyvatelov::FilterUJPocetObyvatelov(KriteriumUJPocetObyv* krit, unsigned int min, unsigned int max) : FilterUJInterval(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
