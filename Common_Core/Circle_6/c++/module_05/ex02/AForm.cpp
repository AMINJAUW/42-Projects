/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:08:08 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 09:30:17 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(void) : _name("default"), _signed(false), _MinSignGrade(1), _MinExecGrade(1)
{
}

AForm::~AForm(void) 
{
}

AForm::AForm(AForm const & cpy) : _name(cpy.getName()), _signed(cpy.getSigned()),
	_MinSignGrade(cpy.getMinSignGrade()), _MinExecGrade(cpy.getMinExecGrade())
{
	if (this->getMinExecGrade() < 1 || this->getMinSignGrade() < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->getMinExecGrade() > 150 || this->getMinSignGrade() > 150)
		throw Bureaucrat::GradeTooLowException();
}

AForm::AForm(string name, int MinSignGrade, int MinExecGrade) :
	_name(name), _signed(false), _MinSignGrade(MinSignGrade), _MinExecGrade(MinExecGrade)
{
	if (this->getMinExecGrade() < 1 || this->getMinSignGrade() < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->getMinExecGrade() > 150 || this->getMinSignGrade() > 150)
		throw Bureaucrat::GradeTooLowException();
}

AForm & AForm::operator=(AForm const & rhs) {
	this->_signed = rhs.getSigned();
	return *this;
}

string const	AForm::getName(void) const
{
	return this->_name;	
}

bool			AForm::getSigned(void) const
{
	return this->_signed;
}

int		AForm::getMinSignGrade(void) const
{
	return this->_MinSignGrade;
}
int		AForm::getMinExecGrade(void) const
{
	return this->_MinExecGrade;
}

void	AForm::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.getGrade() > this->getMinSignGrade())
		throw Bureaucrat::GradeTooLowException();
	this->_signed = true;
}

std::ostream	& operator<<(std::ostream & o, AForm const & rhs)
{
	o << "AForm " << rhs.getName() << ", minimum sign grade " << rhs.getMinSignGrade() << "; minimum excution grade " << rhs.getMinExecGrade();
	o << " ; " << (rhs.getSigned() ? "is signed" : "is not signed");

	return o;
}