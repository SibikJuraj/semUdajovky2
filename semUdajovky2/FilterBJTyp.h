#pragma once

#include "FilterBJHodnota.h"
#include "KriteriumBJTyp.h"
#include "BytovaJednotka.h"

class FilterBJTyp : public FilterBJHodnota<std::wstring>
{
public:
	FilterBJTyp(KriteriumBJTyp* krit, std::wstring hodnota);
};

FilterBJTyp::FilterBJTyp(KriteriumBJTyp* krit, std::wstring hodnota) : FilterBJHodnota(krit, hodnota)
{
	this->hodnota = hodnota;
	this->kriterium = krit;
}

