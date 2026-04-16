/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:57:45 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/16 20:11:28 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

//Exceptions
const char *BitcoinExchange::FileNotOpen::what() const throw() { return "Error opening file"; }
const char *BitcoinExchange::InvalidFile::what() const throw() { return "Invalid file"; }

//Work
static std::map<std::string, float> fileParser(std::ifstream &file)
{
	std::map<std::string, float>	m;
	std::istringstream		ss;
	std::string			line;
	std::string			date;
	std::string			btc;

	std::getline(file, line); // skip "data,exchange_rate"
	while (std::getline(file, line))
	{
		ss = line;
		std::getline(ss, date, ',');
		std::getline(ss, btc);
		m.insert(std::make_pair(date, std::stof(btc)));
	}
	return m;
}

static void thrower(const std::ifstream &stream)
{
	if (stream.fail())
		throw FileNotOpen();
}

static void finders(const std::map<std::string, float> &m, const std::string &file)
{
	std::map<std::string, float>::iterator	it;
	std::ifstream				f;
	std::string				line;
	std::string				date;
	float					btc;

	if (file.substr(file.find_last_of(".") + 1) != "txt")
		throw InvalidFile();
	f.open(file);
	thrower(f); // check if the file failed to open
	it = m.begin();
	std::getline(f, line);
	while (std::getline(f, line))
	{
		date = line.subtr(line.find_first_of("|"));
		if (m.find(date) != m.end())
		{

		}
	}
}

void BitcoinExchange::exchanging(const std::string &file)
{
	std::ifstream f; // File opening & parsing
	std::map<std::string, float> m;

	f.open("data.csv");
	thrower(f);
	m = fileParser(f);
	(f.close(), f.open(file), thrower(f));
}
