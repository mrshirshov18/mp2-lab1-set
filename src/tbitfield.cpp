// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0)
        throw - 1;
    BitLen = len;
    const int bitsInElem = sizeof(TELEM) * 8;
    MemLen = (BitLen - 1) / bitsInElem + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}


int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    const int bitsInElem = sizeof(TELEM) * 8;
    return n / bitsInElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int bitsInElem = sizeof(TELEM) * 8;
    return 1 << (n % bitsInElem);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n >= BitLen) || (n <= -1))
        throw - 1;
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n >= BitLen) || (n <= -1))
        throw - 1;
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n >= BitLen) || (n <= -1))
        throw - 1;
    int ans = 0;
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0)
        ans = 1;
    return ans;
}


// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this == &bf)
        return *this;
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) {
        delete[]pMem;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    int ans = 1;
    for (int i = 0; i < MemLen; i++)
        if (pMem[i] != bf.pMem[i]) {
            ans = 0;
            break;
        }
    return ans;
}
int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !((*this) == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        temp.pMem[i] |= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    TBitField temp(max(BitLen, bf.BitLen));
    for (int i = 0; i < temp.BitLen; i++) {
        temp.SetBit(i);
        if (i >= BitLen || i >= bf.BitLen || (!GetBit(i)) || (!bf.GetBit(i)))
            temp.ClrBit(i);
    }
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);
    TBitField temp2(BitLen);
    for (int i = 0; i < BitLen; i++) {
        temp2.SetBit(i);
    }
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = ~pMem[i];
    temp = temp2 & temp;
    return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char input;
    int i = 0;
    do {
        istr >> input;
        if (input == '1')
            bf.SetBit(i++);
        else if (input == '0')
            bf.ClrBit(i++);
        else
            throw - 1;
    } while (input != ' ');
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    int n = bf.BitLen;
    for (int i = 0; i < n; i++) {
        if (bf.GetBit(i))
            ostr << 1;
        else if (bf.GetBit(i) == 0)
            ostr << 0;
        else
            throw - 1;
    }
    return ostr;
}
