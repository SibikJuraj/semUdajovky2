#pragma once

#include "Filter.h"

template <typename K, typename T, typename V>
class FilterPodlaIntervalu : public Filter<K, T, V>
{
protected:
	V min;
	V max;

public:
	FilterPodlaIntervalu(Kriterium<V, T>* krit, V min, V max);
	bool splnaFilter(T o) override;
};

template<typename K, typename T, typename V>
FilterPodlaIntervalu<K, T, V>::FilterPodlaIntervalu(Kriterium<V, T>* krit, V min, V max) : Filter<K, T, V>(krit)
{
	this->min = min;
	this->max = max;
	this->kriterium = krit;

}

template <typename K, typename T, typename V>
bool FilterPodlaIntervalu<K, T, V>::splnaFilter(T o)
{
	V hodnota = this->kriterium->ohodnot(o);
	return (hodnota >= min && hodnota <= max);
}
