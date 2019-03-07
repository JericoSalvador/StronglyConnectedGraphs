
import os


os.system("make clean"); 
os.system("make")

letters = ['a','b','c','d','e','f']
for letter in letters: 

	os.system("valgrind --leak-check=full --track-origins=yes ./DigraphProperties public/input_" + letter + ".txt public/output_" + letter)
	print("working on:", letter)
	input("press enter to continue...")

os.system("make clean")
