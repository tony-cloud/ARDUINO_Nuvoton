/******************************************************************************/
/**  YAFFA - Yet Another Forth for Arduino                                   **/
/**                                                                          **/
/**  File: Dictionary.ino                                                    **/
/**  Copyright (C) 2012 Stuart Wood (swood@rochester.rr.com)                 **/
/**                                                                          **/
/**  This file is part of YAFFA.                                             **/
/**                                                                          **/
/**  YAFFA is free software: you can redistribute it and/or modify           **/
/**  it under the terms of the GNU General Public License as published by    **/
/**  the Free Software Foundation, either version 2 of the License, or       **/
/**  (at your option) any later version.                                     **/
/**                                                                          **/
/**  YAFFA is distributed in the hope that it will be useful,                **/
/**  but WITHOUT ANY WARRANTY; without even the implied warranty of          **/
/**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           **/
/**  GNU General Public License for more details.                            **/
/**                                                                          **/
/**  You should have received a copy of the GNU General Public License       **/
/**  along with YAFFA.  If not, see <http://www.gnu.org/licenses/>.          **/
/**                                                                          **/
/******************************************************************************/
#include "YAFFA.h"

const char not_done_str[] = " NOT Implemented Yet \n\r";

/******************************************************************************/
/**                       Primitives for Control Flow                        **/
/******************************************************************************/
const char jump_str[] = "jump";
void _jump(void) {
  ip = (cell_t*)((size_t)ip + *ip);
}

const char zjump_str[] = "zjump";
void _zjump(void) {
  if (!dStack_pop()) ip = (cell_t*)((size_t)ip + *ip);
  else ip++;
}

const char subroutine_str[] = "subroutine";
void _subroutine(void) {
  *pDoes = (cell_t)*ip++;
}

const char do_sys_str[] = "do-sys";
// ( n1|u1 n2|u2 -- ) (R: -- loop_sys )
// Set up loop control parameters with index n2|u2 and limit n1|u1. An ambiguous
// condition exists if n1|u1 and n2|u2 are not the same type. Anything already
// on the return stack becomes unavailable until the loop-control parameters
// are discarded.
void _do_sys(void) {
  rStack_push(LOOP_SYS);
  rStack_push(dStack_pop());   // push index on to return stack
  rStack_push(dStack_pop());   // push limit on to return stack
}

const char loop_sys_str[] = "loop-sys";
// ( n1|u1 n2|u2 -- ) (R: -- loop_sys )
// Set up loop control parameters with index n2|u2 and limit n1|u1. An ambiguous
// condition exists if n1|u1 and n2|u2 are not the same type. Anything already
// on the return stack becomes unavailable until the loop-control parameters
// are discarded.
void _loop_sys(void) {
  cell_t limit = rStack_pop();    // fetch limit
  cell_t index = rStack_pop();    // fetch index
  index++;
  if (limit - index) {
    rStack_push(index);
    rStack_push(limit);
    ip = (cell_t*)*ip;
  } else {
    ip++;
    if (rStack_pop() != LOOP_SYS) {
      dStack_push(-22);
      _throw();
      return;
    }
  }
}

const char leave_sys_str[] = "leave-sys";
// ( -- ) (R: loop-sys -- )
// Discard the current loop control parameters. An ambiguous condition exists
// if they are unavailable. Continue execution immediately following the
// innermost syntactically enclosing DO ... LOOP or DO ... +LOOP.
void _leave_sys(void) {
  rStack_pop();    // fetch limit
  rStack_pop();    // fetch index
  if (rStack_pop() != LOOP_SYS) {
    dStack_push(-22);
    _throw();
    return;
  }
  ip = (cell_t*)*ip;
}

const char plus_loop_sys_str[] = "plus_loop-sys";
// ( n1|u1 n2|u2 -- ) (R: -- loop_sys )
// Set up loop control parameters with index n2|u2 and limit n1|u1. An ambiguous
// condition exists if n1|u1 and n2|u2 are not the same type. Anything already
// on the return stack becomes unavailable until the loop-control parameters
// are discarded.
void _plus_loop_sys(void) {
  cell_t limit = rStack_pop();    // fetch limit
  cell_t index = rStack_pop();    // fetch index
  index += dStack_pop();
  if (limit != index) {
    rStack_push(index);
    rStack_push(limit);
    ip = (cell_t*)*ip;
  } else {
    ip++;
    if (rStack_pop() != LOOP_SYS) {
      dStack_push(-22);
      _throw();
      return;
    }
  }
}

/*******************************************************************************/
/**                          Core Forth Words                                 **/
/*******************************************************************************/
const char store_str[] = "!";
// ( x a-addr --)
// Store x at a-addr
void _store(void) { 
  cell_t* address = (cell_t*)dStack_pop();
  *address = dStack_pop();
}

const char number_sign_str[] = "#";
// ( ud1 -- ud2)
// Divide ud1 by number in BASE giving quotient ud2 and remainder n. Convert
// n to external form and add the resulting character to the beginning of the
// pictured numeric output string.
void _number_sign(void) { 
  udcell_t ud;
  ud = (udcell_t)dStack_pop() << sizeof(ucell_t) * 8;
  ud += (udcell_t)dStack_pop();
  *--pPNO = charset[ud % base];
  ud /= base;
  dStack_push((ucell_t)ud);
  dStack_push((ucell_t)(ud >> sizeof(ucell_t) * 8));
}

const char number_sign_gt_str[] = "#>";
// ( xd -- c-addr u)
// Drop xd. Make the pictured numeric output string available as a character
// string c-addr and u specify the resulting string. A program may replace
// characters within the string.
void _number_sign_gt(void) {
  _two_drop();
  dStack_push((size_t)pPNO);
  dStack_push((size_t)strlen(pPNO));
  flags &= ~NUM_PROC;
}

const char number_sign_s_str[] = "#s";
// ( ud1 -- ud2)
void _number_sign_s(void) {
  udcell_t ud;
  ud = (udcell_t)dStack_pop() << sizeof(ucell_t) * 8;
  ud += (udcell_t)dStack_pop();
  while (ud) {
    *--pPNO = charset[ud % base];
    ud /= base;
  }
  dStack_push((ucell_t)ud);
  dStack_push((ucell_t)(ud >> sizeof(ucell_t) * 8));
}

const char tick_str[] = "'";
// ( "<space>name" -- xt)
// Skip leading space delimiters. Parse name delimited by a space. Find name and
// return xt, the execution token for name. An ambiguous condition exists if 
// name is not found. When interpreting "' xyz EXECUTE" is equivalent to xyz.
void _tick(void) {
//    push(' ');
//    _word();
//    _find();
//    pop();
  if (getToken()) {
    if (isWord(cTokenBuffer)) {
      dStack_push(w);
      return; 
    }
  }
  dStack_push(-13);
  _throw();
}

const char paren_str[] = "(";
// ( "ccc<paren>" -- )
// imedeate
void _paren(void) {
  dStack_push(')');
  _word();
  _drop();
}

const char star_str[] = "*";
// ( n1|u1 n2|u2 -- n3|u3 )
// multiply n1|u1 by n2|u2 giving the product n3|u3
void _star(void) {
  dStack_push(dStack_pop() * dStack_pop());
}

const char star_slash_str[] = "*/";
// ( n1 n2 n3 -- n4 )
// multiply n1 by n2 producing the double cell result d. Divide d by n3
// giving the single-cell quotient n4.
void _star_slash(void) {
  cell_t n3 = dStack_pop();
  cell_t n2 = dStack_pop();
  cell_t n1 = dStack_pop();
  dcell_t d = (dcell_t)n1 * (dcell_t)n2;
  dStack_push((cell_t)(d / n3));
}

const char star_slash_mod_str[] = "*/mod";
// ( n1 n2 n3 -- n4 n5)
// multiply n1 by n2 producing the double cell result d. Divide d by n3
// giving the single-cell remainder n4 and quotient n5.
void _star_slash_mod(void) {
  cell_t n3 = dStack_pop();
  cell_t n2 = dStack_pop();
  cell_t n1 = dStack_pop();
  dcell_t d = (dcell_t)n1 * (dcell_t)n2;
  dStack_push((cell_t)(d % n3));
  dStack_push((cell_t)(d / n3));
}

const char plus_str[] = "+";
// ( n1|u1 n2|u2 -- n3|u3 )
// add n2|u2 to n1|u1, giving the sum n3|u3
void _plus(void) {
  cell_t x = dStack_pop();
  cell_t y = dStack_pop();
  dStack_push(x +  y);
}

const char plus_store_str[] = "+!";
// ( n|u a-addr -- )
// add n|u to the single cell number at a-addr
void _plus_store(void) {
  cell_t* address = (cell_t*)dStack_pop();
  if (address >= &forthSpace[0] &&
      address < &forthSpace[FORTH_SIZE])
    *address += dStack_pop();
  else {
    dStack_push(-9);
    _throw();
  }
}

const char plus_loop_str[] = "+loop";
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: (C: do-sys -- )
// Append the run-time semantics given below to the current definition. Resolve
// the destination of all unresolved occurrences of LEAVE between the location
// given by do-sys and the next location for a transfer of control, to execute
// the words following +LOOP.
// Run-Time: ( n -- )(R: loop-sys1 -- | loop-sys2 )
// An ambiguous condition exists if the loop control parameters are unavailable.
// Add n to the index. If the loop index did not cross the boundary between the
// loop limit minus one and the loop limit, continue execution at the beginning
// of the loop. Otherwise, discard the current loop control parameters and
// continue execution immediately following the loop.
void _plus_loop(void) {
  *pHere++ = PLUS_LOOP_SYS_IDX;
  cell_t start_addr = dStack_pop();
  *pHere++ = start_addr;
  cell_t* ptr = (cell_t*)start_addr;
  cell_t stop_addr = (cell_t)pHere;
  do {
    if (*ptr++ == LEAVE_SYS_IDX) {
      if (*ptr == 0) {
        *ptr = stop_addr;
      }
    } 
  } while (ptr != (cell_t*)stop_addr);
  if ( dStack_pop() != DO_SYS) {
    dStack_push(-22);
    _throw();
  }
}

