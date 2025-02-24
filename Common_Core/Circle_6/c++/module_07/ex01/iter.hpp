/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:55:26 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/11 15:08:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <cstdio>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void	print_arr_content(T & value)
{
	cout << value << endl;
}

template <typename TType, typename TSize, typename TFuncReturn>
void	iter(TType *addr, const TSize size, TFuncReturn (*f)(TType & a))
{
	for (TSize i = 0; i < size; i++)
	{
		f(addr[i]);
	}
}


template <typename TType, typename TSize, typename TFuncReturn>
void	iter(const TType *addr, const TSize size, TFuncReturn (*f)(const TType & a))
{
	for (TSize i = 0; i < size; i++)
	{
		f(addr[i]);
	}
}

#endif
