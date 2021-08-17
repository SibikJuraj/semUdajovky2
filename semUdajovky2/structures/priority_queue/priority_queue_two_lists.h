#pragma once

#include "../heap_monitor.h"
#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:

		PriorityQueueTwoLists();

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);

		~PriorityQueueTwoLists();

		Structure* clone() const override;


		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		size_t size() const override;

		void clear() override;

		void push(const int priority, const T& data) override;

		T pop() override;

		T& peek() override;
		const T peek() const override;

		int peekPriority() const override;

		void setStrategy(int strategy);

		size_t constCapacityStrategy(int numberOfOperations);
		size_t variableCapacityStrategy();
	
	private:
		PriorityQueueLimitedSortedArrayList<T>* shortList_;
		LinkedList<PriorityQueueItem<T>*>* longList_;
		bool wasFull_;
		int capacityStrategy_;
		size_t desiredCapacity_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>()),
		wasFull_(false),
		capacityStrategy_(-1),
		desiredCapacity_(4)
	{
	}


	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete shortList_;
		delete longList_;
	
		shortList_ = nullptr;
		longList_ = nullptr;
		
	}

	template<typename T>
	Structure * PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{

		if (this != &other)
		{
			delete shortList_;
			shortList_ = other.shortList_;

			//shortList_ = new PriorityQueueLimitedSortedArrayList<T>(*other.shortList_);
			//shortList_->trySetCapacity(other.shortList_->getCapacity());

			longList_->clear();
			longList_ = other.longList_;

			wasFull_ = other.wasFull_;

		}
		return *this;


	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{
		return this->shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		this->shortList_->clear();

		while (longList_->size() > 0)
		{
			PriorityQueueItem<T>* item = longList_->removeAt(0);
			delete item;
		}

		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T & data)
	{

		if (wasFull_)
		{	
			if (this->shortList_->size() != shortList_->getCapacity())
			{
				shortList_->push(priority, data);
			}
			else
			{
				longList_->add(shortList_->pushAndRemove(priority, data));
			}
		}
		else
		{
			shortList_->push(priority, data);
		}

		if (!wasFull_ && this->shortList_->size() == shortList_->getCapacity())
		{
			wasFull_ = true;
		}
		
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{

		T result = this->shortList_->pop();

		if (this->shortList_->isEmpty() && wasFull_)
		{
			wasFull_ = false;

			if (!longList_->isEmpty())
			{
				
				if (capacityStrategy_ != -1)
				{
					shortList_->trySetCapacity(variableCapacityStrategy());
				}

				
				if (desiredCapacity_ < 2)
				{
					desiredCapacity_ = 2;
					shortList_->trySetCapacity(desiredCapacity_);
				}


				const int llSize = longList_->size();

				for (int i = 0; i < llSize; i++)
				{
					PriorityQueueItem<T>* removedItem = this->longList_->removeAt(0);

					push(removedItem->getPriority(), removedItem->accessData());

					delete removedItem;
				}
			}

		}

		return result;
	}

	template<typename T>
	T & PriorityQueueTwoLists<T>::peek()
	{
		if (size() == 0)
		{
			throw std::logic_error("PriorityQueueTwoLists<T>::peek() => two lists is empty");
		}
		return this->shortList_->peek();
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		if (size() == 0)
		{
			throw std::logic_error("PriorityQueueTwoLists<T>::peek() const => two lists is empty");
		}
		return this->shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		if (size() == 0)
		{
			throw std::logic_error("PriorityQueueTwoLists<T>::peekPriority() => two lists is empty");
		}
		return this->shortList_->peekPriority();
	}
	template<typename T>
	inline void PriorityQueueTwoLists<T>::setStrategy(int strategy)
	{
		capacityStrategy_ = strategy;
	}
	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::constCapacityStrategy(int numberOfOperations)
	{
		if (numberOfOperations >= 1000)
		{
			desiredCapacity_ = numberOfOperations / 1000;
			shortList_->trySetCapacity(desiredCapacity_);
		}
		
		return desiredCapacity_;
	}




	template<typename T>
	inline size_t PriorityQueueTwoLists<T>::variableCapacityStrategy()
	{
		switch (capacityStrategy_)
		{

		case 0:
			desiredCapacity_ = sqrt(size());
			break;

		case 1:
			desiredCapacity_ = size() / 2;
			break;

		default:
			desiredCapacity_ = 4;
			break;
		}

		return desiredCapacity_;

	}


}