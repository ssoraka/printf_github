/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:24:30 by ssoraka           #+#    #+#             */
/*   Updated: 2019/05/05 17:24:30 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include "struct.h"
# include "enum.h"
# include <stdarg.h>
# define DEFAULT 0
# define STAR -1
# define ACC 20

int					ft_printf(char *format, ...);
char				*ft_ltoa_base(long num, int base);
t_prlst				*ft_create_elem(char *data);
t_prlst				*ft_list_push_back(t_prlst **begin_list, char *data);
t_prlst				*ft_str_to_list(char *str);
void				ft_listdel(t_prlst **begin_list);
void				ft_change_type(t_prlst *list);
void				ft_change_spec(t_prlst *list);
void				ft_find_type(t_prlst *list);
void				ft_find_flags(t_prlst *list);
void				ft_find_width(t_prlst *list);
void				ft_find_accuracy(t_prlst *list);
void				ft_find_spec(t_prlst *list);
void				ft_listiter(t_prlst *lst, void (*f)(t_prlst *elem));
void				ft_change_lists(t_prlst *list);
void				ft_get_number_of_arg(t_prlst *list);
int					ft_arg_count(int n, int write);
void				ft_list_push_back_type_num
					(t_prlst **begin_list, char type, int num, int spec);
t_prlst				*ft_return_list_of_args(t_prlst	*list);
long				ft_return_arg(va_list ap, int arg_numb, t_prlst *l_args);
long double			ft_return_argf(va_list ap, int arg_numb, t_prlst *l_args);
void				ft_get_stars(va_list ap, t_prlst *list, t_prlst *args);
char				*ft_chrtoa(unsigned int chr, int spec);
char				*ft_ptrtoa(long num);
char				*ft_wchrtoa(char *str, int spec);
void				ft_return_chrtoa_to_answer(t_prlst *list);
void				ft_return_ltoa_to_answer(t_prlst *list);
void				ft_return_ldtoa_to_answer(t_prlst *list);
void				ft_return_oxtoa_to_answer(t_prlst *list);
void				ft_return_oxtoa_to_answer(t_prlst *list);
char				*ft_num_stretch_spaces(char *str, int width, int minus);
char				*ft_num_get_space(char *str, int space);
char				*ft_num_get_znak(char *str, int plus);
char				*ft_num_get_cage(char *str, int cage, char type, int accur);
char				*ft_num_get_cage_float(char *str, int cage, char type);
char				*ft_num_stretch_zero
					(char *str, int width, int zero, int accur);
int					ft_put_answer(t_prlst *list);
char				*ft_cut_str(char *str, int accur, int type, int spec);
void				ft_change_flags(t_prlst *list);
void				ft_apply_flags_to_answer(t_prlst *list);
void				ft_replace(char *str, char *repls, int num);
void				ft_give_color(t_prlst *list);
int					ft_size_from_spec(int spec, int ldfloat);
void				ft_return_btoa_to_answer(t_prlst *list);
void				ft_create_answers(t_prlst *list);
int					ft_next_utf8(const char *str, int accuracy);
char				*ft_ldtoa_e(long double ld, int accuracy, int type_g);
char				*ft_ldtoa_f(long double ld, int accuracy, int type_g);
char				*ft_ldtoa_g(long double ld, int accuracy);
void				ft_summ_str_str(char *answer, char *str, int shift);
void				ft_division_str_num(char *str, int n, int accuracy);
void				ft_natural_part(t_plist	*p);
void				ft_decimal_part(t_plist	*p, int accuracy);
t_plist				*ft_create_param(int accuracy, long double ld);
void				ft_change_param_ld(long double ld, t_plist	*p);
int					ft_power_of_num(long double ld);
char				*ft_ldtoa_e_shift_point(char *str, int power, int accuracy);
void				ft_round_str_num(char **answer, int accuracy);
void				ft_round_up(char *str, char *accuracy);
void				ft_increase_power(char *str, int *power);
void				ft_clear_null(char *str, int type_g);
char				*ft_ldtoa_e_adde(char *str, int power);
char				*ft_plug(char *str, int accuracy);

#endif
