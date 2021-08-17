#pragma once

#include "Filter.h"
#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"


using namespace structures;

template <typename K, typename T>
class ZlozenyFilter : UniverzalnyFilter<T>
{
private:
	ArrayList<UniverzalnyFilter<T>*>* listFiltrov;

public:
	ZlozenyFilter();
	~ZlozenyFilter();

	void pridajFilter(UniverzalnyFilter<T>* filter);
	void odoberFilter(UniverzalnyFilter<T>* filter);
	void clear();

	bool splnaFilter(T o) override;
	SortedSequenceTable<K, T>* vyfiltrujTabulku(SortedSequenceTable<K, T>* tabulka);
	UnsortedSequenceTable<K, T>* vyfiltrujTabulkuUnsorted(UnsortedSequenceTable<K, T>* tabulka);
};

template<typename K, typename T>
inline ZlozenyFilter<K, T>::ZlozenyFilter() : UniverzalnyFilter<T>()
{
	listFiltrov = new ArrayList<UniverzalnyFilter<T>*>();
}

template<typename K, typename T>
inline ZlozenyFilter<K, T>::~ZlozenyFilter()
{
	delete listFiltrov;
	listFiltrov = nullptr;
}

template<typename K, typename T>
inline void ZlozenyFilter<K, T>::pridajFilter(UniverzalnyFilter<T>* filter)
{
	listFiltrov->add(filter);
}

template<typename K, typename T>
inline void ZlozenyFilter<K, T>::odoberFilter(UniverzalnyFilter<T>* filter)
{
	if (!listFiltrov->isEmpty())
	{
		listFiltrov->tryRemove(filter);
	}
}

template<typename K, typename T>
inline void ZlozenyFilter<K, T>::clear()
{
	listFiltrov->clear();
}

template<typename K, typename T>
inline bool ZlozenyFilter<K, T>::splnaFilter(T o)
{
	if (!listFiltrov->isEmpty())
	{
		for (auto filter : *listFiltrov)
		{
			if (!filter->splnaFilter(o))
			{
				return false;
			}
		}
		
	}
	return true;
	
}

template<typename K, typename T>
inline SortedSequenceTable<K, T>* ZlozenyFilter<K, T>::vyfiltrujTabulku(SortedSequenceTable<K, T>* tabulka)
{
	SortedSequenceTable<K, T>* novaTabulka = new SortedSequenceTable<K, T>();
	for (auto tableItem : *tabulka)
	{
		if (splnaFilter(tableItem->accessData()))
		{
			novaTabulka->insert(tableItem->getKey(), tableItem->accessData());
		}
	}
	return novaTabulka;
}

template<typename K, typename T>
inline UnsortedSequenceTable<K, T>* ZlozenyFilter<K, T>::vyfiltrujTabulkuUnsorted(UnsortedSequenceTable<K, T>* tabulka)
{
	UnsortedSequenceTable<K, T>* novaTabulka = new UnsortedSequenceTable<K, T>();
	for (auto tableItem : *tabulka)
	{
		if (splnaFilter(tableItem->accessData()))
		{
			novaTabulka->insert(tableItem->getKey(), tableItem->accessData());
		}
	}
	return novaTabulka;
}
