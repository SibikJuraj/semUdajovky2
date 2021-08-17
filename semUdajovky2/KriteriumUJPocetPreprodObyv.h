#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJPocetPreprodObyv : public KriteriumUJ<unsigned int>
{

public:
	unsigned int ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

unsigned int KriteriumUJPocetPreprodObyv::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getPocetPreprodObyv();
}