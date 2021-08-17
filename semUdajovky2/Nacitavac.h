#pragma once
#include "UzemnaJednotka.h"
#include "BytovaJednotka.h"
#include "structures/structure_iterator.h"
#include <fstream>
#include <iostream>


class Nacitavac
{
private:
	const std::string CestaKSuboru1 = "CSV/1 Obce SR.csv";
	const std::string CestaKSuboru2 = "CSV/2 Územné èlenenie SR.csv";
	const std::string CestaKSuboru3 = "CSV/3 Zoznam zoskupení bytových jednotiek SR.csv";
	const std::string CestaKSuboru4 = "CSV/4 Bytové jednotky SR.csv";
	const int POC_RIADKOV_CSV = 2926;

	ArrayList<BytovaJednotka*>* listBytovychZoskupeni;

	std::wifstream subor1;
	std::wifstream subor3;
	std::wifstream subor4;
	std::wstring nazovObceBJ;
	bool isSubor1Loaded;
	bool isSubor3Loaded;
	bool isSubor4Loaded;
	bool wasNameRead;

public:
	Nacitavac();
	~Nacitavac();
	void nacitajUzemneJednotky(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ, 
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);
	UzemnaJednotka* nacitajObec(UzemnaJednotka* okres);
	void nacitajBytoveZoskupenia();
	void nacitajRiadokBytovychJednotiek(UzemnaJednotka* obec);
	std::wstring vratVypis(int progres);
	

};

Nacitavac::Nacitavac()
{
	listBytovychZoskupeni = new ArrayList<BytovaJednotka*>();
	isSubor1Loaded = false;
	isSubor3Loaded = false;
	isSubor4Loaded = false;
	wasNameRead = false;
	nazovObceBJ = L"";
}

Nacitavac::~Nacitavac()
{
	for (BytovaJednotka* bJ : *listBytovychZoskupeni)
	{
		delete bJ;
	}
	delete listBytovychZoskupeni;
	listBytovychZoskupeni = nullptr;
}

