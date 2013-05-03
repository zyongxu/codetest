import csv
import sys
from operator import attrgetter

class Record:
    def __init__(self, sb, p, sz):
        self.symbol = sb
        self.price  = int(p)
        self.size   = int(sz)
        self.cmp_key= sb[3]+sb[2]
        if self.size < 0:
            self.cmp_key += "1"
        else:
            self.cmp_key += "0"

def rawcsv2dic(filename):
    buff = []
    fp = open(filename, 'rb')
    records = csv.reader(fp, delimiter=',', quotechar='"')

    for r in records:
        i=0
        while i < len(list(r)):
            if (r[i] != ""):
                buff.append(Record(r[i], r[i+1], r[i+2]))
            i += 4;
    sortedbuf = sorted(buff, key=attrgetter('cmp_key'))

    first_rec = sortedbuf[0]
    pre_symbol = first_rec.symbol
    pre_price  = first_rec.price
    pre_size   = first_rec.size

    for rec in sortedbuf[1:]:
        symbol = rec.symbol
        price  = rec.price
        size   = rec.size

        if (pre_symbol != symbol or pre_price != price or pre_size*size < 0):
            print ("{0}\t{1}\t{2}".format(pre_symbol, pre_price, pre_size))
            pre_symbol = symbol
            pre_price = price
            pre_size  = size
        else:
            pre_size += size;
    # the last line
    print ("{0}\t{1}\t{2}".format(pre_symbol, pre_price, pre_size))


if __name__ == '__main__':
    rawcsv2dic(sys.argv[1])
