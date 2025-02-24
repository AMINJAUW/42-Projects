/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:07:06 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/12 15:25:49 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

#include <string>
using std::string;

int main(void)
{
	int arr1[5] = {0, 1, 2, 3, 4};
	string	arr2[3] = {"hello", "everything ok ?", "i truly hope"};

	cout << "\n________Array of int:________" << endl;
	iter<int, int, void>(arr1, 5, &print_arr_content<int>);
	cout << "\n________Array of strings:________" << endl;
	iter<string, int, void>(arr2, 3, &print_arr_content<string>);
}
/* 
#include "iter.hpp"
#include <iostream>

class Awesome
{
  public:
    Awesome( void ) : _n( 42 ) { return; }
    int get( void ) const { return this->_n; }
  private:
    int _n;
};

std::ostream & operator<<( std::ostream & o, Awesome const & rhs )
{
  o << rhs.get();
  return o;
}

template< typename T >
void print( T& x )
{
  std::cout << x << std::endl;
  return;
}

int main() {
  int tab[] = { 0, 1, 2, 3, 4 };
  Awesome tab2[5];

  iter( tab, 5, print<const int> );
  iter( tab2, 5, print<Awesome> );

  return 0;
} */