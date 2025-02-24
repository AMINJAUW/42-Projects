/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:02:49 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:15:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanA {
	
public:
	/* Constructors and destructors */
	HumanA(string name, Weapon &weapon);
	~HumanA(void);
	
	void	attack(void) const;

private:
	string	_name;
	Weapon	&_weapon;
};
