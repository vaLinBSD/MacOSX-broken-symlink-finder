CFLAGS = -g

all : checkSymlink
	cp checkSymlink /Users/danny/bin/.

checkSymlink: checkSymlink.c

clean:
	rm -f *.o checkSymlink
