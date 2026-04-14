/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:55:23 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/14 10:27:08 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

static bool validFile(const std::string file)
{
	if (file.substr(find.find_last_of(".") + 1) == "csv")
		return false;
	return true;
}

int main(int ac, char **av)
{
	if (ac < 2 || validFile(av[1]))
		return (std::cerr << "ERROR: No arguments have been inputed\n", -1);
	try
	{
		BitcoinExchange::exchanging(av[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Impossible to comply, due to " << e.what() << '\n';
	}
	return 0;
}
