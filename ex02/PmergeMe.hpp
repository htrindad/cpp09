/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 05:18:37 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/06 07:00:47 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <deque>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &ref);
		PmergeMe &operator=(const PmergeMe &ref);
		static void mis(const char **av);
		static void fordJohnsonSort(std::vector<uint32_t> &v, std::size_t s, std::size_t e);
		static void fordJohnsonSort(std::deque<uint32_t> &d, std::size_t s, std::size_t e);
};
