/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:10:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/19 15:11:03 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	randomChump("Test_man");
	
	Zombie *z = newZombie("made_outside");
	z->announce();
	delete z;
	
	Zombie	no_name;
	no_name.announce();
	
	return (0);
}