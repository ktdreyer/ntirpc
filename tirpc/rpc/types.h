/*	$NetBSD: types.h,v 1.13 2000/06/13 01:02:44 thorpej Exp $	*/

/*
 * Copyright (c) 2009, Sun Microsystems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of Sun Microsystems, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *	from: @(#)types.h 1.18 87/07/24 SMI
 *	from: @(#)types.h	2.3 88/08/15 4.0 RPCSRC
 * $FreeBSD: src/include/rpc/types.h,v 1.10.6.1 2003/12/18 00:59:50 peter Exp $
 */

/*
 * Rpc additions to <sys/types.h>
 */
#ifndef _TIRPC_TYPES_H
#define _TIRPC_TYPES_H

#include <sys/types.h>

typedef int32_t bool_t;
typedef int32_t enum_t;

typedef u_int32_t rpcprog_t;
typedef u_int32_t rpcvers_t;
typedef u_int32_t rpcproc_t;
typedef u_int32_t rpcprot_t;
typedef u_int32_t rpcport_t;
typedef int32_t rpc_inline_t;

#ifndef NULL
#	define NULL	0
#endif
#define __dontcare__	-1

#ifndef FALSE
#	define FALSE	(0)
#endif
#ifndef TRUE
#	define TRUE	(1)
#endif

/*
 * Package params support
 */

#define TIRPC_GET_MALLOC           1
#define TIRPC_SET_MALLOC           2
#define TIRPC_GET_FREE             3
#define TIRPC_SET_FREE             4
#define TIRPC_GET_FLAGS            5
#define TIRPC_SET_FLAGS            6
#define TIRPC_GET_DEBUG_FLAGS      7
#define TIRPC_SET_DEBUG_FLAGS      8
#define TIRPC_GET_WARNX            9
#define TIRPC_SET_WARNX            10


/*
 * Debug flags support
 */

#define TIRPC_FLAGS_NONE                 0x00000
#define TIRPC_DEBUG_FLAGS_NONE           0x00000
#define TIRPC_DEBUG_FLAGS_RPC_CACHE      0x00001

typedef void *(*mem_alloc_t)(size_t);
typedef void (*mem_free_t)(void *, size_t);
typedef void (*warnx_t)(const char *fmt, ...);

/*
 * Package params support
 */
typedef struct tirpc_pkg_params {
	u_int flags;
	u_int debug_flags;
	mem_alloc_t mem_alloc;
	mem_free_t mem_free;
	warnx_t warnx;
} tirpc_pkg_params;

extern tirpc_pkg_params __pkg_params;

#define __warnx(...) __pkg_params.warnx(__VA_ARGS__)
#define mem_alloc(size) __pkg_params.mem_alloc((size))
#define mem_free(ptr, size) __pkg_params.mem_free((ptr),(size))

#include <sys/time.h>
#include <sys/param.h>
#include <stdlib.h>
#include <netconfig.h>

/*
 * The netbuf structure is defined here, because FreeBSD / NetBSD only use
 * it inside the RPC code. It's in <xti.h> on SVR4, but it would be confusing
 * to have an xti.h, since FreeBSD / NetBSD does not support XTI/TLI.
 */

/*
 * The netbuf structure is used for transport-independent address storage.
 */
struct netbuf {
  unsigned int maxlen;
  unsigned int len;
  void *buf;
};

/*
 * The format of the addres and options arguments of the XTI t_bind call.
 * Only provided for compatibility, it should not be used.
 */

struct t_bind {
  struct netbuf   addr;
  unsigned int    qlen;
};

/*
 * Internal library and rpcbind use. This is not an exported interface, do
 * not use.
 */
struct __rpc_sockinfo {
	int si_af; 
	int si_proto;
	int si_socktype;
	int si_alen;
};

#endif /* _TIRPC_TYPES_H */