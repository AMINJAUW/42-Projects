/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:24:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:02:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
	string _target;
	RobotomyRequestForm(void);
	RobotomyRequestForm & operator=(RobotomyRequestForm const & rhs);
public:
	RobotomyRequestForm(string target);
	~RobotomyRequestForm(void);
	RobotomyRequestForm(RobotomyRequestForm const & cpy);

	string	getTarget(void) const;
	
	void	execute(Bureaucrat const & executor) const;
};


#endif
