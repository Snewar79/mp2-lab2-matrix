﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out,  TVector &v)
  {
	  for (int i = 0; i < v.GetStartIndex(); i++)
		  cout << "0  ";
	  for (int i = 0; i < v.Size; i++)
		 
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s > MAX_VECTOR_SIZE) throw s;
	if (si < 0) throw si;
	Size = s;
	StartIndex = si;
	pVector = new ValType[s];


} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];



} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	
		delete[] pVector;
		pVector = NULL;


} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos - this->StartIndex < 0 || pos - this->StartIndex >= Size) throw pos;
	return pVector[pos-this->GetStartIndex()]; ///Калялкиw
	// Да, это так




} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !operator==(v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v) return *this;
	if (Size != v.Size)
	{
		Size = v.Size;
		delete pVector;
		pVector = new ValType[Size];
	}
	StartIndex = v.StartIndex;
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
	return *this;



} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector tmp(*this);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] += val;
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector tmp(*this);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] -= val;
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector tmp(*this);
	for (int i = 0; i < Size; i++)
		tmp.pVector[i] *= val;
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)

{
	TVector max = *this;
	TVector min = v;
	if (Size < v.Size)
	{
		max = v;
		min = *this;

	}
	

	TVector tmp(max);
	//StartIndex = v.StartIndex;
	for (int i = 0; i < min.Size; i++)
		tmp.pVector[i] = pVector[i] + v.pVector[i];

	return tmp;
	

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	TVector tmp(v.Size);
	for (int i = 0; i < Size; i++)
		tmp[i] = pVector[i] - v.pVector[i];

	return tmp;


} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	ValType tmp;
	int min;
	min = Size;
	if (v.Size < min) min = v.Size;
	///			????????????????????
	tmp = pVector[0] * v.pVector[0];
		for (int i = 1; i < min; i++)
			tmp += pVector[i] * v.pVector[i];
	return tmp;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) throw s;
	StartIndex = 0;
	//Да нафиг тут ничего не нужно. Вроде..
	for (int i = 0; i < Size; i++)
		pVector[i] = TVector<ValType>(s-i, i);

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this->Size != mt.Size) return false;
	for (int i = 0; i < Size; i++)
		if (this->pVector[i] != mt.pVector[i]) return false;
	return true;





} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{

	if (this == &mt) return *this;
	if (Size != mt.Size)
	{
		Size = mt.Size;
		delete[] this->pVector;
		pVector = new TVector<ValType>[Size];
	}
	for (int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];

	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) throw Size;
	TMatrix<ValType> tmp(mt.Size);
	for (int i = 0; i < Size; i++)
	{
		tmp.pVector[i] = pVector[i] + mt.pVector[i];
		cout << tmp.pVector[i] << "\n";
	}

	return tmp;

	//return TVector<TVector<ValType>>::operator+(mt);





	
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size) throw Size;
	if (Size != mt.Size) throw Size;
	TMatrix<ValType> tmp(mt.Size);
	for (int i = 0; i < Size; i++)
	{
		tmp.pVector[i] = pVector[i] - mt.pVector[i];
		cout << tmp.pVector[i] << "\n";
	}

	return tmp;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
