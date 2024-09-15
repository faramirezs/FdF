/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:33:42 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 11:33:56 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/fdf.h"

int main(int ac, char **av)
{
	t_fdf fdf;
	if (ac != 2)
		return (-1);
	ft_memset(&fdf, 0, sizeof(t_fdf));
	boot_fdf(&fdf, *(av + 1));
	init_mlx(&fdf);
	return (0);
}
