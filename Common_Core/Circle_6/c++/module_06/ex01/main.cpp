/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:41:58 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 14:48:14 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(void)
{
	Data	*obj = new Data();
	std::cout << "> Data object created\n" << std::endl;

	obj->str = "RANDOM STRINGG";
	std::cout << "Data member: " << obj->str << std::endl;
	std::cout << "Address: " << obj << std::endl;

	uintptr_t	raw = Serializer::serialize(obj);
	std::cout << "\n> Serialized: " << raw << std::endl;

	obj = Serializer::deserialize(raw);
	std::cout << "\n> After deserialize: " << std::endl;

	std::cout << "\nData member: " << obj->str << std::endl;
	std::cout << "Address: " << obj << std::endl;

	delete obj;
	return (0);
}
