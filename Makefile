# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hello <hello@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/14 05:25:36 by hello             #+#    #+#              #
#    Updated: 2022/07/14 05:38:47 by hello            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CC_FLAG = -Wextra -Werror -Wall -g

src = 	get_next_line.c			\
		get_next_line_utils.c	\
		get_next_line.h \
		#main.c

src_b = get_next_line_bonus.c			\
		get_next_line_utils_bonus.c			\
		get_next_line_bonus.h 				\
		main.c

all :
	$(CC) $(CC_FLAG) $(src)

b	:
	$(CC) $(CC_FLAG) $(src_b)
