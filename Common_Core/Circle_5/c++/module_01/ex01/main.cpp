/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:44:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/19 15:14:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	std::string	str = "Just another piece of meat";
	int size = 15;

	Zombie *horde = zombieHorde(size, str);

	for (int i = 0; i < size; i++)
	{
		horde[i].announce();
	}
	delete[] horde;
}
