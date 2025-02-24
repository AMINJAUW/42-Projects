/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:21:44 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 15:04:48 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain *brain;
public:
	Dog(void);
	virtual ~Dog();
	Dog(Dog const &cpy);

	Dog & operator=(Dog const & rhs);
	
	string	getType(void) const;
	virtual void makeSound(void) const;
	Brain	*getBrain(void) const;
};

#endif
