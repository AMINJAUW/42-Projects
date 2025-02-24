/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:11:31 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/13 12:32:51 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <vector>
#include <list>

#include "easyfind.hpp"

int main() {
	int a[] = { 1, 2, 3, 4, 5 };

	std::list<int> list(a, a + 5);
	std::cout << std::boolalpha;
	std::cout << easyfind(list, 2) << std::endl;
	std::cout << easyfind(list, 1) << std::endl;
	std::cout << easyfind(list, 0) << std::endl ;

	std::vector<int> vector(a, a + 5);
	std::cout << easyfind(vector, 2) << std::endl;
	std::cout << easyfind(vector, 1) << std::endl;
	std::cout << easyfind(vector, 15) << std::endl;

	return 0;
}