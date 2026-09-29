/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
     return ~(~x|~y)
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~((~x)&(~y))&(~(x&y))
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
   if(!x){
        if(!y){
            return 1;
        }else return 0;
    }else if(!y){
        return 0;
    }else {
        return!((x>>31)^(y>>31));}
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int n;
    int s = 0;
    n = (v >> 16) > 0;
    n = n << 4;
    v = v >> n;
    s = s | n;
    n = (v >> 8) > 0;
    n = n << 3;
    v = v >> n;
    s = s | n;
    n = (v >> 4) > 0;
    n = n << 2;
    v = v >> n;
    s = s | n;
    n = (v >> 2) > 0;
    n = n << 1;
    v = v >> n;
    s = s | n;
    n = (v >> 1) > 0;
    s = s | n;
    return s;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a;
    int b;
    int t;

    a = (x >> (n << 3)) & 0xff;
    b = (x >> (m << 3)) & 0xff;

    t = a ^ b;

    x = x ^ (t << (n << 3));
    x = x ^ (t << (m << 3));

    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int a = 0;
    int i = 32;

    while (i)
    {
        a = a << 1;
        a = a | (v & 1);
        v = v >> 1;

        i = i - 1;
    }

    return a;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask;
    mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
     int n = 0;
    int s;

    s = (!~(x >> 16)) << 4;
    n = n + s;
    x = x << s;

    s = (!~(x >> 24)) << 3;
    n = n + s;
    x = x << s;

    s = (!~(x >> 28)) << 2;
    n = n + s;
    x = x << s;

    s = (!~(x >> 30)) << 1;
    n = n + s;
    x = x << s;

    s = (x >> 31) & 1;
    n = n + s;
    x = x << s;

    return n + ((x >> 31) & 1); 
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned ux;
    unsigned frac;
    unsigned dropped;
    unsigned half;
    int p;
    int rshift;
    int exp;

    sign = x & 0x80000000;
    ux = x;
    p = 0;
    if (x == 0)
        return 0;
    if (sign)
        ux = ~ux + 1;
    while ((ux >> p) > 1)
        p = p + 1;
    exp = p + 127;
    if (p < 24) {
        frac = ux << (23 - p);
    } else {
        rshift = p - 23;
        frac = ux >> rshift;
        dropped = ux & ((1 << rshift) - 1);
        half = 1 << (rshift - 1);
        if (dropped > half)
            frac = frac + 1;
        else if (dropped == half)
            if (frac & 1)
                frac = frac + 1;

        if (frac == 0x1000000)
            exp = exp + 1;
    }

    return sign | (exp << 23) | (frac & 0x7fffff);;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
     unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    // NaN
    if (exp == 255) {
            return uf;
    }
    // 非规格化
    if (exp == 0) {
        frac = frac << 1;
        // fraction 溢出
        if (frac & 0x800000) {
            exp = 1;
            frac = frac & 0x7fffff;
        }
        return sign | (exp << 23) | frac;
    }
    exp = exp + 1;
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exp = (uf2 >> 20) & 0x7ff;
    unsigned frac_hi = uf2 & 0xfffff;
    unsigned frac_lo = uf1;
    int E = exp + (~1023 + 1);
    int val;
    // exp == 0x7ff (NaN or infinity)
    if (!(exp + (~0x7ff + 1)))
        return 0x80000000;
    // E < 0 : 小于1
    if (E < 0)
        return 0;
    // E > 30 : int溢出
    if (E > 30)
        return 0x80000000;

    if (E <= 20)
    {
        val = (frac_hi | 0x100000) >> (20 - E);
    }
    else
    {
        val = (frac_hi | 0x100000) << (E - 20);

        if (E > 32)
        {
            val = val | (frac_lo << (E - 32));
        }
        else
        {
            val = val | (frac_lo >> (32 - E));
        }
    }
    if (sign)
        return -val;
    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    int exp;
    unsigned frac;
    if (x < -149)
        return 0;
    if (x > 127)
        return 0x7f800000;
    if (x < -126)
    {
        frac = 1 << (x + 149);
        return frac;
    }
    exp = x + 127;
    return exp << 23;
    return 2;
}
