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
	BigInt operator+(const BigInt);
	void operator<<(const BigInt);

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
	// handle case where we need to add an extra int at the front of the vector when it carries over
	
	int numberOfTens;
	if (number.size() > secondInt.number.size())
	{
		numberOfTens = secondInt.number.size();
	}
	else
	{
		numberOfTens = number.size();
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
	
		
		number.at(number.size() - numberOfTens + 1) += carry;
	}


	return *this;
}


BigInt BigInt::operator+(const BigInt)
{
	return *this;
}

void BigInt::operator<<(const BigInt)
{
	for (long i = 0; i < BigInt::number.size(); i++)
	{
		std::cout << BigInt::number.at(i);
	}

}




int main()
{
	BigInt a("12345");
	BigInt b;
	BigInt c("6789");

	a += c;

}

