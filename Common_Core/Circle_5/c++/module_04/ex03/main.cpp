/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:01 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/27 13:19:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"


void ft_tests()
{
	// Constructors
	cout << endl;
	cout << "CONSTRUCTORS:" << endl;
	cout << "-----------------------" << endl;
	IMateriaSource* src = new MateriaSource();
	AMateria * ice = new Ice();
	AMateria * cure = new Cure();
	src->learnMateria(ice);
	src->learnMateria(cure);
	ICharacter* me = new Character("me");
	cout << endl;

	// Create Materia
	cout << "CREATE MATERIA:" << endl;
	cout << "-----------------------" << endl;
	AMateria	*tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("fire");
	me->equip(tmp);
	cout << endl;

	// Use on a new character
	cout << "USE ON A NEW CHARACTER:" << endl;
	cout << "-----------------------" << endl;
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	cout << endl;
	me->use(2, *bob); // Use an empty / non existing slot in inventory
	me->use(-4, *bob);
	me->use(18, *bob);
	cout << endl;

	cout << "DEEP COPY CHARACTER:" << endl;
	cout << "-----------------------" << endl;
	Character	*charles = new Character("Charles");
	tmp = src->createMateria("cure");
	charles->equip(tmp);
	tmp = src->createMateria("ice");
	charles->equip(tmp);
	tmp = src->createMateria("earth");
	charles->equip(tmp);
	Character	*charles_copy = new Character(*charles);
	cout << endl;

	cout << "DEEP COPY VS SOURCE:" << endl;
	cout << "-----------------------" << endl;
	tmp = charles->getMateriaFromSpellBook(0);
	charles->unequip(0);
	delete tmp;
	tmp = charles_copy->getMateriaFromSpellBook(1);
	charles_copy->unequip(1);
	delete tmp;
	tmp = src->createMateria("cure");
	charles_copy->equip(tmp);
	tmp = src->createMateria("ice");
	charles_copy->equip(tmp);
	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << "Slot: " << i << endl;
		cout << "original : ";
		charles->use(i, *bob);
		cout << "Copy     : ";
		charles_copy->use(i, *bob);
		cout << endl;
	}

	cout << "UNEQUIP:" << endl;
	cout << "-----------------------" << endl;
	me->unequip(-1);
	me->unequip(18);
	me->unequip(3);
	cout << endl;
	me->use(1, *charles);
	tmp = me->getMateriaFromSpellBook(1);
	me->unequip(1);
	delete tmp;
	me->use(1, *charles);
	cout << endl;

	cout << "Delete everything correctly:" << endl;
	cout << "-----------------------" << endl;
	delete bob;
	delete me;
	delete charles;
	delete charles_copy;
	delete src;
	delete cure;
	delete ice;
	cout << endl;
}


int main()
{
	cout << "GIVEN MAIN" << endl;
	cout << "-----------------------" << endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	
	delete bob;
	delete me;
	delete src;

	system("echo \"Basic main\n\" > leaks_check; leaks Magic >> leaks_check");
	ft_tests();
	system("echo \"\n\nComplexe main\n\" >> leaks_check ; leaks Magic >> leaks_check");
	system("cat leaks_check | grep \"leaked bytes\" ; rm leaks_check");
	return 0;
}