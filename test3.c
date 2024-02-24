#include <stdint.h>

typedef struct s_dinf
{
	uint8_t		sign;
	uint32_t	exponent;
	uint64_t	frac;

}s_dinf;

void	parse_double(double num)
{
	s_dinf	dinf;
	uint64_t	mem;

	memcpy(&mem, &num, sizeof(double));
	dinf.sign = mem >> 63;
	dinf.exponent = mem >> 52;
	dinf.frac = mem >> 
}