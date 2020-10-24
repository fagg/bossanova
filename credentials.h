/* 
 * This file is part of bossanova.
 * Copyright (c) 2020 Dr Ashton Fagg <ashton@fagg.id.au>
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *************************************************************************
 * This utility is inspired in part by usmb by Geoff Johnstone.
 * All other files in this project are subject to their own licensing terms.
 */

#pragma once

#include <stdio.h>

#include "debug.h"

/* This defines a set of user credentials,
 * i.e. username and password, that needs
 * to be passed to Samba. */
typedef struct credentials_t {
	char *username;
	size_t username_sz;

	char *password;
	size_t password_sz;

	char *domain;
	size_t domain_sz;
} credentials_t;

credentials_t *allocate_credentials();

/* Securely tears down credentials struct */
void nuke_credentials(credentials_t *);

/* This checks to make sure the credential struct supplied
 * is appropriately populated. It does *NOT* check if the
 * supplied credentials will actually be accepted by Samba.
 *
 * The following return codes signify this: */

#define CREDENTIALS_POPULATED 1
#define CREDENTIALS_NOT_POPULATED -1
int credentials_populated(credentials_t *);

/* Given a file descriptor, this function will
 * populate the credentials struct and return one of the following
 * codes indicating whether this was successful: */

#define CREDENTIALS_FILE_PARSE_ERROR -1
#define CREDENTIALS_FILE_PARSE_SUCCESS 1
int extract_credentials_from_file(credentials_t *, FILE *);

/* Temporary buffer size */
#define CREDENTIALS_BUFFER_SIZE 256
