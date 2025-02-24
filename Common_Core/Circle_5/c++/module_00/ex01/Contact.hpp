/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:19:36 by aminjauw          #+#    #+#             */
/*   Updated: 2023/06/21 16:28:39 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>


# define RED			"\x1b[31m"
# define BLUE			"\x1b[34m"
# define YELLOW			"\x1b[33m"
# define GREEN			"\x1b[32m"
# define LIGHT_GREY		"\x1b[30m"
# define BK_LIGHT_GREY	"\x1b[100m"
# define BK_NO			"\x1b[49m"
# define NO_COLOR		"\x1b[0m"
# define BOLD		 	"\x1b[1m"
# define BOLD_OFF		"\x1b[21m"


class Contact
{
	private:
		std::string	_fname;
		std::string	_lname;
		std::string	_nickname;
		std::string	_phone_num;
		std::string	_secret;
	public:
		Contact( void );
		~Contact( void );
		/*----accessors----*/
		std::string	get_fname( void ) const;
		std::string	get_lname( void ) const;
		std::string	get_nickname( void ) const;
		std::string	get_phone_num( void ) const;
		std::string	get_secret( void ) const;
		void		set_fname(std::string str);
		void		set_lname(std::string str);
		void		set_nickname(std::string str);
		void		set_phone_num(std::string str);
		void		set_secret(std::string str);
};




#endif