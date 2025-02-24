/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:35:14 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 13:49:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*    zombieHorde( int N, std::string name )
{
	Zombie	*horde;
	int i;

	if (N < 1)
	{
		std::cout << "invalid number of zombies" << std::endl;
		return NULL;
	}
	horde = new Zombie[N];
	i = 0;
	while (i < N)
	{
		horde[i].set_name(name);
		i++;
	}
	return horde;
}