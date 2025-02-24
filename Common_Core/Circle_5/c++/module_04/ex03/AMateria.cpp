/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:44:09 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/26 14:59:37 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
	
}

AMateria::~AMateria()
{
	
}

AMateria::AMateria(string const & type) : _type(type)
{
}

string const & AMateria::getType() const
{
	return this->_type;
}

void AMateria::use(ICharacter& target)
{
	if (this->_type.compare("ice") == 0)
	{
		cout << "* shoots an ice bolt at " << target.getName() << " *" << endl;
	}
	else if (this->_type.compare("cure") == 0)
	{
		cout << "* heals " << target.getName() << "'s wounds *" << endl;
	}
	else
		cout << "* Do some weird magic on " << target.getName() << " *" << endl;
}

AMateria	&AMateria::operator=(AMateria const & cpy)
{
	this->_type = cpy.getType();
	return *this;
}