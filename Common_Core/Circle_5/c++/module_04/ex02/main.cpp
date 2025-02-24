/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:28:33 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/27 13:32:05 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

void	ft_test()
{	
	// Exercice example
	const Animal* dog = new Dog();
	const Animal* cat = new Cat();

	std::cout << std::endl;

	delete dog;
	delete cat;
	
	system("leaks Animals > leaks_check");
	std::cout << std::endl;
	std::cout << std::endl;

	//Deep copy check
	Dog medor;
	Cat fifi;

	std::cout << std::endl << "creating copies" << std::endl;
	Dog medor_copy(medor);
	Cat fifi_copy(fifi);

	cout << "medor brain address      = " << medor.getBrain() << endl;
	cout << "medor_copy brain address = " << medor_copy.getBrain() << endl;
	cout << "fifi brain address       = " << fifi.getBrain() << endl;
	cout << "fifi_copy brain address  = " << fifi_copy.getBrain() << endl;


	// Array of animals
	const Animal	*(animal_array[4]);
	std::cout << std::endl;
	// Half filled with dogs
	for (int i = 0; i < 2; i++)
		animal_array[i] = new Dog();
	std::cout << std::endl;

	// Half filled with cats
	for (int i = 2; i < 4; i++)
		animal_array[i] = new Cat();
	std::cout << std::endl;

	for (int i = 0; i < 4; i++)
		delete animal_array[i];
	std::cout << std::endl;

	system("leaks Animals >> leaks_check");
}

int main( void )
{
	ft_test();
	system("echo \"\nLeaks check:\n\" ; cat leaks_check | grep \"leaked bytes\" ; rm leaks_check");
}
