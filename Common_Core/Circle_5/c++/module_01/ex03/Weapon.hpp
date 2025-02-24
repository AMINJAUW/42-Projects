/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:47:52 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:32:47 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Weapon {

public:
	
	/* Constructors and destructors */
	Weapon(string type);
	~Weapon(void);
	/* Accesors */
	string const & getType(void) const;
	void	setType(string str);

private:
	string _type;
};


#endif
