/*
 * Verse routines for big integer operations.
 * Handy in heavy encryption done during connect.
*/

#include <limits.h>

/* ----------------------------------------------------------------------------------------- */

typedef unsigned short	VBigDig;

#define	V_BIGBITS	(CHAR_BIT * sizeof (VBigDig))

/* Use this macro to initialize big number variables, like so:
 * VBigDig BIGNUM(foo, 128), BIGNUM(bar, 256);
 * Creates automatic variables 'foo' of 128 bits, and 'bar' of 256.
 * 
 * Note that 'bits' must be a multiple of V_BIGBITS, completely
 * arbitrary number sizes is not supported by this module.
*/
#define	VBIGNUM(n, bits)	n[1 + (bits / V_BIGBITS)] = { bits / V_BIGBITS }

/* ----------------------------------------------------------------------------------------- */

/* Import/export numbers from raw bits. The number x must have been allocated
 * with the desired number of bits to read/write.
*/
extern void	v_bignum_raw_import(VBigDig *x, const void *bits);
extern void	v_bignum_raw_export(const VBigDig *x, void *bits);

/* Initializers. */
extern void	v_bignum_set_zero(VBigDig *x);
extern void	v_bignum_set_one(VBigDig *x);
extern void	v_bignum_set_digit(VBigDig *x, VBigDig y);
extern void	v_bignum_set_string(VBigDig *x, const char *string);	/* Decimal. */
extern void	v_bignum_set_string_hex(VBigDig *x, const char *string);
extern void	v_bignum_set_bignum(VBigDig *x, const VBigDig *y);
/* x = <bits> most significant <bits> bits of <y>, starting at <msb>. Right-
 * adjusted in x, so that e.g. y=0xcafebabec001 msb=47 bits=16 gives x=0xcafe.
*/ 
extern void	v_bignum_set_bignum_part(VBigDig *x, const VBigDig *y,
					 unsigned int msb, unsigned int bits);
extern void	v_bignum_set_random(VBigDig *x);

/* Handy during debugging. */
extern void	v_bignum_print_hex(const VBigDig *x);
extern void	v_bignum_print_hex_lf(const VBigDig *x);

/* Bit operators. */
extern void	v_bignum_not(VBigDig *x);
extern int	v_bignum_bit_test(const VBigDig *x, unsigned int bit);
extern void	v_bignum_bit_set(VBigDig *x, unsigned int bit);
extern int	v_bignum_bit_msb(const VBigDig *x);
extern int	v_bignum_bit_size(const VBigDig *x);
extern void	v_bignum_bit_shift_left(VBigDig *x, unsigned int count);
extern void	v_bignum_bit_shift_left_1(VBigDig *x);
extern void	v_bignum_bit_shift_right(VBigDig *x, unsigned int count);

/* Comparators. */
extern int	v_bignum_eq_zero(const VBigDig *x);			/* x == 0. */
extern int	v_bignum_eq_one(const VBigDig *x);			/* x == 1. */
extern int	v_bignum_eq(const VBigDig *x, const VBigDig *y);	/* x == y. */
extern int	v_bignum_gte(const VBigDig *x, const VBigDig *y);	/* x >= y. */

/* Number vs single-digit arithmetic. */
extern void	v_bignum_add_digit(VBigDig *x, VBigDig y);	/* x += y. */
extern void	v_bignum_sub_digit(VBigDig *x, VBigDig y);	/* x -= y. */
extern void	v_bignum_mul_digit(VBigDig *x, VBigDig y);	/* x *= y. */

/* Arithmetic. */
extern void	v_bignum_add(VBigDig *x, const VBigDig *y);	/* x += y. */
extern void	v_bignum_sub(VBigDig *x, const VBigDig *y);	/* x -= y. */
extern void	v_bignum_mul(VBigDig *x, const VBigDig *y);	/* x *= y. */
extern void	v_bignum_div(VBigDig *x, const VBigDig *y, VBigDig *remainder);
extern void	v_bignum_mod(VBigDig *x, const VBigDig *y);	/* x %= y. */
extern void	v_bignum_pow_mod(VBigDig *x, const VBigDig *y,
				 const VBigDig *n);	/* x = pow(x, y) % n. */
