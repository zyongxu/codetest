#!/usr/bin/python

################ 'string' (or "string") ################
str1="hello"

# slice by indices
#  H  e  l  l  o
#  0  1  2  3  4
# -5 -4 -3 -2 -1
# str1[:n]+str[n:] always equals to str1

print str1[1:3]
print str1[:2]
print str1[1:]

# concatenate, use str() to convert a number to string
str2 = str1 + str(123)

# a raw disable backslash escape, '\n' becomes two chars
rstr = r'this\nis\nraw'
print rstr

# methods in string
# -- returns the lowercase or uppercase version of the string
str1.lower()
str1.upper()

# -- returns a string with whitespace removed from the start and end
str1.strip()

# -- tests if ALL the string chars are in the various character classes
str1.isalpha()
str1.isdigit()
str1.isspace()

# -- tests if the string starts or ends with the given other string
str1.startswith('other')
s.endswith('other')

# -- searches for the given other string (not a regular expression) within str1,
# -- and returns the first index where it begins or -1 if not found
str1.find('other')

# -- returns a string where ALL occurrences of 'old' have been replaced by 'new'
str1.replace('old', 'new')

# -- returns a list of substrings separated by the given delimiter.
# -- The delimiter is not a regular expression, it's just text.
# -- e.g. 'aaa,bbb,ccc'.split(',') -> ['aaa', 'bbb', 'ccc']. 
# -- As a convenient special case s.split() (with no arguments) splits on all whitespace chars.
str1.split('delim')

# -- opposite of split(), joins the elements in the given list together using the string as the delimiter.
# e.g. '---'.join(['aaa', 'bbb', 'ccc']) -> aaa---bbb---ccc
s.join(list)

####################### [list] ########################

list=['string', 100, 'allright'];

list[:2]+["concatenatation"];

#minus indicates reverse, -1 is the last
#element
list[-1];

###################### {set} ##########################
# sort unique unordered elements
set1 = {'this', 'is', 'a', 'set'}
# operations:
# |= 'or equal'
# &= 'and equal'
# -= '...'

##################### regex ###########################
# use module re
# sub replace all occurance of pattern! check this out:
# http://stackoverflow.com/questions/6639522/re-sub-replacing-leftmost-occurrences 

###################### file IO #########################

f = open('file.txt', 'r')
f.read()      #return the whole file as a string
f.readline()  #read one line in the file, return a string

f.readlines() #return a list of strings of all lines in the file
# alternativly, use a loop
for line in f:
    print line

# the pickle module:

