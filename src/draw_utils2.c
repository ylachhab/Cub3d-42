/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:15:06 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/30 13:20:21 by ylachhab         ###   ########.fr       */
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
		error(data, "Error in image\n");
}
