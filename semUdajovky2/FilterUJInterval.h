#pragma once

#include "FilterPodlaIntervalu.h"
#include "UzemnaJednotka.h"
#include "KriteriumUJ.h"

template <typename V>
class FilterUJInterval : public FilterPodlaIntervalu<std::wstring, UzemnaJednotka*, V>
{
public:
	FilterUJInterval(KriteriumUJ<V>* krit, V min, V max);
};

template<typename V>
inline FilterUJInterval<V>::FilterUJInterval(KriteriumUJ<V>* krit, V min, V max) : FilterPodlaIntervalu<std::wstring, UzemnaJednotka*, V>(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
