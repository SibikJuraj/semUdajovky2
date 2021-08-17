#pragma once

#include "FilterUJHodnota.h"
#include "KriteriumUJPrislusnost.h"
#include "UzemnaJednotka.h"

class FilterUJPrislusnost : public FilterUJHodnota<bool>
{
public:
	FilterUJPrislusnost(KriteriumUJPrislusnost* krit, bool hodnota);

};


FilterUJPrislusnost::FilterUJPrislusnost(KriteriumUJPrislusnost* krit, bool hodnota) : FilterUJHodnota(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}
