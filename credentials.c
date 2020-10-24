/* 
 * This file is part of the bossanova.
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

#include <stdlib.h>
#include <string.h>

#include "credentials.h"

credentials_t * allocate_credentials() {
	credentials_t *creds = (credentials_t *) calloc(1, sizeof(credentials_t));

	if (!creds) {
		/* calloc went to shit for some reason */
		goto bypass;
	}

	creds->username_sz = creds->password_sz = 0;
	creds->username = creds->password = NULL;

 bypass:
	return creds;
}

void nuke_credentials(credentials_t *creds) {

	/* Check if credentials are populated */
	if (credentials_populated(creds) == CREDENTIALS_NOT_POPULATED) {
		return;
	}

	/* Note to the wise guys among us:
	 *
	 * explicit_bzero is important. The operative word is "Explicit".
	 * bzero will not guarantee the memory gets zeroed before freeing
	 * due to compiler operations. AS SUCH IT IS LESS SECURE.
	 *
	 * Don't fuck with this during a port. If your OS doesn't support
	 * explicit_bzero, here's a nickel go get get a real computer.
	 */

	explicit_bzero(creds->password, creds->password_sz);
	explicit_bzero(creds->username, creds->username_sz);
	creds->password_sz = creds->username_sz = 0;

	free(creds->password);
	free(creds->username);
	free(creds);
}

int credentials_populated(credentials_t *creds) {
	if (creds == NULL) {
		return CREDENTIALS_NOT_POPULATED;
	}
	else if (creds->password == NULL || creds->username == NULL
	    || creds->password_sz == 0 || creds->username_sz == 0) {
		return CREDENTIALS_NOT_POPULATED;
	}
	return CREDENTIALS_POPULATED;
}

int extract_credentials_from_file(credentials_t *creds, FILE *fp) {

	/* Make sure everything is valid */
	int rc = CREDENTIALS_FILE_PARSE_SUCCESS;

	if (fp == NULL || creds == NULL) {
		return CREDENTIALS_FILE_PARSE_ERROR;
	}

	/* The credentials file should look like this:
	 *
	 * username
	 * password
	 *
	 * with nothing else in the file. */

	char *uname_buffer = (char *) calloc(CREDENTIALS_BUFFER_SIZE, sizeof(char));
	char *pw_buffer = (char *) calloc(CREDENTIALS_BUFFER_SIZE, sizeof(char));

	/* We're expecting username first, so read the file until
	 * the we hit the first newline. */

	int c;

	/* Next, we're expecting the password. */
	while ((c = fgetc(fp))
	        && c != EOF
	        && creds->username_sz < CREDENTIALS_BUFFER_SIZE) {
		if (c == '\n')
			break;
		uname_buffer[(*creds).username_sz++] = (char) c;
	}

	/* Next, we're expecting the password. */
	while ((c = fgetc(fp))
	       && c != EOF
	       && creds->password_sz < CREDENTIALS_BUFFER_SIZE) {
		if (c == '\n')
			break;
		pw_buffer[(*creds).password_sz++] = (char) c;
	}

	if (creds->password_sz == 0 || creds->username_sz == 0) {
		/* Shit hit the fan, give up */
		rc = CREDENTIALS_FILE_PARSE_ERROR;
		goto deallocate_temp_buffers;
	}

	creds->password = (char *) calloc(creds->password_sz, sizeof(char));
	creds->username = (char *) calloc(creds->username_sz, sizeof(char));

	/* calloc went to shit */
	if (creds->password == NULL || creds->username == NULL) {
		rc = CREDENTIALS_FILE_PARSE_ERROR;
		goto deallocate_temp_buffers;
	}

	(void) strncpy(creds->password, pw_buffer, creds->password_sz);
	(void) strncpy(creds->username, uname_buffer, creds->username_sz);

 deallocate_temp_buffers:
	/* Finally, deallocate our buffers */
	explicit_bzero(uname_buffer, CREDENTIALS_BUFFER_SIZE);
	explicit_bzero(pw_buffer, CREDENTIALS_BUFFER_SIZE);

	free(uname_buffer);
	free(pw_buffer);

	return rc;
}
