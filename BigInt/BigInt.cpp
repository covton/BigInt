// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>


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
	bool operator==(const BigInt bi);

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
		for (int i = 0; i < sizeDifference; i++)
		{
			number.insert(number.begin() + i, secondInt.number.at(i));
		}

	}

	int carry{ 0 };
	for (long i = 1; i <= numberOfTens; i++)
	{
		carry += number.at(number.size() - i) + secondInt.number.at(secondInt.number.size() - i);
		if (carry >= 10)
		{
			number.at(number.size() - i) = carry - 10;
			carry /= 10;
		}
		else
		{
			number.at(number.size() - i) = carry;
			carry /= 10;
		}
	}
	if (carry > 0)
	{
		//if number of tens is geq to the vector, we put a 1 on the front, since the carry will just make a new power of 10
		if (number.size() <= numberOfTens)
		{
			number.insert(number.begin(), 1);
		}
		else
		{
			// note that each digit will only overflow if it equals 9
			// therefore, we just need to loop backwards through the digits, starting from numberOfTens and change all 9s to zeros
			// until we reach a number that isn't a zero, where we just add the carry
			// if we get to the start and they have all been zeros then add a 1 on the front
		
			for (int i = (number.size() - numberOfTens - 1); i >= 0; i--)
			{
				if (number.at(i) == 9)
				{
					if (i == 0)
					{
						number.at(i) = 0;
						number.insert(number.begin(), 1);
					}
					else
					{
						number.at(i) = 0;
					}
				}
				else
				{
					number.at(i) += 1;
					break;
				}
			}
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
	number.clear();
	for (int i = 0; i < bi.number.size(); i++)
	{
		number.push_back(bi.number.at(i));
	}
	return *this;
}

bool BigInt::operator==(const BigInt bi)
{
	bool result{ true };
	int numberOfTens;
	if (number.size() <= bi.number.size())
	{
		numberOfTens = number.size();
	}
	else
	{
		numberOfTens = bi.number.size();
	}

	for (int i = 0; i < numberOfTens; i++)
	{
		if (number.at(i) != bi.number.at(i))
		{
			result = false;
			break;
		}
	}
	return result;
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
	//to do: == operator will return false for the following two numbers: 0000123 and 123
	// need to implement < and > first

	std::vector<BigInt> vecOfInts;

	std::ifstream readFile("BigInts.txt");
	std::string temp;
	while (std::getline(readFile, temp))
	{
		vecOfInts.push_back(temp);
	}
	
	BigInt answer;
	for (int i = 0; i < vecOfInts.size(); i++)
	{
		answer += vecOfInts.at(i);
	}
	std::cout << answer;

	system("PAUSE");
	return 0;
}


