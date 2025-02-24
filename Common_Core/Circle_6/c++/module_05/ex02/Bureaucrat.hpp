/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:12 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/30 12:46:30 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP


# include <iostream>
using std::cout;
using std::endl;

# include <string>
using std::string;

#include <stdexcept>

class AForm;

class Bureaucrat {
private:
	string const	_name;
	int				_grade;
	Bureaucrat(void);
public:
	class GradeTooHighException : public std::exception
	{
	public :
		virtual const char* what() const throw();
	};
	class GradeTooLowException : public std::exception
	{
	public :
		virtual const char* what() const throw();
	};
	Bureaucrat(string name, int grade);
	~Bureaucrat(void);
	Bureaucrat(Bureaucrat const & cpy);
	Bureaucrat & operator=(Bureaucrat const & rhs);

	int		getGrade(void) const;
	string const	getName(void) const;
	
	void	increment(void);
	void	decrement(void);

	bool	signForm(AForm & form);
	void	executeForm(AForm const & form);
};

std::ostream	& operator<<(std::ostream & o, Bureaucrat const & rhs);


#endif
