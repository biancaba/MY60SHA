import hashlib
import random
import string
from datetime import datetime

NIBBLES = 9
HASHTABLE = {}

def print_time():
  # current date and time
  now = datetime.now()
  print("date-time: ", now)

def my60sha(string, nibbles):
    h = hashlib.sha1(string.encode()).hexdigest()
    return h[:nibbles]

def randomStringDigits(stringLength=10):
    """Generate a random string of letters and digits """
    lettersAndDigits = string.ascii_letters + string.digits
    return ''.join(random.choice(lettersAndDigits) for i in range(stringLength))

def find_collision_random():
    while(True):
        s = randomStringDigits()
        h = my60sha(s, NIBBLES)

        # check for collision
        v = HASHTABLE.get(h)
        if v is not None:
            return v, s
        
        HASHTABLE[h] = s

def find_collision_recursive(initial_string):
	# Start with an initial string
	initial_hash = my60sha(initial_string, NIBBLES)
	HASHTABLE[initial_string] = initial_hash

	# Use the hash as a random string
	while(True):
		s = initial_hash
		h = my60sha(s, NIBBLES)

        # check for collision
		for k, v in HASHTABLE.items():
			if v == h and k != s: 
				return k, s
        
        # if no collision found add to hash table
		HASHTABLE[s] = h
		initial_hash = h

print_time()
result = find_collision_random()
#result = find_collision_recursive(randomStringDigits())
print (result)
print_time()

print(len(HASHTABLE.keys()))
#print(HASHTABLE)