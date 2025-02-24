/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:38:34 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 11:13:40 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Error: could not open file." << endl;
		return 1;
	}
		if (argc > 2)
	{
		cout << "Error: too many args" << endl;
		return 2;
	}
	
	std::ifstream data;
	data.open("testing_files/data.csv");
	if (data.fail())
	{
		cout << "Error: could not open data.csv file in folder 'testing_files'" << endl;
		return 3;
	}
	BitcoinExchange program(data);
	std::ifstream infile;
	infile.open(argv[1]);
	if (infile.fail())
	{
		cout << "Error: could not open file." << endl;
		return 1;
	}
	program.calculate(infile);
}