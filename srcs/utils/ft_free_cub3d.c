/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:21:49 by ifeelbored        #+#    #+#             */
/*   Updated: 2022/04/03 05:16:18 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_mlx(t_cub3d *cub3d)
{
	if (cub3d)
	return ;
}

void	ft_free_images(t_images *images)
{
	if (images)
	return ;
}

void	ft_free_player(t_player *player)
{
	if (player)
	return ;
}

void	ft_free_info(t_info *info)
{
	if (info)
	{
		if (info->no)
			free(info->no);
		if (info->so)
			free(info->so);
		if (info->we)
			free(info->we);
		if (info->ea)
			free(info->ea);
		if (info->c)
			free(info->c);
		if (info->f)
			free(info->f);
		free(info);
	}
	return ;
}

void	ft_free_map(char **map)
{
	if (map)
		ft_free_strarray(map);
	return ;
}

void	ft_free_cub3d(t_cub3d *cub3d)
{
	if (cub3d)
	{
		ft_free_map(cub3d->map);
		ft_free_info(cub3d->info);
		ft_free_player(cub3d->plr);
		ft_free_images(cub3d->images);
		ft_free_mlx(cub3d);
	}
	return ;
}
