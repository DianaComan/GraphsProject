# Darius-Florentin Neatu <neatudarius@gmail.com>
# Copyright 2018

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema 
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului


CFLAGS=-std=c++11

# nume necesar (build)
build: build_minlexbfs build_disjcnt build_revedges
#build_disjcnt build_rtd build_revedges

build_minlexbfs:
	g++ $(CFLAGS) minlexbfs.cpp -o minlexbfs

build_disjcnt:
	g++ $(CFLAGS) disjcnt.cpp -o disjcnt

#build_rtd:
#	g++ $(CFLAGS) rtd.cpp -o rtd

build_revedges:
	g++ $(CFLAGS) revedges.cpp -o revedges

run-p1:
	./minlexbfs

run-p2:
	./disjcnt

#run-p3:      # nume necesar 
#	./rtd

run-p4:
	./revedges

clean:
	rm -f minlexbfs revedges disjcnt
#disjcnt rtd revedges
