/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/13 11:13:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <list>

#define TEST_VALUE 1000000

int main(void)
{
	cout << "________BASIC_TESTT________\n" << endl;
	try 
	{
        const unsigned int size = 5;
        Span mySpan(size);

        int arr[] = {1, 5, 2, 8, 4};
		std::list<int> mylist(arr, arr + size);
        mySpan.addNumber(mylist.begin(), mylist.end());
		cout << "My span = " << mySpan << endl;

        try {
            mySpan.addNumber(11);
        } catch (const Span::FilledSpan &e) {
            std::cerr << "Exception: " << e.what() << " - Span is already filled." << std::endl;
        }

        std::cout << "Shortest Span: " << mySpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << mySpan.longestSpan() << std::endl;


        try {
            Span emptySpan(10);
            std::cout << "Shortest Span (Empty): " << emptySpan.shortestSpan() << std::endl; // Should throw exception
        } catch (const Span::NotEnoughNumbersForSpanCalculation &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

        try {
            Span singleElementSpan(10);
			singleElementSpan.addNumber(2);
            std::cout << "Longest Span (Single Element): " << singleElementSpan.longestSpan() << std::endl; // Should throw exception
        } catch (const Span::NotEnoughNumbersForSpanCalculation &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Unexpected Exception: " << e.what() << std::endl;
    }
	
	cout << "\n________ADVANCE_TESTT________\n" << endl;
	
	Span				tester(TEST_VALUE);
	std::vector<int>	filler;
	
	try
	{
		/* Fill the filler with random numbers */
		srand(time(NULL));
		for(unsigned int i = 0; i < TEST_VALUE; i++)
			filler.push_back(rand());
		std::cout << "Filler OK" << std::endl;

		/* Fill the tester with filler numbers */
		tester.addNumber(filler.begin(), filler.end());
		std::cout << "Tester OK" << std::endl;

		//cout << tester << endl;

		/* Test spans */
		std::cout << "Longest span is " << tester.longestSpan() << std::endl;
		std::cout << "Shortest span is " << tester.shortestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}