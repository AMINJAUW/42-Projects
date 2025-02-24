/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:26:01 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/27 12:59:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character()
{}

Character::Character(string name) : _name(name)
{
	for(int i = 0; i < 4; i++)
	{
		this->_SpellBook[i] = 0;
	}
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_SpellBook[i] != 0)
		{
			delete (this->_SpellBook[i]);
		}
	}
}

string const & Character::getName() const
{
	return (this->_name);
}

Character::Character(Character const & cpy)
{
	*this = cpy;
}

Character & Character::operator=(Character const & rhs)
{
	this->_name = rhs.getName();
	for(int i = 0; i < 4; i++)
	{
		if (this->_SpellBook[i])
			cout << "Creating leaks please delete or clear before asigning";
		if (rhs._SpellBook[i])
			this->_SpellBook[i] = (rhs._SpellBook[i])->clone();
	}
	return (*this);
}

void Character::equip(AMateria* m)
{
	int i = 0;

	if (!m)
	{
		cout << this->_name << " tried to equip nothing and it did nothing" << endl;
		return ;
	}
	while ((this->_SpellBook)[i] != 0 && i < 4)
		i++;
	if (i >= 4)
	{
		cout << this->_name << " can't equip more than 4 Materia";
		return ;
	}
	(this->_SpellBook)[i] = m;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4)
		cout << this->_name << " tried to unequip nothing at slot " << idx << " and it did nothing" << endl;
	else if (!(this->_SpellBook)[idx])
		cout << this->_name << " has nothing equipped at slot " << idx << " so he can't unequip it" << endl;
	else
	{
		(this->_SpellBook)[idx] = 0;
	}
}

void Character::use(int idx, ICharacter& target)
{
	string	name = this->getName();

	if (idx < 0 || idx >= 4 || !(this->_SpellBook)[idx])
	{
		cout << "Nothing found to use at index " << idx << endl;
		return ;
	}
	cout << name;
	((this->_SpellBook)[idx])->use(target);
}

AMateria	*Character::getMateriaFromSpellBook(int idx)
{
	return (this->_SpellBook)[idx];
}