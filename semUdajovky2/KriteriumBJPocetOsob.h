#pragma once

#include "KriteriumBJ.h"
#include "BytovaJednotka.h"


class KriteriumBJPocetOsob : public KriteriumBJ<unsigned int>
{

public:
	unsigned int ohodnot(BytovaJednotka* bytovaJednotka) override;

};

unsigned int KriteriumBJPocetOsob::ohodnot(BytovaJednotka* bytovaJednotka)
{
	return bytovaJednotka->getPocetOsob();
}