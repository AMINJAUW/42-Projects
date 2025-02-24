/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:58 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/19 15:16:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

using 	std::cout;
using	std::string;
using	std::endl;

int main (void)
{
	string	str = "HI THIS IS BRAIN";
	string	*stringPTR = &str;
	string	&stringREF = str;


	cout << "string address: " << &str << endl;
	cout << "stringPTR address: " << stringPTR << endl;
	cout << "stringREF address: " << &stringREF << endl << endl;

	cout << "string = " << str << endl;
	cout << "stringPTR = " << *stringPTR << endl;
	cout << "string = " << stringREF << endl;
}