/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 05:28:32 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/09 18:48:43 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//CDO
PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &ref) { (void)ref; }
PmergeMe &PmergeMe::operator=(const PmergeMe &ref)
{
	(void)ref;
	return *this;
}

// main func

static inline bool	digitVer(const char *av)
{
	std::size_t	i = 0, l = 0;

	i = 0;
	l = 0;
	while (std::isspace(av[i])) i++;
	if (av[i] == '+' || av[i] == '-')
		if (av[i++] == '-') return true;
	while (std::isdigit(av[i])) { i++; l++; }
	return (l > 10 || !l);
}

static uint32_t	jacobStahl(uint32_t n) // necessity of the Ford Johnson
{
	if (n < 2) return n;
	return jacobStahl(n - 1) + 2 * jacobStahl(n - 2);
}

static inline std::vector<std::size_t>	jacobInsertOrder(const std::size_t &count)
{
	std::vector<std::size_t> o;

	if (count < 2) return o;
	std::size_t prev = 1, next = 3;
	while (jacobStahl(next) <= count)
	{
		std::size_t up = jacobStahl(next);
		for (std::size_t i = up; i > prev; --i)
			o.push_back(i - 1);
		prev = up;
		next++;
	}
	if (count > prev)
		for (std::size_t i = count; i > prev; --i)
			o.push_back(i - 1);
	return o;
}

void	PmergeMe::jacobStahlSort(std::vector<uint32_t> &v, std::size_t s, std::size_t e)
{
	typedef std::pair<uint32_t, uint32_t> p;
	std::size_t size = e - s + 1;

	if (size < 11)
	{
		for (std::size_t i = s + 1; i <= e; ++i)
		{
			uint32_t key = v[i];
			std::size_t j = i;
			while (j > s && key < v[j - 1])
			{
				v[j] = v[j - 1];
				j--;
			}
			v[j] = key;
		}
		return ;
	}
	std::vector<p>	pair;
	uint32_t		stra;
	bool			hs = size % 2;
	for (std::size_t i = s; i + 1 <= e; i += 2)
	{
		uint32_t a = v[i];
		uint32_t b = v[i + 1];

		if (b < a)
			std::swap(a, b);
		pair.push_back(p(a, b));
	}
	if (hs)
		stra = v[e];
	std::size_t k = pair.size();
	std::vector<uint32_t> big(k), small(k);
	for (std::size_t i = 0; i < k; ++i)
	{
		big[i] = pair[i].first;
		small[i] = pair[i].second;
	}
	jacobStahlSort(big, 0, k - 1);
	std::vector<uint32_t> ss(k);
	for (std::size_t i = 0; i < k; ++i)
	{
		uint32_t cb = big[i];
		for (std::size_t j = 0; j < pair.size(); ++j)
		{
			if (pair[j].first == cb)
			{
				ss[i] = pair[j].second;
				break ;
			}
		}
	}
	std::vector<uint32_t> c;
	c.push_back(ss[0]);
	c.insert(c.end(), big.begin(), big.end());
	std::vector<std::size_t> pos(k);
	for (std::size_t i = 0; i < k; ++i)
		pos[i] = i + 1;
	std::vector<std::size_t> o = jacobInsertOrder(k);
	for (std::size_t i = 0; i < o.size(); ++i)
	{
		std::size_t id = o[i];
		std::size_t lim = pos[id];
		uint32_t value = ss[id];
		std::size_t l = 0, r = lim;
		while (l < r)
		{
			std::size_t m = l + (r - l) / 2;
			if (value < c[m])
				r = m;
			else
				l = m + 1;
		}
		c.insert(c.begin() + l, value);
		for (std::size_t j = 0; j < k; ++j)
			if (pos[j] >= l)
				pos[j]++;
	}
	if (hs)
	{
		std::size_t l = 0, r = c.size();
		while (l < r)
		{
			std::size_t m = l + (r - l) / 2;
			if (stra < c[m])
				r = m;
			else
				l = m + 1;
		}
		c.insert(c.begin() + left, stra);
	}
	std::copy(c.begin(), c.end(), v.begin() + s);
}

