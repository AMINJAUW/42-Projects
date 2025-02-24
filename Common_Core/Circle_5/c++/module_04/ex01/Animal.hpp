/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:38:51 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:31:35 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
using	std::cout;
using	std::endl;

# include <string>
using	std::string;

class Animal
{
protected:
	string	_type;
public:
	Animal(void);
	virtual ~Animal();
	Animal(Animal const &cpy);

	Animal & operator=(Animal const & rhs);
	
	string	getType(void) const;
	virtual void makeSound(void) const;	
};


#endif
