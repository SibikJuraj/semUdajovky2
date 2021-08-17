#pragma once

#include "FilterPodlaIntervalu.h"
#include "BytovaJednotka.h"
#include "KriteriumBJ.h"

template <typename V>
class FilterBJInterval : public FilterPodlaIntervalu<std::wstring, BytovaJednotka*, V>
{
public:
	FilterBJInterval(KriteriumBJ<V>* krit, V min, V max);
};

template<typename V>
inline FilterBJInterval<V>::FilterBJInterval(KriteriumBJ<V>* krit, V min, V max) : FilterPodlaIntervalu<std::wstring, BytovaJednotka*, V>(krit, min, max)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;
}
