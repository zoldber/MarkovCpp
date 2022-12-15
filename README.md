# MarkovCpp
## C++ implementation of a Markov Chain generator

## Summary:
This library procedurally generates text given a sample document and (optionally) a seed. 
It's more of a fun experiment in maps and probability distributions than anything.

- - -

This is probably the simplest implementation of a Markov chain generator possible.
In this program, a dictionary of words is created and for each word therein, a
list is created. A subsequent word appearing more times in a list means a higher
probability of it being selected when, in the chain constructing loop,

word = randChoose(dictionary[word].subsequent[])

e.g. for the following corpus:

```txt
I have a dog.
They have a boat.
Have two pencils.
```
the following dictionary is built (lower-case for all keys is intentional):

|Dict. Key | Dict. Pointer  |
|:--------:|:--------------:|
|"i"       | "have"         |
|"have"    | "a", "a", "two"|
|"a"       | "dog", "boat"  |
|"dog"     | "."            |
|"."       | /TERMINATE     |
|"they"    | "have"         |
|"boat"    | "."            |
|"two"     | "pencils"      | 
|"pencils" | "."            |

and the following chain might be generated:

"they" ➔ "have" ➔ "a" ➔ "dog" ➔ /TERMINATE

Note that for key "have", there's a 2/3 chance of selecting "a" as the subsequent word, and a 1/3 chance of selecting "two". In this example, the probability of subsequent word selection is represented with word frequency in the list that's pointed to. This is intuitive but suboptimal for a few obvious reasons.

Word chains (meant to emulate sentences) get more interesting for larger sentences and larger sets of sentences. They also tend to get incoherent unless the sentences are sourced similarly (e.g. each corpus should be a set of quotes, or poems, or bicycle advertisements, etc.).

