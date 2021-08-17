#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJPocetPoprodObyv : public KriteriumUJ<unsigned int>
{

public:
	unsigned int ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

unsigned int KriteriumUJPocetPoprodObyv::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getPocetPoprodObyv();
}