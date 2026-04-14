/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:57:45 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/14 10:50:54 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

//Exceptions
const char *BitcoinExchange::FileNotOpen::what() const throw() { return "Error opening file"; }
const char *BitcoinExchange::InvalidFile::what() const throw() { return "Invalid file"; }

//Work
static std::map<std::string, float> fileParser(std::ifstream &file)
{
	std::map<std::string, float> m;
	std::string line;
	std::size_t pos;

	std::getline(file, line); // skip "data | exchange_rate"
	if (line != "date | value")
		throw InvalidFile();
	while (std::getline(file, line))
	{
		pos = line.find_first_of('|');
		m[line.substr(0, pos)] = std::stof(line.substr(pos + 1));
	}
	return m;
}

void BitcoinExchange::exchanging(std::string &file)
{
	std::ifstream f; // File opening & parsing
	std::map<std::string, float> m;

	f.open(file);
	if (f.fail())
		throw FileNotOpen();
	m = fileParser(f);
}
