#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJZastavanost : public KriteriumUJ<double>
{

public:
	double ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};


double KriteriumUJZastavanost::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return (100.0 * (uzemnaJednotka->getZastavanaPlochaV_M2() / uzemnaJednotka->getCelkovaVymeraV_M2()));
}