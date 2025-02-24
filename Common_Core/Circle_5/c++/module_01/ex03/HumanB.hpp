/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:18:42 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 16:49:58 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanB {
	
public:
	/* Constructors and destructors */
	HumanB(string name);
	~HumanB(void);
	
	void	setWeapon(Weapon &weapon);

	void	attack(void) const;

private:
	string	_name;
	Weapon	*_weapon;
};