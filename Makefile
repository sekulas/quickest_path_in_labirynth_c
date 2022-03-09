#Kompilacja
all:
	gcc src/*.c -o bin/labirynt

#Test dla labiryntu 5x5
test1:
	bin/labirynt dane/labirynt0.txt 5 5

#Test dla labiryntu 3x3
test2:
	bin/labirynt dane/labirynt3.txt 3 3

#Test dla labiryntu 5x5
test3:
	bin/labirynt dane/labirynt5.txt 5 5

#Test dla labiryntu 7x7
test4:
	bin/labirynt dane/labirynt7.txt 7 7

#Test dla za duzego labiryntu
testzaduzylabirynt:
	bin/labirynt dane/labirynt0.txt 11 11

#Test dla labiryntu bez podania szerokosci
testbrakszerokosci:
	bin/labirynt dane/labirynt0.txt 5

#Test dla labiryntu bez podania jego rozmiaru
testbrakrozmiaru:
	bin/labirynt dane/labirynt0.txt

#Test bez bez podania pliku w ktorym znajduje sie labirynt oraz jego rozmiaru 
testbrakdanych:
	bin/labirynt

#Test niepoprawnie zakodowany labirynt
test0123:
	bin/labirynt dane/labiryntdane.txt 5 5

#Test labirynt niregularny - 5 x 6 
testunregular:
	bin/labirynt dane/labiryntur.txt 5 6

#Test labirynt 10x10
test10:
	bin/labirynt dane/labirynt10.txt 10 10
