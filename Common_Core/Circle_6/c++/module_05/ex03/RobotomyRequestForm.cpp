/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:59:14 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/01 12:48:59 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <time.h>
#include <stdlib.h>

RobotomyRequestForm::RobotomyRequestForm(void) {
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & cpy) : AForm("RobotomyRequestForm to " + cpy.getTarget(), 72, 45)
{
	*this = cpy;
}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs) 
{
	this->_target = rhs.getTarget();
	return *this;
}

RobotomyRequestForm::RobotomyRequestForm(string target) : AForm("RobotomyRequestForm to " + target, 72, 45), _target(target)
{
	
}

string	RobotomyRequestForm::getTarget(void) const
{
	return this->_target;
}

void	RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (this->getMinExecGrade() < executor.getGrade())
		throw Bureaucrat::GradeTooLowException();
	cout << "BRRRRrrRRRRRRrrrRRr" << endl;
	if (rand() % 2)
		cout << this->getTarget() << " has been robotomized" << endl;
	else
		cout << "robotomy failed on " << this->_target << endl;
}

