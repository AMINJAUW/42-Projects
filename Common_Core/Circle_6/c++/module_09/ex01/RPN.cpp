/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:36:19 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/22 12:58:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const char *WrongRPN::what() const throw()
{
	return "Error";
}

static int operant(char c)
{
	const char op[] = "+-/*";

	if (c >= '0' && c <= '9')
		return 1;
	if (std::find(std::begin(op), std::end(op), c))
		return 0;
	return -1;
}

void rpn(string arg)
{
	std::stack<int> numbers;
	
	arg.erase(remove_if(arg.begin(), arg.end(), isspace), arg.end());
	

	int first;
	int second;

	for (size_t i = 0; i < arg.size(); ++i)
	{
		switch (operant(arg[i]))
		{
		case 1:
			numbers.push(arg[i] - '0');
			break;
		
		case 0:
			if (numbers.size() < 2)
				throw WrongRPN();
			second = numbers.top();
			numbers.pop();
			first = numbers.top();
			numbers.pop();
			switch (arg[i])
			{
			case '+':
				numbers.push(first + second);
				break;
			case '-':
				numbers.push(first - second);
				break;
			case '*':
				numbers.push(first * second);
				break;
			case '/':
				if (second == 0)
					throw WrongRPN();
				numbers.push(first / second);
				break;
			}
			break;
		
		default:
			throw WrongRPN();
		}
	}
	if (numbers.size() != 1)
		throw WrongRPN();
	cout << numbers.top() << endl;
}
