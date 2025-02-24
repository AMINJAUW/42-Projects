/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:53:37 by aminjauw          #+#    #+#             */
/*   Updated: 2023/12/06 14:09:51 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/* Canonical Class */

ScalarConverter::ScalarConverter(void) {
}

ScalarConverter::~ScalarConverter(void) {
}

ScalarConverter::ScalarConverter(ScalarConverter const & cpy) {
	*this = cpy;
}

ScalarConverter & ScalarConverter::operator=(ScalarConverter const & rhs) {
	(void)rhs;
	return *this;
}

char const * ScalarConverter::NotScallar::what() const throw()
{
	return "Not a valid number !";
}

/* Check Type */

static bool	only_numbers(const char *str)
{
	int i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static size_t	not_double_type(const string str)
{
	size_t i = 0;
	bool point = false;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.' && point == false)
			point = true;
		else if ((str[i] < '0' || str[i] > '9'))
			return (i);
		i++;
	}
	return (std::string::npos);
}

static int findtype(const char *str)
{
	string s(str);
	
	if (s.length() == 3 && s[0] == s[2] && s[0] == '\'')
		return (0); // char
	else if (only_numbers(str))
		return (1); // int
	else if (s == "inff" || s == "+inff" || s == "-inff" || s == "nanf" ||
			(s.find('f') == s.length() - 1 && not_double_type(s) == s.length() - 1))
		return (2);	// float
	else if (s == "inf" || s == "+inf" || s == "-inf" || s == "nan" ||
		(not_double_type(s) == std::string::npos))
		return (3); // double
	else
		return (4); // none
}

/* write the type */

static void	from_char(char c)
{
	/* CHAR */
	cout << "char: ";
	if (c > CHAR_MAX || c < CHAR_MIN)
	{
		cout << "impossible" << endl;
	}
	else if (isprint(c))
		cout << "'" << c << "'" << endl;
	else
		cout << "Non displayable" << endl;

	/* INT */

	cout << "int: " << static_cast<int>(c) << endl;
	
	/* FLOAT */

	cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << endl;
	
	/* DOUBLE */

	cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << endl;
}

static void	from_int(int i, const char *str)
{
	/* CHAR */
	cout << "char: ";
	if (i > CHAR_MAX || i < CHAR_MIN)
	{
		cout << "impossible" << endl;
	}
	else if (isprint(i))
		cout << "'" << static_cast<char>(i) << "'" << endl;
	else
		cout << "Non displayable" << endl;

	/* INT */

	if (string(str).compare(std::to_string(i)) != 0)
	{
		cout << "int: Number too large to fit inside a int" << endl;
		cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(i) << "f" " <-- Not relevant because int overflowed" << endl;
		cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) <<  " <-- Not relevant because int overflowed" << endl;
		return;
	}
	else
		cout << "int: " << i << endl;
	
	/* FLOAT */

	cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(i) << "f" << endl;
	
	/* DOUBLE */

	cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << endl;
}

static void	from_float(float f)
{
	/* CHAR */
	cout << "char: ";
	if (f > CHAR_MAX || f < CHAR_MIN)
	{
		cout << "impossible" << endl;
	}
	else if (isprint(f))
		cout << "'" << static_cast<char>(f) << "'" << endl;
	else
		cout << "Non displayable" << endl;

	/* INT */

	if (f > INT_MAX || f < INT_MIN)
		cout << "int: impossible" << endl;
	else
		cout << "int: " << static_cast<int>(f) << endl;
	
	/* FLOAT */
	
	cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << endl;
	
	/* DOUBLE */

	cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << endl;
}

static void from_double(double d)
{	
	/* CHAR */
	cout << "char: ";
	if (isfinite(d) == false || d > CHAR_MAX || d < CHAR_MIN)
	{
		cout << "impossible" << endl;
	}
	else if (isprint(d))
		cout << "'" << static_cast<char>(d) << "'" << endl;
	else
		cout << "Non displayable" << endl;

	/* INT */

	if (isfinite(d) == false || d > INT_MAX || d < INT_MIN)
		cout << "int: impossible" << endl;
	else
		cout << "int: " << static_cast<int>(d) << endl;
	
	/* FLOAT */
	cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << endl;
	
	/* DOUBLE */

	cout << "double: " << std::fixed << std::setprecision(1) << d << endl;
}

void	ScalarConverter::convert(const char *str)
{
	switch (findtype(str))
	{
	case 0:
		from_char(str[1]);
		return;
	case 1:
		from_int(std::atoi(str), str);
		return;
	case 2:
		from_float(std::atof(str));
		return;
	case 3:
		from_double(std::strtod(str, nullptr));
		return;
	default:
		throw NotScallar();
	}
}