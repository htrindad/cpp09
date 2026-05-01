/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 03:55:06 by htrindad          #+#    #+#             */
/*   Updated: 2026/05/01 04:09:52 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class RPN
{
	private:
		std::string	str;
	public:
		RPN();
		~RPN();
		RPN(const RPN &ref);
		RPN &operator=(const RPN &ref);
		RPN(char const *str); // The right way
};
