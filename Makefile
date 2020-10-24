# *
# * This file is part of the bossanova.
# * Copyright (c) 2020 Dr Ashton Fagg <ashton@fagg.id.au>
# * 
# * This program is free software: you can redistribute it and/or modify  
# * it under the terms of the GNU General Public License as published by  
# * the Free Software Foundation, version 3.
# *
# * This program is distributed in the hope that it will be useful, but 
# * WITHOUT ANY WARRANTY; without even the implied warranty of 
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# * General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License 
# * along with this program. If not, see <http://www.gnu.org/licenses/>.
# *
# *************************************************************************
# * This utility is inspired in part by usmb by Geoff Johnstone.
# * All other files in this project are subject to their own licensing terms.
# *


# paths
PREFIX = /usr/local

# flags
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os

CC = cc

PROG=bossanova

SRCS = main.c version.c credentials.c

OBJS = main.o version.o credentials.o

${PROG}: ${OBJS}
	${CC} ${OBJS} ${LDFLAGS} -o ${PROG}

.c.o:
	${CC} -c ${CFLAGS} $<


clean:
	rm -rf *.o
	rm -rf ./bossanova

.PHONY: all clean
