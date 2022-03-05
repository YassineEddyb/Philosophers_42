/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yed-dyb <yed-dyb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:17:08 by yed-dyb           #+#    #+#             */
/*   Updated: 2022/02/20 12:07:38 by yed-dyb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	int_check(int nb, int count, int sign)
{
	if (count > 19)
	{
		if (sign == 1)
			return (-1);
		else if (sign == -1)
			return (0);
	}
	return (nb * sign);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;
	int	i;
	int	count;

	i = 0;
	sign = 1;
	nbr = 0;
	count = 0;
	while ((str[i] > 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (str[i] - '0') + (nbr * 10);
		i++;
		count++;
	}
	return (int_check(nbr, count, sign));
}
