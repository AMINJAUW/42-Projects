/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:54:58 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/09 14:13:32 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

char *to_upp(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 'a' + 'A';
		i++;
	}
	return (str);
}

int	main(int argc, char **argv)
{
	int i;
	
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" <<std::endl;
	else
	{
		i = 1;
		while (i < argc)
		{
			std::cout << to_upp(argv[i]);
			i++;
		}
		std::cout << std::endl;
	}
	return (0);
}