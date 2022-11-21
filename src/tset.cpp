// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}


void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return (BitField == s.BitField) && (MaxPower == s.MaxPower);
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return (BitField != s.BitField) || (MaxPower != s.MaxPower);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet set2(MaxPower);
    set2.InsElem(Elem);
    return (*this) + set2;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet temp = *this;
    temp.DelElem(Elem);
    return temp;
}


TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{   char input, elem;
    istr >> input;
    if (input != '{')
        throw - 1;
    do {
        istr >> elem;
        s.InsElem(elem);
        istr >> input;
        do {
            istr >> input;
        } while ((input != '}') | (input != ','));
    } while (input != '}');
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << '{';
    int n = s.GetMaxPower();
    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (s.IsMember(i)) {
            if (flag == 0) {
                ostr << i;
                flag++;
            }
            else
                ostr << ',' << ' ' << i;
        }
    }
    ostr << '}';
    return ostr;
}
