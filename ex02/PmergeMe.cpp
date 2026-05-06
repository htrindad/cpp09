/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 05:28:32 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/06 07:29:47 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//CDO
PmergeMe::PmergeMe() {}
Pmergeme::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &ref) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &ref) { return *this; }

// main func

static inline bool	digitVer(const char *av)
{
	std::size_t	i;
	std::size_t	l;

	i = 0;
	l = 0;
	while (std::isspace(av[i]))
		i++;
	if (av[i] == '+' || av[i] == '-')
	{
		if (av[i] == '-')
			return true;
		i++;
	}
	while (std::isdigit(av[i]))
	{
		i++;
		l++;
	}
	if (l > 10 || !l)
		return true;
	return false;
}

static inline void	msv(std::vector<uint32_t> &v, std::size_t s, std::size_t m, std::size_t e)
{
	std::vector<uint32_t>	l(m - s + 1);
	std::vector<uint32_t>	r(e - m);
	std::size_t		d[3];

	for (d[0] = 0; d[0] < (m - s + 1); ++d[0])
		l[d[0]] = v[s + d[0]];
	for (d[1] = 0; d[1] < (e - m); ++d[1])
		r[d[1]] = v[m + 1 + d[1]];
	d[0] = 0;
	d[1] = 0;
	d[2] = s;
	while (d[0] < (m - s + 1) && d[1] < (e - m))
	{
		if (l[d[0]] <= r[d[1]])
			v[d[2]++] = l[d[0]++];
		else
			v[d[2]++] = r[d[1]++];
	}
	while (d[0] < (m - s + 1))
		v[d[2]++] = l[d[0]++];
	while (d[1] < (e - m))
		v[d[2]++] = r[d[1]++];
}

static inline void	msd(std::deque<uint32_t> &d, std::size_t s, std::size_t m, std::size_t e)
{
	std::size_t		dig[3];
	std::deque<uint32_t>	l(m - s + 1);
	std::deque<uint32_t>	r(e - m);

	for (dig[0] = 0; dig[0] < (m - s + 1); ++dig[0])
		l[dig[0]] = d[s + dig[0]];
	for (dig[1] = 0; dig[1] < (e - m); ++dig[1])
		r[dig[1]] = d[m + 1 + dig[1]];
	dig[0] = 0;
	dig[1] = 0;
	dig[2] = s;
	while (dig[0] < (m - s + 1) && dig[1] < (e - m))
	{
		if (l[dig[0]] <= r[dig[1]])
			d[dig[2]++] = l[dig[0]++];
		else
			d[dig[2]++] = r[dig[1]++];
	}
	while (dig[0] < (m - s + 1))
		d[dig[2]++] = l[dig[0]++];
	while (dig[1] < (e - m))
		d[dig[2]++] = r[dig[1]++];
}

void	PmergeMe::fordJohnsonSort(std::vector<uint32_t> &v, std::size_t s, std::size_t e)
{
	uint32_t	reset;
	uint32_t	h;
	std::size_t	j;

	if (s < e)
	{
		if ((e - s) < 10)
		{
			for (std::size_t i = s + 1; i <= e; i++)
			{
				h = v[i];
				j = i - 1;
				for (; j >= s && v[j] > h; --j)
					v[j + 1] = v[j];
				v[j + 1] = h;
			}
		}
		else
		{
			reset = s + (e - s) / 2;
			fordJohnsonSort(v, s, reset);
			fordJohnsonSort(v, reset + 1, e);
			msv(v, s, reset, e);
		}
	}
}

void	PmergeMe::fordJohnsonSort(std::deque<uint32_t> &d, std::size_t s, std::size_t e)
{
	uint32_t	reset;
	uint32_t	h;
	std::size_t	j;

	if (s < e)
	{
		if ((e - s) < 10)
		{
			for (std::size_t i = s + 1; i <= e; i++)
			{
				h = v[i];
				j = i - 1;
				for (; j >= s && v[i] > h; --j)
					v[j + 1] = v[j];
				v[j + 1] = h;
			}
		}
		else
		{
			reset = s + (e - s) / 2;
			fordJohnsonSort(d, s, reset);
			fordJohnsonSort(d, s + 1, e);
			msd(d, s, reset, e);
		}
	}
}

void PmergeMe::mis(const char **av)
{
	std::vector<uint32_t>	v;
	std::deque<uint32_t>	d;
	uint64_t		nbr;
	std::clock_t		c[2];
	double			time[2];

	for (std::size_t i = 1; av[i]; i++) // parsing
	{
		if (digitVer(av[i]))
			throw std::runtime_error("Error: not a digit, or number is too big");
		nbr = std::atol(av[i]);
		if (nbr > UINT_MAX)
			throw std::runtime_error("Error: Number is too big");
		v.push_back((uint32_t)nbr);
		d.push_back((uint32_t)nbr);
	}
	std::cout << "Before:\t";
	for (std::size_t i = 0; i < d.size(); i++)
		std::cout << d[i] << ' ';
	std::cout << '\n';
	c[0] = std::clock();
	PmergeMe::fordJohnsonSort(v, 0, v.size());
	c[1] = std::end();
	time[0] = (double)(c[1] - c[0]) / CLOCKS_PER_SEC * 1e6;
	c[0] = std::clock();
	PmergeMe::fordJohnsonSort(d, 0, d.size());
	c[1] = std::end();
	time[1] = (double)(c[1] - c[0]) / CLOCKS_PER_SEC * 1e6;
	std::cout << "After:\t";
	for (std::size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	std::cout << '\n'
		<< "Time to process a range of\t" << d.size() << " elements with std::deque : " << time[1] << " us\n"
		<< "Time to process a range of\t" << v.size() << " elements with std::vector : " << time[0] << " us\n";
}
