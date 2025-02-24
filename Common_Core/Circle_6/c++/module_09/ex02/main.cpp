/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurminjauw <arthurminjauw@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:28:16 by arthurminja       #+#    #+#             */
/*   Updated: 2023/12/27 21:51:39 by arthurminja      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <vector>
#include <list>
#include <deque>

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		cerr << "usage: ./PmergeMe number_1 number_2 ..." << endl;
		return 1;
	}

	try
	{
		PmergeMe<std::vector <int> > vect(argc, argv);
		PmergeMe<std::list <int> > list(argc, argv);
		PmergeMe<std::deque <int> > deque(argc, argv);
		
		cout << "Before:   ";
		for (int i = 1; i < argc; i++)
		{
			if (i == 5 && argc > 6)
			{
				cout << "[...]";
				break;
			}
			cout << argv[i] << " ";
		}
		cout << endl;
		vect.sort();
		list.sort();
		deque.sort();
		
		cout << "After:    ";
		for (int i = 0; i < argc - 1; i++)
		{
			if (i == 4 && argc > 6)
			{
				cout << "[...]";
			}
			else if (i <= 4)
			{
				cout << vect.getArray()[i] << " ";
			}
		}
		cout << endl;
		cout << "Time to process a range of " << argc - 1 << " elements with " << "std::vector : " << std::fixed << vect.getTime_Taken() << " sec. Total comparaison done = " << vect.getComparaison() << endl;
		cout << "Time to process a range of " << argc - 1 << " elements with " << "std::list   : " << std::fixed << list.getTime_Taken() << " sec. Total comparaison done = " << list.getComparaison() << endl;
		cout << "Time to process a range of " << argc - 1 << " elements with " << "std::deque  : " << std::fixed << deque.getTime_Taken() << " sec. Total comparaison done = " << deque.getComparaison() << endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 2;
	}
}