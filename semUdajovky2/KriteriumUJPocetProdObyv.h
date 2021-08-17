#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJPocetProdObyv : public KriteriumUJ<unsigned int>
{

public:
	unsigned int ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

unsigned int KriteriumUJPocetProdObyv::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getPocetProdObyv();
}