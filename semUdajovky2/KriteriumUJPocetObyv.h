#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJPocetObyv : public KriteriumUJ<unsigned int>
{

public:
	unsigned int ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

unsigned int KriteriumUJPocetObyv::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getPocetPreprodObyv() + uzemnaJednotka->getPocetProdObyv() + uzemnaJednotka->getPocetPoprodObyv();
}