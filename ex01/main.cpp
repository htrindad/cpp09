/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 05:18:19 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/15 18:01:35 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static inline bool check(const char &av)
{
	if (!av || av == ' ')
		return true;
	return false;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cerr << "Not the right ammount of args\n", -1);
	if (check(av[1][0]))
		return (std::cerr << "Bad args\n", -1);
	try
	{
		RPN::solver(av[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Something went wrong: " << e.what() << '\n';
		return -1;
	}
	return 0;
}