void Nacitavac::nacitajUzemneJednotky(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ, 
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{

	std::wstring value;

	std::wifstream subor2(CestaKSuboru2);
	subor2.imbue(std::locale("sk_SK.UTF-8"));
	getline(subor2, value);

	int idxRiadkuCSV = 0;
	int idxProg = 0;
	double progres = 0;

	UzemnaJednotka* obec = nullptr;
	UzemnaJednotka* okres = nullptr;
	UzemnaJednotka* kraj = nullptr;
	BytovaJednotka* bytJedn = nullptr;

	while (!subor2.eof())
	{
		if (idxRiadkuCSV == (int)(POC_RIADKOV_CSV * progres))
		{
			std::wcout << vratVypis(idxProg) << std::endl;
			idxProg++;
			progres += 0.05;
		}


		if (!getline(subor2, value, L';'))
		{
			break;
		}

		std::wstring nazovObce = value;

		getline(subor2, value, L';');
		std::wstring nazovOkresu = value;


		getline(subor2, value, L'\n');
		std::wstring nazovKraja = value;
		


		if (!stat->getTabulkaNizsichUC()->containsKey(nazovKraja))
		{
			kraj = new UzemnaJednotka(nazovKraja, KRAJ, stat);
			stat->getTabulkaNizsichUC()->insert(kraj->getNazov(), kraj);
			tabKrajov->insert(kraj->getNazov(), kraj);
			tabUJ->insert(kraj->getNazov(), kraj);

		}
		else
		{
			kraj = (*stat->getTabulkaNizsichUC())[nazovKraja];
		}

		if (!kraj->getTabulkaNizsichUC()->containsKey(nazovOkresu))
		{
			okres = new UzemnaJednotka(nazovOkresu, OKRES, kraj);
			kraj->getTabulkaNizsichUC()->insert(okres->getNazov(), okres);
			tabOkresov->insert(okres->getNazov(), okres);
			tabUJ->insert(okres->getNazov(), okres);
		}
		else
		{
			okres = (*kraj->getTabulkaNizsichUC())[nazovOkresu];
		}
		
		UzemnaJednotka* obec = nacitajObec(okres);
		if (obec != nullptr)
		{
			
			okres->getTabulkaNizsichUC()->insert(obec->getNazov(), obec);
			tabObci->insert(obec->getNazov(), obec);
			tabUJ->insert(obec->getNazov(), obec);

			if (nazovObce != obec->getNazov())
			{
				throw std::logic_error("Názvy obcí sa nezhodujú!");
			}
			
			//NACITAVANIE BYTOVYCH JEDNOTIEK

			nacitajRiadokBytovychJednotiek(obec);



		}
		idxRiadkuCSV++;
	}
	subor2.close();
}



UzemnaJednotka* Nacitavac::nacitajObec(UzemnaJednotka* okres)
{
	std::wstring value;


	if (!isSubor1Loaded)
	{
		subor1.open(CestaKSuboru1);
		subor1.imbue(std::locale("sk_SK.UTF-8"));
		getline(subor1, value);

		isSubor1Loaded = true;
	}



	if (!getline(subor1, value, L';'))
	{
		subor1.close();
		isSubor1Loaded = false;
		return nullptr;
	}
	std::wstring nazovObce = value;

	UzemnaJednotka* obec = new UzemnaJednotka(nazovObce, OBEC, okres);

	getline(subor1, value, L';');
	int pocetPreprodObyv = stoi(value);

	getline(subor1, value, L';');
	int pocetProdObyv = stoi(value);

	getline(subor1, value, L';');
	int pocetPoprodObyv = stoi(value);

	getline(subor1, value, L';');
	double celkovaVymeraV_M2 = stod(value);

	getline(subor1, value, L'\n');
	double zastavanaPlochaV_M2 = stod(value);

	obec->updatujUdaje(pocetPreprodObyv, pocetProdObyv, pocetPoprodObyv, celkovaVymeraV_M2, zastavanaPlochaV_M2);


	return obec;

}

inline void Nacitavac::nacitajBytoveZoskupenia()
{

	std::wstring value;

	std::wifstream subor3(CestaKSuboru3);
	subor3.imbue(std::locale("sk_SK.UTF-8"));
	getline(subor3, value);


	while (!subor3.eof())
	{
		if (!getline(subor3, value, L';'))
		{
			break;
		}
		std::wstring typ = value;
		std::wstring key = typ;


		getline(subor3, value, L';');
		key += value;

		value = value.substr(0, value.find(L' '));
		int pocetOsob = stoi(value);

		getline(subor3, value, L'\n');
		key += value;
		value = value.substr(0, value.find(L' '));
		int pocetObytnychMiestnosti = 0;
		if (value != L"Nezistené")
		{
			pocetObytnychMiestnosti = stoi(value);
		}
		listBytovychZoskupeni->add(new BytovaJednotka(key, typ, pocetOsob, pocetObytnychMiestnosti));


	}
	subor3.close();


}


inline void Nacitavac::nacitajRiadokBytovychJednotiek(UzemnaJednotka* obec)
{

	std::wstring value;

	if (!isSubor4Loaded)
	{
		subor4.open(CestaKSuboru4);
		subor4.imbue(std::locale("sk_SK.UTF-8"));
		getline(subor4, value);

		isSubor4Loaded = true;
	}
	int idx = 0;

	bool okresBJEmpty = obec->getVyssiUC()->getTabulkaBJ()->isEmpty();
	bool krajBJEmpty = obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->isEmpty();
	bool statBJEmpty = obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->isEmpty();

	auto okresBJIter = obec->getVyssiUC()->getTabulkaBJ()->getBeginIterator();
	auto krajBJIter = obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->getBeginIterator();
	auto statBJIter = obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->getBeginIterator();


	while (obec->getNazov() == nazovObceBJ || nazovObceBJ == L"")
	{
		
		if (!wasNameRead)
		{
			if (!getline(subor4, value, L';'))
			{
				subor4.close();
				isSubor4Loaded = false;

				delete okresBJIter;
				delete krajBJIter;
				delete statBJIter;

				return;
			}
			nazovObceBJ = value;
			wasNameRead = true;
			
		}

		if (obec->getNazov() != nazovObceBJ)
		{
			delete okresBJIter;
			delete krajBJIter;
			delete statBJIter;

			return;
		}

		getline(subor4, value, L';');
		getline(subor4, value, L';');
		

		UzemnaJednotka* uj = obec;
		BytovaJednotka* bytJednotkaVUC = nullptr;
		int mnozstvo = 0;
		for (int i = 0; i < 9; i++)
		{
			getline(subor4, value, L';');
			value.erase(remove(value.begin(), value.end(), ','), value.end());
			mnozstvo = stoi(value);
			BytovaJednotka* bytJednotka = (*listBytovychZoskupeni)[idx]->clone();
			bytJednotka->updatujUdaje(mnozstvo);
			obec->getTabulkaBJ()->insert(bytJednotka->getKey(), bytJednotka);

			
			if (okresBJEmpty)
			{
				bytJednotkaVUC = bytJednotka->clone();
				obec->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
			}
			else
			{
				bytJednotka = okresBJIter->operator*()->accessData();
				okresBJIter->operator++();
				//bytJednotka = (*obec->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
				bytJednotka->updatujUdaje(mnozstvo);
			}
			

			if (krajBJEmpty)
			{
				bytJednotkaVUC = bytJednotka->clone();
				obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
			}
			else
			{
				bytJednotka = krajBJIter->operator*()->accessData();
				krajBJIter->operator++();
				//bytJednotka = (*obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
				bytJednotka->updatujUdaje(mnozstvo);
			}

			if (statBJEmpty)
			{
				bytJednotkaVUC = bytJednotka->clone();
				obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
			}
			else
			{
				bytJednotka = statBJIter->operator*()->accessData();
				statBJIter->operator++();
				//bytJednotka = (*obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
				bytJednotka->updatujUdaje(mnozstvo);
			}
			

			idx++;
		}

		getline(subor4, value, L'\n');
		value.erase(remove(value.begin(), value.end(), ','), value.end());
		mnozstvo = stoi(value);
		BytovaJednotka* bytJednotka = (*listBytovychZoskupeni)[idx]->clone();
		bytJednotka->updatujUdaje(mnozstvo);
		obec->getTabulkaBJ()->insert(bytJednotka->getKey(), bytJednotka);


		if (okresBJEmpty)
		{
			bytJednotkaVUC = bytJednotka->clone();
			obec->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
		}
		else
		{
			bytJednotka = okresBJIter->operator*()->accessData();
			okresBJIter->operator++();
			//bytJednotka = (*obec->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
			bytJednotka->updatujUdaje(mnozstvo);
		}


		if (krajBJEmpty)
		{
			bytJednotkaVUC = bytJednotka->clone();
			obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
		}
		else
		{
			bytJednotka = krajBJIter->operator*()->accessData();
			krajBJIter->operator++();
			//bytJednotka = (*obec->getVyssiUC()->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
			bytJednotka->updatujUdaje(mnozstvo);
		}

		if (statBJEmpty)
		{
			bytJednotkaVUC = bytJednotka->clone();
			obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ()->insert(bytJednotkaVUC->getKey(), bytJednotkaVUC);
		}
		else
		{
			bytJednotka = statBJIter->operator*()->accessData();
			statBJIter->operator++();
			//bytJednotka = (*obec->getVyssiUC()->getVyssiUC()->getVyssiUC()->getTabulkaBJ())[bytJednotka->getKey()];
			bytJednotka->updatujUdaje(mnozstvo);
		}



		idx++;

		wasNameRead = false;
	}
	

}

inline std::wstring Nacitavac::vratVypis(int progres)
{
	std::wstring text;
	int prog = progres * 5;
	text.append(L"[");
	for (int i = 0; i < progres; i++)
	{
		text.append(L"=");
	}
	for (int i = progres; i < 20; i++)
	{
		text.append(L"-");
	}

	text.append(L"] ");
	
	text.append(std::to_wstring(prog));
	
	text.append(L" % ");
	
	return text;
}
