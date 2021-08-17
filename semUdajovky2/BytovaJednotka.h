#pragma once


#include <string>
using namespace structures;

class BytovaJednotka
{
private:
	std::wstring typ;
	std::wstring key;
	unsigned int pocetOsob;
	unsigned int pocetObytnychMiestnosti;
	unsigned int mnozstvo;


public:
	BytovaJednotka(std::wstring key, std::wstring typ, unsigned int pocetOsob, unsigned int pocetObytnychMiestnosti);
	BytovaJednotka(BytovaJednotka& other);
	~BytovaJednotka();
	void updatujUdaje(unsigned int mnozstvo);
	std::wstring getKey();
	std::wstring getTyp();
	unsigned int getPocetOsob();
	unsigned int getPocetObytnychMiestnosti();
	unsigned int getMnozstvo();
	BytovaJednotka* clone();
};

BytovaJednotka::BytovaJednotka(std::wstring key, std::wstring typ, unsigned int pocetOsob, unsigned int pocetObytnychMiestnosti)
{
	this->key = key;
	this->typ = typ;
	this->pocetOsob = pocetOsob;
	this->pocetObytnychMiestnosti = pocetObytnychMiestnosti;
	this->mnozstvo = 0;
}

inline BytovaJednotka::BytovaJednotka(BytovaJednotka& other)
{
	this->key = other.key;
	this->typ = other.typ;
	this->pocetOsob = other.pocetOsob;
	this->pocetObytnychMiestnosti = other.pocetObytnychMiestnosti;
	this->mnozstvo = 0;
}

inline BytovaJednotka::~BytovaJednotka()
{
}

inline BytovaJednotka* BytovaJednotka::clone()
{
	return new BytovaJednotka(*this);
}


inline void BytovaJednotka::updatujUdaje(unsigned int mnozstvo)
{
	this->mnozstvo += mnozstvo;
}

inline std::wstring BytovaJednotka::getKey()
{
	return key;
}

inline std::wstring BytovaJednotka::getTyp()
{
	return typ;
}

inline unsigned int BytovaJednotka::getPocetOsob()
{
	return pocetOsob;
}

inline unsigned int BytovaJednotka::getPocetObytnychMiestnosti()
{
	return pocetObytnychMiestnosti;
}

inline unsigned int BytovaJednotka::getMnozstvo()
{
	return mnozstvo;
}

