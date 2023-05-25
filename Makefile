# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

options.o: options.c options.h
	$(CC) $(CFLAGS) -c options.c -o options.o

output.o: output.c output.h
	$(CC) $(CFLAGS) -c output.c -o output.o

rand64-hw.o: rand64-hw.c rand64-hw.h
	$(CC) $(CFLAGS) -c rand64-hw.c -o rand64-hw.o

rand64-sw.o: rand64-sw.c rand64-sw.h
	$(CC) $(CFLAGS) -c rand64-sw.c -o rand64-sw.o

randall: randall.c options.o output.o rand64-hw.o rand64-sw.o
	$(CC) $(CFLAGS) $@.c options.o output.o rand64-hw.o rand64-sw.o -o $@

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt # More files should be listed here, as needed.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

.PHONY: default clean assignment submission-tarball repository-tarball

clean:
	rm -f *.o *.$(TAREXT) randall


check: randall
	./randall 10 | wc -c | grep -q '^10$$'
	./randall 453 | wc -c | grep -q '^453$$'
	./randall 111 -i rdrand | wc -c | grep -q '^111$$'
	./randall 222 -i mrand48_r | wc -c | grep -q '^222$$'
	./randall 333 -i /dev/random | wc -c | grep -q '^333$$'
	./randall 323 -i /dev/urandom | wc -c | grep -q '^323$$'
	./randall 123 -o stdio | wc -c | grep -q '^123$$'
	./randall 456 -o 30 | wc -c | grep -q '^456$$'
	./randall 111 -i rdrand -o stdio | wc -c | grep -q '^111$$'
	./randall 222 -i mrand48_r -o 20 | wc -c | grep -q '^222$$'
	./randall 333 -i /dev/random -o 20 | wc -c | grep -q '^333$$'
		./randall 111 -i rdrand -o 40 | wc -c | grep -q '^111$$'
	./randall 222 -i mrand48_r -o 30 | wc -c | grep -q '^222$$'
	./randall 333 -i /dev/random -o 90 | wc -c | grep -q '^333$$'
	