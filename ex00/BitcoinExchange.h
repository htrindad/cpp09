/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:46:15 by htrindad          #+#    #+#             */
/*   Updated: 2026/04/14 10:38:15 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>

class BitcoinExchange
{
	private:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &ref);
		BitcoinExchange &operator=(const BitcoinExchange &ref);
	public:
		static void exchanging(std::string &file);

	class FileNotOpen : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
	class InvalidFile : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};
