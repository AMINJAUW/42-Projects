/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:03:36 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/21 18:47:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point);

int main( void )
{
	
	int res = 150;
	Point	a(5.0f, 3.2f);
	Point	b(14.89, 114.9);
	Point	c(120.7, 88.9);

	for (int y = res; y >= 0; y--)
	{
		for (int x = 0; x <= res; x++)
		{
			if (bsp(a, b, c, Point(x, y)))
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	return 0;
}