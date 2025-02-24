/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:08:08 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 09:20:53 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) : _name("default"), _signed(false), _MinSignGrade(1), _MinExecGrade(1)
{
}

Form::~Form(void) 
{
}

Form::Form(Form const & cpy) : _name(cpy.getName()), _signed(cpy.getSigned()),
	_MinSignGrade(cpy.getMinSignGrade()), _MinExecGrade(cpy.getMinExecGrade())
{
	if (this->getMinExecGrade() < 1 || this->getMinSignGrade() < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->getMinExecGrade() > 150 || this->getMinSignGrade() > 150)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(string name, int MinSignGrade, int MinExecGrade) :
	_name(name), _signed(false), _MinSignGrade(MinSignGrade), _MinExecGrade(MinExecGrade)
{
	if (this->getMinExecGrade() < 1 || this->getMinSignGrade() < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->getMinExecGrade() > 150 || this->getMinSignGrade() > 150)
		throw Bureaucrat::GradeTooLowException();
}

Form & Form::operator=(Form const & rhs) {
	this->_signed = rhs.getSigned();
	return *this;
}

string const	Form::getName(void) const
{
	return this->_name;	
}

bool			Form::getSigned(void) const
{
	return this->_signed;
}

int		Form::getMinSignGrade(void) const
{
	return this->_MinSignGrade;
}
int		Form::getMinExecGrade(void) const
{
	return this->_MinExecGrade;
}

void	Form::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.getGrade() > this->getMinSignGrade())
		throw Bureaucrat::GradeTooLowException();
	this->_signed = true;
}

std::ostream	& operator<<(std::ostream & o, Form const & rhs)
{
	o << "Form " << rhs.getName() << ", minimum sign grade " << rhs.getMinSignGrade() << "; minimum excution grade " << rhs.getMinExecGrade();
	o << " ; " << (rhs.getSigned() ? "is signed" : "is not signed");

	return o;
}