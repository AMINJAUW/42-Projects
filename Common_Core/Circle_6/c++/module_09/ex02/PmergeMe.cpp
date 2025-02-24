/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurminjauw <arthurminjauw@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:17:39 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/26 23:22:28 by arthurminja      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

size_t Jacobsthal(size_t n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2); 
}


size_t uintPow(size_t n, size_t x)
{
	size_t out = 1;
	if (n == 0)
		return 0;
	if (x == 0)
		return 1;
	for (size_t i = 0; i < x; i++)
	{
		out *= n;
	}
	return out;
}

bool	valid_unsigned_number(const char *str)
{
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] > '9' || str[i] < '0')
			return false;
	}
	int n = std::atoi(str);
	if (string(str) != std::to_string(n))
		return false; // overflow
	return true;
	
}