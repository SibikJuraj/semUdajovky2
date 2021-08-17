#pragma once

#include "Filter.h"
#include "structures/table/table.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"


using namespace structures;

template <typename T>
class UniverzalnyFilter
{
public:

	virtual bool splnaFilter(T o) = 0;
};