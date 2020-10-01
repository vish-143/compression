import random

# Generate purely random paragraph for testing purpose
para_chars = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'e', 'f', 'g', 'h', 'i', '', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '(', '+', '$', '!', '`', '&', '^', '%', '*', '{', '}', '[', ']', '?', '>', '.', '<', ':', ':', '|', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

l = len(para_chars)
random.shuffle(para_chars)

i = 0
characters = random.randint(50000, 100001)	
with open('test.txt', 'w') as test:
	while(i < characters):
		j = random.randint(0, l-1)
		test.write(para_chars[j]);
		i += 1
		
print(characters)
