/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:24:28 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:28:20 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
using	std::cout;
using	std::endl;

# include <string>
using	std::string;

class WrongAnimal
{
protected:
	string	_type;
public:
	WrongAnimal(void);
	~WrongAnimal();
	WrongAnimal(WrongAnimal const &cpy);

	WrongAnimal & operator=(WrongAnimal const & rhs);
	
	string	getType(void) const;
	void makeSound(void) const;	
};


#endif
