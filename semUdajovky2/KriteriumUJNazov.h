#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"



class KriteriumUJNazov : public KriteriumUJ<std::wstring>
{

public:
	std::wstring ohodnot(UzemnaJednotka* uzemnaJednotka) override;

};

std::wstring KriteriumUJNazov::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	return uzemnaJednotka->getNazov();
}
