/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:22:17 by aminjauw          #+#    #+#             */
/*   Updated: 2023/11/14 13:11:27 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
private:
	std::string	_name;
public:
	Zombie(void);
	~Zombie(void);
	std::string	get_name( void ) const;
	void		set_name( std::string str );
	void		announce( void ) const;
};

Zombie*	newZombie( std::string name );
void	randomChump( std::string name );

#endif
