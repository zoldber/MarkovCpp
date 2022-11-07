'''

  This is probably the simplest implementation of a Markov chain generator possible.
  In this program, a dictionary of words is created and for each word therein, a
  list is created. A subsequent word appearing more times in a list means a higher
  probability of it being selected when, in the chain constructing loop,
  
  word = randChoose(dictionary[word].subsequent[])
  
  e.g. for the following corpus:
  
  "I have a dog."
  "They have a boat."
  "Have two pencils."
  
  the following dictionary is built:
  
  dict["i"      "] = { have       }
  dict["have    "] = { a, a, two  } <- 2/3 chance of selecting "a" as next word, 1/3 chance of selecting "two"
  dict["a       "] = { dog, boat  }
  dict["dog     "] = {            } <- Terminal Word
  dict["they    "] = { have       }
  dict["boat    "] = {            } <- Terminal Word
  dict["two     "] = { pencils    } 
  dict["pencils "] = {            } <- Terminal Word
  
  and the following chain might be generated:
  
  "they"->"have"->"a"->"dog"
  
  Obviously these get more interesting for larger sentences and larger sets of sentences. They also tend to get
  incoherent unless the sentences are sourced similarly (e.g. each corpus should be a set of quotes, or poems, or
  bicycle advertisements, etc.)
  
'''

import random

fileLines = []

dictionary = {}

result = []

# Fetch words from sentences in a text file, where '.' => EOL
# (preferably sentences with similar structure an subject matter)
with open("text.txt", 'r') as textFile:
    for line in textFile:
        fileLines.append(line
                         .replace('\n','')
                         .replace(';', '')
                         .replace(',', '')
                         )

# Build dictionary from lines recorded in the step above
for line in fileLines:

    line = line.lower().split(' ')

    for (i, word) in enumerate(line[:-1]):

        nxt = line[i+1]

        if word not in dictionary.keys():

            dictionary[word] = []

        dictionary[word].append(nxt)

# Emulating a do{}while() with a flag
terminalWord = False

# Seed word chosen at random
word = random.choice(list(dictionary.keys()))

while not terminalWord:
    result.append(word)
    word = random.choice(list(dictionary[word]))
    terminalWord = '.' in word

for word in result:

    print(word, end=' ')
