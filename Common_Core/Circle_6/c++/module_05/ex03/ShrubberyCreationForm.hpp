/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:25:16 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:19 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
private:
	string _target;
	ShrubberyCreationForm(void);
	ShrubberyCreationForm & operator=(ShrubberyCreationForm const & rhs);
public:
	ShrubberyCreationForm(string target);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm(ShrubberyCreationForm const & cpy);

	string	getTarget(void) const;
	
	void	execute(Bureaucrat const & executor) const;
};

#endif
