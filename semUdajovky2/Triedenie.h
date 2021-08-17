#pragma once

#include "Kriterium.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorting/quick_sort.h"


template <typename K, typename T, typename V>
class Triedenie
{
private:
	void quick(int min, int max, UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* kriterium, bool vzostupne);
public:
	void sort(UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* kriterium, bool vzostupne);
	

};


template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::sort(UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* kriterium, bool vzostupne)
{
	quick(0, table->size() - 1, table, kriterium, vzostupne);
}

template<typename K, typename T, typename V>
inline void Triedenie<K, T, V>::quick(int min, int max, UnsortedSequenceTable<K, T>* table, Kriterium<V, T>* kriterium, bool vzostupne)
{
	V pivot = kriterium->ohodnot((table->getItemAtIndex((min + max) / 2)).accessData());
	int lavy = min;
	int pravy = max;
	do
	{
		if (vzostupne)
		{
			while (kriterium->ohodnot((table->getItemAtIndex(lavy)).accessData()) < pivot)
			{
				lavy++;
			}
			while (kriterium->ohodnot((table->getItemAtIndex(pravy)).accessData()) > pivot)
			{
				pravy--;
			}
		}
		else
		{
			while (kriterium->ohodnot((table->getItemAtIndex(lavy)).accessData()) > pivot)
			{
				lavy++;
			}
			while (kriterium->ohodnot((table->getItemAtIndex(pravy)).accessData()) < pivot)
			{
				pravy--;
			}
		}
	
		if (lavy <= pravy)
		{
			table->swap(lavy, pravy);
			lavy++;
			pravy--;
		}
	} while (lavy <= pravy);

	if (min < pravy)
	{
		quick(min, pravy, table, kriterium, vzostupne);
	}
	if (lavy < max)
	{
		quick(lavy, max, table, kriterium, vzostupne);
	}

}