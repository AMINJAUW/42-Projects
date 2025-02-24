/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:41:25 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/23 11:42:42 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# ifndef SIZE_MAX
#  define SIZE_MAX 65535
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE 
#  define BUFFER_SIZE 0
# endif

# ifndef LC_NUMERIC
#  define LC_NUMERIC 56
# endif

# define HEX_MIN "0123456789abcdef"
# define HEX_MAJ "0123456789ABCDEF"
# define FALSE 0
# define TRUE 1
# define SUCCES 0
# define FAIL 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Libft Mandatory */
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoins(size_t str_nbr, ...);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *s, const char *searched, size_t len);
char			*ft_strtrim(char const *s, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

/* Libft Bonus */
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_lstsize(t_list *lst);

/* Libft Personal: Arrays */
int				ft_ar_addone(char ***ar, char *s);
int				ft_ar_delone(char ***ar, size_t index);
int				ft_ar_replace(char **ar, size_t index, char *s);
void			ft_ar_clear(char ***ar);
char			**ft_ar_dup(char **ar);
size_t			ft_ar_len(char **ar);
t_list			*ft_ar_tolist(char **ar);

/* Libft Personal: Others */
size_t			ft_abs(int nbr);
int				ft_sign(int nbr);
int				ft_nb_len(int n);
int				ft_isspace(char c);
size_t			ft_char_count(char *str, char c);
int				ft_in_set_char(char c, char *set);
int				ft_in_set_str(char *s, char **set);

/* Ft_printf */
int				ft_printf(const char *s, ...);
int				ft_convert(va_list list, char key);
int				ft_putchar_value_fd(char c, int fd);
int				ft_putmem_hex_fd(long int n, int fd);
int				ft_putnbr_value_fd(int n, int fd);
int				ft_putstr_value_fd(char *s, int fd);
int				ft_putui_fd(unsigned int n, int fd);
int				ft_putui_hex_fd(unsigned int n, int ltrs, int fd);

/* Ft_fprintf */
int				ft_fprintf(int fd, const char *s, ...);
int				ft_convertfd(va_list list, char key, int fd);

/* Get_next_line */
void			ft_bzero_gnl(void *s, size_t n);
char			*ft_strchr_gnl(const char *s, int c);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
size_t			ft_strlen_gnl(const char *s);
char			*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char			*get_next_line(int fd);

#endif
