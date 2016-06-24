/*
 * rlm_eap_tls.h
 *
 * Version:     $Id$
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Copyright 2001  hereUare Communications, Inc. <raghud@hereuare.com>
 * Copyright 2003  Alan DeKok <aland@freeradius.org>
 * Copyright 2006  The FreeRADIUS server project
 */
#ifndef _RLM_EAP_TLS_H
#define _RLM_EAP_TLS_H

#include <freeradius-devel/ident.h>
RCSIDH(rlm_eap_tls_h, "$Id$")

#include "eap_tls.h"

#include <freeradius-devel/radiusd.h>
#include <freeradius-devel/modules.h>

/* configured values goes right here */
typedef struct eap_tls_conf {
	char		*private_key_password;
	char		*private_key_file;
	char		*certificate_file;
#ifndef NO_OPENSSL
	char		*random_file;
#endif
	char		*ca_path;
	char		*ca_file;
	char		*dh_file;
	char		*rsa_file;
	char		*make_cert_command;
#ifndef NO_OPENSSL
	int		rsa_key;
	int		dh_key;
	int		rsa_key_length;
	int		dh_key_length;
	int		verify_depth;
#endif
	int		file_type;
	int		include_length;

	/*
	 *	Always < 4096 (due to radius limit), 0 by default = 2048
	 */
	int		fragment_size;
#ifndef NO_OPENSSL
	int		check_crl;
	int		allow_expired_crl;
	char		*check_cert_issuer;
#endif
	char		*check_cert_cn;
	char		*cipher_list;

	int     	session_cache_enable;
	int     	session_timeout;
#ifndef NO_OPENSSL
    int     	session_cache_size;
    char		*session_id_name;
	char		session_context_id[128];
	time_t		session_last_flushed;
	
	char		*verify_tmp_dir;
	char		*verify_client_cert_cmd;

#if OPENSSL_VERSION_NUMBER >= 0x0090800fL
#ifndef OPENSSL_NO_ECDH
	char		*ecdh_curve;
#endif
#endif
#endif /* ifndef NO_OPENSSL */

	/*
	 * OCSP Configuration
	 */
	int		ocsp_enable;
	int		ocsp_override_url;
	char		*ocsp_url;
} EAP_TLS_CONF;

/* This structure gets stored in arg */
typedef struct _eap_tls_t {
	EAP_TLS_CONF 	*conf;

#ifndef NO_OPENSSL
	SSL_CTX		*ctx;
#ifdef HAVE_OPENSSL_OCSP_H
	X509_STORE	*store; /* OCSP Revocation Store */
#endif
#endif

#ifndef NO_CYASSL
	CYASSL_CTX	*ctx;
#endif
} eap_tls_t;


#endif /* _RLM_EAP_TLS_H */