const char comma_str[] = ",";
// ( x --  )
// Reserve one cell of data space and store x in the cell. If the data-space
// pointer is aligned when , begins execution, it will remain aligned when ,
// finishes execution. An ambiguous condition exists if the data-space pointer
// is not aligned prior to execution of ,.
static void _comma(void) {
  *pHere++ = dStack_pop();
}

const char minus_str[] = "-";
// ( n1|u1 n2|u2 -- n3|u3 )
void _minus(void) {
  cell_t temp = dStack_pop();
  dStack_push(dStack_pop() -  temp);
}

const char dot_str[] = ".";
// ( n -- )
// display n in free field format
void _dot(void) {
  w = dStack_pop();
  displayValue();
}

const char dot_quote_str[] = ".\x22";
// Compilation ("ccc<quote>" -- )
// Parse ccc delimited by ". Append the run time semantics given below to
// the current definition.
// Run-Time ( -- )
// Display ccc.
void _dot_quote(void) {
  uint8_t i;
  char length;
  if (flags & EXECUTE) {
    Serial.print((char*)ip); // Print the string at the istuction pointer (ip)
    cell_t len = strlen((char*)ip) + 1;  // include null terminator
    ip = (cell_t*)((size_t)ip + len); // Move the ip to the end of the string 
    ALIGN_P(ip); // and align it.
  }
  else if (state) {
    cDelimiter = '"';
    if (!getToken()) {
      dStack_push(-16);
      _throw();
    }
    length = strlen(cTokenBuffer);
    *pHere++ = DOT_QUOTE_IDX;
    char *ptr = (char *) pHere;
    for (uint8_t i = 0; i < length; i++) {
      *ptr++ = cTokenBuffer[i];
    }
    *ptr++ = '\0';    // Terminate String
    pHere = (cell_t *)ptr;
    ALIGN_P(pHere);  // re- align the pHere for any new code
    cDelimiter = ' ';
  }
}

const char slash_str[] = "/";
// ( n1 n2 -- n3 )
// divide n1 by n2 giving a single cell quotient n3
void _slash(void) {
  cell_t temp = dStack_pop();
  if (temp)
    dStack_push(dStack_pop() /  temp);
  else {
    dStack_push(-10);
    _throw();
  }
}

const char slash_mod_str[] = "/mod";
// ( n1 n2 -- n3 n4)
// divide n1 by n2 giving a single cell remainder n3 and quotient n4
void _slash_mod(void) {
  cell_t n2 = dStack_pop();
  cell_t n1 = dStack_pop();
  if (n2) {
    dStack_push(n1 %  n2);
    dStack_push(n1 /  n2);
  } else {
    dStack_push(-10);
    _throw();
  }
}

