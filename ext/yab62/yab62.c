#include <ruby.h>

/*
 *  base62.c
 *
 *  Created by Jason Hullinger on 5/27/10.
 *
 *  Modified by Teng Siong Ong on 11/15/2011.
 */
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static const char base62_vals[] = "0123456789"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const int base62_index[] = {
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
       0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,    0,    0, 
       0,    0,    0,    0,    0, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 
    0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 
    0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d,    0,    0,    0,    0,    0, 
       0, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 
    0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 
    0x21, 0x22, 0x23, 
};

void
strreverse_inplace (char *str)
{
    char c;
    u_int64_t half;
    u_int64_t len;
    u_int64_t i;

    len = strlen(str);
    half = len >> 1;
    for (i = 0; i < half; i++) {
        c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
}

int
base62_encode(u_int64_t val, char *str, size_t len)
{
    u_int64_t i = 0;
    u_int64_t v;

    do {
        if (i + 1 >= len)
            return 0;
        v = val % 62;
        str[i++] = base62_vals[v];
        val = (val - v) / 62;
    } while (val > 0);
    str[i] = '\0';
    strreverse_inplace(str);

    return 1;
}

u_int64_t
base62_decode (const char *str)
{
    u_int64_t val = 0;
    char c;
    u_int64_t len;
    u_int64_t i;

    len = strlen(str);
    for (i = 0; i < len; i++) {
        c = str[i];
        if (!isalnum(c)) {
            return -1;
        }
        val += base62_index[c] * pow(62, len - i - 1);
    }

    return val; 
}

/* Ruby code starts here */

static VALUE alphadecimal_base62_encode(VALUE self, VALUE arg) {
  long val = NUM2LONG(arg);
  if (val < 0)
    rb_raise(rb_eRangeError, "Number must be greater than or equal to 0");

  char str[12];
  base62_encode(val, str, 12);
  return rb_str_new2(str);
}

static VALUE alphadecimal_base62_decode(VALUE self, VALUE arg) {
  char* str = StringValuePtr(arg);
  long val = base62_decode(str);
  return INT2NUM(val);
}

/* ruby calls this to load the extension */
void Init_yab62(void) {
  // Create a Ruby module.
  VALUE base62Module = rb_define_module("YAB62");

  // Add a module method.
  int arg_count = 1;
  rb_define_singleton_method(base62Module, "encode62", alphadecimal_base62_encode, arg_count);

  // Add a module method.
  arg_count = 1;
  rb_define_singleton_method(base62Module, "decode62", alphadecimal_base62_decode, arg_count);
}