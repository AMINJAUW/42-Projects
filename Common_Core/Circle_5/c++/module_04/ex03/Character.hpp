/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:27:18 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/27 12:29:31 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include "ICharacter.hpp"


class Character : public ICharacter
{
private:
	string		_name;
	AMateria	*(_SpellBook[4]);
	Character(void);
public:
	Character(string const name);
	Character(Character const & cpy);
	~Character();
	
	Character	& operator=(Character const & rhs);
	string const & getName() const;
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);
	
	virtual	AMateria	*getMateriaFromSpellBook(int idx);
};



#endif
