/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:55:05 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/27 12:19:48 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
	{
		this->_inventory[i] = 0;
	}
}

MateriaSource::~MateriaSource()
{}

MateriaSource::MateriaSource(MateriaSource const & cpy)
{
	*this = cpy;
}

MateriaSource	& MateriaSource::operator=(MateriaSource const & rhs)
{
	for (int i = 0; i < 4; i++)
	{
		if (rhs._inventory[i] == 0)
			this->_inventory[i] = 0;
		else
			this->_inventory[i] = rhs._inventory[i]->clone();
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria *m)
{
	int i = 0;
	while (i < 4 && this->_inventory[i])
		i++;
	if (i == 4)
	{
		cout << "you cannot learn more than 4 spells in a MateriaSource";
		return;
	}
	this->_inventory[i] = m;
	return ;
}

AMateria 	*MateriaSource::createMateria(string const & type)
{
	int i = 0;
	while (i < 4 && this->_inventory[i] != 0 && this->_inventory[i]->getType() != type)
		i++;
	if (i == 4 || this->_inventory[i] == 0)
		return 0;
	return this->_inventory[i]->clone();
}