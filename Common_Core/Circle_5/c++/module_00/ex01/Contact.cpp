/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:47:48 by aminjauw          #+#    #+#             */
/*   Updated: 2023/06/21 16:09:00 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(void) : 
	_fname(""), _lname(""), _nickname(""), _phone_num(""), _secret("")
{
	return ;
}

Contact::~Contact(void)
{
	return ;
}

std::string	Contact::get_fname(void) const
{
	return this->_fname;
}

std::string	Contact::get_lname(void) const
{
	return this->_lname;
}

std::string	Contact::get_nickname(void) const
{
	return this->_nickname;
}

std::string	Contact::get_phone_num(void) const
{
	return this->_phone_num;
}

std::string	Contact::get_secret(void) const
{
	return this->_secret;
}

void	Contact::set_fname(std::string str)
{
	this->_fname = str;
	return ;
}

void	Contact::set_lname(std::string str)
{
	this->_lname = str;
	return ;
}

void	Contact::set_nickname(std::string str)
{
	this->_nickname = str;
	return ;
}

void	Contact::set_phone_num(std::string str)
{
	this->_phone_num = str;
	return ;
}

void	Contact::set_secret(std::string str)
{
	this->_secret = str;
	return ;
}
