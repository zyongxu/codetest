#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import gplot
import datetime
import os

class DataRecord:
    def __init__(self, filename):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.price     = 0
        self.size      = 0
        self.prev_size = 0
        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields = curr_line.split(',');
        self.sec   = str2sec(fields[0])
        self.price = float(fields[2])
        cur_size   = int(fields[3])

        self.size = cur_size - self.prev_size
        self.prev_size = cur_size

        return self.sec

def main(fname1):
    dr1 = DataRecord(fname1)
    spread_name = os.path.basename(fname1)
    result = {}

    sec1 = dr1.getRecord()

    while 1:
        sp_price = dr1.price
        sp_size  = dr1.size
        millisec = datetime.timedelta(milliseconds = sec1 * 100)
        tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
        tmp_date = tmp_date + millisec
        result[tmp_date] = [sp_size, sp_price]
        sec1 = dr1.getRecord()
        if sec1 == -1:
            break

    gplot.drawChart(result, spread_name)

def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

if __name__ == "__main__":
    main(sys.argv[1])
