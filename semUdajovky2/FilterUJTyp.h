#pragma once

#include "FilterUJHodnota.h"
#include "KriteriumUJTyp.h"
#include "UzemnaJednotka.h"

class FilterUJTyp : public FilterUJHodnota<UzemnaJednotkaTyp>
{
public:
	FilterUJTyp(KriteriumUJTyp* krit, UzemnaJednotkaTyp hodnota);
};

FilterUJTyp::FilterUJTyp(KriteriumUJTyp* krit, UzemnaJednotkaTyp hodnota) : FilterUJHodnota(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}

