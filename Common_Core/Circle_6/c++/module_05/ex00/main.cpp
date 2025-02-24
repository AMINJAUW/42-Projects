/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 07:58:01 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/30 12:51:44 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat eric("eric", 3);
		Bureaucrat phillipe("phillipe", 4);
		cout << eric << endl << phillipe << endl;
		Bureaucrat god("God", 0);
		cout << god << endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}

	try
	{
		Bureaucrat eric("eric", 3);
		while (1)
		{
			eric.increment();
			cout << eric << endl;
		}
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << endl;
	}

	try
	{
		Bureaucrat phillipe("phillipe", 145);
		while (1)
		{
			phillipe.decrement();
			cout << phillipe << endl;
		}
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << endl;
	}
}