#!/usr/bin/python

import sys
import re

class DataRecord:
    def __init__(self, filename):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.price     = 0
        self.size      = 0
        self.prev_size = 0
        self.fobj.readline() #The first line is a summary of yesterday

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        self.sec = str2sec(curr_line)
        [self.price, cur_size] = priceAndSize(curr_line)

        self.size = cur_size - self.prev_size
        self.prev_size = cur_size

        print ("{0}\t{1}".format(self.price, self.size))
        return self.sec

def foo(fname1, fname2):
    dr1 = DataRecord(fname1)
    result = {}

    while 1:
        sec1 = dr1.getRecord()
        if sec1 == -1:
            break;
        print sec1

def str2sec(time_stamp):
    hour    = float(time_stamp[1:3]) - 9
    minu    = float(time_stamp[4:6])
    sec     = float(time_stamp[7:9])
    milisec = float(time_stamp[10:13])

    #print ("{0}\t{1}\t{2}\t{3}".format(hour, minu, sec, milisec))
    return hour*3600 + minu*60 + sec + milisec/1000

def priceAndSize(str1):
    fields = str1.split(' ', 4)
    price = float(fields[1])
    size  = float(fields[2])

    return [price, size]

if __name__ == "__main__":
    foo(sys.argv[1], sys.argv[2])
