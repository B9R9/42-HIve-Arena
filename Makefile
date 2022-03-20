 
all:
	make -C src
	make -C Framboisier
	cp Framboisier/agent .
