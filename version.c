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

#include <stdio.h>

#include "version.h"

void show_version(FILE *fp) {
    fprintf(fp, "bossanova version %f\n", BOSSANOVA_VERSION);
}
