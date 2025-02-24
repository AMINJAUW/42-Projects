/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:22:09 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 11:02:22 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP


# include "Bureaucrat.hpp"

class AForm {
protected:
	string const	_name;
	bool			_signed;
	int const		_MinSignGrade;
	int const		_MinExecGrade;
	AForm & operator=(AForm const & rhs);
public:
	AForm(void);
	virtual ~AForm(void);
	AForm(AForm const & cpy);
	AForm(string name, int MinSignGrade, int MinExecGrade);

	string const	getName(void) const;
	bool			getSigned(void) const;
	int				getMinSignGrade(void) const;
	int				getMinExecGrade(void) const;

	void	beSigned(Bureaucrat const & bureaucrat);
	virtual void	execute(Bureaucrat const & executor) const = 0;
};

std::ostream	& operator<<(std::ostream & o, AForm const & rhs);

#endif
