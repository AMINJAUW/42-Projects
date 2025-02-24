/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:16:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 11:20:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap 
{
private:
	ScavTrap(void);
public:
	ScavTrap(ScavTrap const & cpy);
	ScavTrap(string name);
	~ScavTrap(void);

	ScavTrap	& operator=(ScavTrap const & rhs);
	void	attack(string const & traget);
	void	guardGate();
};

#endif
