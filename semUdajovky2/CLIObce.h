#pragma once
#include "CLI.h"

class CLIObce
{
public:
	void vypisInfoOObciach(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaObci);
	void zoradObce(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaObci);

};


inline void CLIObce::vypisInfoOObciach(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaObci)
{
	std::wstring str;
	std::wcout << "----OBCE----" << std::endl;
	std::wcout << "  ----Vypisanie informacii----" << std::endl;

	std::wcout << "Stlacte 'A' pre filtrovanie na zaklade nazvu" << std::endl;
	std::wcout << "Stlacte 'B' pre filtrovanie na zaklade poctu obyvatelov" << std::endl;
	std::wcout << "Stlacte 'C' pre filtrovanie na zaklade zastavanosti" << std::endl;

	std::wcin >> str;

	KriteriumUJNazov kritUJNazov;
	KriteriumUJTyp kritUJTyp;
	KriteriumUJPocetObyv kritUJPocetObyv;
	KriteriumUJPocetPreprodObyv kritUJPocetPreProdObyv;
	KriteriumUJPocetProdObyv kritUJPocetProdObyv;
	KriteriumUJPocetPoprodObyv kritUJPocetPoprodObyv;
	KriteriumUJZastavanost kritUJZastavanost;
	KriteriumUJCelkovaVymera kritUJCelkovaVymera;
	KriteriumUJZastavanaPlocha kritUJZastavanaPlocha;

	if (str.at(0) == L'a' || str.at(0) == L'A') {
		//A
		std::wstring nazov;

		std::wcout << "Zadajte nazov obce" << std::endl;
		std::wcin.ignore();
		std::getline(std::wcin, nazov);

		FilterUJNazov filterUJNazov(&kritUJNazov, nazov);

		std::wcout << std::endl;



		UzemnaJednotka* uj = (*tabulkaObci)[nazov];

		if (uj == nullptr)
		{
			std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
			return;
		}

		UzemnaJednotka* VUC = uj;

		std::wcout << "///////// OBEC //////////" << std::endl;
		std::wcout << std::endl;

		while (VUC != nullptr)
		{
			std::wcout << "	Nazov : " << kritUJNazov.ohodnot(VUC) << std::endl;
			std::wcout << "	Typ : " << kritUJTyp.ohodnot(VUC) << std::endl;
			VUC = VUC->getVyssiUC();
		}

		std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(uj) << std::endl;
		std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(uj) << std::endl;
		std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
		std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(uj) << std::endl;
		std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(uj) << std::endl;
		std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
		std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;


		std::wcout << std::endl;


		/*
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = filterUJNazov.vyfiltrujTabulku(tabulkaObci);


		if (tempT->isEmpty())
		{
			std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
			delete tempT;
			return;
		}
		

		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{

			UzemnaJednotka* uj = tableItem->accessData();
			UzemnaJednotka* VUC = uj;

			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			while (VUC != nullptr)
			{
				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(VUC) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(VUC) << std::endl;
				VUC = VUC->getVyssiUC();
			}

			std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(uj) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;


			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;
		*/
	}
	else if (str.at(0) == L'b' || str.at(0) == L'B') {
		//B
		std::wstring pocObyvMin;
		std::wstring pocObyvMax;

		std::wcout << "Zadajte min pocet obyvatelov" << std::endl;
		std::wcin >> pocObyvMin;
		std::wcout << "Zadajte max pocet obyvatelov" << std::endl;
		std::wcin >> pocObyvMax;

		FilterUJPocetObyvatelov filterUJPocetObyv(&kritUJPocetObyv, std::stoi(pocObyvMin), std::stoi(pocObyvMax));

		std::wcout << std::endl;
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = filterUJPocetObyv.vyfiltrujTabulku(tabulkaObci);
		if (tempT->isEmpty())
		{
			std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
			delete tempT;
			return;
		}

		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{

			UzemnaJednotka* uj = tableItem->accessData();
			UzemnaJednotka* VUC = uj;

			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			while (VUC != nullptr)
			{
				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(VUC) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(VUC) << std::endl;
				VUC = VUC->getVyssiUC();
			}

			std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(uj) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;


			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;

	}
	else if (str.at(0) == L'c' || str.at(0) == L'C') {
		//C
		std::wstring zastMin;
		std::wstring zastMax;

		std::wcout << "Zadajte min zastavanost" << std::endl;
		std::wcin >> zastMin;
		std::wcout << "Zadajte max zastavanost" << std::endl;
		std::wcin >> zastMax;

		FilterUJZastavanost filterUJZastavanost(&kritUJZastavanost, std::stod(zastMin), std::stod(zastMax));

		std::wcout << std::endl;
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = filterUJZastavanost.vyfiltrujTabulku(tabulkaObci);
		if (tempT->isEmpty())
		{
			std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
			delete tempT;
			return;
		}
		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{

			UzemnaJednotka* uj = tableItem->accessData();
			UzemnaJednotka* VUC = uj;

			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			while (VUC != nullptr)
			{
				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(VUC) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(VUC) << std::endl;
				VUC = VUC->getVyssiUC();
			}

			std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(uj) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;


			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;

	}
	else
	{
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}

}

inline void CLIObce::zoradObce(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaObci)
{
	std::wstring str;
	std::wcout << "----OBCE----" << std::endl;
	std::wcout << "  ----Zoradenie obci----" << std::endl;

	std::wcout << "Stlacte 'A' pre zoradenie na zaklade nazvu" << std::endl;
	std::wcout << "Stlacte 'B' pre zoradenie na zaklade poctu obyvatelov" << std::endl;
	std::wcout << "Stlacte 'C' pre zoradenie na zaklade zastavanosti" << std::endl;

	std::wcin >> str;

	KriteriumUJNazov kritUJNazov;

	if (str.at(0) == L'a' || str.at(0) == L'A') {
		//A

		Triedenie<std::wstring, UzemnaJednotka*, std::wstring> triedenie;

		bool vzost;
		std::wcout << "Prajete si triedit vzostupne?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;
		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			vzost = true;
		}
		else
		{
			vzost = false;
		}

		UnsortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tabulkaObci->clone());
		triedenie.sort(tempT, &kritUJNazov, vzost);


		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{
			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			UzemnaJednotka* uj = tableItem->accessData();

			std::wcout << "	Nazov : " << kritUJNazov.ohodnot(uj) << std::endl;

			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;
	}
	else if (str.at(0) == L'b' || str.at(0) == L'B') {
		//B
		KriteriumUJPocetObyv kritUJPocetObyv;

		Triedenie<std::wstring, UzemnaJednotka*, unsigned int> triedenie;

		bool vzost;
		std::wcout << "Prajete si triedit vzostupne?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;
		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			vzost = true;
		}
		else
		{
			vzost = false;
		}

		UnsortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tabulkaObci->clone());
		triedenie.sort(tempT, &kritUJPocetObyv, vzost);

		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{
			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			UzemnaJednotka* uj = tableItem->accessData();

			std::wcout << "	Nazov : " << kritUJNazov.ohodnot(uj) << std::endl;
			std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(uj) << std::endl;

			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;

	}
	else if (str.at(0) == L'c' || str.at(0) == L'C') {
		//C
		KriteriumUJZastavanost kritUJZastavanost;

		Triedenie<std::wstring, UzemnaJednotka*, double> triedenie;

		bool vzost;
		std::wcout << "Prajete si triedit vzostupne?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;
		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			vzost = true;
		}
		else
		{
			vzost = false;
		}

		UnsortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tabulkaObci->clone());
		triedenie.sort(tempT, &kritUJZastavanost, vzost);

		for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
		{
			std::wcout << "///////// OBEC //////////" << std::endl;
			std::wcout << std::endl;

			UzemnaJednotka* uj = tableItem->accessData();

			std::wcout << "	Nazov : " << kritUJNazov.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(uj) << std::endl;

			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;

	}
	else
	{
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
}