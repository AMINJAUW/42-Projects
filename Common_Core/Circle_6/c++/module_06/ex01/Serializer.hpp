/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:24:02 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 14:45:11 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include "Data.hpp"
# include <stdint.h>

#include <iostream>
using std::cout;
using std::endl;

class Serializer {
protected:
	Serializer(void);
	Serializer(Serializer const & cpy);
	Serializer & operator=(Serializer const & rhs);
public:
	~Serializer(void);

	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

#endif
