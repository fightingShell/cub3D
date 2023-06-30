/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:01:20 by yejinkim          #+#    #+#             */
/*   Updated: 2023/06/30 21:12:04 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

# define BUFFER_SIZE 42
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_RO_L 123
# define KEY_RO_R 124
# define KEY_ESC 53
# define KEY_EXIT 17
# define WIDTH 640
# define HEIGHT 480
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define K_ESC 53
# define N 1
# define S 2
# define E 3
# define W 4
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

char worldMap[WIDTH][HEIGHT]=
{
	{1,1,1,1,1,1},
	{1,0,0,1,0,1},
	{1,0,1,0,0,1},
	{1,1,0,0,'N'},
	{1,1,1,1,1,1},
}; // test용

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	int		endian;
	int		bpp;
	int		line_size;
	int		*data;
	int		tex_buf[64][64];
}	t_img;

typedef struct s_data
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3]; // rgb color int형으로 변환. 이거 그대로 사용하면 됨. -> r,g,b 따로 따로 담아줘야될것 같오~~~
	int		ceil[3]; // 위와 동일 ! -> 얘도!!!
}	t_data; // ㅋㅋㅋ 확인 완료했숩니당 ㅇㅖ키미 맴~~ ㅎㅋ

typedef struct s_mapcamera
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perwalldist;
	int		line_height;
	int		start_point;
	int		end_point;
	int		step_x;
	int		step_y;
	int		wall_x;
	int		tex_x;
	int		tex_y;
	int		tex_pos;
	int		hit;
	int		side;
	double	step;
}	t_mapcamera;

typedef struct s_info
{
	char	**map;
	char	start_dir; //예지나 처음 플레이어 방향만 여기다가 담아줭 A,S,D,W 중에 하나!
	t_data	*data;
	t_img	img[4];
	void	*mlx;
	void	*win;
	double	pos_x; // 초기 위치 x좌표 담아줭 !!
	double	pos_y; // 초기 위치 y좌표 담아줭 !!
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	movespeed;
	double	rotspeed;
	int		buf[WIDTH][HEIGHT];
}	t_info;

// main.c
void	print_error(void);

// parsing/parsing.c
void	parsing(t_info *info, char *file);
void	init_data(t_data *data);
// parsing/parse_data.c
int		parse_data(t_data *data, char *line);
void	check_data(t_data *data);
char	*parse_texture(char *var, char *str);
int		parse_color(int var, char *str);
// parsing/parse_map.c
void	parse_map(char **map, char *line);
void	check_map(char **map);
// parsing/utils.c
char	*remove_space(char *str);
char	*remove_space_back(char *str);
int		ft_atoi_255(char *str);
int		rgb_to_int(char **str);
// parsing/get_next_line.c
char	*get_next_line(int fd);

// raycasting/raycasting.c
int		raycasting(t_info *info);
void	wall_x_or_y(t_info *info, t_mapcamera *mapcam);
void	set_moving_dir(t_info *info, t_mapcamera *mapcam);
void	set_mapcamera(t_info *info, t_mapcamera *mapcam, int i);
// raycasting/draw_map.c
void	draw_floor_ceil(t_info *info);
void	draw_map_texture(t_info *info, t_mapcamera *mapcam, int i, char dir);
void	draw_mapcamera(t_info *info, t_mapcamera *mapcam, int i);
void	draw_map(t_info *info);
// raycasting/keypress.c
void	keypress_wd(int keycode, t_info *info);
void	keypress_as(int keycode, t_info *info);
void	keypress_lr(int keycode, t_info *info, int ori_plane_x, int ori_dir_x);
int		key_press(int keycode, t_info *info);
// raycasting/set_info.c
void	start_dir_ns(t_info *info);
void	start_dir_ew(t_info *info);
void	init_buf(t_info *info);
void	set_info(t_info *info);
// raycasting/set_texture.c
void	set_texture_util(t_info *info, int dir, char *path);
void	set_texture(t_info *info);

#endif