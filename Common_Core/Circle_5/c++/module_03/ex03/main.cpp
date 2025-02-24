/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:26:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 12:34:20 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

#include "DiamondTrap.hpp"

using std::cout;
using std::endl;

int main(void)
{
    DiamondTrap Bozo("Bozo");
    DiamondTrap Rato("Rato");
	DiamondTrap	copy(Bozo);

    cout << endl;

    Rato.attack("Bozo");
    Bozo.takeDamage(30);

    cout << endl;

    Rato.attack("Bozo");
    Bozo.takeDamage(30);

    cout << endl;

    Rato.attack("Bozo");
    Bozo.takeDamage(30);

    cout << endl;

    cout << endl;

    Rato.attack("Bozo Clone");

    cout << endl;

    Rato.guardGate();

    cout << endl;

    cout << endl;

    Rato.whoAmI();

    cout << endl;

    return EXIT_SUCCESS;
}