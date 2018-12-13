default:
	clear
	clang++ *.cpp -lncurses -o carz
	# IF DOESNT WORK, IN THE TERMINAL WRITE  
	# sudo apt-get install ncurses5-dev   AND     
	# sudo apt-get install ncurses.h  
	#
	# write MAKE RUN to start the programm
	 
clean:
	rm carz	
run:
	./carz	
	clear
