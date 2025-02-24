/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:44:21 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/24 14:44:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	this->_ideas = new std::string[100];
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = "Brain idea n°" + std::to_string(i + 1);
	std::cout << "A brain has been constructed and filled with ideas\n";
}

Brain::~Brain()
{
	delete [] (this->_ideas);
	std::cout << "A brain has been destroyed\n";
}

Brain::Brain(Brain & ref)
{
	std::string *ref_ideas = ref.getIdeas();
	
	this->_ideas = new std::string[100];
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = ref_ideas[i] + " stolen";
	std::cout << "A brain has been copy constructed and stole the other's ideas\n";
}

Brain & Brain::operator=(Brain const & rhs)
{
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = rhs._ideas[i];
	return (*this);
}

std::string *Brain::getIdeas()
{
	return (this->_ideas);
}