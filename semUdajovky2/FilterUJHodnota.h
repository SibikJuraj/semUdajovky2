#pragma once

#include "FilterPodlaHodnoty.h"
#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"

template <typename V>
class FilterUJHodnota : public FilterPodlaHodnoty<std::wstring, UzemnaJednotka*, V>
{
public:
	FilterUJHodnota(KriteriumUJ<V>* krit, V hodnota);

};

template <typename V>
FilterUJHodnota<V>::FilterUJHodnota(KriteriumUJ<V>* krit, V hodnota) : FilterPodlaHodnoty<std::wstring, UzemnaJednotka*, V>(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}

