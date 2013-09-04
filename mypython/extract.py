#!/usr/bin/python

import sys
import re

class DataRecord:
    def __init__(self, filename):
        self.fobj = open(filename, 'rb')
        self.prev_line = "0 0 0 0"
        self.price = 0
        self.sec   = 0
        self.size  = 0
        self.fobj.readline()

    def next():
        curr_line = self.fobj.readline()
        self.sec = str2sec(curr_line)
        [self.price, cur_size] = priceAndSize(curr_line)

        self.prev_line = curr_line


def foo(fname1, fname2):
    leg1_fobj = open(fname1, 'rb')
    leg2_fobj = open(fname2, 'rb')
    result = {}

    prev_line = "0 0 0 0"
    while 1:
        line1 = leg1_fobj.readline();
        if not line1:
            break;

        #line2 = leg2_fobj.readline();
        #if not line2:
        #    break;

        sec1 = str2sec(line1)
        #sec2 = str2sec(line2)
        print sec1
        priceAndSize(line1, line1)

def str2sec(time_stamp):
    hour    = float(time_stamp[1:3]) - 9
    minu    = float(time_stamp[4:6])
    sec     = float(time_stamp[7:9])
    milisec = float(time_stamp[10:13])

    #print ("{0}\t{1}\t{2}\t{3}".format(hour, minu, sec, milisec))
    return hour*3600 + minu*60 + sec + milisec/1000

def priceAndSize(str1, str2):
    fields = str1.split(' ', 4)
    price = float(fields[1])
    size  = float(fields[2])
    print ("{0}\t{1}".format(price, size))

if __name__ == "__main__":
    foo(sys.argv[1], sys.argv[2])
