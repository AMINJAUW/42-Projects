/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:39:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/20 17:08:47 by aminjauw         ###   ########.fr       */
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

	bool	operator>(Fixed const & rhs) const;
	bool	operator<(Fixed const & rhs) const;
	bool	operator>=(Fixed const & rhs) const;
	bool	operator<=(Fixed const & rhs) const;
	bool	operator==(Fixed const & rhs) const;
	bool	operator!=(Fixed const & rhs) const;

	Fixed	operator+(Fixed const & rhs) const;
	Fixed	operator-(Fixed const & rhs) const;
	Fixed	operator*(Fixed const & rhs) const;
	Fixed	operator/(Fixed const & rhs) const;

	Fixed	&operator++(void);
	Fixed	&operator--(void);
	Fixed	operator++(int);
	Fixed	operator--(int);

	static	Fixed	&min(Fixed &a, Fixed &b);
	static	Fixed	&max(Fixed &a, Fixed &b);
	static	const Fixed	&min(const Fixed &a, const Fixed &b);
	static	const Fixed	&max(const Fixed &a, const Fixed &b);

};

std::ostream & operator<<(std::ostream & o, Fixed const & rhs);


#endif
