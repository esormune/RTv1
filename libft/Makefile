# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/11 10:42:46 by eniini            #+#    #+#              #
#    Updated: 2022/02/18 22:25:04 by esormune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
PRINTF	=	libftprintf.a

# compiler
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

# header directory
INCDIR	=	includes

# source directories
SRCDIRS	=	array_utils: \
		char_utils: \
		llist_utils: \
		math: \
		mem_utils: \
		misc: \
		print: \
		string_utils: \
		type_conversion: \
PFTDIR	=	ft_printf:
# vpath
VPATH	+=	$(addprefix srcs/,$(SRCDIRS))
VPATH	+=	$(addprefix srcs/,$(PFTDIR))
# source files
SRCS	=	ft_free_arr.c \
		ft_arr_size.c \
		ft_is_neg_minus.c \
		ft_is_neg.c \
		ft_is_whitespace.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstpush.c \
		ft_lstsize.c \
		ft_abs.c \
		ft_avg.c \
		ft_brounding.c \
		ft_brounding_ld.c \
		ft_c_add.c \
		ft_c_divide.c \
		ft_c_multiply.c \
		ft_c_sq.c \
		ft_c_sub.c \
		ft_clamp_d.c \
		ft_max.c \
		ft_min.c \
		ft_neg_pow_ten.c \
		ft_numlength_neg.c \
		ft_numlength.c \
		ft_pow.c \
		ft_uintmax_pow.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_colour.c \
		ft_getout.c \
		ft_rand.c \
		get_next_line.c \
		ft_print_array.c \
		ft_print_bits.c \
		ft_print_hex.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putnstr_fd.c \
		ft_putnstr.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_implode.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower_str.c \
		ft_toupper_str.c \
		ft_atof.c \
		ft_atoi_base.c \
		ft_atoi_max.c \
		ft_atoi_sizet.c \
		ft_atoi.c \
		ft_flitoa.c \
		ft_flitoa_ldouble.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_itoa_exp.c \
		ft_itoa_intmax_base.c \
		ft_itoa_llong_base.c \
		ft_itoa_size_t_base.c \
		ft_itoa_uintmax_base.c \
		ft_itoa_ulong_base.c 

PFTSRCS	=	ft_parser.c \
		ft_printf.c \
		ft_split.c \
		ft_convert.c \
		ft_specs.c \
		ft_next.c \
		ft_sprintf.c \
		ft_dprintf.c \
		ft_conflicts.c \
		ft_char.c \
		ft_string.c \
		ft_octal.c \
		ft_hex.c \
		ft_int.c \
		ft_exp.c \
		ft_u_int.c \
		ft_pointer.c \
		ft_binary.c \
		ft_float.c \
		ft_percent.c \
		ft_null_string.c \
		ft_init.c \
		ft_rev_split.c \
		ft_width.c \
		ft_nb.c \
		ft_add_neg.c

#object directory
OBJDIR	=	objs
PFTOBJDIR =	pftobjs

#object files
OBJS	=	$(patsubst %,$(OBJDIR)/%,$(SRCS:.c=.o))
PFTOBJS	=	$(patsubst %,$(PFTOBJDIR)/%,$(PFTSRCS:.c=.o))

#colors
CYAN	=	\033[0;36m
PURPLE	=	\033[1;35m
NC	=	\033[0m
#clear line, move backwards x columns
RESET	=	\033[1K\033[100D

.PHONY: all clean fclean re

#compiles all libraries together
all: $(NAME) $(PRINTF)
	@ar -rc $(NAME) $(PFTOBJS) $(GFXOBJS)
	@printf "$(CYAN)$(RESET)[libft] finished!$(NC)\n"

#link obj files
$(OBJDIR)/%.o:%.c
	@mkdir -p $(OBJDIR)
	@printf "$(CYAN)."
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR)

$(PFTOBJDIR)/%.o:%.c
	@mkdir -p $(PFTOBJDIR)
	@printf "$(PURPLE)."
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCDIR)

#compile each library separately
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(CYAN)$(RESET)[libft] library built!$(NC)\n"

$(PRINTF): $(PFTOBJS)
	@ar rcs $(PRINTF) $(PFTOBJS)
	@printf "$(PURPLE)$(RESET)[ftprintf] library built!$(NC)\n"

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(PFTOBJDIR)
	@printf "$(CYAN)[libft] object files removed$(NC)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(PRINTF)
	@printf "$(CYAN)[libft] static libraries removed$(NC)\n"

re: fclean all
