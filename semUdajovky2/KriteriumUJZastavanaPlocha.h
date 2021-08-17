#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJZastavanaPlocha : public KriteriumUJ<double>
{

public:
	double ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};


double KriteriumUJZastavanaPlocha::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getZastavanaPlochaV_M2();
}