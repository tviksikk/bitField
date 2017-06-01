






#include "tset.h"

TSet::TSet(unsigned int mp) : BitField(mp), MaxPower(mp)
{}


TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{}


TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{}

TSet::operator TBitField()
{
	return this->BitField;
}

int TSet::GetMaxPower(void) const 
{
	return this->MaxPower;
}

bool TSet::IsMember(const unsigned int Elem) const 
{
    return BitField.GetBit(Elem)==1?true:false;
}

void TSet::InsElem(const unsigned int Elem) 
{
	if (Elem >= MaxPower || Elem < 0)
		throw ERROR_SET_VALUE;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const unsigned int Elem) 
{
	if (Elem >= MaxPower || Elem < 0)
		throw ERROR_SET_VALUE;
	BitField.ClrBit(Elem);

}



TSet& TSet::operator=(const TSet &s) 
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

bool TSet::operator==(const TSet &s) const 
{
	if (this->MaxPower != s.MaxPower)
		return false;
	return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const 
{
	return !this->operator==(s);
}

TSet TSet::operator+(const TSet &s) 
{
	if (this->MaxPower != s.MaxPower)
		return ERROR_SET_SIZE;

	TSet temp(*this);
	temp.BitField |= s.BitField;
	return temp;
}

TSet TSet::operator+(const int Elem) 
{
	TSet temp(*this);
	temp.InsElem(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) 
{
	TSet temp(*this);
	temp.DelElem(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) 
{
	if (this->MaxPower != s.MaxPower)
		return ERROR_SET_SIZE;

	TSet temp(*this);
	temp.BitField &= s.BitField;
	return temp;
}

TSet TSet::operator~(void) 
{
	TSet temp(*this);
	temp.BitField = ~temp.BitField;
	return temp;
}

void TSet::printSquard()
{
	for (size_t i = 0; i < s.GetMaxPower();i++)
	{
		if (s.IsMember(i))
			ostr << i*i << endl;
	}
}

istream &operator>>(istream &istr, TSet &s) 
{
	if (s.MaxPower < istr.gcount())
		throw ERROR_SET_SIZE;
	
	char temp;
	int value = -1;
	int index = 0;
	while (istr.get(temp))
	{
		if (temp == '\n')
		{
			s.InsElem(value);
			break;
		}
		if (temp == ' ' && value == -1)
			continue;
		if (temp == ' ')
		{
			s.InsElem(value);
			value = -1;
			index = 0;
			continue;
		}
		switch (temp) {
		case '0':case '1':case '2':case '3':case '4':case '5': case '6': case '7': case '8':case '9':
			break;
		default:
			throw ERROR_SET_VALUE;
		}

		if (value == -1)
			value = 0;
		value = value*10+((int)temp-48);
	}

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) 
{
	for (size_t i = 0; i < s.GetMaxPower();i++)
	{
		if (s.IsMember(i))
			ostr << i << endl;
	}
	return ostr;
}
