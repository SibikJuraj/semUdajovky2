#pragma once

#include <string>
#include "UzemnaJednotkaTyp.h"
#include "BytovaJednotka.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"


using namespace structures;

class UzemnaJednotka
{
private:
	std::wstring nazov;
	unsigned int pocetPreprodObyv;
	unsigned int pocetProdObyv;
	unsigned int pocetPoprodObyv;
	double celkovaVymeraV_M2;
	double zastavanaPlochaV_M2;
	UzemnaJednotkaTyp typUzemnejJednotky;

	UzemnaJednotka* vyssiUC;
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaNizsichUC;
	UnsortedSequenceTable<std::wstring, BytovaJednotka*>* tabulkaBJ;

public:
	UzemnaJednotka(std::wstring nazov, UzemnaJednotkaTyp typUzemnejJednotky, UzemnaJednotka* vyssiUC);
	~UzemnaJednotka();
	void updatujUdaje(unsigned int pocetPreprodObyv, unsigned int pocetProdObyv, unsigned int pocetPoprodObyv, double celkovaVymeraV_M2, double zastavanaPlochaV_M2);
	std::wstring getNazov();
	unsigned int getPocetPreprodObyv();
	unsigned int getPocetProdObyv();
	unsigned int getPocetPoprodObyv();
	double getCelkovaVymeraV_M2();
	double getZastavanaPlochaV_M2();
	UzemnaJednotkaTyp getTypUzemnejJednotky();
	UzemnaJednotka* getVyssiUC();
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* getTabulkaNizsichUC();
	UnsortedSequenceTable<std::wstring, BytovaJednotka*>* getTabulkaBJ();
};


UzemnaJednotka::UzemnaJednotka(std::wstring nazov, UzemnaJednotkaTyp typUzemnejJednotky, UzemnaJednotka* vyssiUC)
{
	this->nazov = nazov;
	this->typUzemnejJednotky = typUzemnejJednotky;
	this->vyssiUC = vyssiUC;
	pocetPreprodObyv = 0;
	pocetProdObyv = 0;
	pocetPoprodObyv = 0;
	celkovaVymeraV_M2 = 0;
	zastavanaPlochaV_M2 = 0;


	this->tabulkaNizsichUC = new SortedSequenceTable<std::wstring, UzemnaJednotka*>();
	this->tabulkaBJ = new UnsortedSequenceTable<std::wstring, BytovaJednotka*>();

}


UzemnaJednotka::~UzemnaJednotka()
{
	
	for (auto bjItem : *tabulkaBJ)
	{
		delete bjItem->accessData();
		bjItem = nullptr;
	}
	

	delete tabulkaBJ;
	tabulkaBJ = nullptr;

	delete tabulkaNizsichUC;
	tabulkaNizsichUC = nullptr;
	vyssiUC = nullptr;


}

void UzemnaJednotka::updatujUdaje(unsigned int pocetPreprod, unsigned int pocetProd, unsigned int pocetPoprod, double celkovaVymera, double zastavanaPlocha)
{
	pocetPreprodObyv += pocetPreprod;
	pocetProdObyv += pocetProd;
	pocetPoprodObyv += pocetPoprod;

	celkovaVymeraV_M2 += celkovaVymera;
	zastavanaPlochaV_M2 += zastavanaPlocha;
	


	//Updatuj aj info o bytovych jednotkach
	// 
	//tabulkaBJ

	if (vyssiUC != nullptr)
	{
		vyssiUC->updatujUdaje(pocetPreprod, pocetProd, pocetPoprod, celkovaVymera, zastavanaPlocha);
	}
}

inline std::wstring UzemnaJednotka::getNazov()
{
	return nazov;
}

inline unsigned int UzemnaJednotka::getPocetPreprodObyv()
{
	return pocetPreprodObyv;
}

inline unsigned int UzemnaJednotka::getPocetProdObyv()
{
	return pocetProdObyv;
}

inline unsigned int UzemnaJednotka::getPocetPoprodObyv()
{
	return pocetPoprodObyv;
}

inline double UzemnaJednotka::getCelkovaVymeraV_M2()
{
	return celkovaVymeraV_M2;
}

inline double UzemnaJednotka::getZastavanaPlochaV_M2()
{
	return zastavanaPlochaV_M2;
}

inline UzemnaJednotkaTyp UzemnaJednotka::getTypUzemnejJednotky()
{
	return typUzemnejJednotky;
}

inline UzemnaJednotka* UzemnaJednotka::getVyssiUC()
{
	return vyssiUC;
}

inline SortedSequenceTable<std::wstring, UzemnaJednotka*>* UzemnaJednotka::getTabulkaNizsichUC()
{
	return tabulkaNizsichUC;
}

inline UnsortedSequenceTable<std::wstring, BytovaJednotka*>* UzemnaJednotka::getTabulkaBJ()
{
	return tabulkaBJ;
}

