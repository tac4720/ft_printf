#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putptr(void *ptr);
int	ft_putint(int n);
int	ft_putuint(unsigned int n);
int ft_puthex_complement(int n);
int ft_putHex_complement(int n);
int	ft_puthex(long n);
int	ft_putHex(long n);
int	is_fo(int c);
int	ft_select(char type, va_list args);
int ft_printf(const char *format, ...);