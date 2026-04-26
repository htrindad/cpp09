/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:55:23 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/26 20:02:56 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cerr << "Need an argument\n", -1);
	try
	{
		BitcoinExchange::exchanging(av[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Impossible to comply, due to " << e.what() << "\n\n 'data.csv' non-existent, or failure to open the txt file.\n";
		return -1;
	}
	return 0;
}
