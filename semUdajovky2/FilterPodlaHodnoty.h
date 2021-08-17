#pragma once

#include "Filter.h"

template <typename K, typename T, typename V>
class FilterPodlaHodnoty : public Filter<K, T, V>
{
protected:
	V hodnota;

public:
	FilterPodlaHodnoty(Kriterium<V, T>* krit, V hodnota);
	bool splnaFilter(T o) override;
	
};

template<typename K, typename T, typename V>
FilterPodlaHodnoty<K, T, V>::FilterPodlaHodnoty(Kriterium<V, T>* krit, V hodnota) : Filter<K, T, V>(krit)
{
	this->kriterium = krit;
	this->hodnota = hodnota;
}

template <typename K, typename T, typename V>
bool FilterPodlaHodnoty<K, T, V>::splnaFilter(T o)
{
	return this->kriterium->ohodnot(o) == hodnota;
}


