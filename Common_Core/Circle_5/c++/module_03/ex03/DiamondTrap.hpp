/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:57:13 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 12:30:25 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
	DiamondTrap();
	string	_name;
public:
	~DiamondTrap();
	DiamondTrap(string const & name);
	DiamondTrap(const DiamondTrap &cpy);
	DiamondTrap & operator=(const DiamondTrap &rhs);

	void whoAmI();
	using ScavTrap::attack;
};






#endif
