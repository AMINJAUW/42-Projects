/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:16:29 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/12 12:36:34 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>
#include <deque>


template <typename T>
class MutantStack : public std::stack< T, std::deque< T > >
{
public:
	MutantStack<T>(void) : std::stack< T, std::deque< T > >() {}
	virtual ~MutantStack<T>() {}
	MutantStack<T>(MutantStack const & cpy) : std::stack< T, std::deque< T > >(cpy) {}
	MutantStack<T> & operator=(MutantStack const & rhs)
	{
		std::stack< T, std::deque< T > >::operator=(rhs);
		return *this;
	}
	
    typedef typename std::deque<T>::iterator    iterator;

    iterator    begin() { return this->c.begin(); }
    iterator    end() { return this->c.end(); }
};


#endif
