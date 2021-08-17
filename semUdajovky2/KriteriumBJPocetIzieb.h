#pragma once

#include "KriteriumBJ.h"
#include "BytovaJednotka.h"


class KriteriumBJPocetIzieb : public KriteriumBJ<unsigned int>
{

public:
	unsigned int ohodnot(BytovaJednotka* bytovaJednotka) override;

};

unsigned int KriteriumBJPocetIzieb::ohodnot(BytovaJednotka* bytovaJednotka)
{
	return bytovaJednotka->getPocetObytnychMiestnosti();
}