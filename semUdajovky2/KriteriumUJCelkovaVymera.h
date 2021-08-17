#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJCelkovaVymera : public KriteriumUJ<double>
{

public:
	double ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};


double KriteriumUJCelkovaVymera::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getCelkovaVymeraV_M2();
}