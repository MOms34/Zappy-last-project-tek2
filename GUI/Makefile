##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

QMAKE = /home/omay/Qt/5.15.12/gcc_64/bin/qmake #need to change qmake binary path

all:
	$(QMAKE) -makefile -o Makefile zappy_gui.pro
	make

clean:
	$(QMAKE) -makefile -o Makefile zappy_gui.pro
	make clean

distclean: clean
	rm -f Makefile