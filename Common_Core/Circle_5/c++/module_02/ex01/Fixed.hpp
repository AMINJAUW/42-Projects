/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:39:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/20 14:23:12 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
using std::cout;
using std::endl;

# include <cmath>
using std::roundf;

class Fixed {

private :

	int _raw_bits;
	static int const _frac_bits = 8;

public :
	Fixed(void);
	Fixed(const int n);
	Fixed(const float f);
	Fixed(const Fixed &cpy);
	~Fixed(void);

	Fixed & operator=(Fixed const & rhs);
	
	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	float	toFloat( void ) const;
	int		toInt( void ) const;
};

std::ostream & operator<<(std::ostream & o, Fixed const & rhs);


#endif
