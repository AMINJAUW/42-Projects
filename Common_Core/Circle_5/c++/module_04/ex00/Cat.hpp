/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:18:22 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 12:31:46 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
public:
	Cat(void);
	virtual ~Cat();
	Cat(Cat const &cpy);

	Cat & operator=(Cat const & rhs);
	
	string	getType(void) const;
	virtual void makeSound(void) const;	
};

#endif
