/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:39:45 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/20 14:22:35 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
using std::cout;
using std::endl;

class Fixed {

private :

	int _raw_bits;
	static int const _frac_bits;

public :
	Fixed(void);
	Fixed(const Fixed &cpy);
	~Fixed(void);

	Fixed & operator=(Fixed const & rhs);
	
	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
};


#endif
