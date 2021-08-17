#pragma once

#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono> 

#include "structures/heap_monitor.h"

#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/list/list.h"

#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"

#include "structures/table/sorting/quick_sort.h"
#include "Nacitavac.h"
#include "Triedenie.h"

#include "Kriterium.h"
	#include "KriteriumUJ.h"
		#include "KriteriumUJCelkovaVymera.h"
		#include "KriteriumUJNazov.h"
		#include "KriteriumUJPocetObyv.h"
		#include "KriteriumUJPocetPoprodObyv.h"
		#include "KriteriumUJPocetPreprodObyv.h"
		#include "KriteriumUJPocetProdObyv.h"
		#include "KriteriumUJPrislusnost.h"
		#include "KriteriumUJTyp.h"
		#include "KriteriumUJZastavanaPlocha.h"
		#include "KriteriumUJZastavanost.h"
	#include "KriteriumBJ.h"
		#include "KriteriumBJPocet.h"
		#include "KriteriumBJPocetIzieb.h"
		#include "KriteriumBJPocetOsob.h"
		#include "KriteriumBJTyp.h"



#include "ZlozenyFilter.h"
#include "Filter.h"
	#include "FilterPodlaHodnoty.h"
		#include "FilterUJHodnota.h"
			#include "FilterUJNazov.h"
			#include "FilterUJPrislusnost.h"
			#include "FilterUJTyp.h"
		#include "FilterBJHodnota.h"
			#include "FilterBJTyp.h"
	#include "FilterPodlaIntervalu.h"
		#include "FilterUJInterval.h"
			#include "FilterUJPocetObyvatelov.h"
			#include "FilterUJZastavanost.h"
		#include "FilterBJInterval.h"
			#include "FilterBJPocetIzieb.h"
			#include "FilterBJPocetOsob.h"

#include "CLIObce.h"
#include "CLIUzemneJednotky.h"
#include "CLIBytoveJednotky.h"

#include <time.h>
#include <chrono> 
#include <locale>
#include <io.h>
#include <fcntl.h>


class CLI
{
private:
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaUJ;
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaObci;
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaOkresov;
	SortedSequenceTable<std::wstring, UzemnaJednotka*>* tabulkaKrajov;
	UzemnaJednotka* stat;

public:

	CLI();
	~CLI();
	
	bool behAplikacie();
	void obce();
		void vypisInfoOObciach();
		void zoradObce();
	void uzemneJednotky();
		void vypisInfoOUzemnychJednotkach();
		void zoradUzemneJednotky();
	void vypisBJ();
		void vypisInfoOZoskBJvoZvolenejUJ();
		void vypisSumInfoOPoctochBJvoZvolenychUJ();
		void zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ();
	std::wstring vratVypis(int progres);
};


CLI::CLI()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	std::wcout << "Vitajte v aplikacii! " << std::endl;
	std::wcout << "Tato aplikacia sluzi na filtrovanie udajov z uzemnych a bytovych jednotiek, ktore boli nacitane zo suborov typu csv." << std::endl;
	std::wcout << "Prajem prijemny zazitok!" << std::endl;


	std::wcout << "///////// ZACINA NACITAVANIE SUBOROV //////////" << std::endl;

	tabulkaUJ = new SortedSequenceTable<std::wstring, UzemnaJednotka*>();
	tabulkaObci = new SortedSequenceTable<std::wstring, UzemnaJednotka*>();
	tabulkaOkresov = new SortedSequenceTable<std::wstring, UzemnaJednotka*>();
	tabulkaKrajov = new SortedSequenceTable<std::wstring, UzemnaJednotka*>();

	stat = new UzemnaJednotka(L"Slovensko", STAT, nullptr);
	tabulkaUJ->insert(stat->getNazov(), stat);

	
	Nacitavac* nacitavac = new Nacitavac();

	nacitavac->nacitajBytoveZoskupenia();

	auto start = std::chrono::high_resolution_clock::now();
	
	nacitavac->nacitajUzemneJednotky(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::wcout << "RYCHLOST V MILLI : " << duration.count() << std::endl;

	delete nacitavac;

	std::wcout << "///////// NACITAVANIE SUBOROV HOTOVE //////////" << std::endl;
}


CLI::~CLI()
{

	std::wcout << "///////// ZACINA MAZANIE STRUKTUR //////////" << std::endl;

	int idxTI = 0;
	int idxProg = 0;
	double progres = 0;

	for (TableItem<std::wstring, UzemnaJednotka*>* tableItem : *tabulkaUJ)
	{
		if (idxTI == (int)(tabulkaUJ->size() * progres))
		{
			std::wcout << vratVypis(idxProg) << std::endl;
			idxProg++;
			progres += 0.05;
		}
		idxTI++;

		delete tableItem->accessData();
		tableItem = nullptr;
	}
	if (idxTI == (int)(tabulkaUJ->size() * progres))
	{
		std::wcout << vratVypis(idxProg) << std::endl;
		idxProg++;
		progres += 0.05;
	}


	delete tabulkaUJ;
	tabulkaUJ = nullptr;

	delete tabulkaObci;
	tabulkaObci = nullptr;

	delete tabulkaOkresov;
	tabulkaOkresov = nullptr;

	delete tabulkaKrajov;
	tabulkaKrajov = nullptr;

	stat = nullptr;

	std::wcout << "///////// MAZANIE STRUKTUR HOTOVE //////////" << std::endl;
}


