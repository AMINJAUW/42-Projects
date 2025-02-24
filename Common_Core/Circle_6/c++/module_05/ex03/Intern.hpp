/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:15:35 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/29 13:39:00 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"

class Intern 
{
private:
	Intern(Intern const & cpy);
	Intern & operator=(Intern const & rhs);
public:
	Intern(void);
	~Intern(void);

	AForm	* makeForm(string type, string target) const;
};

#endif
