/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:32:35 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/12 15:39:10 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>

template <typename T>
class Array
{
private :
	T *_arr;
	int	_size;
	
public:
	Array(void) : _arr(new T[0]), _size(0) {}
	Array(int n) : _arr(new T[n]), _size(n) {}
	Array(Array const & cpy)
	{
		this->_arr = new T[0];
		*this = cpy;
	}
	~Array(void)
	{
		delete [] this->_arr;	
	}
	Array & operator=(Array const & rhs)
	{
		this->_size = rhs.size();
		delete [] this->_arr;
		this->_arr = new T[this->_size];
		for (int i = 0; i < this->_size; i++)
		{
			this->_arr[i] = rhs[i];
		}
		return *this;
	}
	
	T & operator[](int i) 
	{
		if (i < 0 || i >= this->_size)
			throw std::out_of_range("invlaid index for array");
		return this->_arr[i]; 
	}

	T const & operator[](int i) const
	{
		if (i < 0 || i >= this->_size)
			throw std::out_of_range("invlaid index for array");
		return this->_arr[i]; 
	}
	
	int	size(void) const
	{ return this->_size; }
};

#endif
