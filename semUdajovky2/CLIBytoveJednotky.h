#pragma once
#include "CLI.h"

class CLIBytoveJednotky
{
public:
	void vypisInfoOZoskBJvoZvolenejUJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);
	void vypisSumInfoOPoctochBJvoZvolenychUJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);
	void zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
		UzemnaJednotka* stat);

};

void CLIBytoveJednotky::vypisInfoOZoskBJvoZvolenejUJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{

	std::wstring str;
	std::wcout << "----BYTOVE JEDNOTKY----" << std::endl;
	std::wcout << "  ----Vypisanie informacii----" << std::endl;

	ZlozenyFilter<std::wstring, UzemnaJednotka*> zFilter;
	zFilter.clear();


	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabWorking = tabUJ;

	KriteriumUJNazov kritUJNazov;
	KriteriumUJTyp kritUJTyp;
	KriteriumUJPocetObyv kritUJPocetObyv;
	KriteriumUJPocetProdObyv kritUJPocetProdObyv;
	KriteriumUJCelkovaVymera kritUJCelkovaVymera;
	KriteriumUJZastavanaPlocha kritUJZastavanaPlocha;

	KriteriumBJTyp kritBJTyp;
	KriteriumBJPocetOsob kritBJPocetOsob;
	KriteriumBJPocetIzieb kritBJPocetIzieb;
	KriteriumBJPocet kritBJPocet;

	UzemnaJednotkaTyp ujTyp = UzemnaJednotkaTyp::OBEC;
	std::wstring prislusnost;

	try
	{

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
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(stat) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(stat) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(stat) << std::endl;

			std::wcout << std::endl;

			for (auto tI : *stat->getTabulkaBJ())
			{
				std::wcout << "	///////// BYTOVA JEDNOTKA PRE " << stat->getNazov() << " //////////" << std::endl;
				std::wcout << std::endl;

				BytovaJednotka* bJ = tI->accessData();
				std::wcout << "		Typ : " << kritBJTyp.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet osob : " << kritBJPocetOsob.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet izieb : " << kritBJPocetIzieb.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet : " << kritBJPocet.ohodnot(bJ) << std::endl;

				std::wcout << std::endl;
			}
			std::wcout << std::endl;
			return;
		}

		FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
		zFilter.pridajFilter(&filterUJTyp);
		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilter.odoberFilter(&filterUJTyp);
		}


		std::wcout << "Prajete si pridat filter nazov?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;

		std::wstring nazov;
		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			std::wcout << "Zadajte nazov uzemnej jednotky" << std::endl;
			std::wcin.ignore();
			std::getline(std::wcin, nazov);

		}


		FilterUJNazov filterUJNazov(&kritUJNazov, nazov);
		zFilter.pridajFilter(&filterUJNazov);

		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilter.odoberFilter(&filterUJNazov);
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
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;

			std::wcout << std::endl;

			for (auto tI : *uj->getTabulkaBJ())
			{
				std::wcout << "	///////// BYTOVA JEDNOTKA PRE " << uj->getNazov() <<" //////////" << std::endl;
				std::wcout << std::endl;

				BytovaJednotka* bJ = tI->accessData();
				std::wcout << "		Typ : " << kritBJTyp.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet osob : " << kritBJPocetOsob.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet izieb : " << kritBJPocetIzieb.ohodnot(bJ) << std::endl;
				std::wcout << "		Pocet : " << kritBJPocet.ohodnot(bJ) << std::endl;

				std::wcout << std::endl;
			}
			std::wcout << std::endl;
		}
		std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		delete tempT;
			

	}
	catch (const std::exception e)
	{
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}

}

