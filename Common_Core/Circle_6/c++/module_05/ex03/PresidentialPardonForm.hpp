/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:35:59 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:09 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
	string _target;
	PresidentialPardonForm(void);
	PresidentialPardonForm & operator=(PresidentialPardonForm const & rhs);
public:
	PresidentialPardonForm(string target);
	~PresidentialPardonForm(void);
	PresidentialPardonForm(PresidentialPardonForm const & cpy);

	string	getTarget(void) const;
	
	void	execute(Bureaucrat const & executor) const;
};



#endif
