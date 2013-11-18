#!/usr/bin/python

import sys
import re
import datetime
import os

class MakeLeg:
    def __init__(self, filename):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.bid_price = 0
        self.ask_price = 0
        self.fobj.readline() #The first line is a summary of yesterday
        self.fobj.readline() #do a favor to IF

    def getRecord(self):
        curr_line = self.fobj.readline()
        if not curr_line:
            return -1

        fields = curr_line.split(',');
        self.sec = str2sec(fields[0])
        cur_mkt = fields[1].split(' ')
        self.bid_price = float(cur_mkt[0])
        self.ask_price = float(cur_mkt[2])
        return self.sec

class LiftHitLeg:
    def __init__(self, filename, stop_tick):
        self.fobj = open(filename, 'rb')
        self.sec       = 0
        self.time_str  = ""
        self.bid_price = 0
        self.ask_price = 0
        self.last_middle_price = 0
        self.avg_lift_lost = 0
        self.avg_hit_lost  = 0

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
        self.time_str = fields[0]
        self.sec = str2sec(fields[0])
        cur_mkt  = fields[1].split(' ')
        tprice = float(fields[2])

        new_bids = []
        for bid in self.bid_buf:
            if (bid[1] >= tprice):
                self.bid_fill_cnt += 1
            elif (bid[1] <= self.last_middle_price - self.stop_loss):
                self.bid_stop_cnt += 1
                lost = tprice - bid[1]
                self.avg_lift_lost += lost
                print "lift:\t{}\t{}\tbuy:\t{}\t{}\tlost={}".format(bid[0], bid[1], self.time_str, tprice, lost)
            else:
                new_bids.append(bid)
        self.bid_buf = new_bids

        new_asks = []
        for ask in self.ask_buf:
            if (ask[1] <= tprice):
                self.ask_fill_cnt += 1
            elif (ask[1] >= self.last_middle_price + self.stop_loss):
                self.ask_stop_cnt += 1
                lost = ask[1] - tprice
                self.avg_hit_lost += lost
                print "hit:\t{}\t{}\tsell:\t{}\t{}\tlost={}".format(ask[0], ask[1], self.time_str, tprice, lost)
            else:
                new_asks.append(ask)
        self.ask_buf = new_asks

        self.bid_price = float(cur_mkt[0])
        self.ask_price = float(cur_mkt[2])
        self.last_middle_price = (self.bid_price + self.ask_price) / 2

        return self.sec

    def addLift(self):
        self.bid_buf.append([self.time_str, self.ask_price])

    def addHit(self):
        self.ask_buf.append([self.time_str, self.bid_price])

def main(fname1, fname2, stop_tick):
    dr1 = LiftHitLeg(fname1, stop_tick)
    dr2 = MakeLeg(fname2)
    sec1 = dr1.getRecord()
    sec2 = dr2.getRecord()
    bid_trigger = -2.0
    ask_trigger = -1.4

    while 1:
        if sec1 == -1 or sec2 == -1:
            break
        elif sec1 < sec2:
            sec1 = dr1.getRecord()
        elif sec2 < sec1:
            sec2 = dr2.getRecord()
        else:
            sp_bid_price = dr1.ask_price - dr2.ask_price + 0.2
            sp_ask_price = dr1.bid_price - dr2.bid_price - 0.2
            if (sp_bid_price < bid_trigger):
                dr1.addLift()
            elif (sp_ask_price > ask_trigger):
                dr1.addHit()

            sec1 = dr1.getRecord()
            sec2 = dr2.getRecord()

    print "buy stop: {}, buy fill: {}, avg lost: {}\nsell stop: {}, sell fill: {}, agv lost: {}".format(dr1.bid_stop_cnt, dr1.bid_fill_cnt, dr1.avg_lift_lost/dr1.bid_stop_cnt, dr1.ask_stop_cnt, dr1.ask_fill_cnt, dr1.avg_hit_lost/dr1.ask_stop_cnt)

def str2sec(time_stamp):
    hour    = int(time_stamp[0:2]) - 9
    minu    = int(time_stamp[3:5])
    sec     = int(time_stamp[6:8])
    milisec = int(time_stamp[9:12])

    return (hour*3600 + minu*60 + sec)*10 + milisec/100

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
