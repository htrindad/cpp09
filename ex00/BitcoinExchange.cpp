/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:57:45 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/08 17:49:57 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Exceptions
const char *BitcoinExchange::FileNotOpen::what() const throw() { return "Error opening file"; }
const char *BitcoinExchange::InvalidFile::what() const throw() { return "Invalid file"; }

//Work
static inline bool	dateAnomaly(const std::size_t &year, const std::size_t &month, const std::size_t &day)
{
	if (year > 2026 || month > 12 || day > 31)
		return true;
	if (month == 2 && day > 29)
		return true;
	if (month == 2 && day > 28 && (year % 400 || (year % 4 && !(year % 100))))
		return true;
	if (day > 30)
	{
		switch (month)
		{
			case 9:
				return true;
			case 4:
				return true;
			case 6:
				return true;
			case 11:
				return true;
			default:
				return false;
		}
	}
	return false;
}

static inline void	dateCheck(const std::string &date)
{
	std::istringstream	ss(date);
	std::string		year;
	std::string		month;
	std::string		day;
	std::size_t		value[3];
	
	std::getline(ss, year, '-');
	std::getline(ss, month, '-');
	std::getline(ss, day);
	std::istringstream(year) >> value[0];
	std::istringstream(month) >> value[1];
	std::istringstream(day) >> value[2];
	if (value[0] > 2026)
		throw std::runtime_error("Error: invalid year");
	if (value[1] > 12)
		throw std::runtime_error("Error: invalid month");
	if (dateAnomaly(value[0], value[1], value[2]))
		throw std::runtime_error("Error: invalid date");
}

static inline void	btcCheck(const float &btc)
{
	if (btc < 0)
		throw std::runtime_error("Error: not a positive number");
}

static inline std::map<std::string, float> fileParser(std::ifstream &file)
{
	std::map<std::string, float>	m;
	std::string			line;
	std::string			date;
	std::string			btc;
	float				value;

	std::getline(file, line); // skip "data,exchange_rate"
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::getline(ss, date, ',');
		dateCheck(date);
		std::getline(ss, btc);
		std::istringstream(btc) >> value;
		btcCheck(value);
		m.insert(std::make_pair(date, value));
	}
	return m;
}

static inline void thrower(std::ifstream &stream)
{
	if (stream.fail())
		throw BitcoinExchange::InvalidFile();
	if (!stream.is_open())
		throw BitcoinExchange::FileNotOpen();
}

static inline void finders(const std::map<std::string, float> &m, std::ifstream &f)
{
	std::map<std::string, float>::const_iterator	it;
	std::string					line;
	std::string					date;
	std::size_t					fo;
	std::size_t					start;
	std::size_t					end;
	float						btc;

	it = m.begin();
	std::getline(f, line);
	while (std::getline(f, line))
	{
		try
		{
			fo = line.find_first_of("|");
			if (fo == std::string::npos)
				throw BitcoinExchange::InvalidFile();
			date = line.substr(0, fo);
			dateCheck(date);
			std::istringstream(line.substr(fo + 1)) >> btc;
			btcCheck(btc);
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
		catch (std::exception &e)
		{
			std::cerr << "Error: on line '" << line << "': " << e.what() << '\n';
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
	if (m.empty())
		throw std::runtime_error("memory failure");
	(f.close(), f.open(file.c_str()), thrower(f));
	finders(m, f);
}