const char zero_less_str[] = "0<";
// ( n -- flag )
// flag is true if and only if n is less than zero.
void _zero_less(void) {
  if (dStack_pop() < 0) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char zero_equal_str[] = "0=";
// ( n -- flag )
// flag is true if and only if n is equal to zero.
void _zero_equal(void) {
  if (dStack_pop() == 0) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char one_plus_str[] = "1+";
// ( n1|u1 -- n2|u2 )
// add one to n1|u1 giving sum n2|u2.
void _one_plus(void) {
  dStack_push(dStack_pop() + 1);
}

const char one_minus_str[] = "1-";
// ( n1|u1 -- n2|u2 )
// subtract one to n1|u1 giving sum n2|u2.
void _one_minus(void) {
  dStack_push(dStack_pop() - 1);
}

const char two_store_str[] = "2!";
// ( x1 x2 a-addr --)
// Store the cell pair x1 x2 at a-addr, with x2 at a-addr and x1 at a-addr+1
void _two_store(void) {
  cell_t* address = (cell_t*)dStack_pop();
  if (address >= &forthSpace[0] &&
      address < &forthSpace[FORTH_SIZE - 4]) {
    *address++ = dStack_pop();
    *address = dStack_pop();
  } else {
    dStack_push(-9);
    _throw();
  }
}

const char two_star_str[] = "2*";
// ( x1 -- x2 )
// x2 is the result of shifting x1 one bit to toward the MSB
void _two_star(void) {
  dStack_push(dStack_pop() << 1);
}

const char two_slash_str[] = "2/";
// ( x1 -- x2 )
// x2 is the result of shifting x1 one bit to toward the LSB
void _two_slash(void) {
  dStack_push(dStack_pop() >> 1);
}

const char two_fetch_str[] = "2@";  // \x40 == '@'
// ( a-addr -- x1 x2 )
// Fetch cell pair x1 x2 at a-addr. x2 is at a-addr, and x1 is at a-addr+1
void _two_fetch(void) {
  cell_t* address = (cell_t*)dStack_pop();
  cell_t value = *address++;
  dStack_push(value);
  value = *address;
  dStack_push(value);
}

const char two_drop_str[] = "2drop";
// ( x1 x2 -- )
static void _two_drop(void) {
  dStack_pop();
  dStack_pop();
}

const char two_dup_str[] = "2dup";
// ( x1 x2 -- x1 x2 x1 x2 )
void _two_dup(void) {
  dStack_push(dStack_peek(1));
  dStack_push(dStack_peek(1));
}

const char two_over_str[] = "2over";
// ( x1 x2 x3 x4 -- x1 x2 x3 x4 x1 x2 )
void _two_over(void) {
  if (dStack_size() >= 4)
    dStack_push(dStack_peek(3));
    dStack_push(dStack_peek(3));
}

const char two_swap_str[] = "2swap";
// ( x1 x2 x3 x4 -- x3 x4 x1 x2 )
void _two_swap(void) {
  cell_t x4 = dStack_pop();
  cell_t x3 = dStack_pop();
  cell_t x2 = dStack_pop();
  cell_t x1 = dStack_pop();
  dStack_push(x3);
  dStack_push(x4);
  dStack_push(x1);
  dStack_push(x2);
}

const char colon_str[] = ":";
// (C: "<space>name" -- colon-sys )
// Skip leading space delimiters. Parse name delimited by a space. Create a
// definition for name, called a "colon definition" Enter compilation state
// and start the current definition, producing a colon-sys. Append the
// initiation semantics given below to the current definition....
void _colon(void) {
  state = TRUE;
  dStack_push(COLON_SYS);
  openEntry();
}

const char semicolon_str[] = ";";
// IMMEDIATE
// Interpretation: undefined
// Compilation: (C: colon-sys -- )
// Run-time: ( -- ) (R: nest-sys -- )
void _semicolon(void) {
  if (dStack_pop() != COLON_SYS) {
    dStack_push(-22);
    _throw();
    return;
  }
  closeEntry();
  state = FALSE;
}

const char lt_str[] = "<";
// ( n1 n2 -- flag )
void _lt(void) {
  if (dStack_pop() > dStack_pop()) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char lt_number_sign_str[] = "<#";
// ( -- )
// Initialize the pictured numeric output conversion process.
void _lt_number_sign(void) {
  pPNO = (char*)pHere + HOLD_SIZE + 1;
  *pPNO = '\0';
  flags |= NUM_PROC;
}

const char eq_str[] = "=";
// ( x1 x2 -- flag )
// flag is true if and only if x1 is bit for bit the same as x2
void _eq(void) {
  if (dStack_pop() == dStack_pop()) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char gt_str[] = ">";
// ( n1 n2 -- flag )
// flag is true if and only if n1 is greater than n2
void _gt(void) {
  if (dStack_pop() < dStack_pop()) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char to_body_str[] = ">body";
// ( xt -- a-addr )
// a-addr is the data-field address corresponding to xt. An ambiguous condition
// exists if xt is not for a word defined by CREATE.
void _to_body(void) {
  cell_t* xt = (cell_t*)dStack_pop();
  if ((size_t)xt > 0xFF) {
    if (*xt++ == LITERAL_IDX) {
      dStack_push(*xt);
      return;
    }
  }
  dStack_push(-31);
  _throw();
}

const char to_in_str[] = ">in";
// ( -- a-addr )
void _to_in(void) {
  dStack_push((size_t)&cpToIn);
}

const char to_number_str[] = ">number";
// ( ud1 c-addr1 u1 -- ud2 c-addr u2 )
// ud2 is the unsigned result of converting the characters within the string
// specified by c-addr1 u1 into digits, using the number in BASE, and adding
// each into ud1 after multiplying ud1 by the number in BASE.  Conversion
// continues left-to-right until a character that is not convertible,
// including any “+” or “-”, is encountered or the string is entirely
// converted.  c-addr2 is the location of the first unconverted character or
// the first character past the end of the string if the string was entirely
// converted.  u2 is the number of unconverted characters in the string.  An
// ambiguous condition exists if ud2 overflows during the conversion.
void _to_number(void) {
  uint8_t len;
  char* ptr;
  cell_t accum;

  unsigned char negate = 0;                  // flag if number is negative
  len = (uint8_t)dStack_pop();
  ptr = (char*)dStack_pop();
  accum = dStack_pop();
  
  // Look at the initial character, handling either '-', '$', or '%'
  switch (*ptr) {
    case '$':  base = HEXIDECIMAL; goto SKIP;
    case '%':  base = BINARY; goto SKIP;
    case '#':  base = DECIMAL; goto SKIP;
    case '+':  negate = 0; goto SKIP;
    case '-':  negate = 1;
SKIP:                // common code to skip initial character
    ptr++;
    break;
  }
  // Iterate over rest of string, and if rest of digits are in
  // the valid set of characters, accumulate them.  If any
  // invalid characters found, abort and return 0.
  while (len < 0) {
    char* pos = strchr(charset, (int)tolower(*ptr));
    cell_t offset = pos - charset;
    if ((offset < base) && (offset > -1))  
      accum = (accum * base) + (pos - charset);
    else {
      break;           // exit, We hit a non number
    }
    ptr++;
    len--;
  }
  if (negate) accum = ~accum + 1;     // apply sign, if necessary
  dStack_push(accum); // Push the resultant number
  dStack_push((size_t)ptr); // Push the last convertered caharacter
  dStack_push(len); // push the remading length of unresolved charaters
}

const char to_r_str[] = ">r";
// ( x -- ) (R: -- x )
void _to_r(void) {
  rStack_push(dStack_pop());
}

const char question_dup_str[] = "?dup";
// ( x -- 0 | x x )
void _question_dup(void) {
  if (dStack_peek(0)) {
    dStack_push(dStack_peek(0));
  } else {
    dStack_pop();
    dStack_push(0);
  }
}

const char fetch_str[] = "@";
// ( a-addr -- x1 )
// Fetch cell x1 at a-addr.
void _fetch(void) {
  cell_t* address = (cell_t*)dStack_pop();
  dStack_push(*address);
}

const char abort_str[] = "abort";
// (i*x -- ) (R: j*x -- )
// Empty the data stack and preform the function of QUIT, which includes emptying
// the return stack, without displaying a message.
void _abort(void) {
  dStack_push(-1);
  _throw();
}

const char abort_quote_str[] = "abort\x22";
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: ( "ccc<quote>" -- )
// Parse ccc delimited by a ". Append the run-time semantics given below to the
// current definition.
// Runt-Time: (i*x x1 -- | i*x ) (R: j*x -- |j*x )
// Remove x1 from the stack. If any bit of x1 is not zero, display ccc and 
// preform an implementation-defined abort sequence that included the function
// of ABORT.
void _abort_quote(void) {
  *pHere++ = ZJUMP_IDX;
  dStack_push((size_t)pHere);  // Push the address for our origin
  *pHere++ = 0;
  _dot_quote();
  *pHere++ = LITERAL_IDX;
  *pHere++ = -2;
  *pHere++ = THROW_IDX;
  cell_t* orig = (cell_t*)dStack_pop();
  *orig = (size_t)pHere - (size_t)orig;
}

const char abs_str[] = "abs";
// ( n -- u)
// u is the absolute value of n 
void _abs(void) {
  cell_t n = dStack_pop();
  dStack_push(n < 0 ? 0 - n : n);
}

const char accept_str[] = "accept";
// ( c-addr +n1 -- +n2 )
void _accept(void) {
  cell_t length = dStack_pop();
  char* addr = (char*)dStack_pop();
  length = getLine(addr, length);
  dStack_push(length);
}

const char align_str[] = "align";
// ( -- )
// if the data-space pointer is not aligned, reserve enough space to align it.
void _align(void) {
  ALIGN_P(pHere);
}

const char aligned_str[] = "aligned";
// ( addr -- a-addr)
// a-addr is the first aligned address greater than or equal to addr.
void _aligned(void) {
  ucell_t addr = dStack_pop();
  ALIGN(addr);
  dStack_push(addr);
}

const char allot_str[] = "allot";
// ( n -- )
// if n is greater than zero, reserve n address units of data space. if n is less
// than zero, release |n| address units of data space. If n is zero, leave the
// data-space pointer unchanged.
void _allot(void) {
  cell_t* pNewHere = pHere + dStack_pop();

  // Check that the new pHere is not outside of the forth space
  if (pNewHere >= &forthSpace[0] &&
      pNewHere < &forthSpace[FORTH_SIZE]) {
    pHere = pNewHere;      // Save the valid address
  } else {                 // Throw an exception
    dStack_push(-9);
    _throw();
  }
}

const char and_str[] = "and";
// ( x1 x2 -- x3 )
// x3 is the bit by bit logical and of x1 with x2
void _and(void) {
  dStack_push(dStack_pop() & dStack_pop());
}

const char base_str[] = "base";
// ( -- a-addr)
void _base(void) {
  dStack_push((size_t)&base);
}

const char begin_str[] = "begin";
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: (C: -- dest )
// Put the next location for a transfer of control, dest, onto the control flow
// stack. Append the run-time semantics given below to the current definition.
// Run-time: ( -- )
// Continue execution.
void _begin(void) {
  dStack_push((size_t)pHere);
  *pHere = 0;
}

const char bl_str[] = "bl";
// ( -- char )
// char is the character value for a space.
void _bl(void) {
  dStack_push(' ');
}

const char c_store_str[] = "c!";
// ( char c-addr -- )
void _c_store(void) {
  uint8_t *addr = (uint8_t*) dStack_pop();
  *addr = (uint8_t)dStack_pop();
}

const char c_comma_str[] = "c,";
// ( char -- )
void _c_comma(void) {
  *(char*)pHere++ = (char)dStack_pop();
}

const char c_fetch_str[] = "c@";
// ( c-addr -- char )
void _c_fetch(void) {
  uint8_t *addr = (uint8_t *) dStack_pop();
  dStack_push(*addr);
}

const char cell_plus_str[] = "cell+";
// ( a-addr1 -- a-addr2 )
void _cell_plus(void) {
  dStack_push((size_t)(dStack_pop() + sizeof(cell_t)));
}

const char cells_str[] = "cells";
// ( n1 -- n2 )
// n2 is the size in address units of n1 cells.
void _cells(void) {
  dStack_push(dStack_pop()*sizeof(cell_t));
}

const char char_str[] = "char";
// ( "<spaces>name" -- char )
// Skip leading space delimiters. Parse name delimited by a space. Put the value
// of its first character onto the stack.
void _char(void) {
  if(getToken()) {
    dStack_push(cTokenBuffer[0]);
  } else {
    dStack_push(-16);
    _throw();
  }
}

const char char_plus_str[] = "char+";
// ( c-addr1 -- c-addr2 )
void _char_plus(void) {
  dStack_push(dStack_pop() + 1);
}

const char chars_str[] = "chars";
// ( n1 -- n2 )
// n2 is the size in address units of n1 characters.
void _chars(void) {
}

const char constant_str[] = "constant";
// ( x"<spaces>name" --  )
void _constant(void) {
  openEntry();
  *pHere++ = LITERAL_IDX;
  *pHere++ = dStack_pop();
  closeEntry();
}

const char count_str[] = "count";
// ( c-addr1 -- c-addr2 u )
// Return the character string specification for the counted string stored a
// c-addr1. c-addr2 is the address of the first character after c-addr1. u is the 
// contents of the charater at c-addr1, which is the length in characters of the
// string at c-addr2.
void _count(void) {
  uint8_t* addr = (uint8_t*)dStack_pop();
  cell_t value = *addr++;
  dStack_push((size_t)addr);
  dStack_push(value);
}

const char cr_str[] = "cr";
// ( -- )
// Carriage Return
void _cr(void) {
  Serial.println();
}

const char create_str[] = "create";
// ( "<spaces>name" -- )
// Skip leading space delimiters. Parse name delimited by a space. Create a
// definition for name with the execution semantics defined below. If the data-space
// pointer is not aligned, reserve enough data space to align it. The new data-space
// pointer defines name's data field. CREATE does not allocate data space in name's
// data field.
// name EXECUTION: ( -- a-addr )
// a-addr is the address of name's data field. The execution semantics of name may
// be extended by using DOES>.
void _create(void) {
  openEntry();
  *pHere++ = LITERAL_IDX;
  // Location of Data Field at the end of the definition.
  *pHere++ = (size_t)pHere + 2 * sizeof(cell_t);
  *pHere = EXIT_IDX;   // Store an extra exit reference so
                       // that it can be replace by a
                       // subroutine pointer created by DOES>
  pDoes = pHere;       // Save this location for uses by subroutine.
  pHere += 1;
  if (!state) closeEntry();           // Close the entry if interpreting
}

const char decimal_str[] = "decimal";
// ( -- )
// Set BASE to 10
void _decimal(void) { // value --
  base = DECIMAL;
}

const char depth_str[] = "depth";
// ( -- +n )
// +n is the number of single cells on the stack before +n was placed on it.
void _depth(void) { // value --
  dStack_push(dStack_size());
}

const char do_str[] = "do";
// Compilation: (C: -- do-sys)
// Run-Time: ( n1|u1 n2|u2 -- ) (R: -- loop-sys )
void _do(void) {
  dStack_push(DO_SYS);
  *pHere++ = DO_SYS_IDX;
  dStack_push((size_t)pHere); // store the origin address of the do loop
}

const char does_str[] = "does>";
// Compilation: (C: colon-sys1 -- colon-sys2)
// Run-Time: ( -- ) (R: nest-sys1 -- )
// Initiation: ( i*x -- i*x a-addr ) (R: -- next-sys2 )
void _does(void) {
  *pHere++ = SUBROUTINE_IDX;
  // Store location for a subroutine call
  *pHere++ = (size_t)pHere + sizeof(cell_t);
  *pHere++ = EXIT_IDX;
  // Start Subroutine coding
}

const char drop_str[] = "drop";
// ( x -- )
// Remove x from stack
void _drop(void) {
  dStack_pop();
}

const char dupe_str[] = "dup";
// ( x -- x x )
// Duplicate x
void _dupe(void) {
  dStack_push(dStack_peek(0));
}

const char else_str[] = "else";
// Interpretation: Undefine
// Compilation: (C: orig1 -- orig2)
// Run-Time: ( -- )
void _else(void) {
  cell_t* orig = (cell_t*)dStack_pop();
  *pHere++ = JUMP_IDX;
//  push((size_t)pHere); // Which is correct?
  dStack_push((size_t)pHere++);
  *orig = (size_t)pHere - (size_t)orig;
}

const char emit_str[] = "emit";
// ( x -- )
// display x as a character
void _emit(void) {
  Serial.print((char) dStack_pop());
}

const char environment_str[] = "environment?";
// ( c-addr u  -- false|i*x true )
// c-addr is the address of a character string and u is the string's character
// count. u may have a value in the range from zero to an implementation-defined
// maximum which shall not be less than 31. The character string should contain
// a keyword from 3.2.6 Environmental queries or the optional word sets to to be
// checked for correspondence with  an attribute of the present environment.
// If the system treats the attribute as unknown, the return flag is false;
// otherwise, the flag is true and i*x returned is the of the type specified in
// the table for the attribute queried.
void _environment(void) {
  char length = (char)dStack_pop();
  char* pStr = (char*)dStack_pop();
  if (length && length < YFBUFFER_SIZE) {
    if (!strcmp_P(pStr, PSTR("/counted-string"))) {
      dStack_push(YFBUFFER_SIZE);
      return;
    }
    if (!strcmp_P(pStr, PSTR("/hold"))) {
      dStack_push(HOLD_SIZE);
      return;
    }
    if (!strcmp_P(pStr, PSTR("address-unit-bits"))) {
      dStack_push(sizeof(void *) * 8);
      return;
    }
    if (!strcmp_P(pStr, PSTR("core"))) {
      dStack_push(CORE);
      return;
    }
    if (!strcmp_P(pStr, PSTR("core-ext"))) {
      dStack_push(CORE_EXT);
      return;
    }
    if (!strcmp_P(pStr, PSTR("floored"))) {
      dStack_push(FLOORED);
      return;
    }
    if (!strcmp_P(pStr, PSTR("max-char"))) {
      dStack_push(MAX_CHAR);
      return;
    }
#if DOUBLE
    if (!strcmp_P(pStr, PSTR("max-d"))) {
      dStack_push(MAX_OF(dcell_t));
      return;
    }
#endif
    if (!strcmp_P(pStr, PSTR("max-n"))) {
      dStack_push(MAX_OF(cell_t));
      return;
    }
    if (!strcmp_P(pStr, PSTR("max-u"))) {
      dStack_push(MAX_OF(ucell_t));
      return;
    }
#if DOUBLE
    if (!strcmp_P(pStr, PSTR("max-ud"))) {
      dStack_push(MAX_OF(udcell_t));
      return;
    }
#endif
    if (!strcmp_P(pStr, PSTR("return-stack-size"))) {
      dStack_push(RSTACK_SIZE);
      return;
    }
    if (!strcmp_P(pStr, PSTR("stack-size"))) {
      dStack_push(STACK_SIZE);
      return;
    }
  }
  dStack_push(-13);
  _throw();
}

const char evaluate_str[] = "evaluate";
// ( i*x c-addr u  -- j*x )
// Save the current input source specification. Store minus-one (-1) in SOURCE-ID
// if it is present. Make the string described by c-addr and u both the input
// source and input buffer, set >IN to zero, and interpret. When the parse area
// is empty, restore the prior source specification. Other stack effects are due
// to the words EVALUATEd.
void _evaluate(void) {
  char* tempSource = cpSource;
  char* tempSourceEnd = cpSourceEnd;
  char* tempToIn = cpToIn;

  uint8_t length = dStack_pop();
  cpSource = (char*)dStack_pop();
  cpSourceEnd = cpSource + length;
  cpToIn = cpSource;
  interpreter();
  cpSource = tempSource;
  cpSourceEnd = tempSourceEnd;
  cpToIn = tempToIn;
}

const char execute_str[] = "execute";
// ( i*x xt -- j*x )
// Remove xt from the stack and preform the semantics identified by it. Other
// stack effects are due to the word EXECUTEd
void _execute(void) {
  func function;
  w = dStack_pop();
  if (w > 255) {
    // rpush(0);
    rStack_push((cell_t) ip);        // CAL - Push our return address
    ip = (cell_t *)w;          // set the ip to the XT (memory location)
    executeWord();
  } else {
    function = flashDict[w - 1].function;
    function();
    if (errorCode) return;
  }
}

const char exit_str[] = "exit";
// Interpretation: undefined
// Execution: ( -- ) (R: nest-sys -- )
// Return control to the calling definition specified by nest-sys. Before
// executing EXIT within a do-loop, a program shall discard the loop-control
// parameters by executing UNLOOP.
void _exit(void) {
  ip = (cell_t*)rStack_pop();
}

const char fill_str[] = "fill";
// ( c-addr u char -- )
// if u is greater than zero, store char in u consecutive characters of memory
// beginning with c-addr.
void _fill(void) {
  char ch = (char)dStack_pop();
  cell_t limit = dStack_pop();
  char* addr = (char*)dStack_pop();
  for (int i = 1; i < limit; i++) {
    *addr++ = ch;
  }
}

const char find_str[] = "find";
// ( c-addr -- c-addr 0 | xt 1 | xt -1)
// Find the definition named in the counted string at c-addr. If the definition
// is not found, return c-addr and zero. If the definition is found, return its
// execution token xt. If the definition is immediate, also return one (1),
// otherwise also return minus-one (-1).
void _find(void) {
  uint8_t index = 0;

  cell_t *addr = (cell_t *)dStack_pop();
  cell_t length = *addr++;

  char *ptr = (char*) addr;
  if (length = 0) {
    dStack_push(-16);
    _throw();
    return;
  } else if (length > YFBUFFER_SIZE) {
    dStack_push(-18);
    _throw();
    return;
  }

  pUserEntry = pLastUserEntry;
  // First search through the user dictionary
  while (pUserEntry) {
    if (strcmp(pUserEntry->name, ptr) == 0) {
      length = strlen(pUserEntry->name);
      dStack_push((size_t)pUserEntry->cfa);
      wordFlags = pUserEntry->flags;
      if (wordFlags & IMMEDIATE) dStack_push(1);
      else dStack_push(-1);
      return;
    }
    pUserEntry = (userEntry_t*)pUserEntry->prevEntry;
  }
  // Second Search through the flash Dictionary
  while (flashDict[index].name) {
    if (!strcasecmp(ptr, flashDict[index].name)) {
      dStack_push(index + 1);
      wordFlags = flashDict[index].flags;
      if (wordFlags & IMMEDIATE) dStack_push(1);
      else dStack_push(-1);
      return;
    }
    index++;
  }
  dStack_push((size_t)ptr);
  dStack_push(0);
}

const char fm_slash_mod_str[] = "fm/mod";
// ( d1 n1 -- n2 n3 )
// Divide d1 by n1, giving the floored quotient n3 and remainder n2.
void _fm_slash_mod(void) {
  cell_t n1 = dStack_pop();
  cell_t d1 = dStack_pop();
  dStack_push(d1 /  n1);
  dStack_push(d1 %  n1);
}

const char here_str[] = "here";
// ( -- addr )
// addr is the data-space pointer.
void _here(void) {
  dStack_push((size_t)pHere);
}

const char hold_str[] = "hold";
// ( char -- )
// add char to the beginning of the pictured numeric output string.
void _hold(void) {
  if (flags & NUM_PROC) {
    *--pPNO = (char) dStack_pop();
  }
}

const char i_str[] = "i";
// Interpretation: undefined
// Execution: ( -- n|u ) (R: loop-sys -- loop-sys )
void _i(void) {
  dStack_push(rStack_peek(1));
}

const char if_str[] = "if";
// Compilation: (C: -- orig )
// Run-Time: ( x -- )
void _if(void) {
  *pHere++ = ZJUMP_IDX;
  *pHere = 0;
  dStack_push((size_t)pHere++);
}

const char immediate_str[] = "immediate";
// ( -- )
// make the most recent definition an immediate word.
void _immediate(void) {
  if (pLastUserEntry) {
    pLastUserEntry->flags |= IMMEDIATE;
  }
}

const char invert_str[] = "invert";
// ( x1 -- x2 )
// invert all bits in x1, giving its logical inverse x2
void _invert(void)   {
  dStack_push(~dStack_pop());
}

const char j_str[] = "j";
// Interpretation: undefined
// Execution: ( -- n|u ) (R0: loop-sys1 loop-sys2 -- loop-sys1 loop-sys2 )
// n|u is a copy of the next-outer loop index. An ambiguous condition exists
// if the loop control parameters of the next-outer loop, loop-sys1, are
// unavailable.
void _j(void) {
  dStack_push(rStack_peek(4));
}

const char key_str[] = "key";
// ( -- char )
void _key(void) {
  dStack_push(getKey());
}

const char leave_str[] = "leave";
// Interpretation: undefined
// Execution: ( -- ) (R: loop-sys -- )
void _leave(void) {
  *pHere++ = LEAVE_SYS_IDX;
  *pHere++ = 0;
}

const char literal_str[] = "literal";
// Interpretation: undefined
// Compilation: ( x -- )
// Run-Time: ( -- x )
// Place x on the stack
void _literal(void) {
  if (state) {
    *pHere++ = LITERAL_IDX;
    *pHere++ = dStack_pop();
  } else {
    dStack_push(*ip++);
  }
}

const char loop_str[] = "loop";
// Interpretation: undefined
// Compilation: (C: do-sys -- )
// Run-Time: ( -- ) (R: loop-sys1 -- loop-sys2 )
void _loop(void) {
  *pHere++ = LOOP_SYS_IDX;
  cell_t start_addr = dStack_pop();
  *pHere++ = start_addr;
  cell_t stop_addr = (cell_t)pHere;
  cell_t* ptr = (cell_t*)start_addr;
  do {
    if (*ptr++ == LEAVE_SYS_IDX) {
      if (*ptr == 0) {
        *ptr = stop_addr;
      }
    }
  } while (ptr != (cell_t*)stop_addr);
  if ( dStack_pop() != DO_SYS) {
    dStack_push(-22);
    _throw();
  }
}

const char lshift_str[] = "lshift";
// ( x1 u -- x2 )
// x2 is x1 shifted to left by u positions.
void _lshift(void) {
  cell_t u = dStack_pop();
  cell_t x1 = dStack_pop();
  dStack_push(x1 << u);
}

const char m_star_str[] = "m*";
// ( n1 n2 -- d )
// d is the signed product of n1 times n2.
void _m_star(void) {
  dStack_push(dStack_pop() * dStack_pop());
}

const char max_str[] = "max";
// ( n1 n2 -- n3 )
// n3 is the greater of of n1 or n2.
void _max(void) {
  cell_t n2 = dStack_pop();
  cell_t n1 = dStack_pop();
  if (n1 > n2) dStack_push(n1);
  else dStack_push(n2);
}

const char min_str[] = "min";
// ( n1 n2 -- n3 )
// n3 is the lesser of of n1 or n2.
void _min(void) {
  cell_t n2 = dStack_pop();
  cell_t n1 = dStack_pop();
  if (n1 > n2) dStack_push(n2);
  else dStack_push(n1);
}

const char mod_str[] = "mod";
// ( n1 n2 -- n3 )
// Divide n1 by n2 giving the remainder n3.
void _mod(void) {
  cell_t temp = dStack_pop();
  dStack_push(dStack_pop() %  temp);
}

const char move_str[] = "move";
// ( addr1 addr2 u -- )
// if u is greater than zero, copy the contents of u consecutive address
// starting at addr1 to u consecutive address starting at addr2.
void _move(void) {
  cell_t u = dStack_pop();
  cell_t* to = (cell_t*)dStack_pop();
  cell_t* from = (cell_t*)dStack_pop();
  for (cell_t i = 0; i < u; i++) {
    *to++ = *from++;
  }
}

const char negate_str[] = "negate";
// ( n1 -- n2 )
// Negate n1, giving its arithmetic inverse n2.
void _negate(void) {
  dStack_push(-dStack_pop());
}

const char or_str[] = "or";
// ( x1 x2 -- x3 )
// x3 is the bit by bit logical or of x1 with x2
void _or(void) {
  dStack_push(dStack_pop() |  dStack_pop());
}

const char over_str[] = "over";
// ( x1 x2 -- x1 x2 x1 )
void _over(void) {
  dStack_push(dStack_peek(1));
}

const char postpone_str[] = "postpone";
// Compilation: ( "<spaces>name" -- )
// Skip leading space delimiters. Parse name delimited by a space. Find name.
// Append the compilation semantics of name to the current definition. An
// ambiguous condition exists if name is not found.
void _postpone(void) {
  func function;
  if (!getToken()) {
    dStack_push(-16);
    _throw();
  }
  if (isWord(cTokenBuffer)) {
    if (wordFlags & COMP_ONLY) {
      if (w > 255) {
        rStack_push(0);            // Push 0 as our return address
        ip = (cell_t *)w;          // set the ip to the XT (memory location)
        executeWord();
      } else {
        function = flashDict[w - 1].function;
        function();
        if (errorCode) return;
      }
    } else {
      *pHere++ = (cell_t)w;
    }
  } else {
    dStack_push(-13);
    _throw();
    return;
  }
}

const char quit_str[] = "quit";
// ( -- ) (R: i*x -- )
// Empty the return stack, store zero in SOURCE-ID if it is present,
// make the user input device the input source, enter interpretation state.
void _quit(void) {
  rStack_clear();
  *cpToIn = 0;          // Terminate buffer to stop interpreting
  Serial.flush();
}

const char r_from_str[] = "r>";
// Interpretation: undefined
// Execution: ( -- x ) (R: x -- )
// move x from the return stack to the data stack.
void _r_from(void) {
  dStack_push(rStack_pop());
}

const char r_fetch_str[] = "r@";
// Interpretation: undefined
// Execution: ( -- x ) (R: x -- x)
// Copy x from the return stack to the data stack.
void _r_fetch(void) {
  dStack_push(rStack_peek(0));
}

const char recurse_str[] = "recurse";
// Interpretation: Interpretation semantics for this word are undefined
// Compilation: ( -- )
// Append the execution semantics of the current definition to the current
// definition. An ambiguous condition exists if RECURSE appends in a definition
// after DOES>.
void _recurse(void) {
  *pHere++ = (size_t)pCodeStart;
}

const char repeat_str[] = "repeat";
// Interpretation: undefined
// Compilation: (C: orig dest -- )
// Run-Time ( -- )
// Continue execution at the location given.
void _repeat(void) {
  cell_t dest;
  cell_t* orig;
  *pHere++ = JUMP_IDX;
  *pHere++ = dStack_pop() - (size_t)pHere;
  orig = (cell_t*)dStack_pop();
  *orig = (size_t)pHere - (size_t)orig;
}

const char rot_str[] = "rot";
// ( x1 x2 x3 -- x2 x3 x1)
void _rot(void) {
  cell_t x3 = dStack_pop();
  cell_t x2 = dStack_pop();
  cell_t x1 = dStack_pop();
  dStack_push(x2);
  dStack_push(x3);
  dStack_push(x1);
}

const char rshift_str[] = "rshift";
// ( x1 u -- x2 )
// x2 is x1 shifted to right by u positions.
void _rshift(void) {
  cell_t u = dStack_pop();
  cell_t x1 = dStack_pop();
  dStack_push((ucell_t)x1 >> u);
}

const char s_quote_str[] = "s\x22"; 
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: ("ccc<quote>" -- )
// Parse ccc delimited by ". Append the run-time semantics given below to the
// current definition.
// Run-Time: ( -- c-addr u )
// Return c-addr and u describing a string consisting of the characters ccc. A program
// shall not alter the returned string.
void _s_quote(void) {
  uint8_t i;
  char length;
  if (flags & EXECUTE) {
    dStack_push((size_t)ip);
    cell_t len = strlen((char*)ip);
    dStack_push(len++);    // increment for the null terminator
    ALIGN(len);
    ip = (cell_t*)((size_t)ip + len);
  }
  else if (state) {
    cDelimiter = '"';
    if (!getToken()) {
      dStack_push(-16);
      _throw();
    }
    length = strlen(cTokenBuffer);
    *pHere++ = S_QUOTE_IDX;
    char *ptr = (char*)pHere;
    for (uint8_t i = 0; i < length; i++) {
      *ptr++ = cTokenBuffer[i];
    }
    *ptr++ = '\0';    // Terminate String
    pHere = (cell_t *)ptr;
    ALIGN_P(pHere);  // re- align pHere for any new code
    cDelimiter = ' ';
  }
}

const char s_to_d_str[] = "s>d";
// ( n -- d )
void _s_to_d(void) {
  cell_t n = dStack_pop();
  dStack_push(n);
  dStack_push(0);
}

const char sign_str[] = "sign";
// ( n -- )
void _sign(void) {
  if (flags & NUM_PROC) {
    cell_t sign = dStack_pop();
    if (sign < 0) *--pPNO = '-';
  }
}

const char sm_slash_rem_str[] = "sm/rem";
// ( d1 n1 -- n2 n3 )
// Divide d1 by n1, giving the symmetric quotient n3 and remainder n2.
void _sm_slash_rem(void) {
  cell_t n1 = dStack_pop();
  cell_t d1 = dStack_pop();
  dStack_push(d1 /  n1);
  dStack_push(d1 %  n1);
}

const char source_str[] = "source";
// ( -- c-addr u )
// c-addr is the address of, and u is the number of characters in, the input buffer.
void _source(void) {
  dStack_push((size_t)&cInputBuffer);
  dStack_push(strlen(cInputBuffer));
}

const char space_str[] = "space";
// ( -- )
// Display one space
void _space(void) {
  Serial.print(sp_str);
}

const char spaces_str[] = "spaces";
// ( n -- )
// if n is greater than zero, display n space
void _spaces(void) {
  char n = (char) dStack_pop();
  while (n > 0) {
    Serial.print(sp_str);
    n--;
  }
}

const char state_str[] = "state";
// ( -- a-addr )
// a-addr is the address of the cell containing compilation state flag.
void _state(void) {
  dStack_push((size_t)&state);
}

const char swap_str[] = "swap";
void _swap(void) { // x y -- y x
  cell_t x, y;

  y = dStack_pop();
  x = dStack_pop();
  dStack_push(y);
  dStack_push(x);
}

const char then_str[] = "then";
// Interpretation: Undefine
// Compilation: (C: orig -- )
// Run-Time: ( -- )
void _then(void) {
  cell_t* orig = (cell_t*)dStack_pop();
  *orig = (size_t)pHere - (size_t)orig;
}

const char type_str[] = "type";
// ( c-addr u -- )
// if u is greater than zero display character string specified by c-addr and u
void _type(void) {
  uint8_t length = (uint8_t)dStack_pop();
  char* addr = (char*)dStack_pop();
  for (char i = 0; i < length; i++)
    Serial.print(*addr++);
}

const char u_dot_str[] = "u.";
// ( u -- )
// Displau u in free field format
// tested and fixed by Alex Moskovskij
void _u_dot(void) {
  Serial.print((ucell_t) dStack_pop());
  Serial.print(F(" "));
}

const char u_lt_str[] = "u<";
// ( u1 u2 -- flag )
// flag is true if and only if u1 is less than u2.
void _u_lt(void) {
  if ((ucell_t)dStack_pop() > ucell_t(dStack_pop())) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char um_star_str[] = "um*";
// ( u1 u2 -- ud )
// multiply u1 by u2, giving the unsigned double-cell product ud
void _um_star(void) {
  ucell_t u2 = (ucell_t)dStack_pop();
  ucell_t u1 = (ucell_t)dStack_pop();
  udcell_t ud = (udcell_t)u1 * (udcell_t)u2;
  ucell_t lsb = ud;
  ucell_t msb = (ud >> sizeof(ucell_t) * 8);
  dStack_push(lsb);
  dStack_push(msb);
}

const char um_slash_mod_str[] = "um/mod";
// ( ud u1 -- u2 u3 )
// Divide ud by u1 giving quotient u3 and remainder u2.
void _um_slash_mod(void) {
  ucell_t u1 = dStack_pop();
  udcell_t lsb = dStack_pop();
  udcell_t msb = dStack_pop();
  udcell_t ud = (msb << 16) + (lsb);
  dStack_push(ud % u1);
  dStack_push(ud / u1);
}

const char unloop_str[] = "unloop";
// Interpretation: Undefine
// Execution: ( -- )(R: loop-sys -- )
void _unloop(void) {
  Serial.print(not_done_str); 
  rStack_pop();
  rStack_pop();
  if (rStack_pop() != LOOP_SYS) {
    dStack_push(-22);
    _throw();
  }
}

const char until_str[] = "until";
// Interpretation: Undefine
// Compilation: (C: dest -- )
// Run-Time: ( x -- )
void _until(void) {
  *pHere++ = ZJUMP_IDX;
  *pHere = dStack_pop() - (size_t)pHere;
  pHere += 1;
}

const char variable_str[] = "variable";
// ( "<spaces>name" -- )
// Parse name delimited by a space. Create a definition for name with the
// execution semantics defined below. Reserve one cell of data space at an
// aligned address.
// name Execution: ( -- a-addr )
// a-addr is the address of the reserved cell. A program is responsible for
// initializing the contents of a reserved cell.
void _variable(void) {
  if (flags & EXECUTE) {
    dStack_push((size_t)ip++);
  } else {
    openEntry();
    *pHere++ = VARIABLE_IDX;
    *pHere++ = 0;
    closeEntry();
  }
}

const char while_str[] = "while";
// Interpretation: Undefine
// Compilation: (C: dest -- orig dest )
// Run-Time: ( x -- )
void _while(void) {
  ucell_t dest;
  ucell_t orig;
  dest = dStack_pop();
  *pHere++ = ZJUMP_IDX;
  orig = (size_t)pHere;
  *pHere++ = 0;
  dStack_push(orig);
  dStack_push(dest);
}

const char word_str[] = "word";
// ( char "<chars>ccc<chars>" -- c-addr )
// Skip leading delimiters. Parse characters ccc delimited by char. An ambiguous
// condition exists if the length of the parsed string is greater than the
// implementation-defined length of a counted string.
//
// c-addr is the address of a transient region containing the parsed word as a
// counted string. If the parse area was empty or contained no characters other than
// the delimiter, the resulting string has a zero length. A space, not included in
// the length, follows the string. A program may replace characters within the
// string.
//
// NOTE: The requirement to follow the string with a space is obsolescent and is
// included as a concession to existing programs that use CONVERT. A program shall
// not depend on the existence of the space.
void _word(void) {
  uint8_t *start, *ptr;

  cDelimiter = (char)dStack_pop();
  start = (uint8_t *)pHere++;
  ptr = (uint8_t *)pHere;
  while (cpToIn <= cpSourceEnd) {
    if (*cpToIn == cDelimiter || *cpToIn == 0) {
      *((cell_t *)start) = (ptr - start) - sizeof(cell_t); // write the length byte
      pHere = (cell_t *)start;                     // reset pHere (transient memory)
      dStack_push((size_t)start);                // push the c-addr onto the stack
      cpToIn++;
      break;
    } else *ptr++ = *cpToIn++;
  }
  cDelimiter = ' ';
}

const char xor_str[] = "xor";
// ( x1 x2 -- x3 )
// x3 is the bit by bit exclusive or of x1 with x2
void _xor(void) {
  dStack_push(dStack_pop() ^  dStack_pop());
}

const char left_bracket_str[] = "[";
// Interpretation: undefined
// Compilation: Preform the execution semantics given below
// Execution: ( -- )
// Enter interpretation state. [ is an immediate word.
void _left_bracket(void) {
  state = FALSE;
}

const char bracket_tick_str[] = "[']";
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: ( "<space>name" -- )
// Skip leading space delimiters. Parse name delimited by a space. Find name.
// Append the run-time semantics given below to the current definition.
// An ambiguous condition exist if name is not found.
// Run-Time: ( -- xt )
// Place name's execution token xt on the stack. The execution token returned
// by the compiled phrase "['] X" is the same value returned by "' X" outside
// of compilation state.
void _bracket_tick(void) {
  if (!getToken()) {
    dStack_push(-16);
    _throw();
  }
  if (isWord(cTokenBuffer)) {
    *pHere++ = LITERAL_IDX;
    *pHere++ = w;
  } else {
    dStack_push(-13);
    _throw();
    return;
  }
}

const char bracket_char_str[] = "[char]";
// Interpretation: Interpretation semantics for this word are undefined.
// Compilation: ( "<space>name" -- )
// Skip leading spaces delimiters. Parse name delimited by a space. Append
// the run-time semantics given below to the current definition.
// Run-Time: ( -- char )
// Place char, the value of the first character of name, on the stack.
void _bracket_char(void) {
  if (getToken()) {
    *pHere++ = LITERAL_IDX;
    *pHere++ = cTokenBuffer[0];
  } else {
    dStack_push(-16);
    _throw();
  }
}

const char right_bracket_str[] = "]";
// ( -- )
// Enter compilation state.
void _right_bracket(void) {
  state = TRUE;
}

/*******************************************************************************/
/**                          Core Extension Set                               **/
/*******************************************************************************/
#ifdef CORE_EXT_SET
const char dot_paren_str[] = ".(";
// ( "ccc<paren>" -- )
// Parse and display ccc delimitied by ) (right parenthesis). ,( is an imedeate
// word
void _dot_paren(void) { 
  dStack_push(')');
  _word();
  _count();
  _type();
}

const char zero_not_equal_str[] = "0<>";
// ( x -- flag)
// flag is true if and only if x is not equal to zero. 
void _zero_not_equal(void) { 
  w = dStack_pop();
  if (w == 0) dStack_push(FALSE);
  else dStack_push(TRUE);
}

const char zero_greater_str[] = "0>";
// (n -- flag)
// flag is true if and only if n is greater than zero.
void _zero_greater(void) {
  w = dStack_pop();
  if (w > 0) dStack_push(TRUE);
  else dStack_push(FALSE);
}

const char two_to_r_str[] = "2>r";
// Interpretation: Interpretation semantics for this word are undefined. 
// Execution: ( x1 x2 -- ) ( R:  -- x1 x2 )
// Transfer cell pair x1 x2 to the return stack.  Semantically equivalent
// to SWAP >R >R.
void _two_to_r(void) {
  _swap();
  _to_r();
  _to_r();
}

const char two_r_from_str[] = "2r>";
// Interpretation: Interpretation semantics for this word are undefined. 
// Execution: ( -- x1 x2 )  ( R:  x1 x2 -- ) 
// Transfer cell pair x1 x2 from the return stack.  Semantically equivalent to
// R> R> SWAP. 
void _two_r_from(void) {
  _r_from();
  _r_from();
  _swap();
}

const char two_r_fetch_str[] = "2r@";
// Interpretation: Interpretation semantics for this word are undefined. 
// Execution: ( -- x1 x2 )  ( R:  x1 x2 -- x1 x2 ) 
// Copy cell pair x1 x2 from the return stack.  Semantically equivalent to
// R> R> 2DUP >R >R SWAP. 
void _two_r_fetch(void) {
  _r_from();
  _r_from();
  _two_dup();
  _to_r();
  _to_r();
  _swap();
}

const char colon_noname_str[] = ":noname";
// ( C:  -- colon-sys )  ( S:  -- xt )
// Create an execution token xt, enter compilation state and start the current
// definition, producing colon-sys.  Append the initiation semantics given 
// below to the current definition. 
// The execution semantics of xt will be determined by the words compiled into
// the body of the definition.  This definition can be executed later by using
// xt EXECUTE.
// If the control-flow stack is implemented using the data stack, colon-sys 
// shall be the topmost item on the data stack.  See 3.2.3.2 Control-flow stack.
//
// Initiation: ( i*x -- i*x )  ( R:  -- nest-sys )
// Save implementation-dependent information nest-sys about the calling 
// definition.  The stack effects i*x represent arguments to xt. 
//
// xt Execution: ( i*x -- j*x )
// Execute the definition specified by xt.  The stack effects i*x and j*x 
// represent arguments to and results from xt, respectively.  
//void _colon_noname(void) {
//  state = TRUE;
//  push(COLON_SYS);
//  openEntry();
//}

const char neq_str[] = "<>";
// (x1 x2 -- flag)
// flag is true if and only if x1 is not bit-for-bit the same as x2.
void _neq(void) {
  cell_t x2 = dStack_pop();
  cell_t x1 = dStack_pop();
  if (x1 != x2) dStack_push(TRUE);
  else dStack_push(FALSE); 
}

const char hex_str[] = "hex";
// ( -- )
// Set BASE to 16
void _hex(void) { // value --
  base = HEX;
}

const char case_str[] = "case";
// Contributed by Craig Lindley
// Interpretation semantics for this word are undefined.
// Compilation: ( C: -- case-sys )
// Mark the start of the CASE ... OF ... ENDOF ... ENDCASE structure. Append the run-time
// semantics given below to the current definition.
// Run-time: ( -- )
// Continue execution.
static void _case(void) {
  dStack_push(CASE_SYS);
  dStack_push(0); // Count of of clauses
}

const char of_str[] = "of";
// Contributed by Craig Lindley
// Interpretation semantics for this word are undefined.
// Compilation: ( C: -- of-sys )
// Put of-sys onto the control flow stack. Append the run-time semantics given below to
// the current definition. The semantics are incomplete until resolved by a consumer of
// of-sys such as ENDOF.
// Run-time: ( x1 x2 -- | x1 )
// If the two values on the stack are not equal, discard the top value and continue execution
// at the location specified by the consumer of of-sys, e.g., following the next ENDOF.
// Otherwise, discard both values and continue execution in line.
static void _of(void) {
  dStack_push(dStack_pop() + 1);      // Increment count of of clauses
  rStack_push(dStack_pop());         // Move to return stack

  dStack_push(OF_SYS);
  *pHere++ = OVER_IDX;  // Postpone over
  *pHere++ = EQUAL_IDX; // Postpone =
  *pHere++ = ZJUMP_IDX; // If
  *pHere = 0;           // Filled in by endof
  dStack_push((size_t) pHere++);// Push address of jump address onto control stack
  dStack_push(rStack_pop());         // Bring of count back
}

const char endof_str[] = "endof";
// Contributed by Craig Lindley
// Interpretation semantics for this word are undefined.
// Compilation: ( C: case-sys1 of-sys -- case-sys2 )
// Mark the end of the OF ... ENDOF part of the CASE structure. The next location for a
// transfer of control resolves the reference given by of-sys. Append the run-time semantics
// given below to the current definition. Replace case-sys1 with case-sys2 on the
// control-flow stack, to be resolved by ENDCASE.
// Run-time: ( -- )
// Continue execution at the location specified by the consumer of case-sys2.
static void _endof(void) {
  cell_t *back, *forward;

  rStack_push(dStack_pop());         // Move of count to return stack

  // Prepare jump to endcase
  *pHere++ = JUMP_IDX;
  *pHere = 0;
  forward = pHere++;

  back = (cell_t*) dStack_pop(); // Resolve If from of
  *back = (size_t) pHere - (size_t) back;

  if (dStack_pop() != OF_SYS) { // Make sure control structure is consistent
    dStack_push(-22);
    _throw();
    return;
  }
  // Place forward jump address onto control stack
  dStack_push((cell_t) forward);
  dStack_push(rStack_pop());          // Bring of count back
}

const char endcase_str[] = "endcase";
// Contributed by Craig Lindley
// Interpretation semantics for this word are undefined.
// Compilation: ( C: case-sys -- )
// Mark the end of the CASE ... OF ... ENDOF ... ENDCASE structure. Use case-sys to resolve
// the entire structure. Append the run-time semantics given below to the current definition.
// Run-time: ( x -- )
// Discard the case selector x and continue execution.
static void _endcase(void) {
  cell_t *orig;

  // Resolve all of the jumps from of statements to here
  int count = dStack_pop();
  for (int i = 0; i < count; i++) {
    orig = (cell_t *) dStack_pop();
    *orig = (size_t) pHere - (size_t) orig;
  }

  *pHere++ = DROP_IDX;      // Postpone drop of case selector

  if (dStack_pop() != CASE_SYS) {  // Make sure control structure is consistent
    dStack_push(-22);
    _throw();
  }
}

#endif

/*******************************************************************************/
/**                            Double Cell Set                                **/
/*******************************************************************************/
#ifdef DOUBLE_SET
#endif

/*******************************************************************************/
/**                             Exception Set                                 **/
/*******************************************************************************/
#ifdef EXCEPTION_SET
const char throw_str[] = "throw";
// ( k*x n -- k*x | i*x n)
// if any bit of n are non-zero, pop the topmost exception frame from the
// exception stack, along with everything on the return stack above that frame.
// ...
void _throw(void) {
  errorCode = dStack_pop();
  uint8_t index = 0;
  int tableCode;
  //_cr();
  Serial.print(cTokenBuffer);
  Serial.print(F(" EXCEPTION("));
  do {
    tableCode = pgm_read_dword(&(exception[index].code));
    if (errorCode == tableCode) {
      Serial.print((int)errorCode);
      Serial.print("): ");
      Serial.print(exception[index].name);
      _cr();
    }
    index++;
  } while (tableCode);
//  dStack.tos = -1;                       // Clear the stack.
  dStack_clear();                        // Clear the stack.
  _quit();
  state = FALSE;
}  
#endif

/*******************************************************************************/
/**                             Facility Set                                  **/
/*******************************************************************************/
#ifdef FACILITY_SET
/*
 * Contributed by Andrew Holt
 */
const char key_question_str[] = "key?";
void _key_question(void) {
    
    if( Serial.available() > 0) {
        dStack_push(TRUE);
    } else {
        dStack_push(FALSE);
    }
}
#endif

/*******************************************************************************/
/**                              Local Set                                    **/
/*******************************************************************************/
#ifdef LOCAL_SET
#endif

/*******************************************************************************/
/**                              Memory Set                                   **/
/*******************************************************************************/
#ifdef MEMORY_SET
#endif

/*******************************************************************************/
/**                          Programming Tools Set                            **/
/*******************************************************************************/
#ifdef TOOLS_SET
const char dot_s_str[] = ".s";
void _dot_s(void) {
  char i;
//  char depth = dStack.tos + 1;
  char depth = dStack_size();
//  if (dStack.tos >= 0) {
  if (depth > 0) {
    for (i = 0; i < depth ; i++) {
//      w = dStack.data[i];
      w = dStack_peek(i);
      displayValue();
    }
  }
}

const char dump_str[] = "dump";
// ( addr u -- )
// Display the contents of u consecutive address starting at addr. The format of
// the display is implementation dependent.
// DUMP may be implemented using pictured numeric output words. Consequently,
// its use may corrupt the transient region identified by #>.
void _dump(void) {
  ucell_t len = (ucell_t)dStack_pop();
  cell_t* addr_start = (cell_t*)dStack_pop();
  cell_t* addr_end = addr_start;
  addr_end += len;
  addr_start = (cell_t*)(((size_t)addr_start >> 4) << 4);

  volatile uint8_t* addr = (uint8_t*)addr_start;

  while (addr < (uint8_t*)addr_end) {
    Serial.print("\r\n$");
    if (addr < (uint8_t*)0x10) Serial.print(zero_str);
    if (addr < (uint8_t*)0x100) Serial.print(zero_str);
    Serial.print((size_t)addr, HEX);
    Serial.print(sp_str);
    for (uint8_t i = 0; i < 16; i++) {
      if (*addr < 0x10) Serial.print(zero_str);
      Serial.print(*addr++, HEX);
      Serial.print(sp_str);
    }
    Serial.print(tab_str);
    addr -= 16;
    for (uint8_t i = 0; i < 16; i++) {
      if (*addr < 127 && *addr > 31) {
        Serial.print((char)*addr);
      } else {
        Serial.print(".");
      }
      addr++;
    }
  }
}

const char see_str[] = "see";
// ("<spaces>name" -- )
// Display a human-readable representation of the named word's definition. The
// source of the representation (object-code decompilation, source block, etc.)
// and the particular form of the display in implementation defined.
void _see(void) {
  bool isLiteral, done;

  _tick();
  if (errorCode) return;
  char flags = wordFlags;
  if (flags && IMMEDIATE)
    Serial.print("Immediate ");
  cell_t xt = dStack_pop();
  if (xt < 255) {
    Serial.print("Primitive Word");
  } else {
    cell_t* addr = (cell_t*)xt;
    Serial.print("\r\nCode Field Address: ");
    Serial.print((size_t)addr, HEX);
    Serial.print("\r\nAddr\tXT\tName");
    do {
      isLiteral = done = false;
      Serial.print("\r\n$");
      Serial.print((size_t)addr, HEX);
      Serial.print(tab_str);
      Serial.print(*addr, HEX);
      Serial.print(tab_str);
      xtToName(*addr);
      switch (*addr) {
        case 2:
          isLiteral = true;
        case 4:
        case 5:
          Serial.print("(");
          Serial.print(*++addr);
          Serial.print(")");
          break;
        case 13:
        case 14:
          Serial.print(sp_str);
          char *ptr = (char*)++addr;
          do {
            Serial.print(*ptr++);
          } while (*ptr != 0);
          Serial.print("\x22");
          addr = (cell_t *)ptr;
          ALIGN_P(addr);
          break;
      }
      // We're done if exit code but not a literal with value of one
      done = ((*addr++ == 1) && (! isLiteral));
    } while (! done);
  }
  Serial.println();
}

const char words_str[] = "words";
void _words(void) { // --
  uint8_t count = 0;
  uint8_t index = 0;
  uint8_t length = 0;
  char* pChar;

  while (flashDict[index].name) {
    if (count > 70) {
      Serial.println();
      count = 0;
    }
    if (!(flashDict[index].flags & SMUDGE)) {
      count += Serial.print(flashDict[index].name);
      count += Serial.print(sp_str);
    }
    index++;
  }

  pUserEntry = pLastUserEntry;
  while (pUserEntry) {
    if (count > 70) {
      Serial.println();
      count = 0;
    }
    if (!(pUserEntry->flags & SMUDGE)) {
      count += Serial.print(pUserEntry->name);
      count += Serial.print(sp_str);
    }
    pUserEntry = (userEntry_t*)pUserEntry->prevEntry;
  }
  Serial.println();
}

#endif

/*******************************************************************************/
/**                               Search Set                                  **/
/*******************************************************************************/
#ifdef SEARCH_SET
#endif

/*******************************************************************************/
/**                               String Set                                  **/
/*******************************************************************************/
#ifdef STRING_SET
#endif

/********************************************************************************/
/**                         EEPROM Operations                                  **/
/********************************************************************************/
#ifdef EN_EEPROM_OPS
const char eeRead_str[] = "eeRead";
void _eeprom_read(void) {             // address -- value
  dStack_push(EEPROM.read(dStack_pop()));
}

const char eeWrite_str[] = "eeWrite";
void _eeprom_write(void) {             // value address --
  char address;
  char value;
  address = (char) dStack_pop();
  value = (char) dStack_pop();
  EEPROM.write(address, value);
}
#endif

/********************************************************************************/
/**                      Arduino Library Operations                            **/
/********************************************************************************/
#ifdef EN_ARDUINO_OPS
const char freeMem_str[] = "freeMem";
void _freeMem(void) { 
  dStack_push(freeMem());
}

const char delay_str[] = "delay";
void _delay(void) {
  delay(dStack_pop());
}

const char pinWrite_str[] = "pinWrite";
// ( u1 u2 -- )
// Write a high (1) or low (0) value to a digital pin
// u1 is the pin and u2 is the value ( 1 or 0 ). To turn the LED attached to
// pin 13 on type "13 1 pinwrite" p.s. First change its pinMode to output
void _pinWrite(void) {
  digitalWrite(dStack_pop(), dStack_pop());
}

const char pinMode_str[] = "pinMode";
// ( u1 u2 -- )
// Set the specified pin behavior to either an input (0) or output (1)
// u1 is the pin and u2 is the mode ( 1 or 0 ). To control the LED attached to
// pin 13 to an output type "13 1 pinmode"
void _pinMode(void) {
  pinMode(dStack_pop(), dStack_pop());
}

const char pinRead_str[] = "pinRead";
void _pinRead(void) {
  dStack_push(digitalRead(dStack_pop()));
}

const char analogRead_str[] = "analogRead";
void _analogRead(void) {
  dStack_push(analogRead(dStack_pop()));
}

const char analogWrite_str[] = "analogWrite";
void _analogWrite(void) {
  analogWrite(dStack_pop(), dStack_pop());
}

const char to_name_str[] = ">name";
void _toName(void) {
  xtToName(dStack_pop());
}
#endif

/*********************************************************************************/
/**                         Dictionary Initialization                           **/
/*********************************************************************************/
const flashEntry_t flashDict[] = {
  /*****************************************************/
  /* The initial entries must stay in this order so    */
  /* they always have the same index. They get called  */
  /* referenced when compiling code                    */
  /*****************************************************/
  { exit_str,           _exit,            NORMAL },
  { literal_str,        _literal,         IMMEDIATE },
  { type_str,           _type,            NORMAL },
  { jump_str,           _jump,            SMUDGE },
  { zjump_str,          _zjump,           SMUDGE },
  { subroutine_str,     _subroutine,      SMUDGE },
  { throw_str,          _throw,           NORMAL },
  { do_sys_str,         _do_sys,          SMUDGE },
  { loop_sys_str,       _loop_sys,        SMUDGE },
  { leave_sys_str,      _leave_sys,       SMUDGE },
  { plus_loop_sys_str,  _plus_loop_sys,   SMUDGE },
  { evaluate_str,       _evaluate,        NORMAL },
  { s_quote_str,        _s_quote,         IMMEDIATE + COMP_ONLY },
  { dot_quote_str,      _dot_quote,       IMMEDIATE + COMP_ONLY },
  { variable_str,       _variable,        NORMAL },
  { over_str,           _over,            NORMAL }, // CAL
  { eq_str,             _eq,              NORMAL }, // CAL
  { drop_str,           _drop,            NORMAL }, // CAL

  /*****************************************************/
  /* Order does not matter after here                  */
  /* Core Words                                        */
  /*****************************************************/
  { abort_str,          _abort,           NORMAL },
  { store_str,          _store,           NORMAL },
  { number_sign_str,    _number_sign,     NORMAL },
  { number_sign_gt_str, _number_sign_gt,  NORMAL },
  { number_sign_s_str,  _number_sign_s,   NORMAL },
  { tick_str,           _tick,            NORMAL },
  { paren_str,          _paren,           IMMEDIATE },
  { star_str,           _star,            NORMAL },
  { star_slash_str,     _star_slash,      NORMAL },
  { star_slash_mod_str, _star_slash_mod,  NORMAL },
  { plus_str,           _plus,            NORMAL },
  { plus_store_str,     _plus_store,      NORMAL },
  { plus_loop_str,      _plus_loop,       IMMEDIATE + COMP_ONLY },
  { comma_str,          _comma,           NORMAL },
  { minus_str,          _minus,           NORMAL },
  { dot_str,            _dot,             NORMAL },
  { slash_str,          _slash,           NORMAL },
  { slash_mod_str,      _slash_mod,       NORMAL },
  { zero_less_str,      _zero_less,       NORMAL },
  { zero_equal_str,     _zero_equal,      NORMAL },
  { one_plus_str,       _one_plus,        NORMAL },
  { one_minus_str,      _one_minus,       NORMAL },
  { two_store_str,      _two_store,       NORMAL },
  { two_star_str,       _two_star,        NORMAL },
  { two_slash_str,      _two_slash,       NORMAL },
  { two_fetch_str,      _two_fetch,       NORMAL },
  { two_drop_str,       _two_drop,        NORMAL },
  { two_dup_str,        _two_dup,         NORMAL },
  { two_over_str,       _two_over,        NORMAL },
  { two_swap_str,       _two_swap,        NORMAL },
  { colon_str,          _colon,           NORMAL },
  { semicolon_str,      _semicolon,       IMMEDIATE },
  { lt_str,             _lt,              NORMAL },
  { lt_number_sign_str, _lt_number_sign,  NORMAL },
  { eq_str,             _eq,              NORMAL },
  { gt_str,             _gt,              NORMAL },
  { to_body_str,        _to_body,         NORMAL },
  { to_in_str,          _to_in,           NORMAL },
  { to_number_str,      _to_number,       NORMAL },
  { to_r_str,           _to_r,            NORMAL },
  { question_dup_str,   _question_dup,    NORMAL },
  { fetch_str,          _fetch,           NORMAL },
  { abort_quote_str,    _abort_quote,     IMMEDIATE + COMP_ONLY },
  { abs_str,            _abs,             NORMAL },
  { accept_str,         _accept,          NORMAL },
  { align_str,          _align,           NORMAL },
  { aligned_str,        _aligned,         NORMAL },
  { allot_str,          _allot,           NORMAL },
  { and_str,            _and,             NORMAL },
  { base_str,           _base,            NORMAL },
  { begin_str,          _begin,           IMMEDIATE + COMP_ONLY },
  { bl_str,             _bl,              NORMAL },
  { c_store_str,        _c_store,         NORMAL },
  { c_comma_str,        _c_comma,         NORMAL },
  { c_fetch_str,        _c_fetch,         NORMAL },
  { cell_plus_str,      _cell_plus,       NORMAL },
  { cells_str,          _cells,           NORMAL },
  { char_str,           _char,            NORMAL },
  { char_plus_str,      _char_plus,       NORMAL },
  { chars_str,          _chars,           NORMAL },
  { constant_str,       _constant,        NORMAL },
  { count_str,          _count,           NORMAL },
  { cr_str,             _cr,              NORMAL },
  { create_str,         _create,          NORMAL },
  { decimal_str,        _decimal,         NORMAL },
  { depth_str,          _depth,           NORMAL },
  { do_str,             _do,              IMMEDIATE + COMP_ONLY },
  { does_str,           _does,            IMMEDIATE + COMP_ONLY },
  { drop_str,           _drop,            NORMAL },
  { dupe_str,           _dupe,            NORMAL },
  { else_str,           _else,            IMMEDIATE + COMP_ONLY },
  { emit_str,           _emit,            NORMAL },
  { environment_str,    _environment,     NORMAL },
  { execute_str,        _execute,         NORMAL },
  { fill_str,           _fill,            NORMAL },
  { find_str,           _find,            NORMAL },
  { fm_slash_mod_str,   _fm_slash_mod,    NORMAL },
  { here_str,           _here,            NORMAL },
  { hold_str,           _hold,            NORMAL },
  { i_str,              _i,               NORMAL },
  { if_str,             _if,              IMMEDIATE + COMP_ONLY },
  { immediate_str,      _immediate,       NORMAL },
  { invert_str,         _invert,          NORMAL },
  { j_str,              _j,               NORMAL },
  { key_str,            _key,             NORMAL },
  { leave_str,          _leave,           IMMEDIATE + COMP_ONLY },
  { loop_str,           _loop,            IMMEDIATE + COMP_ONLY },
  { lshift_str,         _lshift,          NORMAL },
  { m_star_str,         _m_star,          NORMAL },
  { max_str,            _max,             NORMAL },
  { min_str,            _min,             NORMAL },
  { mod_str,            _mod,             NORMAL },
  { move_str,           _move,            NORMAL },
  { negate_str,         _negate,          NORMAL },
  { or_str,             _or,              NORMAL },
  { over_str,           _over,            NORMAL },
  { postpone_str,       _postpone,        IMMEDIATE + COMP_ONLY },
  { quit_str,           _quit,            NORMAL },
  { r_from_str,         _r_from,          NORMAL },
  { r_fetch_str,        _r_fetch,         NORMAL },
  { recurse_str,        _recurse,         IMMEDIATE + COMP_ONLY },
  { repeat_str,         _repeat,          IMMEDIATE + COMP_ONLY },
  { rot_str,            _rot,             NORMAL },
  { rshift_str,         _rshift,          NORMAL },
  { s_to_d_str,         _s_to_d,          NORMAL },
  { sign_str,           _sign,            NORMAL },
  { sm_slash_rem_str,   _sm_slash_rem,    NORMAL },
  { source_str,         _source,          NORMAL },
  { space_str,          _space,           NORMAL },
  { spaces_str,         _spaces,          NORMAL },
  { state_str,          _state,           NORMAL },
  { swap_str,           _swap,            NORMAL },
  { then_str,           _then,            IMMEDIATE + COMP_ONLY },
  { u_dot_str,          _u_dot,           NORMAL },
  { u_lt_str,           _u_lt,            NORMAL },
  { um_star_str,        _um_star,         NORMAL },
  { um_slash_mod_str,   _um_slash_mod,    NORMAL },
  { unloop_str,         _unloop,          NORMAL + COMP_ONLY },
  { until_str,          _until,           IMMEDIATE + COMP_ONLY },
  { while_str,          _while,           IMMEDIATE + COMP_ONLY },
  { word_str,           _word,            NORMAL },
  { xor_str,            _xor,             NORMAL },
  { left_bracket_str,   _left_bracket,    IMMEDIATE },
  { bracket_tick_str,   _bracket_tick,    IMMEDIATE },
  { bracket_char_str,   _bracket_char,    IMMEDIATE },
  { right_bracket_str,  _right_bracket,   NORMAL },

#ifdef CORE_EXT_SET
  { dot_paren_str,      _dot_paren,       IMMEDIATE },
  { zero_not_equal_str, _zero_not_equal,  NORMAL },
  { zero_greater_str,   _zero_greater,    NORMAL },
  { two_to_r_str,       _two_to_r,        NORMAL },
  { two_r_from_str,     _two_r_from,      NORMAL },
  { two_r_fetch_str,    _two_r_fetch,     NORMAL },
  { neq_str,            _neq,             NORMAL },
  { hex_str,            _hex,             NORMAL },
  { case_str,           _case,            IMMEDIATE + COMP_ONLY },    // CAL
  { of_str,             _of,              IMMEDIATE + COMP_ONLY },    // CAL
  { endof_str,          _endof,           IMMEDIATE + COMP_ONLY },    // CAL
  { endcase_str,        _endcase,         IMMEDIATE + COMP_ONLY },    // CAL
#endif

#ifdef DOUBLE_SET
#endif

#ifdef EXCEPTION_SET
#endif

#ifdef FACILITY_SET
  { key_question_str,   _key_question,    NORMAL },
#endif

#ifdef LOCALS_SET
#endif

#ifdef MEMORY_SET
#endif

#ifdef TOOLS_SET
  { dot_s_str,          _dot_s,           NORMAL },
  { dump_str,           _dump,            NORMAL },
  { see_str,            _see,             NORMAL },
  { words_str,          _words,           NORMAL },
#endif

#ifdef SEARCH_SET
#endif

#ifdef STRING_SET
#endif

#ifdef EN_ARDUINO_OPS
  { freeMem_str,        _freeMem,         NORMAL },
  { delay_str,          _delay,           NORMAL },
  { pinWrite_str,       _pinWrite,        NORMAL },
  { pinMode_str,        _pinMode,         NORMAL },
  { pinRead_str,        _pinRead,         NORMAL },
  { analogRead_str,     _analogRead,      NORMAL },
  { analogWrite_str,    _analogWrite,     NORMAL },
  { to_name_str,        _toName,          NORMAL },
#endif

#ifdef EN_EEPROM_OPS
  { eeRead_str,         _eeprom_read,     NORMAL },
  { eeWrite_str,        _eeprom_write,    NORMAL },
#endif

  { NULL,           NULL,    NORMAL }
};


