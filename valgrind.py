
import os


if __name__ == "__main__":  

	letters = ['a','b','c','d']#,'e','f']
	os.system("make clean")
	os.system("make")
	for letter in letters: 

		command = os.path.join(os.getcwd(), "DigraphProperties ") + os.path.join("public", "input_") + letter + ".txt " + os.path.join("public", "output_" + letter);
		os.system("valgrind --leak-check=full --track-origins=yes " + command); 	
		print("working on:", letter)
	os.system("make clean")
