/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:57:45 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/26 19:42:59 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.h"

//Exceptions
const char *BitcoinExchange::FileNotOpen::what() const throw() { return "Error opening file"; }
const char *BitcoinExchange::InvalidFile::what() const throw() { return "Invalid file"; }

//Work
static inline std::map<std::string, float> fileParser(std::ifstream &file)
{
	std::map<std::string, float>	m;
	std::istringstream		ss;
	std::string			line;
	std::string			date;
	std::string			btc;
	float				value;

	std::getline(file, line); // skip "data,exchange_rate"
	while (std::getline(file, line))
	{
		ss << line;
		std::getline(ss, date, ',');
		std::getline(ss, btc);
		std::ifstringstream(btc) >> value;
		m.insert(std::make_pair(date, value));
	}
	return m;
}

static inline void thrower(std::ifstream &stream)
{
	if (stream.fail())
		throw InvalidFile();
	if (!stream.is_open())
		throw FileNotOpen();
}

static inline void finders(const std::map<std::string, float> &m, const std::ifstream &f)
{
	std::map<std::string, float>::iterator	it;
	std::string				line;
	std::string				date;
	std::size_t				fo;
	std::size_t				start;
	std::size_t				end;
	float					btc;

	it = m.begin();
	std::getline(f, line);
	while (std::getline(f, line))
	{
		fo = line.find_first_of("|");
		date = line.substr(0, fo);
		std::ifstringstream(line.substr(fo + 1)) >> btc;
		start = date.find_first_not_of(" \t");
		end = date.find_last_not_of(" \t");
		if (start != std::string::npos && end != std::string::npos)
			date = date.substr(start, end - start + 1);
		it = m.lower_bound(date);
		if (it == m.end() || it->first != date)
		{
			if (it == m.begin())
				throw std::range_error("Error with the date found");
			else
				it--;
		}
		std::cout << date << " => " << btc << " = " << (btc * it->second) << '\n';
	}
}

void BitcoinExchange::exchanging(const std::string &file)
{
	std::ifstream f; // File opening & parsing
	std::map<std::string, float> m;

	f.open("data.csv");
	thrower(f);
	m = fileParser(f);
	if (m.empty())
		throw std::runtime_error("memory failure");
	(f.close(), f.open(file), thrower(f));
	finders(m, f);
}