void	PmergeMe::jacobStahlSort(std::deque<uint32_t> &d, std::size_t s, std::size_t e)
{
	typedef std::pair<uint32_t, uint32_t> pair;
	std::size_t size = e - s + 1;

	if (size < 11)
	{
		for (std::size_t i = s + 1; i <= e; ++i)
		{
			uint32_t k = d[i];
			std::size_t j = i;
			while (j > s && k < d[j - 1])
			{
				d[j] = d[j - 1];
				j--;
			}
			d[j] = k;
		}
		return ;
	}
	std::deque<pair>	p;
	uint32_t		stra;
	bool			hs = size % 2;
	for (std::size_t i = s; i + 1 <= e; i += 2)
	{
		uint32_t a = d[i];
		uint32_t b = d[i + 1];
		if (b < a)
			std::swap(a, b);
		p.push_back(pair(a, b));
	}
	if (hs)
		stra = d[e];
	std::size_t k = p.size();
	std::deque<uint32_t> big(k), small(k);
	for (std::size_t i = 0; i < k; ++i)
	{
		big[i] = p[i].first;
		small[i] = p[i].second;
	}
	jacobStahlSort(big, 0, k - 1);
	std::deque<uint32_t> ss(k);
	for (std::size_t i = 0; i < k; ++i)
	{
		uint32_t cb = big[i];
		for (std::size_t j = 0; j < p.size(); ++j)
		{
			if (p[j].first == cb)
			{
				ss[i] = p[j].second;
				break ;
			}
		}
	}
	std::deque<uint32_t> c;
	c.push_back(ss[0]);
	c.insert(c.end(), big.begin(), big.end());
	std::vector<std::size_t> pos(k);
	for (std::size_t i = 0; i < k; ++i)
		pos[i] = i + 1;
	std::vector<std::size_t> o = jacobInsertOrder(k);
	for (std::size_t i = 0; i < o.size(); ++i)
	{
		std::size_t id = o[i];
		std::size_t lim = pos[i];
		uint32_t value = ss[id];
		std::size_t l = 0, r = lim;
		while (l < r)
		{
			std::size_t m = l + (r - s) / 2;
			if (value < c[m])
				r = m;
			else
				l = m + 1;
		}
		c.insert(c.begin() + l, value);
		for (std::size_t j = 0; j < k; ++j)
			if (pos[j] >= l)
				pos[j]++;
	}
	if (hs)
	{
		std::size_t l = 0, r = c.size();
		while (l < r)
		{
			std::size_t m = l + (r - l) / 2;
			if (stra < c[m])
				r = m;
			else
				l = m + 1;
		}
		c.insert(c.begin() + l, stra);
	}
	std::copy(c.begin(), c.end(), d.begin() + s);
}

void	PmergeMe::fordJohnsonSort(std::vector<uint32_t> &v, std::size_t s, std::size_t e)
{
	jacobStahlSort(v, s, e);
}

void	PmergeMe::fordJohnsonSort(std::deque<uint32_t> &d, std::size_t s, std::size_t e)
{
	jacobStahlSort(d, s, e);
}

void PmergeMe::mis(char **av, const int &ac)
{
	std::vector<uint32_t>	v;
	std::deque<uint32_t>	d;
	uint64_t		nbr;
	std::clock_t		c[2];
	double			time[2];
	std::size_t		s;

	if (ac == 2)
		s = 0;
	else
		s = 1;
	for (std::size_t i = s; av[i]; i++) // parsing
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
	fordJohnsonSort(v, 0, v.size() - 1);
	c[1] = std::clock();
	time[0] = (double)(c[1] - c[0]) / CLOCKS_PER_SEC * 1e6;
	c[0] = std::clock();
	fordJohnsonSort(d, 0, d.size() - 1);
	c[1] = std::clock();
	time[1] = (double)(c[1] - c[0]) / CLOCKS_PER_SEC * 1e6;
	std::cout << "After:\t";
	for (std::size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	std::cout << '\n'
		<< "Time to process a range of\t" << d.size() << " elements with std::deque : " << time[1] << " us\n"
		<< "Time to process a range of\t" << v.size() << " elements with std::vector : " << time[0] << " us\n";
}
