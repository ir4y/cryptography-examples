all: test

test: clean
	ghc -fhpc Test.hs
	./Test
	hpc markup Test

clean:
	rm -f *.o
	rm -f *.tix
	rm -f *.hi
