#pragma once

#include "KriteriumBJ.h"
#include "BytovaJednotka.h"


class KriteriumBJPocet : public KriteriumBJ<unsigned int>
{

public:
	unsigned int ohodnot(BytovaJednotka* bytovaJednotka) override;

};

unsigned int KriteriumBJPocet::ohodnot(BytovaJednotka* bytovaJednotka)
{
	return bytovaJednotka->getMnozstvo();
}