inline void CLIBytoveJednotky::vypisSumInfoOPoctochBJvoZvolenychUJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{


	std::wstring str;
	std::wcout << "----BYTOVE JEDNOTKY----" << std::endl;
	std::wcout << "  ----Vypisanie sumarnych informacii----" << std::endl;

	ZlozenyFilter<std::wstring, UzemnaJednotka*> zFilter;
	zFilter.clear();

	ZlozenyFilter<std::wstring, BytovaJednotka*> zFilterBJ;
	zFilterBJ.clear();

	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabWorking = tabUJ;

	KriteriumUJNazov kritUJNazov;
	KriteriumUJTyp kritUJTyp;
	KriteriumUJPocetObyv kritUJPocetObyv;
	KriteriumUJPocetProdObyv kritUJPocetProdObyv;
	KriteriumUJCelkovaVymera kritUJCelkovaVymera;
	KriteriumUJZastavanaPlocha kritUJZastavanaPlocha;

	KriteriumBJTyp kritBJTyp;
	KriteriumBJPocetOsob kritBJPocetOsob;
	KriteriumBJPocetIzieb kritBJPocetIzieb;
	KriteriumBJPocet kritBJPocet;


	UzemnaJednotkaTyp ujTyp = UzemnaJednotkaTyp::OBEC;
	std::wstring prislusnost;

	try
	{

		std::wcout << "Prajete si pridat filter typ uzemnej jednotky?" << std::endl;
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

		FilterUJTyp filterUJTyp(&kritUJTyp, ujTyp);
		zFilter.pridajFilter(&filterUJTyp);
		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilter.odoberFilter(&filterUJTyp);
		}


		std::wstring pocObyvMin = L"0";
		std::wstring pocObyvMax = L"0";

		std::wcout << "Prajete si pridat filter pocet obyvatelov?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;

		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			std::wcout << "Zadajte min pocet obyvatelov" << std::endl;
			std::wcin >> pocObyvMin;
			std::wcout << "Zadajte max pocet obyvatelov" << std::endl;
			std::wcin >> pocObyvMax;

		}

		FilterUJPocetObyvatelov filterUJPocetObyv(&kritUJPocetObyv, std::stoi(pocObyvMin), std::stoi(pocObyvMax));

		zFilter.pridajFilter(&filterUJPocetObyv);


		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilter.odoberFilter(&filterUJPocetObyv);
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


		std::wcout << "Prajete si pridat filter typ bytovej jednotky?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;

		std::wstring typBJ;

		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			std::wcout << "Zadajte typ bytovej jednotky" << std::endl;
			std::wcin.ignore();
			std::getline(std::wcin, typBJ);

		}

		FilterBJTyp filterBJTyp(&kritBJTyp, typBJ);
		zFilterBJ.pridajFilter(&filterBJTyp);

		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilterBJ.odoberFilter(&filterBJTyp);
		}


		std::wcout << "Prajete si pridat filter pocet osob bytovej jednotky?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;

		std::wstring pocOsobBJMin = L"0";
		std::wstring pocOsobBJMax = L"0";
		

		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			std::wcout << "Zadajte pocet osob bytovej jednotky" << std::endl;

			std::wcout << "Zadajte min pocet osob" << std::endl;
			std::wcin >> pocOsobBJMin;

			std::wcout << "Zadajte max pocet osob" << std::endl;
			std::wcin >> pocOsobBJMax;
		}


		FilterBJPocetOsob filterBJPocetOsob(&kritBJPocetOsob, stoi(pocOsobBJMin), stoi(pocOsobBJMax));
		zFilterBJ.pridajFilter(&filterBJPocetOsob);

		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilterBJ.odoberFilter(&filterBJPocetOsob);
		}



		std::wcout << "Prajete si pridat filter pocet izieb bytovej jednotky?" << std::endl;
		std::wcout << "a - Ano | n - Nie" << std::endl;
		std::wcin >> str;

		std::wstring pocIziebBJMin = L"0";
		std::wstring pocIziebBJMax = L"0";


		if (str.at(0) == L'a' || str.at(0) == L'A')
		{
			std::wcout << "Zadajte pocet izieb bytovej jednotky" << std::endl;

			std::wcout << "Zadajte min pocet izieb" << std::endl;
			std::wcin >> pocIziebBJMin;

			std::wcout << "Zadajte max pocet izieb" << std::endl;
			std::wcin >> pocIziebBJMax;
		}


		FilterBJPocetIzieb filterBJPocetIzieb(&kritBJPocetIzieb, stoi(pocIziebBJMin), stoi(pocIziebBJMax));
		zFilterBJ.pridajFilter(&filterBJPocetIzieb);

		if (str.at(0) != L'a' && str.at(0) != L'A')
		{
			zFilterBJ.odoberFilter(&filterBJPocetIzieb);
		}

		int bjPocet = 0;


		SortedSequenceTable<std::wstring, UzemnaJednotka*>* tempT = zFilter.vyfiltrujTabulku(tabWorking);
		if (tempT->isEmpty())
		{
			std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
			delete tempT;
			return;
		}

		std::wcout << std::endl;
		if (ujTyp == UzemnaJednotkaTyp::STAT)
		{
			std::wcout << "///////// UZEMNA JEDNOTKA //////////" << std::endl;
			std::wcout << std::endl;

			std::wcout << "	Nazov : " << kritUJNazov.ohodnot(stat) << std::endl;
			std::wcout << "	Typ : " << kritUJTyp.ohodnot(stat) << std::endl;

			std::wcout << "	Pocet obyv. : " << kritUJPocetObyv.ohodnot(stat) << std::endl;
			std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(stat) << std::endl;
			std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(stat) << std::endl;
			std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(stat) << std::endl;

			std::wcout << std::endl;


			UnsortedSequenceTable<std::wstring, BytovaJednotka*>* tempG = zFilterBJ.vyfiltrujTabulkuUnsorted(stat->getTabulkaBJ());
			if (tempG->isEmpty())
			{
				std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
				delete tempG;
				delete tempT;
				return;
			}

			for (auto tI : *tempG)
			{
				BytovaJednotka* bJ = tI->accessData();

				bjPocet += kritBJPocet.ohodnot(bJ);

			}
			std::wcout << "Pocet zvolenych zoskupeni bytovych jednotiek : " << bjPocet << std::endl;

			std::wcout << std::endl;
			delete tempG;
		}
		else
		{

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
				std::wcout << "	Pocet prod obyv. : " << kritUJPocetProdObyv.ohodnot(uj) << std::endl;
				std::wcout << "	Celkova vymera : " << kritUJCelkovaVymera.ohodnot(uj) << std::endl;
				std::wcout << "	Zastavana plocha : " << kritUJZastavanaPlocha.ohodnot(uj) << std::endl;

				std::wcout << std::endl;

				UnsortedSequenceTable<std::wstring, BytovaJednotka*>* tempG = zFilterBJ.vyfiltrujTabulkuUnsorted(tableItem->accessData()->getTabulkaBJ());
				if (tempG->isEmpty())
				{
					std::wcout << "Nenasli sa ziadne vysledky" << std::endl;
					delete tempG;
					delete tempT;
					return;
				}


				for (auto tI : *tempG)
				{
					BytovaJednotka* bJ = tI->accessData();

					bjPocet += kritBJPocet.ohodnot(bJ);

				}
				std::wcout << "Pocet zvolenych zoskupeni bytovych jednotiek : " << bjPocet << std::endl;

				std::wcout << std::endl;
				delete tempG;
			}
			std::wcout << "Celkovy pocet vysledkov : " << tempT->size() << std::endl;

		}
		delete tempT;
	}
	catch (const std::exception e)
	{
		
		std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
}

inline void CLIBytoveJednotky::zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ(SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabUJ,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabObci,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabOkresov,
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabKrajov,
	UzemnaJednotka* stat)
{
	std::wcout << "WIP" << std::endl;
}