#pragma once

#include "FilterUJHodnota.h"
#include "KriteriumUJNazov.h"
#include "UzemnaJednotka.h"

class FilterUJNazov : public FilterUJHodnota<std::wstring>
{
public:
	FilterUJNazov(KriteriumUJNazov* krit, std::wstring hodnota);

};


FilterUJNazov::FilterUJNazov(KriteriumUJNazov* krit, std::wstring hodnota) : FilterUJHodnota(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}