/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 04:09:57 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/12 20:57:27 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//CDO
RPN::RPN() { std::cout << "Nope\n"; }
RPN::~RPN() { std::cout << "Nuh uh\n"; }
RPN::RPN(const RPN &ref)
{
	(void)ref;
	std::cout << "Not even close\n";
}
RPN &RPN::operator=(const RPN &ref)
{
	(void)ref;
	std::cout << "shut up...";
	return *this;
}

// The one and only

void RPN::solver(char const *av)
{
	std::istringstream	ss(av);
	std::string		str;
	std::list<int>		l;
	int			a;
	int			b;
	int			t;
	bool			integer = false;

	while (ss >> str)
	{
		if (str.size() > 1) { integer = true; break ; }
		if (std::isdigit(str[0]))
		{
			t = std::atoi(str.c_str());
			if (t < 0 || t > 9)
				throw std::runtime_error("Error: number is not a single digit");
			l.push_back(std::atoi(str.c_str()));
		}
		else
		{
			if (l.size() < 2)
				throw std::runtime_error("Error");
			b = l.back(); l.pop_back();
			a = l.back(); l.pop_back();
			switch (str[0])
			{
				case '+':
					l.push_back(a + b);
					break ;
				case '-':
					l.push_back(a - b);
					break ;
				case '*':
					l.push_back(a * b);
					break ;
				case '/':
					if (!b)
						throw std::runtime_error("Error: dividing by zero");
					l.push_back(a / b);
					break ;
				default:
					throw std::runtime_error("Error: Bad formating");
			}
		}
	}
	if (l.size() > 1)
		throw std::runtime_error("Error: Bad formating");
	if (!integer)
	{
		std::cout << l.back() << '\n';
		l.pop_back();
	}
	else
		throw std::runtime_error("Error: some weird formatting");
}
