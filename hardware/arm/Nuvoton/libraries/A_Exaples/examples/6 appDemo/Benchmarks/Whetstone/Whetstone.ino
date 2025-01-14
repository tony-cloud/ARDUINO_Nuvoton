/*  Arduino-compatible Whetstone benchmark.
    Based on the work of Thomas Kirchner, modified to work
    with the Arduino IDE 1.6.x series.
    Modified by Gareth Halfacree <gareth@halfacree.co.uk>
    Further modified to use single-precision floats, instead of
    double-precision doubles, for fairer comparison between
    AVR (where doubles and floats are both 32-bit) and other
    platforms.
*/

/* Source: http://www.netlib.org/benchmark/whetstonec

   C Converted Whetstone float Precision Benchmark
        Version 1.2 22 March 1998

    (c) Copyright 1998 Painter Engineering, Inc.
        All Rights Reserved.

        Permission is granted to use, duplicate, and
        publish this text and program as long as it
        includes this entire comment block and limited
        rights reference.

   Converted by Rich Painter, Painter Engineering, Inc. based on the
   www.netlib.org benchmark/whetstoned version obtained 16 March 1998.

   A novel approach was used here to keep the look and feel of the
   FORTRAN version.  Altering the FORTRAN-based array indices,
   starting at element 1, to start at element 0 for C, would require
   numerous changes, including decrementing the variable indices by 1.
   Instead, the array E1[] was declared 1 element larger in C.  This
   allows the FORTRAN index range to function without any literal or
   variable indices changes.  The array element E1[0] is simply never
   used and does not alter the benchmark results.

   The major FORTRAN comment blocks were retained to minimize
   differences between versions.  Modules N5 and N12, like in the
   FORTRAN version, have been eliminated here.

   An optional command-line argument has been provided [-c] to
   offer continuous repetition of the entire benchmark.
   An optional argument for setting an alternate LOOP count is also
   provided.  Define PRINTOUT to cause the POUT() function to print
   outputs at various stages.  Final timing measurements should be
   made with the PRINTOUT undefined.

   Questions and comments may be directed to the author at
            r.painter@ieee.org
*/

void setup() {
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 115200bps 8N1) */

  delay(2000);
  while (!Serial) {}
  Serial.println("Whetstone Benchmark, Version 1.2 (Language: C)");
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
/* the following is optional depending on the timing function used */
//#include <time.h>

/* map the FORTRAN math functions, etc. to the C versions */
#define DSIN    sinf
#define DCOS    cosf
#define DATAN   atanf
#define DLOG    logf
#define DEXP    expf
#define DSQRT   sqrtf
#define IF      if

/* function prototypes */
void POUT(long N, long J, long K, float X1, float X2, float X3, float X4);
void Proc_A(float E[]);
void P0(void);
void P3(float X, float Y, float *Z);
#define USAGE   "usage: whetdc [-c] [loops]\n"
//#define PRINTOUT

/*
    COMMON T,T1,T2,E1(4),J,K,L
*/
float T, T1, T2, E1[5];
int J, K, L;

int argc = 0; //Mod for nucleo. Change in code below if you want non-default loop count



void
Proc_A(float E[])
{
  J = 0;

L10:
  E[1] = ( E[1] + E[2] + E[3] - E[4]) * T;
  E[2] = ( E[1] + E[2] - E[3] + E[4]) * T;
  E[3] = ( E[1] - E[2] + E[3] + E[4]) * T;
  E[4] = (-E[1] + E[2] + E[3] + E[4]) / T2;
  J += 1;

  if (J < 6)
    goto L10;
}

void
P0(void)
{
  E1[J] = E1[K];
  E1[K] = E1[L];
  E1[L] = E1[J];
}

void
P3(float X, float Y, float *Z)
{
  float X1, Y1;

  X1 = X;
  Y1 = Y;
  X1 = T * (X1 + Y1);
  Y1 = T * (X1 + Y1);
  *Z  = (X1 + Y1) / T2;
}

#ifdef PRINTOUT
void
POUT(long N, long J, long K, float X1, float X2, float X3, float X4)
{
  /*sprintf("%7ld %7ld %7ld %12.4e %12.4e %12.4e %12.4e\n",
                       N, J, K, X1, X2, X3, X4);*/

}
#endif

int
whetstone(int argc)
{
//  UNUSED(argc);  /*remove warning by huaweiwx@sina.com 2018.7*/
  /* used in the FORTRAN version */
  long I;
  long N1, N2, N3, N4, N6, N7, N8, N9, N10, N11;
  float X1, X2, X3, X4, X, Y, Z;
  long LOOP;
  int II, JJ;

  /* added for this version */
  long loopstart;
  long startsec, finisec;
  float KIPS;
  int continuous;

  loopstart = 1000;       /* see the note about LOOP below */
  continuous = 0;

  II = 1;

LCONT:
  /*
    C
    C   Start benchmark timing at this point.
    C
  */
  startsec = millis();

  /*
    C
    C   The actual benchmark starts here.
    C
  */
  T  = .499975;
  T1 = 0.50025;
  T2 = 2.0;
  /*
    C
    C   With loopcount LOOP=10, one million Whetstone instructions
    C   will be executed in EACH MAJOR LOOP..A MAJOR LOOP IS EXECUTED
    C   'II' TIMES TO INCREASE WALL-CLOCK TIMING ACCURACY.
    C
      LOOP = 1000;
  */
  LOOP = loopstart;
  II   = 1;

  JJ = 1;

IILOOP:
  N1  = 0;
  N2  = 12 * LOOP;
  N3  = 14 * LOOP;
  N4  = 345 * LOOP;
  N6  = 210 * LOOP;
  N7  = 32 * LOOP;
  N8  = 899 * LOOP;
  N9  = 616 * LOOP;
  N10 = 0;
  N11 = 93 * LOOP;
  /*
    C
    C   Module 1: Simple identifiers
    C
  */
  X1  =  1.0;
  X2  = -1.0;
  X3  = -1.0;
  X4  = -1.0;

  for (I = 1; I <= N1; I++) {
    X1 = (X1 + X2 + X3 - X4) * T;
    X2 = (X1 + X2 - X3 + X4) * T;
    X3 = (X1 - X2 + X3 + X4) * T;
    X4 = (-X1 + X2 + X3 + X4) * T;
  }
#ifdef PRINTOUT
  IF (JJ == II)POUT(N1, N1, N1, X1, X2, X3, X4);
#endif

  /*
    C
    C   Module 2: Array elements
    C
  */
  E1[1] =  1.0;
  E1[2] = -1.0;
  E1[3] = -1.0;
  E1[4] = -1.0;

  for (I = 1; I <= N2; I++) {
    E1[1] = ( E1[1] + E1[2] + E1[3] - E1[4]) * T;
    E1[2] = ( E1[1] + E1[2] - E1[3] + E1[4]) * T;
    E1[3] = ( E1[1] - E1[2] + E1[3] + E1[4]) * T;
    E1[4] = (-E1[1] + E1[2] + E1[3] + E1[4]) * T;
  }

#ifdef PRINTOUT
  IF (JJ == II)POUT(N2, N3, N2, E1[1], E1[2], E1[3], E1[4]);
#endif

  /*
    C
    C   Module 3: Array as parameter
    C
  */
  for (I = 1; I <= N3; I++)
    Proc_A(E1);

#ifdef PRINTOUT
  IF (JJ == II)POUT(N3, N2, N2, E1[1], E1[2], E1[3], E1[4]);
#endif

  /*
    C
    C   Module 4: Conditional jumps
    C
  */
  J = 1;
  for (I = 1; I <= N4; I++) {
    if (J == 1)
      J = 2;
    else
      J = 3;

    if (J > 2)
      J = 0;
    else
      J = 1;

    if (J < 1)
      J = 1;
    else
      J = 0;
  }

#ifdef PRINTOUT
  IF (JJ == II)POUT(N4, J, J, X1, X2, X3, X4);
#endif

  /*
    C
    C   Module 5: Omitted
    C   Module 6: Integer arithmetic
    C
  */

  J = 1;
  K = 2;
  L = 3;

  for (I = 1; I <= N6; I++) {
    J = J * (K - J) * (L - K);
    K = L * K - (L - J) * K;
    L = (L - K) * (K + J);
    E1[L - 1] = J + K + L;
    E1[K - 1] = J * K * L;
  }

#ifdef PRINTOUT
  IF (JJ == II)POUT(N6, J, K, E1[1], E1[2], E1[3], E1[4]);
#endif

  /*
    C
    C   Module 7: Trigonometric functions
    C
  */
  X = 0.5;
  Y = 0.5;

  for (I = 1; I <= N7; I++) {
    X = T * DATAN(T2 * DSIN(X) * DCOS(X) / (DCOS(X + Y) + DCOS(X - Y) - 1.0));
    Y = T * DATAN(T2 * DSIN(Y) * DCOS(Y) / (DCOS(X + Y) + DCOS(X - Y) - 1.0));
  }

#ifdef PRINTOUT
  IF (JJ == II)POUT(N7, J, K, X, X, Y, Y);
#endif

  /*
    C
    C   Module 8: Procedure calls
    C
  */
  X = 1.0;
  Y = 1.0;
  Z = 1.0;

  for (I = 1; I <= N8; I++)
    P3(X, Y, &Z);

#ifdef PRINTOUT
  IF (JJ == II)POUT(N8, J, K, X, Y, Z, Z);
#endif

  /*
    C
    C   Module 9: Array references
    C
  */
  J = 1;
  K = 2;
  L = 3;
  E1[1] = 1.0;
  E1[2] = 2.0;
  E1[3] = 3.0;

  for (I = 1; I <= N9; I++)
    P0();

#ifdef PRINTOUT
  IF (JJ == II)POUT(N9, J, K, E1[1], E1[2], E1[3], E1[4]);
#endif

  /*
    C
    C   Module 10: Integer arithmetic
    C
  */
  J = 2;
  K = 3;

  for (I = 1; I <= N10; I++) {
    J = J + K;
    K = J + K;
    J = K - J;
    K = K - J - J;
  }

#ifdef PRINTOUT
  IF (JJ == II)POUT(N10, J, K, X1, X2, X3, X4);
#endif

  /*
    C
    C   Module 11: Standard functions
    C
  */
  X = 0.75;

  for (I = 1; I <= N11; I++)
    X = DSQRT(DEXP(DLOG(X) / T1));

#ifdef PRINTOUT
  IF (JJ == II)POUT(N11, J, K, X, X, X, X);
#endif

  /*
    C
    C      THIS IS THE END OF THE MAJOR LOOP.
    C
  */
  if (++JJ <= II)
    goto IILOOP;

  /*
    C
    C      Stop benchmark timing at this point.
    C
  */
  finisec = millis();

  /*
    C----------------------------------------------------------------
    C      Performance in Whetstone KIP's per second is given by
    C
    C   (100*LOOP*II)/TIME
    C
    C      where TIME is in seconds.
    C--------------------------------------------------------------------
  */
  Serial.write("\n");
  if (finisec - startsec <= 0) {
    Serial.write("Insufficient duration- Increase the LOOP count\n");
    return (1);
  }

  Serial.print("Loops: ");
  Serial.print(LOOP);
  Serial.print(", Iterations: ");
  Serial.print(II);
  Serial.print(", Duration: ");
  Serial.print(finisec - startsec);
  Serial.println(" ms.");//Arduino measures time in milliseconds

  //    KIPS = (100.0*LOOP*II)/(float)(finisec-startsec);
  KIPS = (100.0 * LOOP * II) / (float)(finisec - startsec) * 1000; //convert to seconds from milliseconds
  if (KIPS >= 1000.0) {
    Serial.print("C Converted Single Precision Whetstones: ");
    Serial.print(KIPS / 1000.0);
    Serial.println(" MIPS");
  }
  else {
    Serial.print("C Converted Single Precision Whetstones: ");
    Serial.print(KIPS);
    Serial.println(" KIPS");
  }

  if (continuous)
    goto LCONT;

  return (0);
}


void loop() {
  whetstone(0);
}
