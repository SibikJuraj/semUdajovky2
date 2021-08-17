#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJTyp : public KriteriumUJ<UzemnaJednotkaTyp>
{

public:
	UzemnaJednotkaTyp ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

UzemnaJednotkaTyp KriteriumUJTyp::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getTypUzemnejJednotky();
}