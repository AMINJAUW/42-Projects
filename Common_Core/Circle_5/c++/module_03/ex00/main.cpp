/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:26:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 10:13:14 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap claptrap1("Ragnar Lothbrok");
    ClapTrap claptrap2(claptrap1);
    ClapTrap claptrap3("Floki");

    claptrap1.attack("Floki");
    claptrap1.takeDamage(100000000);
    claptrap1.beRepaired(10);

    claptrap1.attack("Floki");
    claptrap3.takeDamage(5);
    claptrap3.beRepaired(1000);
    claptrap3.takeDamage(1000);
    claptrap3.beRepaired(1000);

	cout << claptrap1 << endl;
	cout << claptrap2 << endl;
	cout << claptrap3 << endl;

    return 0;
}