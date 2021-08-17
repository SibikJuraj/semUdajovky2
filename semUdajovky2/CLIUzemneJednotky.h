#pragma once
#include "CLI.h"

class CLIUzemneJednotky
{
public:
	void vypisInfoOUzemnychJednotkach(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);
	void zoradUzemneJednotky(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);

};

void CLIUzemneJednotky::vypisInfoOUzemnychJednotkach(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{

	std::wstring str;
	std::wcout << "----UZEMNE JEDNOTKY----" << std::endl;
	std::wcout << "  ----Vypisanie informacii----" << std::endl;

	std::wcout << "Stlacte 'A' pre filtrovanie na zaklade nazvu" << std::endl;
	std::wcout << "Stlacte 'B' pre filtrovanie na zaklade poctu obyvatelov" << std::endl;
	std::wcout << "Stlacte 'C' pre filtrovanie na zaklade zastavanosti" << std::endl;

	std::wcin >> str;

	ZlozenyFilter<std::wstring, UzemnaJednotka*> zFilter;
	zFilter.clear();


	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabWorking = tabUJ;

	KriteriumUJNazov kritUJNazov;
	KriteriumUJTyp kritUJTyp;
	KriteriumUJPocetObyv kritUJPocetObyv;
	KriteriumUJPocetPreprodObyv kritUJPocetPreProdObyv;
	KriteriumUJPocetProdObyv kritUJPocetProdObyv;
	KriteriumUJPocetPoprodObyv kritUJPocetPoprodObyv;
	KriteriumUJZastavanost kritUJZastavanost;
	KriteriumUJCelkovaVymera kritUJCelkovaVymera;
	KriteriumUJZastavanaPlocha kritUJZastavanaPlocha;
	UzemnaJednotkaTyp ujTyp = UzemnaJednotkaTyp::OBEC;
	std::wstring prislusnost;

	try
	{
		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			//A
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;
				
				switch (std::stoi(str))
				{
					case 0:
						ujTyp = UzemnaJednotkaTyp::STAT;
						break;
					case 1:
						ujTyp = UzemnaJednotkaTyp::KRAJ;
						tabWorking = tabKrajov;
						break;
					case 2:
						ujTyp = UzemnaJednotkaTyp::OKRES;
						tabWorking = tabOkresov;
						break;
					case 3:
						ujTyp = UzemnaJednotkaTyp::OBEC;
						tabWorking = tabObci;
						break;
					default:
						std::wcout << "Zle zadane cislo" << std::endl;
						return;
				}

			}
			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(stat) << std::endl;

				std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(stat) << std::endl;
				std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}
			
	
			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}
			
			std::wstring nazov;

			std::wcout << "Zadajte nazov uzemnej jednotky" << std::endl;
			std::wcin.ignore();
			std::getline(std::wcin, nazov);

			FilterUJNazov filterUJNazov(&kritUJNazov, nazov);
			zFilter.pridajFilter(&filterUJNazov);

			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{	
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);
				
			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;

			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}

			UzemnaJednotka* uj = (*tempT)[nazov];

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
			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				UzemnaJednotka* uj = tableItem->accessData();
				UzemnaJednotka* VUC = uj;
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
			*/
			delete tempT;
				
			
			
		}
		else if (str.at(0) == L'b' || str.at(0) == L'B') {
			//B
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;

				switch (std::stoi(str))
				{
				case 0:
					ujTyp = UzemnaJednotkaTyp::STAT;
					break;
				case 1:
					ujTyp = UzemnaJednotkaTyp::KRAJ;
					tabWorking = tabKrajov;
					break;
				case 2:
					ujTyp = UzemnaJednotkaTyp::OKRES;
					tabWorking = tabOkresov;
					break;
				case 3:
					ujTyp = UzemnaJednotkaTyp::OBEC;
					tabWorking = tabObci;
					break;
				default:
					std::wcout << "Zle zadane cislo" << std::endl;
					return;
				}


			}
			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(stat) << std::endl;

				std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(stat) << std::endl;
				std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}



			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}

			std::wstring pocObyvMin;
			std::wstring pocObyvMax;

			std::wcout << "Zadajte min pocet obyvatelov" << std::endl;
			std::wcin >> pocObyvMin;
			std::wcout << "Zadajte max pocet obyvatelov" << std::endl;
			std::wcin >> pocObyvMax;

			FilterUJPocetObyvatelov filterUJPocetObyv(&kritUJPocetObyv, std::stoi(pocObyvMin), std::stoi(pocObyvMax));

			zFilter.pridajFilter(&filterUJPocetObyv);

			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);

			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;

			
			
			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}
			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				UzemnaJednotka* uj = tableItem->accessData();
				UzemnaJednotka* VUC = uj;
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
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;

				switch (std::stoi(str))
				{
				case 0:
					ujTyp = UzemnaJednotkaTyp::STAT;
					break;
				case 1:
					ujTyp = UzemnaJednotkaTyp::KRAJ;
					tabWorking = tabKrajov;
					break;
				case 2:
					ujTyp = UzemnaJednotkaTyp::OKRES;
					tabWorking = tabOkresov;
					break;
				case 3:
					ujTyp = UzemnaJednotkaTyp::OBEC;
					tabWorking = tabObci;
					break;
				default:
					std::wcout << "Zle zadane cislo" << std::endl;
					return;
				}


			}

			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
				std::wcout << "	Typ : " << kritUJTyp.ohodnot(stat) << std::endl;

				std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet preprod obyv. : " << kritUJPocetPreProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Pocet poprod obyv. : " << kritUJPocetPoprodObyv.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(stat) << std::endl;
				std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}


			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}

			std::wstring zastMin;
			std::wstring zastMax;

			std::wcout << "Zadajte min zastavanost" << std::endl;
			std::wcin >> zastMin;
			std::wcout << "Zadajte max zastavanost" << std::endl;
			std::wcin >> zastMax;

			FilterUJZastavanost filterUJZastavanost(&kritUJZastavanost, std::stod(zastMin), std::stod(zastMax));


			zFilter.pridajFilter(&filterUJZastavanost);

			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);

			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;


			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}
			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				UzemnaJednotka* uj = tableItem->accessData();
				UzemnaJednotka* VUC = uj;
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
	catch (const std::exception e)
	{
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
}

