import hashlib
import random
import string

NIBBLES = 6
HASHTABLE = {}

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
        for k, v in HASHTABLE.items():
            if v == h and k != s: 
                return k, s
        
        # if no collision found add to hash table
        HASHTABLE[s] = h

result = find_collision_random()
print (result)

print(len(HASHTABLE.keys()))