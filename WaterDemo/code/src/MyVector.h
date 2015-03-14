/*--------------------------------------------------------------------------------------------------
This project was made by Gabrielle Bennett and Amanda Rivet in 2013. 
All rights reserved. 
--------------------------------------------------------------------------------------------------*/
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <cassert> // for assert()
#include <random>

template<typename T>
class MyVector
{
	T* m_pData; // Array of some type of data.
	int m_nSize; // Number of elements in the array 

public:
	/* CONSTRUCTOR (UNPARAMETERIZED): initialize array to nullptr and the size to 0. */
	MyVector(void): m_pData(nullptr), m_nSize(0){ };

	/* COPY CONSTRUCTOR: Make a temporary vector and use CopyContent() to copy. Then swap! */
	MyVector(const MyVector& other) : m_pData (nullptr), m_nSize(0)
	{
		MyVector<T> temporal(other.m_nSize); 
		CopyContent(temporal, other, other.m_nSize);
		Swap(temporal);
	};

	/* COPY ASSIGNMENT OPERATOR: Overwrite "=" sign. */
	MyVector& operator=(const MyVector& other)
	{
		//m_pData (nullptr), m_nSize(0)
		MyVector<T> temporal(other.m_nSize);
		CopyContent(temporal, other, other.m_nSize);
		Swap(temporal);
		return *this;
	};

	/* DESTRUCTOR: Delete data. */
	~MyVector(void){ Release(); };

	/* Release data from the structure. */
	void Release(void)
	{
		if(this->m_pData != nullptr)
		{
			delete[] this->m_pData;
			this->m_pData = nullptr;
			this->m_nSize = 0;
		}
	};
	
	/* Accessor for "size": Returns the number of elements. */
	int GetSize(void) const{ return this->m_nSize; };

	/* Push data onto the vector: Make a temporary vector with a size one larger, copy over, and then swap. */
	void Push(const T input){
		MyVector temporal( this->m_nSize + 1);
		CopyContent(temporal, *this, this->m_nSize);
		temporal.m_pData[temporal.m_nSize -1] = input;
		Swap(temporal);	
	};
	
	// Finds a random value within, removes it, and returns it
	T RetrieveRandom(int num)
	{
		MyVector<T> temporal = MyVector<T>(); // New temporary vector
		int temporalSize = 0; // Purely for keeping track of the size of the "blank" vector.

		T temporary; // One temporary data of type T. 
		int randomNum; // Declared to be used in a lesser scope and outside of it.

		// Using the size, find a random value to pull.
		if(num !=0){
			randomNum = rand() % num +1;
		}
		else { randomNum = 0;}


		// Now we need to get at that number in the vector: 
		// pop things off and back on to temporal
		for(int i=GetSize(); i>randomNum; i--)
		{
			temporal.Push(GetTop()); temporalSize++;
			Pop();
		}
		// Now put temporal back onto the MyVector
		temporary = GetTop();

		Pop();


		for(int i=temporalSize; i>=0; i--)
		{
			Push(temporal.GetTop()); 
			temporal.Pop(); temporalSize--;
		}
		return temporary;
	};

	/* Retreive one data of type T from a specified index. Useful in "Go Fish" when you take someone's card from their hand. */
	T RetrieveByIndex(int index)
	{
		MyVector<T> temporal = MyVector<T>(); // Make a temporary vector
		T temporary;
		
		// Using the index that we called the method with, pull that data.
		if(index >= 0 && index <= m_nSize)
		{
			for(int i = GetSize(); i>(index+1); i--)
			{
					temporal.Push(GetTop());
					Pop();
			}

			// Put the temporal back onto the MyVector: we are now at the point where we have what we need on top of the first vector.
			temporary = T(this->GetTop()); // set our temporary T to the data we are looking to pull
			
			Pop(); // Make sure that the data is not remaining on the vector. 

			// Now, we want to make sure that we push the elements that we removed from our main vector BACK ONTO our main vector.
			for(int i = temporal.GetSize(); i>=1; i--)
			{
					Push(temporal.GetTop());
					temporal.Pop();
			}
			return temporary; // The temporal vector is destroyed when it goes out of scope.
		}
	} // end RetrieveByIndex()


	/* POP(): pop data out of the vector */
	void Pop(void)
	{
		if(m_nSize > 0)
		{
			MyVector temporal(this->m_nSize - 1);
			CopyContent(temporal, *this, temporal.m_nSize);
			
			Swap(temporal);	
		}
	};

	/* GetTop(): Returns a copy of the data on top of the vector. */
	T GetTop(){

		if(!IsEmpty())
		{
			return m_pData[GetSize()-1];
		}
		else
		{
			return nullptr;
		}
	}

	// Operator [] overloaded to access an element on the vector at any point
	T& operator[](const unsigned int nIndex)
	{
		assert(nIndex < static_cast <unsigned int> (this->m_nSize));
	
		return this->m_pData[nIndex];
	};

	const T GetCopyAt(const unsigned int nIndex)
	{
		return this->m_pData[nIndex];
	};

	/* Returns true if no elements are in the vector. */
	bool IsEmpty(void){
		return (this->m_pData == nullptr ? true : false);
	}

	/*
	// Friend operator assignment
	friend std::ostream& operator<<(std::ostream& os, MyVector& other)
	{
		//(friend needs to be kept in the header)
		other.Print();
		return os;
	}*/

	/* Constructor with size parameter (for swap, copy) */
	MyVector(int nSize): m_pData(new T[nSize]), m_nSize(nSize){ };


	/* Swaps contents of data members with those of an incoming vector. */
	void Swap(MyVector& other)
	{
		std::swap( this->m_nSize, other.m_nSize);
		std::swap( this->m_pData, other.m_pData);
	};

	/* CopyContent(): Copy the content of m_data from one object to other, from 0 to nLimit (inclusive) */
	void CopyContent(MyVector& destination, const MyVector& origin, const unsigned int nLimit)
		{
		if((int) nLimit > destination.m_nSize || (int) nLimit > origin.m_nSize)
			return;
		
		for(int i = 0; i < nLimit; i++)
		{
			destination.m_pData[i] = origin.m_pData[i];
		}
	};

	// Prints the data of the vector (for debugging)
	void Print(void){
		//std::cout << "[" << typeid(*this).name() << "] ";
		std::cout << "[ ";
		for(int i = 0; i < m_nSize; i++)
		{
			std::cout << m_pData[i] << ", ";
		}
		if(m_nSize > 0)
		{
			std::cout << static_cast <char> (8);
			std::cout << static_cast <char> (8);
		}
		std::cout << " ]";
	};


};

#endif