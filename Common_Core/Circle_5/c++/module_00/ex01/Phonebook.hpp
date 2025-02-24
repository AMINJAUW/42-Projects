/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:19:09 by aminjauw          #+#    #+#             */
/*   Updated: 2023/06/21 13:13:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iomanip>

# ifndef STD_NBR
# define STD_NBR "1307"
# endif

class PhoneBook
{
	private:
		Contact _contacts[8];
		int		_index;
	public:
		PhoneBook(void);
		~PhoneBook(void);
		/*---Commands---*/
		void	add(void) ;
		void	search(void) const;
};

bool		valid_phone_nbr(std::string str, int print);
bool		valid_first_name(std::string str, int print);
bool		valid_last_name(std::string str, int print);
std::string *format_first_name(std::string *addr);
std::string *format_last_name(std::string *addr);

#endif
