/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:41 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 14:03:00 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <limits.h>

#include <cstdlib>

# include <iostream>
using	std::cout;
using	std::endl;

# include <string>
using	std::string;

#include <cmath>
using	std::isfinite;

#include <cctype>
using	std::isprint;

#include <iomanip>

class ScalarConverter {
protected:
	ScalarConverter(void);
	~ScalarConverter(void);
	ScalarConverter(ScalarConverter const & cpy);
	ScalarConverter & operator=(ScalarConverter const & rhs);
public:
	static	void	convert(char const * str);
	class	NotScallar : public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif
