/* 
 * CS:APP Data Lab 
 * 
 * Raymond Van Zandt
 * rlv220
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif


//1


/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*
 * flip x and y, or them, and then take the inverse
 * 0110 AND 0101 = 0010 = 4
 * 1.) ~0110 = 1001, ~0101 = 1010
 * 2.) 1001 | 0101 = 1101
 * 3.)~1101 = 0010 = 4
*/

	int flip1 = ~x;
	int flip2 = ~y;
	int orOp = flip2|flip1;
	return ~orOp;
}


/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/*
 * Had trouble with this one. Left it until the end and tried multiple approaches.
 * I am probably overthinking it.
*/

//	int smallest = 1<<31;//-2147483648--------can't use <<!!
//	int smallest = 0x80000000; --- illegal
//	int checkX = smallest + x;
//	int addOne = checkX + 1;
//	return !addOne;


//	printf("x: %d\n", x);
//	int negate = ~x;//opposite of Tmax is -1;
//	printf("~x: %d\n", negate);
//	printf("negate - 1: %d\n", (int)((int)(~x) - 1));
//	printf("flag: %d\n", !(negate - 1));
//	return !(negate + 1);//

	return !(x^0x7FFFFFFF);

}


/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
/*
 *creates smallest number by shifting 1 all the way left
 *in the sign position ---> (-2147483648)
*/
  return 1<<31;
}


/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
/*
 * create even byte = 01010101 = 0x55
 * shift it over 8 bits and OR it with 0x55 to get 16 bits
 * then shift 16 more bits and or with the orginal 16
 * to create even 32 bits
*/
	int evenByte = 0x55;
	int even16 = (evenByte<<8|0x55);
	int even32 = (even16<<16) | even16;
	return even32;
}


//2


/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
/*
 *CREATE MASK FROM EVENBITS(void)
 * create even byte = 01010101 = 0x55
 * shift it over 8 bits and or it with 0x55 to get 16 bits
 * then shift 16 more bits and or with the orginal 16
 * to create even 32 bits.
 *
 * NEW STUFF:
 * Then AND x with even 32 to either get 0 (no even bits) or some other number
 * then take logical negation ! twice ----> if 0 --> !(!0)) = 0
 * else---> !(!somenumber) = !(0) = 1
*/
    int evenByte = 0x55;
    int even16 = (evenByte<<8|0x55);
    int even32 = (even16<<16) | even16;
	int checkEvenBits = (x&even32);
	return !(!checkEvenBits);
}


/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
/*
 *first get the whole m and n byte = m * 3/ n * 3
 *then get the low byte (nShift) and high byte (mShift)
 *XOR n and shift back to the n byte and then xor it with x.
 *XOR twice gets us m in n's place ,vice versa
 */
	int nShift = n<<3;
	int mShift = m<<3;
	int getNbyte = (x >> nShift);
	int getMbyte = (x >> mShift);
	int intersect = (getNbyte ^ getMbyte);//1's mask between N and M
	int xorONE = x ^ ((0xFF & intersect) << nShift);
	int xorTWO = xorONE ^ ((0xFF & intersect) << mShift);

	return xorTWO;
}


/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
/*
 * Get sign bit
 * check if signed bit is negative
 * x + the signCheck shifted over n + signedBit will get us our corrected number
 * then we just return the normal division >>n
 */
//	printf("x/y: %d %d\n", x, n);
//	printf("sign: %d\n", x>>31);
    int signedBit = x>>31;

//	printf("signCheck: %d\n", !(!signedBit));
	int signCheck = !(!signedBit);//1 if -1, 0 if 0

//	printf("checkX: %d\n", (x + (signCheck<<n) + signedBit));
	int checkX = (x + (signCheck<<n) + signedBit);

//	printf("return: %d\n", checkX>>n);
	return checkX>>n;
}


//3


/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
/*
 *shift 10 over highbit places
 * take the mask of highbit + 11111 ---> 0000(highbit = 1)111111...1
 * then we cut off the extra least significant 1's by shift down to low bit
 * and then back up to replace the 1's with 0's
 */
	int highBit = (2<<highbit);
	int highBitMask = (highBit + ~0);
	int lowBitShift = highBitMask >>lowbit;
	return lowBitShift<<lowbit;
}


/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
/*
 *first we set lower bound and upper bound
 *then we add x to each and check for -1
 * if we get a negative we return 0;
 */
	int lowerBound = ~(0x2F);//negative (0x30 - 1)
	int upperBound = (0x3a);//0x30 + 1
	int lowCheck = x + lowerBound;
	int highCheck = ~x + upperBound;
	return !((lowCheck|highCheck)>>31);//checks if negative ---> returns 1 if not else 0
}


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
/*
 * get both sign bits of x and y
 * x > y if y - x is negative == y + (~x + 1)
 * get the sign bit: 1 if negative else 0
 * return true (x<=y): if x is negative and y is postive OR if the opSign is postive with x and y having different signs
 */
	int xSign = (x >> 31);
	int ySign = (y >> 31);
	int yMinusX = y + (~x + 1);
	int getSignBit = yMinusX >> 31;
	return (xSign & !ySign) | (!(xSign ^ ySign) & !getSignBit);
}


//4


/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
/*
 *To find bit parity we can XOR each half with the next half
 *if we get a 0 we have even parity, thus we AND with 1
 */

	//take 3 for example which has even 0's:
	x ^= x >>16;//(0*30) 11 ^ 0Mask = (0*30) 11
	x ^= x >>8;//(0*6)11 ^ 0 = 00000011
	x ^= x >>4;//(0*2) 11 ^ 0 = 0011
	x ^= x >>2;//11 ^ 0 = 11
	x ^= x >>1;// 1 ^ 0 = 1
	return x&1;// 1 & 1 = 1 ----> even


}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*
 *we negate x and add one
 *we or that with x and shift down to LSB
 * then return the value + 1
 * 
 */
	int negXPlusOne = (~x + 1);//if x = 0 -----> 11111111111111 + 1 = -0
	int orOp = (x | negXPlusOne) >> 31;//-1 or 0 ----> if 0 we get---> 0 | -0 = 0
	return orOp + 1;// 0 + 1 = 1----> !0 = 1
}


//float


/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
/*
 *unsigned float has a range of 0x7FFFFFFF <---> 0x7F800001
 *
 *	set max and min number
 *	remove sign bit
 *  if number is not NaN return it its ABS else return back uf
 */


	int maxNumber = 0x7FFFFFFF;//0(1*32)
	int nan = 0x7F800001;//NaN
	int takeABS = uf & maxNumber;//remove the sign bit and keep everything else

	if(takeABS >= nan){
		return uf;//if the ABS is greater than the minNAN than it is NAN and we return uf;
	}
	else{
		return takeABS;//if not NaN we can return the ABS VAL!
	}

/*
	unsigned negSign = 1 << 31;
	unsigned posMask = ~(negSign);
	return uf & posMask;
*/
}


/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
/*
 *Get sign, exponent, and fraction of both floats and then
 * check each condition with if statments (described line by line)
 */
    int ufSign = (uf >> 31) & 1;
    int ugSign = (ug >> 31) & 1;
	int ufExponent = (uf >> 23) & 0xFF;
    int ugExponent = (ug >> 23) & 0xFF;
	int ufFraction = (uf & 0x007FFFFF);
    int ugFraction = (ug & 0x007FFFFF);

	if(!(uf & 0x7FFFFFFF) && !(ug & 0x7FFFFFFF)){//if ug AND uf is NAN return 0
//		printf("is NAN\n %d%d",!(uf & 0x7FFFFFFF), !(ug & 0x7FFFFFFF));//SHOULD BE && not ||
		return 0;
	}

	if((ufExponent == 0xFF && ufFraction) || (ugExponent == 0xFF && ugFraction)){//if 0/-0 return 0
//		printf("is 0/-0\n");
		return 0;
	}

	if(ufSign ^ ugSign){//compare signs
//		printf("return 1: %d\n", ufSign > ugSign);
		return ufSign > ugSign;
	}

	if(ufExponent ^ ugExponent){//compare exponents
//		printf("return 2: %d\n",(ufExponent < ufExponent) ^ (ufSign));
		return (ufExponent < ugExponent) ^ (ufSign);
	}

	if(ufFraction ^ ugFraction){//compare fractions
//		printf("return 3: %d\n",(ufFraction < ugFraction) ^ (ufSign));
		return (ufFraction < ugFraction) ^ (ufSign);
	}
//	printf("last return\n");
	return 0;

}


/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

unsigned floatScale2(unsigned uf) {

/*
 *	first get the exponent
 *	then check if it is denormalized ---> normalize it
 *  then check if there is an overflow and set it to infinite
 *  lastly check if nothing needs to be processed, increase exponent, and return uf
 *  else return NAN
 */
	unsigned exponent = (uf >> 23) & 0xFF;//255

	if(!exponent){//denormalized case --- exponent is all 0's
		exponent = 0xFF;//255
		uf = (uf & 0x80000000) | (uf << 1);//normalize
	}
	if(!(exponent ^ 0xFE)){//overflow
		exponent = 0xFF;//255
		uf = (uf & 0x80000000) | (exponent << 23);//set to infinte
	}
	if(exponent ^ 0xFF){//normalized case ---> increment exponent
		uf = uf + (1 << 23);
	}
	return uf;//return uf or NAN
}
