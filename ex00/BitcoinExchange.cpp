/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:57:45 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/13 21:25:21 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//Exceptions
const char *BitcoinExchange::FileNotOpen::what() const throw() { return "Error opening file"; }
const char *BitcoinExchange::InvalidFile::what() const throw() { return "Invalid file"; }

//Work
static inline bool	dateAnomaly(const std::size_t &year, const std::size_t &month, const std::size_t &day)
{
	if (month > 12 || day > 31 || !year || !month || !day)
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

static inline void	stringCheck(const std::string &year, const std::string &month, const std::string &day)
{
	std::string data[3] = { year, month, day };

	for (std::size_t i = 0; i < 3; i++)
		data[i].erase(std::remove(data[i].begin(), data[i].end(), ' '), data[i].end());
	if (data[0].size() != 4 || data[1].size() != 2 || data[2].size() != 2)
		throw std::runtime_error("Error: Poor size");
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
	stringCheck(year, month, day);
	std::istringstream(year) >> value[0];
	std::istringstream(month) >> value[1];
	std::istringstream(day) >> value[2];
	if (dateAnomaly(value[0], value[1], value[2]))
		throw std::runtime_error("Error: invalid date");
}

static inline void	btcCheck(const float &btc)
{
	if (btc > 1000)
		throw std::runtime_error("Error: Non acceptable value");
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
		std::getline(ss, btc);
		std::istringstream(btc) >> value;
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

static const inline std::string checker(const std::string &line, std::size_t fo)
{
	const std::string cpy = line.substr(fo + 1);
	std::size_t i = 0;
	uint8_t		options = 0;

	while (i < cpy.size())
	{
		if (!std::isspace(cpy[i]))
		{
			if (std::isdigit(cpy[i]) && !(options & 1))
				options |= 1;
			if (!std::isdigit(cpy[i]) || options & 2)
			{
				if (options & 2)
					throw std::runtime_error("Error: Number after space");
				if (!std::isdigit(cpy[i]))
				{
					if (cpy[i] == '-')
						throw std::runtime_error("Error: sign character not acceptable");
					if (cpy[i] == '+' && !(options & 1)) { i++; continue ; }
					if (cpy[i] == '.' && options & 1 && !(options & 4)) { options |= 4; i++; continue ; }
					throw std::runtime_error("Error: Not a digit");
				}
			}
		}
		else
			if (options & 1)
				options |= 2;
		i++;
	}
	if (options & 1)
		return cpy;
	throw std::runtime_error("Error: Invalid number");
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
			std::istringstream(checker(line, fo)) >> btc;
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
