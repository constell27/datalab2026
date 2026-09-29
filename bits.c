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
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);;
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
    if (!x) {
        return !y;
    }
    return !!y && !((x ^ y) >> 31);;
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
    int r, s;

    r = ((v >> 16) > 0) << 4;
    v = v >> r;

    s = ((v >> 8) > 0) << 3;
    r = r | s;
    v = v >> s;

    s = ((v >> 4) > 0) << 2;
    r = r | s;
    v = v >> s;

    s = ((v >> 2) > 0) << 1;
    r = r | s;
    v = v >> s;

    return r | (v >> 1);
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
    int ns = n << 3;
    int ms = m << 3;
    int diff = ((x >> ns) ^ (x >> ms)) & 255;
    return x ^ (diff << ns) ^ (diff << ms);
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
    unsigned result = 0;
    int n = 32;
    while (n) {
        result = (result << 1) | (v & 1);
        v = v >> 1;
        n = n - 1;
    }
    return result;
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
    int mask = ~(((1 << 31) >> n) << 1);
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
    int y = ~x;
    int n, s;
    n = !(y >> 16) << 4;
    y = y << n;
    s = !(y >> 24) << 3;
    n = n + s;
    y = y << s;
    s = !(y >> 28) << 2;
    n = n + s;
    y = y << s;
    s = !(y >> 30) << 1;
    n = n + s;
    y = y << s;
    s = !(y >> 31);
    n = n + s;
    y = y << s;
    return n + !y;
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
    unsigned sign = 0;
    unsigned v = x;
    unsigned exponent = 158;
    unsigned fraction, tail;
    if (!x) {
        return 0;
    }
    if (x < 0) {
        sign = 0x80000000;
        v = ~v + 1;
    }
    while (!(v >> 31)) {
        v = v << 1;
        exponent = exponent - 1;
    }
    fraction = (v >> 8) & 0x7fffff;
    tail = v & 255;
    if (tail > 128) {
        fraction = fraction + 1;
    } else if (tail == 128) {
        fraction = fraction + (fraction & 1);
    }
    return sign + (exponent << 23) + fraction;
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
    unsigned exponent = (uf >> 23) & 255;
    unsigned fraction = uf & 0x7fffff;
    if (exponent == 255) {
        return uf;
    }
    if (!exponent) {
        return sign | (fraction << 1);
    }
    exponent = exponent + 1;
    if (exponent == 255) {
        return sign | 0x7f800000;
    }
    return sign | (exponent << 23) | fraction;
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
    int exponent = (uf2 >> 20) & 0x7ff;
    unsigned sign = uf2 >> 31;
    unsigned significand = (uf2 & 0xfffff) | 0x100000;
    unsigned magnitude;
    exponent = exponent - 1023;
    if (exponent < 0) {
        return 0;
    }
    if (exponent >= 31) {
        return 0x80000000;
    }
    if (exponent <= 20) {
        magnitude = significand >> (20 - exponent);
    } else {
        magnitude = (significand << (exponent - 20)) |
                    (uf1 >> (52 - exponent));
    }
    if (sign) {
        return ~magnitude + 1;
    }
    return magnitude;
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
    if (x < -149) {
        return 0;
    }
    if (x < -126) {
        return 1 << (x + 149);
    }
    if (x > 127) {
        return 0x7f800000;
    }
    return (x + 127) << 23;
}
