/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:56:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 11:26:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*--------Pivate member functions------------*/

BitcoinExchange::BitcoinExchange(void) {
}

BitcoinExchange::~BitcoinExchange(void) {
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & cpy) {
	*this = cpy;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & rhs) {
	(void)rhs;
	return *this;
}

void BitcoinExchange::check_date(string const date)
{
	int time[3] = {std::atoi(date.c_str()), std::atoi(&(date.c_str()[5])), std::atoi(&(date.c_str()[8]))};
	if( time[1] > 12) 
		throw BitcoinExchange::WrongDate(); //month
    if( time[2] > 31 ) 
		throw BitcoinExchange::WrongDate(); //day
    if( time[2] == 31 && ( time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11 ) ) 
		throw BitcoinExchange::WrongDate(); //30 days in Apr, Jun, Sen, Nov
    if( time[1] == 2) //Feb
	{
		if( time[2] > 29 ) 
			throw BitcoinExchange::WrongDate();
		if( time[2] == 29 && (time[0] % 4 != 0 || (time[0] % 100 == 0 && time[0] % 400 != 0)))
			throw BitcoinExchange::WrongDate();
    }
}

void BitcoinExchange::check_data(string const line)
{
	if (line.size() < 12)
		throw BitcoinExchange::WrongFormat();
	
	bool point = false;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (line[i] == '-')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
		if (i < 10)
		{
			if (line[i] >= '0' && line[i] <= '9')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
		if (i == 10)
		{
			if (line[i] == ',')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
		if (i > 10)
		{
			if (line[i] == '.' && point == false)
			{
				point = true;
				continue;
			}
			else if (line[i] >= '0' && line[i] <= '9')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
	}
	check_date(line.substr(0,10));	
}

void BitcoinExchange::check_input(string const line)
{
	if (line.size() < string("2011-01-03 | 3").size())
		throw BitcoinExchange::WrongFormat();
	bool point = false;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (line[i] == '-')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
		if (i < 10)
		{
			if (line[i] >= '0' && line[i] <= '9')
				continue;
			else
				throw BitcoinExchange::WrongFormat();			
		}
		if (i == 10 || i == 12)
		{
			if (line[i] == ' ')
				continue;
			else
				throw BitcoinExchange::WrongFormat();			
		}
		if (i == 11)
		{
			if (line[i] == '|')
				continue;
			else
				throw BitcoinExchange::WrongFormat();			
		}
		if (i > 12)
		{
			if (i == 13 && (line[i] == '+' || line[i] == '-'))
				continue;
			if (line[i] == '.' && point == false)
			{
				point = true;
				continue;
			}
			else if (line[i] >= '0' && line[i] <= '9')
				continue;
			else
				throw BitcoinExchange::WrongFormat();
		}
	}
	check_date(line.substr(0, 10));
}

/*-------Public member functions---------*/

BitcoinExchange::BitcoinExchange(std::ifstream & data) {
	bool first_line = true;
	while (!data.eof())
	{
		string line;
		std::getline(data, line);
		if (line.size() == 0)
			break;
		if (first_line)
		{
			if (line != string("date,exchange_rate"))
			{
				cout << "Error input file shoud begin with `date,exchange_rate\' as first line" << endl;
				return;
			}
			first_line = false;
			continue;
		}
		try
		{
			check_data(line);
			float value = std::atof(&((line.c_str())[11]));
			line = line.substr(0,10);
			this->_exchange_rates[line] = value;
		}
		catch (const std::exception & e)
		{
			cout << "Error: " << e.what() << line << endl;
		}
	}
}

void BitcoinExchange::calculate(std::ifstream & input)
{
	bool first_line = true;
	while (!input.eof())
	{
		string line;
		std::getline(input, line);
		if (line.size() == 0)
			break;
		if (first_line)
		{
			if (line != string("date | value"))
			{
				cout << "Error input file shoud begin with `date | value\' as first line" << endl;
				return;
			}
			first_line = false;
			continue;
		}
		try
		{
			check_input(line);
			float value = std::atof(&((line.c_str())[13]));
			string date = line.substr(0, 10);
			if (date < this->_exchange_rates.begin()->first)
			{
				cout << "Error: Date Before first date in data set <= " << date << endl;
				continue;
			}
			if (value < 0)
			{
				cout << "Error: not a positive number." << endl;
				continue;
			}
			if (value > 1000)
			{
				cout << "Error: too large a number." << endl;
				continue;
			}
			cout << date << " => " << value << " = " << value * (--this->_exchange_rates.upper_bound(date))->second << endl;
		}
		catch (const BitcoinExchange::WrongDate & e)
		{
			cout << "Error: " << e.what() << line.substr(0, 10) << endl;
		}
		catch (const std::exception & e)
		{
			cout << "Error: " << e.what() << line << endl;
		}
	}
}

const char *BitcoinExchange::WrongFormat::what(void) const throw()
{
	return "bad input => ";
}

const char *BitcoinExchange::WrongDate::what(void) const throw()
{
	return "Invalid date => ";
}