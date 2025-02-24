/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:58:27 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 15:32:23 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>

#include <iostream>
using std::cout;
using std::endl;

Base * generate(void)
{
	switch (rand() % 3)
	{
		case 0:
			return new A;
		case 1:
			return new B;
		case 2:
			return new C;
		default:
			return nullptr;
	}
}

void identify(Base* p)
{
	if (nullptr != dynamic_cast<A *>(p))
		cout << "It's a class A !" << endl;
	else if (nullptr != dynamic_cast<B *>(p))
		cout << "It's a class B !" << endl;
	else if (nullptr != dynamic_cast<C *>(p))
		cout << "It's a class C !" << endl;
	else
		cout << "Not A or B or C" << endl;
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A &>(p);
		cout << "It's class A !" << endl;
		return ;
	}
	catch (const std::bad_cast e)
	{
		try
		{
			(void)dynamic_cast<B &>(p);
			cout << "It's class B !" << endl;
			return ;
		}
		catch (const std::bad_cast e)
		{
			try
			{
				(void)dynamic_cast<C &>(p);
				cout << "It's class C !" << endl;
				return ;				
			}
			catch (const std::bad_cast e)
			{
				cout << "It isn't not A B nor a C class" << endl;
			}
		}
	}
}

int main(void)
{
	srand(time(NULL));
	Base *class1 = generate();
	Base *class2 = generate();
	Base *class3 = generate();

	cout << "\n_____class1____\n" << endl;
	
	cout << "Address identification : ";
	identify(class1);

	cout << "Reference identification : ";
	identify(*class1);

	cout << "\n_____class2____\n" << endl;
	
	cout << "Address identification : ";
	identify(class2);

	cout << "Reference identification : ";
	identify(*class2);

		cout << "\n_____class3____\n" << endl;
	
	cout << "Address identification : ";
	identify(class3);

	cout << "Reference identification : ";
	identify(*class3);

	delete class1;
	delete class2;
	delete class3;	
}