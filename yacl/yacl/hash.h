/*
 * Copyright (c) 2012, Mao Jianjun <justmao945@gmail.com>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef YACL_HASH_H
#define YACL_HASH_H

#include <stdbool.h>
#include <stddef.h>
#include <yacl/__conf.h>

#ifdef YACL_CXX
extern "C" {
#endif

#ifdef YACL_64
extern const size_t hash_prime_list[60];
#else
extern const size_t hash_prime_list[28];
#endif

/**
 * MurmurHash function.
 * @see https://sites.google.com/site/murmurhash
 */
size_t hash_murmur2(const void* key, size_t len);


#ifdef YACL_CXX
}
#endif

#endif /* - YACL_HASH_H - */
