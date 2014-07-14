/**
 * vmod_common.c
 *
 * Copyright (c) 2014 by Byteworks GmbH
 * All rights reserved
 *
 * http://www.byteworks.ch/
 *
 * This vmod has been inspired by:
 * - https://github.com/varnish/libvmod-example
 * - the official vmod_std
 *
 * $Id$
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "config.h"

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"


void
strtolower(char *str)
{
	char *c;

	for (c = str; *c; c++) {
		if (isupper(*c)) *c = tolower(*c);
	}

	return;
}


int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
        return (0);
}


const char
*_upperlower(struct sess *sp, unsigned int mode, va_list arg_list, const char *s, ...)
{
	const char *arg;
	unsigned temp_size;
	char *temp, *temp_ptr, *temp_end;
	
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->ws, WS_MAGIC);

        temp_size  = WS_Reserve(sp->wrk->ws, 0);
        temp = sp->wrk->ws->f;
	temp_ptr = temp;
        temp_end = temp + temp_size; 

	arg = s;

	while (arg != vrt_magic_string_end && temp_ptr < temp_end) {
		while (*arg != '\0' && temp_ptr < temp_end) {
			if (mode == 0)
				*temp_ptr = toupper(*arg);
			else
				*temp_ptr = tolower(*arg);

			arg++;
			temp_ptr++;
		}

		arg = va_arg(arg_list, const char *);
	}

	va_end(arg_list);

	if (temp_ptr >= temp_end) {
		WS_Release(sp->wrk->ws, 0);
		return (NULL);
	}

	*temp_ptr = '\0';	

	WS_Release(sp->wrk->ws, temp_ptr - temp + 1);

	return (temp);
}


const char
*vmod_toupper(struct sess *sp, const char *s, ...)
{
	va_list arg_list;

	va_start(arg_list, s);
	return _upperlower(sp, 0, arg_list, s);
}


const char
*vmod_tolower(struct sess *sp, const char *s, ...)
{
	va_list arg_list;

	va_start(arg_list, s);
	return _upperlower(sp, 1, arg_list, s);
}


const char
*vmod_substr(struct sess *sp, const char *s, const int start, const int length)
{
	char *temp;
	int count = length;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->ws, WS_MAGIC);

	if (start >= strlen(s))
		return (NULL);
 
	if (start + length > strlen(s))
		count = strlen(s) - start;
		
	temp = WS_Alloc(sp->wrk->ws, count + 1);

	strncpy(temp, s + start, count);

	return (temp);
}


int
vmod_strlen(struct sess *sp, const char *s, ...)
{
	va_list arg_list;
	const char *arg;
	unsigned int length;

	length = strlen(s);

	va_start(arg_list, s);

	while ((arg = va_arg(arg_list, const char *)) != NULL) {
		length += strlen(arg);
	}

	va_end(arg_list);
}



double
vmod_random(struct sess *sp, double low, double high)
{
	double temp;

	temp = random();

	return (temp);
}


int
vmod_duration2integer(struct sess *sp, double d)
{
	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->ws, WS_MAGIC);

	return (int) d;
}


const char
*vmod_duration2string(struct sess *sp, double d)
{
	char *temp;
	unsigned temp_size;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(sp->ws, WS_MAGIC);

        temp_size  = WS_Reserve(sp->wrk->ws, 0);
        temp = sp->wrk->ws->f;

	snprintf(temp, temp_size, "%d", (int) d);

	WS_Release(sp->wrk->ws, strlen(temp) + 1);
	
	return (temp);
}


double
vmod_string2duration(struct sess *sp, const char *s)
{
	return (0);
}


int
vmod_string2integer(struct sess *sp, const char *s)
{
	int i;
	char *temp;

	i = strtol(s, &temp, 10);
	if (*temp != '\0')
		return NULL;

	if(errno || i >= INT_MAX || i <= INT_MIN)
		return NULL;
	
	return (i);
}


const char *
vmod_version(struct sess *sp)
{
	return VERSION;
}

