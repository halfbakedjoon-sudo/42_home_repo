CC=cc
CCARGS=-Wall -Wextra -Werror

RM=rm
RMARGS=-fr

AR=ar
ARARGS=rcs

MKDIR=mkdir

FILES=	ft_printf		ft_convert	ft_handle_convert	ft_convert_arg1\
		ft_convert_arg2

BFILES=	ft_printf		ft_convert	ft_handle_convert	ft_convert_arg1\
		ft_convert_arg2	ft_utils

MCDIR=srcs/

BCDIR=bonus/

ODIR=objects/
MOFILES=$(FILES:%=$(ODIR)%.o)
BOFILES=$(BFILES:%=$(ODIR)%_bonus.o)

LIBFTDIR=libft/
LIBFTFILE:=libft.a
LIBFTA=$(LIBFTDIR)$(LIBFTFILE)

NAME=libftprintf.a
INCLUDE=includes $(LIBFTDIR) .

$(ODIR)%.o: $(MCDIR)%.c | $(ODIR)
	$(CC) $(CCARGS) $(INCLUDE:%=-I%) -o $@ -c $<

$(ODIR)%_bonus.o: $(BCDIR)%_bonus.c | $(ODIR)
	$(CC) $(CCARGS) $(INCLUDE:%=-I%) -o $@ -c $<

all: $(NAME)

$(NAME): $(LIBFTA) $(MOFILES)
	$(RM) -f $(NAME) $(BOFILES)
	cp $(LIBFTA) $(NAME)
	$(AR) $(ARARGS) $(NAME) $(MOFILES)
	$(RM) -f .bonus

bonus: .bonus

.bonus: $(LIBFTA) $(BOFILES)
	$(RM) -f $(NAME) $(MOFILES)
	cp $(LIBFTA) $(NAME)
	$(AR) $(ARARGS) $(NAME) $(BOFILES)
	touch .bonus

$(LIBFTA):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(RMARGS) $(ODIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(RMARGS) $(NAME) $(BNAME)
	$(RM) -f .bonus
	make -C $(LIBFTDIR) fclean

re: fclean all

$(ODIR):
	$(MKDIR) $(ODIR)

.PHONY: all clean fclean re bonus
