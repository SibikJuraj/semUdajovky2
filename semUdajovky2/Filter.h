#pragma once

#include "Kriterium.h"
#include "UniverzalnyFilter.h"
#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"


using namespace structures;

template <typename K, typename T, typename V>
class Filter : public UniverzalnyFilter<T>
{
protected:
	Kriterium<V, T>* kriterium;
	
public:
	Filter(Kriterium<V, T>* krit);
	~Filter();
	virtual bool splnaFilter(T o) = 0;
	SortedSequenceTable<K, T>* vyfiltrujTabulku(SortedSequenceTable<K, T>* tabulka);
	UnsortedSequenceTable<K, T>* vyfiltrujTabulkuUnsorted(UnsortedSequenceTable<K, T>* tabulka);
};

template <typename K, typename T, typename V>
inline Filter<K, T, V>::Filter(Kriterium<V, T>* krit) : UniverzalnyFilter<T>()
{
	kriterium = krit;
}

template <typename K, typename T, typename V>
inline Filter<K, T, V>::~Filter()
{
}


template<typename K, typename T, typename V>
inline SortedSequenceTable<K, T>* Filter<K, T, V>::vyfiltrujTabulku(SortedSequenceTable<K, T>* tabulka)
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

template<typename K, typename T, typename V>
inline UnsortedSequenceTable<K, T>* Filter<K, T, V>::vyfiltrujTabulkuUnsorted(UnsortedSequenceTable<K, T>* tabulka)
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