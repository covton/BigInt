// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<vector>
#include<iostream>


class BigInt
{
private:
	std::vector<int> number;

public:
	BigInt();
	BigInt(std::string input);
	BigInt operator+=(const BigInt secondInt);
	BigInt operator+(const BigInt bi);
	BigInt operator=(const BigInt bi);

	friend std::ostream& operator<<(std::ostream &os, const BigInt bi);
};
BigInt::BigInt()
	:number(0)
{
}
BigInt::BigInt(std::string input)
{
	std::vector<int> result;
	for (long i = 0; i < input.size(); i++)
	{
		result.push_back(input.at(i) - '0');
	}
	number = result;
}

BigInt BigInt::operator+=(const BigInt secondInt)
{
	// todo:
	// handle case where secondint is bigger than first (i.e. swap them around)
	
	int numberOfTens;
	if (number.size() >= secondInt.number.size())
	{	
		numberOfTens = secondInt.number.size();
	}
	else
	{
		numberOfTens = number.size();
		int sizeDifference;
		sizeDifference = secondInt.number.size() - number.size();
		for (int i = 0; i < sizeDifference ; i++)
		{
			number.insert(number.begin() + i, secondInt.number.at(i));
		}

	}

	int carry{ 0 };
	for (long i = 1; i <= numberOfTens; i++)
	{
		carry += number.at(number.size() - i) + secondInt.number.at(secondInt.number.size() - i);
		if (carry > 10)
		{
			number.at(number.size() - i) = carry % 10;
		}
		else
		{
			number.at(number.size() - i) = carry;
		}
		carry /= 10;
	}
	if (carry > 0)
	{
		//if overflows the vector, need to insert an element,
		if (number.size() <= numberOfTens)
		{
			number.insert(number.begin(), 1);
		}
		else if (number.at(number.size() - (numberOfTens + 1)) + carry > 9)
		{
			int dummy;
			dummy = number.at(number.size() - (numberOfTens + 1)) + carry;
			number.at(number.size() - (numberOfTens + 1)) = dummy - 10;
			
			if (number.size() < (numberOfTens + 2))
			{
				number.insert(number.begin(), 1);
			}
			else
			{
				number.at(number.size() - (numberOfTens + 2)) += 1;
			}
		}
		else
		{
			number.at(number.size() - (numberOfTens + 1)) += carry;
		}
	}



	return *this;
}

BigInt BigInt::operator+(const BigInt bi)
{
	BigInt ret(*this);
	ret += bi;
	return ret;
}

BigInt BigInt::operator=(const BigInt bi)
{
	for (int i = 0; i < bi.number.size(); i++)
	{
		number.push_back(bi.number.at(i));
	}
	return *this;
}

std::ostream& operator<<(std::ostream &os, const BigInt bi)
{
	for (long i = 0; i < bi.number.size(); i++)
	{
		os << bi.number.at(i);
	}
	return os;
}

int main()
{
	
	//to do: adding two BigInts via + not working
	// works fine with += though

	BigInt d("92345");
	BigInt e("99999");
	BigInt f;
	f = d;
	f = d + e;

	system("PAUSE");
	return 0;
}


