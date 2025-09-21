#!/bin/bash
OTM="-O0"

# Passo 1: Compilar o limpador da cache
gcc -O2 -Wall clean_cache.c -o clean_cache

# Passo 2: Compilar os programas 
gcc $OTM cen.c tecnicas.c -o cen
gcc $OTM ceb.c tecnicas.c -o ceb
gcc $OTM cdn.c tecnicas.c -o cdn
gcc $OTM cdb.c tecnicas.c -o cdb
gcc $OTM ben.c tecnicas.c -o ben
gcc $OTM beu.c tecnicas.c -o beu
gcc $OTM bdn.c tecnicas.c -o bdn
gcc $OTM bdu.c tecnicas.c -o bdu

# Passo 3: EXecutar programas com perf
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in
./clean_cache
perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in

# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./cen < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./ceb < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./cdn < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./cdb < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./ben < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./beu < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdn < in.in
# perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./bdu < in.in