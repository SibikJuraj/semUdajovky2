#pragma once

#include "KriteriumUJ.h"
#include "UzemnaJednotka.h"


class KriteriumUJPrislusnost : public KriteriumUJ<bool>
{
private:
	UzemnaJednotka* VUC = nullptr;

public:
	KriteriumUJPrislusnost(UzemnaJednotka* VUC);
	bool ohodnot(UzemnaJednotka* uzemnaJednotka) override;
	~KriteriumUJPrislusnost();

};

KriteriumUJPrislusnost::KriteriumUJPrislusnost(UzemnaJednotka* VUC)
{
	this->VUC = VUC;
}

inline KriteriumUJPrislusnost::~KriteriumUJPrislusnost()
{
	VUC = nullptr;
}


bool KriteriumUJPrislusnost::ohodnot(UzemnaJednotka* uzemnaJednotka)
{
	UzemnaJednotka* aktUJ = uzemnaJednotka->getVyssiUC();
	while (aktUJ != nullptr)
	{
		if (aktUJ == VUC)
		{
			return true;
		}
		aktUJ = aktUJ->getVyssiUC();

	}
	return false;
}


