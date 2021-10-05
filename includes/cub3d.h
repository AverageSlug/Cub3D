/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:00:46 by nlaurids          #+#    #+#             */
/*   Updated: 2021/10/05 18:03:31 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include <math.h>
# include "./../minilibx/mlx.h"

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_sprite {
	double		spx;
	double		spy;
	t_data		spt;
}				t_sprite;

typedef struct	s_conf {
	char		**realine;
	int			temp[9];
	int			xres;
	int			yres;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*s;
	int			f[3];
	int			c[3];
	char		**map;
	int			l;
	char		msp;
	double		mspx;
	double		mspy;
	int			spn;
	t_sprite	*sprs;
	char		ac[256];
	int			mxs[3];
}				t_conf;

typedef struct	s_sdir {
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		plnx;
	double		plny;
	double		camx;
	double		rayx;
	double		rayy;
	int			mpx;
	int			mpy;
	double		sidx;
	double		sidy;
	double		delx;
	double		dely;
	double		pwd;
	int			stpx;
	int			stpy;
	int			hit;
	int			side;
	int			lh;
	int			dsta;
	int			dend;
}				t_sdir;

typedef struct	s_imgd {
	void		*notex;
	int			notew;
	int			noteh;
	t_data		nodat;
	void		*sotex;
	int			sotew;
	int			soteh;
	t_data		sodat;
	void		*wetex;
	int			wetew;
	int			weteh;
	t_data		wedat;
	void		*eatex;
	int			eatew;
	int			eateh;
	t_data		eadat;
	void		*stex;
	int			stew;
	int			steh;
	t_data		sdat;
}				t_imgd;

typedef struct	s_key {
	int			mv_hor;
	int			mv_ver;
	int			look;
}				t_key;

typedef struct	s_tex {
	double		walx;
	int			texx;
	int			texy;
	int			texw;
	int			texh;
	double		tstp;
	double		tpos;
	char		*tex;
	t_data		texd;
}				t_tex;

typedef struct	s_spriterc{
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			sprscrx;
	int			sprh;
	int			dstay;
	int			dendy;
	int			sprw;
	int			dstax;
	int			dendx;
	int			stripe;
	int			stexx;
	int			stexy;
}				t_spriterc;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	int			hold;
	int			a[2];
	int			save;
	double		mov;
	double		rot;
	double		plux;
	double		pluy;
	t_data		img;
	t_imgd		imgd;
	t_sdir		sdir;
	t_conf		config;
	t_key		key;
	t_tex		tex;
	t_spriterc	spriterc;
}				t_vars;

int				main(int argc, char **argv);
void			cub3d_parse(t_conf *config);
void			cub3d_parse_no(t_conf *config);
void			cub3d_parse_so(t_conf *config);
void			cub3d_parse_we(t_conf *config);
void			cub3d_parse_ea(t_conf *config);
void			cub3d_parse_s(t_conf *config);
void			cub3d_parse_f(t_conf *config);
void			cub3d_parse_c(t_conf *config);
void			cub3d_parse_map(t_conf *config, int fd);
int				cub3d_parse_map_a(t_conf *config, int i, int j);
void			cub3d_set_ac(char ac[256], char tile, int j, int mxs);
void			cub3d_set_mxs(int mxs[3], char **map, int i);
char			**cub3d_split(char const *s, char c);
int				cub3d_atoi(const char *str);
int				cub3d_realloc(char **tem, char *line, int size, t_conf *config);
char			*cub3d_strdup(const char *s1);
void			freerealine(char **realine);
int				ft_strlen(const char *s);
int				create_trgb(int t, int r, int g, int b);
int				is_digit(char *c);
int				freeturn(char **data, int ret);
void			freeall(t_conf *config);
void			my_mlx_pixel_put(t_data *img, int x, int y, int color);
void			cub3d_mlx(t_vars *vars);
void			cub3d_set(t_vars *vars);
void			cub3d_fc(t_vars vars, int a[2]);
int				exitcub3d(t_vars *vars);
int				cub3d_key(t_vars *vars);
int				cub3d_key_press(int keycode, t_vars *vars);
int				cub3d_key_release(int keycode, t_vars *vars);
void			mv_hor(t_vars *vars);
void			mv_ver(t_vars *vars);
void			look(t_vars *vars);
void			cub3d_raycast(t_vars *vars);
void			cub3d_setdir(t_vars *vars);
void			cub3d_setdir2(t_vars *vars);
void			cub3d_raycasting(t_vars *vars);
void			cub3d_verline(t_vars *vars, int i);
void			cub3d_texside(t_vars *vars);
int				tex_color_get(t_data *data, int x, int y);
void			cub3d_spriterc(t_vars *vars, double zbuf[vars->config.xres]);
void			save_bitmap(const char *file_name, t_vars *vars);

#endif
