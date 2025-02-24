/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:08:13 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 10:22:38 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

# include "Bureaucrat.hpp"

class Form {
private:
	string const	_name;
	bool			_signed;
	int const		_MinSignGrade;
	int const		_MinExecGrade;
	Form & operator=(Form const & rhs);
public:
	Form(void);
	~Form(void);
	Form(Form const & cpy);
	Form(string name, int MinSignGrade, int MinExecGrade);

	string const	getName(void) const;
	bool			getSigned(void) const;
	int				getMinSignGrade(void) const;
	int				getMinExecGrade(void) const;

	void	beSigned(Bureaucrat const & bureaucrat);
};

std::ostream	& operator<<(std::ostream & o, Form const & rhs);

#endif

