#1 list comprehension
foo = [some_func(x) for x in range(1, 11) if not (x % 2)]
#2 dict comprehension
{n:n*n for n in range(5)}

#3 regex
import re
pattern = re.compile(r'ab*.')
m = pattern.match("")
#  m.group()
#  m.start(), m.end(), m.span

m = pattern.sub('rep', str)



#itertools: count(start [, step]), cycle(iterable), repeat(element [, num_of_rep])

#2 generator: a "function" used as a iterable in place of a list


