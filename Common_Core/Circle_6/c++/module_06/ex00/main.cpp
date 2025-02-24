/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:10:56 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 13:35:45 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"



int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "usage : ./convert \"string\"" << endl;
		return EXIT_FAILURE;
	}
	try
	{
		ScalarConverter::convert(argv[1]);
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << endl;
		return (1);
	}
	return (0);
}

