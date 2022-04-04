/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifeelbored <ifeelbored@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:50:11 by jahuang           #+#    #+#             */
/*   Updated: 2022/04/03 23:46:35 by ifeelbored       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_my_img	*ft_create_tile(t_cub3d *cub3d, unsigned int color, int size)
{
	t_my_img	*img_holder;
	int			i;
	int			j;
	char		*pixel;

	img_holder = malloc(sizeof(t_my_img));
	img_holder->img_ptr = mlx_new_image(cub3d->mlx_ptr, size, size);
	img_holder->img_addr = mlx_get_data_addr(img_holder->img_ptr, \
		&(img_holder->bpp), &(img_holder->size), &(img_holder->endian));
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel = img_holder->img_addr + \
				(i * img_holder->size) + j * (img_holder->bpp / 8);
			ft_memcpy(pixel, &color, sizeof(unsigned int));
			j++;
		}
		i++;
	}
	return (img_holder);
}

void	ft_minimap_lp(t_cub3d *cub, t_my_img *map, t_my_img *floor, int i)
{
	int	j;

	j = -1;
	while (++j < (int)ft_strlen((cub->map)[i]))
	{
		if (cub->map[i][j] == '1')
		{
			mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, map->img_ptr, \
				j * 10 + 20, i * 10 + 20);
		}
		if (cub->map[i][j] == '0' || cub->map[i][j] == 'W' || \
			cub->map[i][j] == 'E' || cub->map[i][j] == 'N' || \
			cub->map[i][j] == 'S')
		{
			mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, floor->img_ptr, \
				j * 10 + 20, i * 10 + 20);
		}
	}
}

int	ft_print_minimap(t_cub3d *cub, t_images *ig)
{
	int			i;

	if (!ig->minimp)
		ig->minimp = ft_create_tile(cub, 0x00AAAAAA, 10);
	if (!ig->plr)
		ig->plr = ft_create_tile(cub, 0x009F0000, 5);
	if (!ig->dir)
		ig->dir = ft_create_tile(cub, 0x009F00FF, 5);
	if (!ig->flr)
		ig->flr = ft_create_tile(cub, 0x00000000, 10);
	i = 0;
	while (i < ft_arraylen(cub->map))
	{
		ft_minimap_lp(cub, ig->minimp, ig->flr, i);
		i++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, ig->plr->img_ptr, \
		cub->plr->p_y * 10 + 20 - 2, cub->plr->p_x * 10 + 20 - 2);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, ig->dir->img_ptr, \
		(cub->plr->p_y + cub->plr->d_y) * 10 + 20 - 2, \
		(cub->plr->p_x + cub->plr->d_x) * 10 + 20 - 2);
	return (0);
}

int	ft_run_cub3d(t_cub3d *cub3d)
{
	if (!cub3d->mlx_ptr)
		return (ERR_MLX);
	cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, S_W, S_H,
			"cub3d");
	if (!cub3d->win_ptr)
		return (ERR_MLX);
	cub3d->imgs->canvas = NULL;
	cub3d->imgs->minimp = NULL;
	cub3d->imgs->plr = NULL;
	cub3d->imgs->dir = NULL;
	cub3d->imgs->flr = NULL;
	ft_print_canvas(cub3d);
	ft_print_minimap(cub3d, cub3d->imgs);
	mlx_hook(cub3d->win_ptr, 2, 1l << 0, &ft_key_event, cub3d);
	mlx_hook(cub3d->win_ptr, 17, 1l << 0, &ft_close, cub3d);
	mlx_loop(cub3d->mlx_ptr);
	return (0);
}

int	main(int ac, char **av)
{
	int		ret;
	t_cub3d	*cub3d;

	ret = -1;
	if (ac != 2)
		return (ERR_ARGS);
	ret = ft_parser(av[1], &cub3d);
	if (ret != 0)
		return (ft_return(ret, cub3d));
	cub3d->imgs = malloc(sizeof(t_images));
	ft_print_struct(cub3d);
	cub3d->mlx_ptr = mlx_init();
	if (init_texture(cub3d))
		return (ft_return(ERR_INFO, cub3d));
	if (ft_run_cub3d(cub3d))
		return (ft_return(ERR_INFO, cub3d));
	return (0);
}
