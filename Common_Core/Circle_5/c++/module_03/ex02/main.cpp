/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:26:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 11:44:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

// void attack(std::string const & target);
// void takeDamage(unsigned int amount);
// void beRepaired(unsigned int amount);

int	main(void)
{
	std::string s1 = "Clyde";
	std::string s2 = "Scarlet";
	std::string s3 = "Fred";

	// Constructors
	ClapTrap claptrap(s1);
	ScavTrap scavtrap(s2);
	FragTrap fragtrap(s3);
	std::cout << std::endl;

	// Attacks for each class
	fragtrap.attack(s2);
	claptrap.attack(s2);
	scavtrap.attack(s1);
	std::cout << std::endl;

	// New class attack
	fragtrap.attack(s2);
	fragtrap.attack(s2);
	fragtrap.attack(s2);
	fragtrap.attack(s2);
	std::cout << std::endl;

	// New class personal method call
	fragtrap.highFivesGuys();
	std::cout << std::endl;

	// Repair 0
	fragtrap.beRepaired(0);

	// Take damage
	fragtrap.takeDamage(50);

	// Die
	fragtrap.takeDamage(50);

	// Do something after dying
	fragtrap.beRepaired(20);
	fragtrap.attack(s2);

	std::cout << std::endl;
	return (0);
}