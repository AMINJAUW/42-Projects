/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:35:53 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:04:08 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) {
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & cpy) : AForm("PresidentialPardonForm to " + cpy.getTarget(), 25, 5)
{
	*this = cpy;
}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & rhs) 
{
	this->_target = rhs.getTarget();
	return *this;
}

PresidentialPardonForm::PresidentialPardonForm(string target) : AForm("PresidentialPardonForm to " + target, 25, 5), _target(target)
{
}

string	PresidentialPardonForm::getTarget(void) const
{
	return this->_target;
}

void	PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (this->getMinExecGrade() < executor.getGrade())
		throw Bureaucrat::GradeTooLowException();
	cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox" << endl;
}
