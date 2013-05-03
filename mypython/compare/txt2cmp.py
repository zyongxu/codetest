import sys
import re

# Usage: provide the chunk of txt record to sort
def rawtxt2dic(filename):
    symbol_mask = {"JUN13": "RBM3",
                   "JUL13": "RBN3",
                   "AUG13": "RBQ3",
                   "SEP13": "RBU3",
                   "OCT13": "RBV3",
                   "NOV13": "RBX3",
                   "DEC13": "RBZ3",
                   "JAN14": "RBF4"}

    fp = open(filename, 'rb')
    buflist = []
    side = 1
    for line in fp:
        if len(line) < 10:
            continue
        if (line[9] == ' '):
            side = -1
        else:
            side = 1

        fields = line.split();
        if (fields[3] == "RBOB"):
            price = int(re.sub(r'\.', '', fields[5]))
            size  = int(fields[0])
            size *= side;
            symbol= symbol_mask[fields[1]]
            #print ("{0}\t{1}\t{2}".format(symbol, price, size))
            buflist.append([symbol, price, size])

    first_rec = buflist[0]
    pre_symbol = first_rec[0]
    pre_price  = first_rec[1]
    pre_size   = first_rec[2]

    for rec in buflist[1:]:
        symbol = rec[0]
        price  = rec[1]
        size   = rec[2]

        if (pre_symbol != symbol or pre_price != price or pre_size*size < 0):
            print ("{0}\t{1}\t{2}".format(pre_symbol, pre_price, pre_size))
            pre_symbol = symbol
            pre_price = price
            pre_size  = size
        else:
            pre_size += size;
    # the last line
    print ("{0}\t{1}\t{2}".format(pre_symbol, pre_price, pre_size))

if __name__ == "__main__":
    rawtxt2dic(sys.argv[1])
