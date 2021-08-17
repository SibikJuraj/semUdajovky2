#pragma once

#include "FilterPodlaHodnoty.h"
#include "KriteriumBJ.h"
#include "BytovaJednotka.h"

template <typename V>
class FilterBJHodnota : public FilterPodlaHodnoty<std::wstring, BytovaJednotka*, V>
{
public:
	FilterBJHodnota(KriteriumBJ<V>* krit, V hodnota);

};

template <typename V>
FilterBJHodnota<V>::FilterBJHodnota(KriteriumBJ<V>* krit, V hodnota) : FilterPodlaHodnoty<std::wstring, BytovaJednotka*, V>(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}

