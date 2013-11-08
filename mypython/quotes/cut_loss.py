#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
import re
import dyplot
import datetime
import os

class DataRecord:
    def __init__(self, filename, stop_tick):
        self.fobj = open(filename, 'rb')
        self.sec       = 0

        self.stop_loss    = float(stop_tick)
        self.bid_stop_cnt = 0
        self.bid_fill_cnt = 0
        self.ask_stop_cnt = 0
        self.ask_fill_cnt = 0
        self.bid_buf      = []
        self.ask_buf      = []

        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields   = curr_line.split(',')
        self.sec = str2sec(fields[0])

        tprice = float(fields[2])
        new_bids = []
        for bid in self.bid_buf:
            if (bid >= tprice):
                self.bid_fill_cnt += 1
            elif (bid <= tprice - self.stop_loss):
                self.bid_stop_cnt += 1
            else:
                new_bids.append(bid)
        self.bid_buf = new_bids

        new_asks = []
        for ask in self.ask_buf:
            if (ask <= tprice):
                self.ask_fill_cnt += 1
            elif (ask >= tprice + self.stop_loss):
                self.ask_stop_cnt += 1
            else:
                new_asks.append(ask)
        self.ask_buf = new_asks

        cur_mkt    = fields[1].split(' ')
        self.bid_buf.append(float(cur_mkt[2]))
        self.ask_buf.append(float(cur_mkt[0]))

        return self.sec

def main(fname1, stop_tick):
    dr1 = DataRecord(fname1, stop_tick)
    spread_name = os.path.basename(fname1)
    result = {}

    sec1 = dr1.getRecord()

    while 1:
        millisec = datetime.timedelta(milliseconds = sec1 * 100)
        tmp_date = datetime.datetime.combine(datetime.date.today(), datetime.time(9,0,0,0))
        tmp_date = tmp_date + millisec
        sec1 = dr1.getRecord()
        if sec1 == -1:
            break
    print "bid stop: {}, bid fill: {}\nask stop: {}, ask fill: {}".format(dr1.bid_stop_cnt, dr1.bid_fill_cnt, dr1.ask_stop_cnt, dr1.ask_fill_cnt)

def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
