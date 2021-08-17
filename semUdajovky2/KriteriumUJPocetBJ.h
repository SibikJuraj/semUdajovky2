#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"
#include "BytovaJednotka.h"


class KriteriumUJPocetBJ : public KriteriumUJ<unsigned int>
{

public:
	unsigned int pocet = 0;
	std::wstring key;

	KriteriumUJPocetBJ(std::wstring key);
	unsigned int ohodnot(UzemnaJednotka* uzemnaJednotka) override;
	unsigned int cyklus(UzemnaJednotka* uj);
	~KriteriumUJPocetBJ();


};

inline KriteriumUJPocetBJ::KriteriumUJPocetBJ(std::wstring key)
{
	this->key = key;
}

inline unsigned int KriteriumUJPocetBJ::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	try
	{
		UzemnaJednotka* uJ = uzemnaJednotka;
		pocet += cyklus(uJ);
	}
	catch (std::exception ex)
	{
	}
	
	return pocet;
}

inline unsigned int KriteriumUJPocetBJ::cyklus(UzemnaJednotka* uj)
{
	if (uj->getTabulkaNizsichUC()->isEmpty())
	{
		return 1;
	}
	else
	{
		for (auto tI : *uj->getTabulkaNizsichUC())
		{
			cyklus(tI->accessData());
		}
	}

}


inline KriteriumUJPocetBJ::~KriteriumUJPocetBJ()
{
	key = nullptr;
}

