/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:18:31 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:43:05 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern(void) {
}

Intern::~Intern(void) {
}

Intern::Intern(Intern const & cpy) {
	*this = cpy;
}

Intern & Intern::operator=(Intern const & rhs) {
	(Intern const)rhs;
	return *this;
}


AForm	* Intern::makeForm(string type, string target) const
{
	static string forms_type[3] = {"robotomy request", "shrubbery creation", "presidential pardon"};
	int i = 0;
	while(i < 3)
	{
		if (type == forms_type[i])
			break;
		i++;
	}
	switch (i)
	{
	case 0:
		cout << "Intern creats " << forms_type[i] << " form" << endl;
		return new RobotomyRequestForm(target);

	case 1:
		cout << "Intern creats " << forms_type[i] << " form" << endl;
		return new ShrubberyCreationForm(target);

	case 2:
		cout << "Intern creats " << forms_type[i] << " form" << endl;
		return new PresidentialPardonForm(target);
		
	default:
		cout << "Intern can not work, unvalid type" << endl;
		return nullptr;
	}	
}