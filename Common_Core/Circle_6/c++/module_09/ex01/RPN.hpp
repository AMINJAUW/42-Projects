/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:36:13 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 12:17:05 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <algorithm>

class WrongRPN : public std::exception
{
public:
	const char *what() const throw();
};

void rpn(string arg);

#endif
