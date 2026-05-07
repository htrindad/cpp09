/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 06:01:05 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/07 11:36:05 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

inline char	*smallString(const std::string &original, const int &s, const int &i)
{
	std::string	tmp;
	char		*ret;

	tmp = original.substr(s, i - s);
	ret = new char[tmp.length() + 1];
	std::strcpy(ret, tmp.c_str());
	return ret;
}

inline char	**split(char const *str, char const &del)
{
	int		t;
	int		s;
	int		i;
	int		l;
	char		**ptr;
	std::string	ss(str);

	if (str == NULL)
		throw std::runtime_error("Error: Malloc failure");
	t = 0;
	for (std::size_t j = 0; str[j]; j++)
	{
		if (str[j] != del)
		{
			t++;
			while (str[j + 1] && str[j] != del)
				j++;
		}
	}
	ptr = new char *[t + 1];
	if (ptr == NULL)
		throw std::runtime_error("Error: Malloc failure");
	i = 0;
	l = 0;
	while (str[i])
	{
		while (str[i] == del && str[i])
			i++;
		if (str[i] != del && str[i])
		{
			s = i;
			while (str[i] && str[i] != del)
				i++;
			ptr[l++] = smallString(ss, s, i);
		}
	}
	ptr[l] = NULL;
	return ptr;
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (std::cerr << "Not enough args\n", -1);
	try
	{
		if (ac == 2)
			av = split(av[1], ' ');
		PmergeMe::mis(av, ac);
		if (ac == 2)
		{
			for (std::size_t i = 0; av[i]; i++)
				delete[] av[i];
			delete[] av;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}