inline void CLIUzemneJednotky::zoradUzemneJednotky(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{
	std::wstring str;
	std::wcout << "----UZEMNE JEDNOTKY----" << std::endl;
	std::wcout << "  ----Zoradenie uzemnych jednotiek----" << std::endl;

	std::wcout << "Stlacte 'A' pre zoradenie na zaklade nazvu" << std::endl;
	std::wcout << "Stlacte 'B' pre zoradenie na zaklade poctu obyvatelov" << std::endl;
	std::wcout << "Stlacte 'C' pre zoradenie na zaklade zastavanosti" << std::endl;

	std::wcin >> str;

	ZlozenyFilter<std::wstring, UzemnaJednotka*> zFilter;
	zFilter.clear();

	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabWorking = tabUJ;

	KriteriumUJNazov kritUJNazov;
	KriteriumUJTyp kritUJTyp;
	KriteriumUJPocetObyv kritUJPocetObyv;
	KriteriumUJZastavanost kritUJZastavanost;
	UzemnaJednotkaTyp ujTyp = UzemnaJednotkaTyp::OBEC;
	std::wstring prislusnost;

	try
	{
		if (str.at(0) == L'a' || str.at(0) == L'A') {
			//A
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;

				switch (std::stoi(str))
				{
				case 0:
					ujTyp = UzemnaJednotkaTyp::STAT;
					break;
				case 1:
					ujTyp = UzemnaJednotkaTyp::KRAJ;
					tabWorking = tabKrajov;
					break;
				case 2:
					ujTyp = UzemnaJednotkaTyp::OKRES;
					tabWorking = tabOkresov;
					break;
				case 3:
					ujTyp = UzemnaJednotkaTyp::OBEC;
					tabWorking = tabObci;
					break;
				default:
					std::wcout << "Zle zadane cislo" << std::endl;
					return;
				}

			}
			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}

			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}

			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);

			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;

		
			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}


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

			triedenie.sort(reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tempT), &kritUJNazov, vzost);


			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
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
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;

				switch (std::stoi(str))
				{
				case 0:
					ujTyp = UzemnaJednotkaTyp::STAT;
					break;
				case 1:
					ujTyp = UzemnaJednotkaTyp::KRAJ;
					tabWorking = tabKrajov;
					break;
				case 2:
					ujTyp = UzemnaJednotkaTyp::OKRES;
					tabWorking = tabOkresov;
					break;
				case 3:
					ujTyp = UzemnaJednotkaTyp::OBEC;
					tabWorking = tabObci;
					break;
				default:
					std::wcout << "Zle zadane cislo" << std::endl;
					return;
				}

			}

			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
				std::wcout << "	Poc. obyv " << kritUJPocetObyv.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}

			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}
			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);

			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;

		
			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}

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

			triedenie.sort(reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tempT), &kritUJPocetObyv, vzost);

			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
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
			std::wcout << "Prajete si pridat filter typ?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;

			if (str.at(0) == L'a' || str.at(0) == L'A')
			{

				std::wcout << "Zadajte typ uzemnej jednotky" << std::endl;
				std::wcout << "0 = stat | 1 = kraj | 2 = okres | 3 = obec" << std::endl;
				std::wcin >> str;

				switch (std::stoi(str))
				{
				case 0:
					ujTyp = UzemnaJednotkaTyp::STAT;
					break;
				case 1:
					ujTyp = UzemnaJednotkaTyp::KRAJ;
					tabWorking = tabKrajov;
					break;
				case 2:
					ujTyp = UzemnaJednotkaTyp::OKRES;
					tabWorking = tabOkresov;
					break;
				case 3:
					ujTyp = UzemnaJednotkaTyp::OBEC;
					tabWorking = tabObci;
					break;
				default:
					std::wcout << "Zle zadane cislo" << std::endl;
					return;
				}

			}

			if (ujTyp == UzemnaJednotkaTyp::STAT)
			{
				std::wcout << std::endl;
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
				std::wcout << std::endl;

				std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
				std::wcout << "	Zastavanost : " << kritUJZastavanost.ohodnot(stat) << std::endl;

				std::wcout << std::endl;
				return;
			}

			FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
			zFilter.pridajFilter(&filterUJTyp);
			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJTyp);
			}

			std::wcout << "Prajete si pridat filter prislusnost?" << std::endl;
			std::wcout << "a - Ano | n - Nie" << std::endl;
			std::wcin >> str;


			if (str.at(0) == L'a' || str.at(0) == L'A')
			{
				std::wcout << "Zadajte nazov uzemnej jednotky, pod ktoru ma patrit uzemna jednotka so zvolenym nazvom" << std::endl;
				std::wcin.ignore();
				std::getline(std::wcin, prislusnost);

			}
			else
			{
				prislusnost = L"Slovensko";
			}

			KriteriumUJPrislusnost kritUJPrislusnost((*tabUJ)[prislusnost]);
			FilterUJPrislusnost filterUJPrislusnost(&kritUJPrislusnost, true);
			zFilter.pridajFilter(&filterUJPrislusnost);

			if (str.at(0) != L'a' && str.at(0) != L'A')
			{
				zFilter.odoberFilter(&filterUJPrislusnost);
			}

			std::wcout << std::endl;

			
			SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
			if (tempT->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempT;
				return;
			}

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

			triedenie.sort(reinterpret_cast<UnsortedSequenceTable<std::wstring, UzemnaJednotka*>*>(tempT), &kritUJZastavanost, vzost);

			for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tempT)
			{
				std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
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
	catch (const std::exception e)
	{
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
}
