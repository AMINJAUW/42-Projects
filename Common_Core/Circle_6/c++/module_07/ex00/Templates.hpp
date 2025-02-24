/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Templates.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:44:59 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/12 15:30:35 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATES_HPP
# define TEMPLATES_HPP

template <typename T>
void	swap(T & a, T & b)
{
	T temp = a;
	a = b;
	b = temp;
	return ;
}

template <typename T>
T const &	max(T const & a, T const & b)
{
	return (a >= b ? a : b);
}

template <typename T>
T const &	min(T const & a, T const & b)
{
	return (a <= b ? a : b);
}

#endif
