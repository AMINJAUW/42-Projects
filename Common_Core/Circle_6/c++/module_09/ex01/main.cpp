/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:16:42 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 12:19:52 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Error: Invalid parameter number" << endl;
		return 1;
	}
	try
	{
		rpn(string(argv[1]));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}