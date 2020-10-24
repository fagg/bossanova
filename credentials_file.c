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

#include "credentials_file.h"
#include "debug.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int attempt_to_find_config_file(char *filename) {
	const char *home = get_home_directory();
	size_t length = strlen(home) + strlen("/.bossanova_credentials") + 1;

	filename = (char *) calloc(length, sizeof(char));
	if (!filename) {
		fprintf(stderr, "attempt_to_find_config_file(): calloc failed\n");
		abort();
	}
	
	(void) snprintf(filename, length, "%s/.bossanova_credentials", home);

	return check_file_exists(filename);
}
