/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:26:46 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/22 10:39:57 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
using std::cout;
using std::endl;

# include <string>
using std::string;


# define RED		"\x1b[31m"
# define YELLOW		"\x1b[33m"
# define GREEN		"\x1b[32m"
# define NO_COLOR	"\x1b[0m"

class ClapTrap
{
protected:
	string	_name;
	unsigned int		_Hp;
	unsigned int		_Ep;
	unsigned int		_Att;
	ClapTrap(void);
public:
	ClapTrap(string	name);
	ClapTrap(ClapTrap const &cpy);
	~ClapTrap(void);

	ClapTrap & operator=(ClapTrap const &rhs);

	void attack(const std::string & target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	string	get_name(void) const;
	unsigned int		get_Hp(void) const;
	unsigned int		get_Ep(void) const;
	unsigned int		get_Att(void) const;
};

std::ostream	& operator<<(std::ostream & o, ClapTrap const &rhs);

#endif
