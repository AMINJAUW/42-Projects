/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:37:43 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 11:56:57 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap 
{
private:
	FragTrap(void);
public:
	FragTrap(FragTrap const & cpy);
	FragTrap(string name);
	~FragTrap(void);

	FragTrap	& operator=(FragTrap const & rhs);

	void highFivesGuys(void);
};



#endif
