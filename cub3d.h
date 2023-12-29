/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:39:39 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:37:20 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./mlx/mlx.h"

# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

# define TILE_SIZE 32
# define RADIUS 4
# define MINIMAP_SCALE 0.2
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 200
# define MOUSE_ROT_SPEED 0.0007
# define WIDTH 1200
# define HEIGHT 720

typedef struct s_im0g
{
	void	*img;
	void	*addr;
	int		*addr_tex;
	int		tex_x;
	int		tex_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_cub3d
{
	t_img	img;
	t_img	img_n;
	t_img	img_s;
	t_img	img_w;
	t_img	img_e;
	void	*mlx;
	void	*mlx_win;
	char	**map;
	char	*tmp;
	int		width;
	int		height;
	char	*north;
	char	*soulth;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
	float	p_x;
	float	p_y;
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	rot_right;
	bool	rot_left;
	bool	mouse_show;
	float	angle;
	int		walk_dir;
	int		turn_dir;
	float	move_speed;
	float	move_step;
	float	rot_speed;
	float	fov_angle;
	int		nbr_rays;
	int		wall_strip;
	float	ray_angle;
	float	wallhitx;
	float	wallhity;
	float	distance;
	bool	hit_vertical;
	float	wall_height;
	float	end;
	float	begin;
	int		mouse_x;
	int		mouse_y;
	bool	center_mouse;
}	t_cub3d;

typedef struct s_ray
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	bool	ray_facing_down;
	bool	ray_facing_right;
	bool	found_horz_wall;
	float	wall_hit_horzx;
	float	wall_hit_horzy;
	bool	found_vert_wall;
	float	wall_hit_vertx;
	float	wall_hit_verty;
	float	horz_distance;
	float	vert_distance;
	float	y;
	float	x;
}	t_ray;

typedef struct s_line
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	dx;
	float	dy;
	float	step;
}	t_line;

int		ft_strcmp(char *s1, char *s2);
void	empty_line(char *line);
int		open_file(char *file);
void	check_file_name(char *file);
char	*ft_strtrim_line(char const *s1);
void	print_error(char *str);
void	read_map(t_cub3d *data, char *file);
void	check_variable(t_cub3d *data, char *line);
void	stock_var(t_cub3d *data, char *key, char *value);
void	floor_ceiling(t_cub3d *data, char *value, char *key);
void	check_floor_ceiling_var(int *var, char *value);
void	open_tex_file(char *value, char *key);
void	check_comma(char *value);
void	free_str(char **str);
int		atoi_util(char *str);
void	split_map(int *var, char *value);
void	stock_map(t_cub3d *data);
void	error(t_cub3d *data, char *str);
void	valid_content(t_cub3d *data);
void	print_error(char *str);
int		my_strlen(char *s);
void	map_close(t_cub3d *data);
void	is_wall(char *str, t_cub3d *data);
void	check_space(t_cub3d *data);
void	check_player(t_cub3d *data);
void	check_map_lenght(t_cub3d *data);
void	is_space(t_cub3d *data, char *str, int *i);
void	valid_map(t_cub3d *data);
void	load_game(t_cub3d *data);
void	draw_player(t_cub3d *data);
void	draw_map(t_cub3d *data);
void	put_color(t_cub3d *data, int x, int y, int color);
void	my_pixel_put(t_cub3d *data, int x, int y, int color);
int		keyrelease(int keycode, t_cub3d *data);
int		keypressed(int keycode, t_cub3d *data);
int		move(t_cub3d *data);
void	draw(t_cub3d *data);
void	down(t_cub3d *data);
void	left(t_cub3d *data);
void	right(t_cub3d *data);
void	rot_left(t_cub3d *data);
void	rot_right(t_cub3d *data);
int		check_position_p(t_cub3d *data, double x, double y);
void	cast(t_cub3d *data, int column);
void	normalize_angle(t_cub3d *data);
int		has_wall(t_cub3d *data, float x, float y);
void	check_distance(t_cub3d *data, t_ray *ray);
void	vert_intersection(t_cub3d *data, t_ray *ray);
void	horz_intersection(t_cub3d *data, t_ray *ray);
void	ray_direction(t_cub3d *data, t_ray *ray);
int		has_wall(t_cub3d *data, float x, float y);
float	distance_value(float x1, float y1, float x2, float y2);
void	my_pixel_put_floor(t_cub3d *data, int x, int y, int *color);
t_img	get_img(t_cub3d *data, t_ray ray);
void	render_projected_walls(t_cub3d *data, int column, t_ray	ray);
void	put_wall_color(t_cub3d *data, t_ray ray, int a, int x);
void	draw_minimap(t_cub3d *data);
void	draw_player(t_cub3d *data);
void	set_tex(t_cub3d *data, t_img *tex, char *str);
void	center_mouse(t_cub3d *data);
int		mouse_hook(int x, int y, t_cub3d *data);
int		get_color(t_cub3d *data, int j, int i);
void	draw_line(t_cub3d *data, t_line *line);
int		cross_click(t_cub3d	*data);

#endif