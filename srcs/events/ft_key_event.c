#include "cub3d.h"

int clean_screen(t_cub3d *cub3d)
{
	t_my_img	*dark_img;
	int i;
	int j;

	dark_img = ft_create_tile(cub3d, 0x00000000, 10);
	i = 0;
	while (i < ft_arraylen(cub3d->map))
	{
		j = 0;
		while (j < (int)ft_strlen((cub3d->map)[i]))
		{

			mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr, dark_img->img_ptr, j * 10 + 20, i * 10 + 20 );
			j++;
		}
		i++;
	}
	return (0);
}
int	ft_move_player(int key, t_cub3d *cub3d)
{
	float	player_to_x;
	float	player_to_y;


	if (key == XK_W)
	{
		printf("player x: %f, y: %f\n", cub3d->plr->p_x, cub3d->plr->p_y);
		player_to_x = cub3d->plr->p_x + cub3d->plr->d_x * MOVE_DIST;
		player_to_y = cub3d->plr->p_y + cub3d->plr->d_y * MOVE_DIST;
		if (cub3d->map[(int)player_to_x][(int)player_to_y] != '1')
		{
			cub3d->map[(int)cub3d->plr->p_x][(int)cub3d->plr->p_y] = '0';
			cub3d->plr->p_x = player_to_x;
			cub3d->plr->p_y = player_to_y;
			cub3d->map[(int)player_to_x][(int)player_to_y] = 'W';
		}
               else if (cub3d->map[(int)cub3d->plr->p_x][(int)player_to_y] != '1')
                       cub3d->plr->p_y = player_to_y;
               else if (cub3d->map[(int)player_to_x][(int)cub3d->plr->p_y] != '1')
                       cub3d->plr->p_x = player_to_x;
	}
	if (key == XK_S)
	{
		player_to_x = cub3d->plr->p_x - cub3d->plr->d_x * MOVE_DIST;
		player_to_y = cub3d->plr->p_y - cub3d->plr->d_y * MOVE_DIST;
		if (cub3d->map[(int)player_to_x][(int)player_to_y] != '1')
		{
			cub3d->map[(int)cub3d->plr->p_x][(int)cub3d->plr->p_y] = '0';
			cub3d->plr->p_x = player_to_x;
			cub3d->plr->p_y = player_to_y;
			cub3d->map[(int)player_to_x][(int)player_to_y] = 'W';
		}
               else if (cub3d->map[(int)cub3d->plr->p_x][(int)player_to_y] != '1')
                       cub3d->plr->p_y = player_to_y;
               else if (cub3d->map[(int)player_to_x][(int)cub3d->plr->p_y] != '1')
                       cub3d->plr->p_x = player_to_x;
	}
	if (key == XK_A)
	{
		player_to_x = cub3d->plr->p_x - cub3d->plr->d_y * MOVE_DIST;
		player_to_y = cub3d->plr->p_y + cub3d->plr->d_x * MOVE_DIST;
		if (cub3d->map[(int)player_to_x][(int)player_to_y] != '1')
		{
			cub3d->map[(int)cub3d->plr->p_x][(int)cub3d->plr->p_y] = '0';
			cub3d->plr->p_x = player_to_x;
			cub3d->plr->p_y = player_to_y;
			cub3d->map[(int)player_to_x][(int)player_to_y] = 'W';
		}
               else if (cub3d->map[(int)cub3d->plr->p_x][(int)player_to_y] != '1')
                       cub3d->plr->p_y = player_to_y;
               else if (cub3d->map[(int)player_to_x][(int)cub3d->plr->p_y] != '1')
                       cub3d->plr->p_x = player_to_x;
	}
	if (key == XK_D)
	{
		player_to_x = cub3d->plr->p_x + cub3d->plr->d_y * MOVE_DIST;
		player_to_y = cub3d->plr->p_y - cub3d->plr->d_x * MOVE_DIST;
		if (cub3d->map[(int)player_to_x][(int)player_to_y] != '1')
		{
			cub3d->map[(int)cub3d->plr->p_x][(int)cub3d->plr->p_y] = '0';
			cub3d->plr->p_x = player_to_x;
			cub3d->plr->p_y = player_to_y;
			cub3d->map[(int)player_to_x][(int)player_to_y] = 'W';
		}
               else if (cub3d->map[(int)cub3d->plr->p_x][(int)player_to_y] != '1')
                       cub3d->plr->p_y = player_to_y;
               else if (cub3d->map[(int)player_to_x][(int)cub3d->plr->p_y] != '1')
                       cub3d->plr->p_x = player_to_x;
	}
	ft_print_canvas(cub3d);
	ft_print_minimap(cub3d);
	return (0);
}


int	ft_rotate_player(t_cub3d *cub3d, int key)
{
	double oldDirX;
	double oldPlaneX;

	if (key == XK_LEFT)
	{
		oldDirX = cub3d->plr->d_x;
		cub3d->plr->d_x = cub3d->plr->d_x * cos(ROT_SPEED) - cub3d->plr->d_y * sin(ROT_SPEED);
		cub3d->plr->d_y = oldDirX * sin(ROT_SPEED) + cub3d->plr->d_y * cos(ROT_SPEED);
		oldPlaneX = cub3d->plr->pl_x;
		cub3d->plr->pl_x = cub3d->plr->pl_x * cos(ROT_SPEED) - cub3d->plr->pl_y * sin(ROT_SPEED);
		cub3d->plr->pl_y = oldPlaneX * sin(ROT_SPEED) + cub3d->plr->pl_y * cos(ROT_SPEED);
	}
	if (key == XK_RIGHT)
	{
		oldDirX = cub3d->plr->d_x;
		cub3d->plr->d_x = cub3d->plr->d_x * cos(-ROT_SPEED) - cub3d->plr->d_y * sin(-ROT_SPEED);
		cub3d->plr->d_y = oldDirX * sin(-ROT_SPEED) + cub3d->plr->d_y * cos(-ROT_SPEED);
		oldPlaneX = cub3d->plr->pl_x;
		cub3d->plr->pl_x = cub3d->plr->pl_x * cos(-ROT_SPEED) - cub3d->plr->pl_y * sin(-ROT_SPEED);
		cub3d->plr->pl_y = oldPlaneX * sin(-ROT_SPEED) + cub3d->plr->pl_y * cos(-ROT_SPEED);
	}
	ft_print_canvas(cub3d);
	ft_print_minimap(cub3d);
	return (0);
}


int	ft_key_event(int key, t_cub3d *cub3d)
{

	(void)cub3d;
	if (key == XK_ESCAPE)
		ft_close(cub3d);
	if (key == XK_A || key == XK_D || key == XK_W || key == XK_S)
		ft_move_player(key, cub3d);
	if (key == XK_LEFT || key == XK_RIGHT)
	{
		ft_rotate_player(cub3d, key);
		// ft_putstr_fd("rotate: ", 1);
		// ft_putnbr_fd(key, 1);
	}
	return (0);
}
