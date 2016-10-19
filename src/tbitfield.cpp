// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <iostream>
using namespace std;
TBitField::TBitField(int len)
{
	if(len>=0)
	{
		BitLen = len;
		MemLen = (BitLen-1)/(sizeof(TELEM)*8) + 1;
		pMem = new TELEM[MemLen];
		for(int i=0;i<MemLen;i++)
			pMem[i]=0;
	}
	else
		throw 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for(int i=0;i<MemLen;i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n>=0)
		return n/(sizeof(TELEM)*8);
	else
		throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1<<(n-GetMemIndex(n)*sizeof(TELEM)*8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>=0)&&(n<BitLen))
	{
		TELEM newTElem = (pMem[GetMemIndex(n)] | GetMemMask(n));
		pMem[GetMemIndex(n)]=newTElem;
	}
	else
		throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if((n>=0)&&(n<BitLen))
	{
		TELEM newTElem = (pMem[GetMemIndex(n)] &~ GetMemMask(n));
		pMem[GetMemIndex(n)]=newTElem;
	}
	else
		throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n<BitLen)
	{
		if(pMem[GetMemIndex(n)] & GetMemMask(n))
			return 1;
		else return 0;
	}
	else throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen!=bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete [] pMem;
		pMem = new TELEM[MemLen];
	}
	for(int i=0;i<MemLen;i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if(BitLen==bf.BitLen)
	{
		TBitField returnable(1);
		returnable.SetBit(0); //Временная переменная = 1
		for(int i=0;i<MemLen;i++)
		{
			if (pMem[i]!=bf.pMem[i])
			{
				returnable.ClrBit(0);
				break;
			}
		}
	return returnable.GetBit(0);
	  }
	else
		return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if(BitLen==bf.BitLen)
	{
		TBitField returnable(1);
		returnable.ClrBit(0); //Временная переменная = 0
			for(int i=0;i<MemLen;i++)
			{
				if (pMem[i]!=bf.pMem[i])
				{
					returnable.SetBit(0);
					break;
				}
			}
		return returnable.GetBit(0);
	}
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int newMemLen = 0;
	TBitField newBF(newMemLen);
	if(bf.BitLen>BitLen)
	{
		newBF = bf;
		newMemLen = MemLen;
	}
	else
	{
		newBF = *this;
		newMemLen = bf.MemLen;
	}
	for(int i=0;i<newMemLen;i++)
	{
		newBF.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return newBF;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int newMemLen = 0;
	TBitField newBF(newMemLen);
	if(bf.BitLen>BitLen)
	{
		newBF = bf;
		newMemLen = MemLen;
	}
	else
	{
		newBF = *this;
		newMemLen = bf.MemLen;
	}
	for(int i=0;i<newMemLen;i++)
	{
		newBF.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return newBF;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField newBF = *this;
    for (int i=0;i<BitLen;i++)
    {
        if (newBF.GetBit(i))
            newBF.ClrBit(i);
        else
            newBF.SetBit(i);
    }
    return newBF;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i=0;i<bf.GetLength();i++)
	{
		cout << bf.GetBit(i);
	}
	return ostr;
}
