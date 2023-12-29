/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:15:06 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 18:06:31 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_tex(t_cub3d *data, t_img *tex, char *str)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, str,
			&tex->tex_x, &tex->tex_y);
	tex->addr_tex = (int *)mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length,
			&tex->endian);
	if (!tex->img || !tex->addr_tex)
	{
		free(data->north);
		free(data->soulth);
		free(data->west);
		free(data->east);
		free_str(data->map);
		exit(1);
	}
}
