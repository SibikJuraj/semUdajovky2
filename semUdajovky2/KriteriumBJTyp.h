#pragma once

#include "KriteriumBJ.h"
#include "BytovaJednotka.h"


class KriteriumBJTyp : public KriteriumBJ<std::wstring>
{

public:
	std::wstring ohodnot(BytovaJednotka* bytovaJednotka) override;

};

std::wstring KriteriumBJTyp::ohodnot(BytovaJednotka* bytovaJednotka)
{
	return bytovaJednotka->getTyp();
}