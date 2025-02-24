/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:20 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/30 12:46:01 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) {
}

Bureaucrat::~Bureaucrat(void) {
}

Bureaucrat::Bureaucrat(Bureaucrat const & cpy) : _name(cpy.getName())
{
	*this = cpy;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & rhs) {
	this->_grade = rhs.getGrade();
	return *this;
}

Bureaucrat::Bureaucrat(string name, int grade) : _name(name), _grade(grade)
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

int	Bureaucrat::getGrade(void) const
{
	return this->_grade;
}

string const	Bureaucrat::getName(void) const
{
	return this->_name;
}

char const * Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Grade too High !";
}

char const * Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Grade too Low !";
}

std::ostream	& operator<<(std::ostream & o, Bureaucrat const & rhs)
{
	o << rhs.getName() <<  ", bureaucrat grade " << rhs.getGrade();
	return o;
}

void	Bureaucrat::decrement(void)
{
	if (this->getGrade() == 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade += 1;
}
void	Bureaucrat::increment(void)
{
	if (this->getGrade() == 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade -= 1;
}
