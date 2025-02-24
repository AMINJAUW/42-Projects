/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:32:50 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 11:07:51 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
using std::map;

#include <string>
using std::string;

#include <fstream>

#include <iostream>
using std::cout;
using std::endl;

#include <stdexcept>

#include <ctime>


class BitcoinExchange {
private:
	map<string, float>	_exchange_rates;
	BitcoinExchange(BitcoinExchange const & cpy);
	BitcoinExchange(void);
	BitcoinExchange & operator=(BitcoinExchange const & rhs);

	void check_date(string const date);
	void check_data(string const line);
	void check_input(string const line);

public:
	~BitcoinExchange(void);
	BitcoinExchange(std::ifstream & data);
	
	class WrongFormat : public std::exception
	{
	public :
		virtual const char *what(void) const throw();	
	};
	class WrongDate : public std::exception
	{
	public :
		virtual const char *what(void) const throw();	
	};
	void calculate(std::ifstream & input);
};

#endif
