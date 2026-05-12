/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 03:55:06 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/12 20:30:05 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

class RPN
{
	private:
		RPN();
		~RPN();
		RPN(const RPN &ref);
		RPN &operator=(const RPN &ref);
	public:
		static void solver(char const *av);
};
