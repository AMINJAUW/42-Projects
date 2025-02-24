/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:54:57 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/12 15:02:34 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <vector>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;


#include <stdexcept>

class Span {
private:
	std::vector<int> 	_v;
	const unsigned int 	_size;
	Span(void);
public:
	~Span(void);
	Span(Span const & cpy);
	Span(const unsigned int size);
	Span & operator=(Span const & rhs);

	int	shortestSpan(void) const;
	int longestSpan(void) const;

	void	addNumber(int n);
	template <class Iterator>
	void	addNumber(Iterator begin, Iterator end)
	{
		if (this->_v.size() + std::distance(begin, end) > this->_size)
			throw FilledSpan();
		std::copy(begin, end, std::back_inserter(this->_v));
	}
	class FilledSpan : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class NotEnoughNumbersForSpanCalculation : public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	std::vector<int> getArr() const;

};

#endif

std::ostream & operator<<(std::ostream & o, const Span & rhs);