bool CLI::behAplikacie()
{

	std::wstring str;
	std::wcout << "Stlacte : 1 : pre pracu s obcami" << std::endl;
	std::wcout << "Stlacte : 2 : pre pracu s uzemnymi jednotkami" << std::endl;
	std::wcout << "Stlacte : 3 : pre pracu s bytovymi jednotkami" << std::endl;
	std::wcout << "Stlacte : 4 : pre koniec" << std::endl;
	std::wcin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			obce();
			break;
		}
		case 2: {
			uzemneJednotky();
			break;
		}
		case 3: {
			vypisBJ();
			break;
		}
		case 4: {
			return false;
			break;
		}

		default:
			std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {
		
		std::wcout << str << std::endl;

		return behAplikacie();
	}

	std::wcout << std::endl;
}

inline void CLI::obce()
{

	std::wstring str;
	std::wcout << "----OBCE----" << std::endl;
	std::wcout << "Stlacte : 1 : pre vypisanie informacii o obciach (Uloha1)" << std::endl;
	std::wcout << "Stlacte : 2 : pre zoradenie obci (Uloha2)" << std::endl;
	std::wcin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			vypisInfoOObciach();
			break;
		}
		case 2: {
			zoradObce();
			break;
		}

		default:
			std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {

		std::wcout << str << std::endl;

		return;
	}

	std::wcout << std::endl;
}

inline void CLI::vypisInfoOObciach()
{
	CLIObce cliObce;
	cliObce.vypisInfoOObciach(tabulkaObci);

}

inline void CLI::zoradObce()
{
	CLIObce cliObce;
	cliObce.zoradObce(tabulkaObci);
}

inline void CLI::uzemneJednotky()
{
	std::wstring str;
	std::wcout << "----UZEMNE JEDNOTKY----" << std::endl;
	std::wcout << "Stlacte : 1 : pre vypisanie informacii o uzemnych jednotkach (Uloha3)" << std::endl;
	std::wcout << "Stlacte : 2 : pre zoradenie uzemnych jednotiek (Uloha4)" << std::endl;
	std::wcin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			vypisInfoOUzemnychJednotkach();
			break;
		}
		case 2: {
			zoradUzemneJednotky();
			break;
		}

		default:
			std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {

		std::wcout << str << std::endl;

		return;
	}

	std::wcout << std::endl;
}

inline void CLI::vypisInfoOUzemnychJednotkach()
{
	CLIUzemneJednotky cliUJ;
	cliUJ.vypisInfoOUzemnychJednotkach(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);
}

inline void CLI::zoradUzemneJednotky()
{
	CLIUzemneJednotky cliUJ;
	cliUJ.zoradUzemneJednotky(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);

}

inline void CLI::vypisBJ()
{
	std::wstring str;
	std::wcout << "----BYTOVE JEDNOTKY----" << std::endl;
	std::wcout << "Stlacte : 1 : pre vypisanie informacii o zoskupeni bytovych jednotiek vo zvolenej uzemnej jednotke (Uloha5)" << std::endl;
	std::wcout << "Stlacte : 2 : pre vypisanie sumarnych informacii o poctoch bytovych jednotiek vo zovlenych uzemnych jednotkach (Uloha6)" << std::endl;
	//std::wcout << "Stlacte : 3 : pre zoradenie uzemnych jednotiek podla sumarneho poctu zvolenych bytovych jednotiek (Uloha7)" << std::endl;
	std::wcin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			vypisInfoOZoskBJvoZvolenejUJ();
			break;
		}
		case 2: {
			vypisSumInfoOPoctochBJvoZvolenychUJ();
			break;
		}
		/*
		case 3: {
			zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ();
			break;
		}
		*/
		default:
			std::wcout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {

		std::wcout << str << std::endl;

		return;
	}

	std::wcout << std::endl;
}

inline void CLI::vypisInfoOZoskBJvoZvolenejUJ()
{
	CLIBytoveJednotky cliBJ;
	cliBJ.vypisInfoOZoskBJvoZvolenejUJ(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);
}

inline void CLI::vypisSumInfoOPoctochBJvoZvolenychUJ()
{
	CLIBytoveJednotky cliBJ;
	cliBJ.vypisSumInfoOPoctochBJvoZvolenychUJ(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);
}

inline void CLI::zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ()
{
	CLIBytoveJednotky cliBJ;
	cliBJ.zoradUzemneJednotkyPodlaSumPoctuZvolenychBJ(tabulkaUJ, tabulkaObci, tabulkaOkresov, tabulkaKrajov, stat);
}

inline std::wstring CLI::vratVypis(int progres)
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