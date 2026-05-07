/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 05:18:37 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/07 11:23:54 by htrindad         ###   ########.fr       */
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
#include <cstring>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &ref);
		PmergeMe &operator=(const PmergeMe &ref);
		static void mis(char **av, const int &ac);
		static void fordJohnsonSort(std::vector<uint32_t> &v, std::size_t s, std::size_t e);
		static void fordJohnsonSort(std::deque<uint32_t> &d, std::size_t s, std::size_t e);
		static void mergeSort(std::vector<uint32_t> &v, std::size_t s, std::size_t m, std::size_t e);
		static void mergeSort(std::deque<uint32_t> &d, std::size_t s, std::size_t m, std::size_t e);
};
