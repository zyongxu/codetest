#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
from localib import util
from localib import dyplot
from localib.data_record import DataRecord

def outrightLoop(sec, drs, result):
    while 1:
        sp_price = drs[0].price
        sp_size  = drs[0].size
        result[util.sec2str(sec[0])] = [sp_price, sp_size]
        sec[0] = drs[0].getRecord()
        if sec[0] == -1:
            break

def spreadLoop(sec, drs, result):
    while 1:
        if sec[0] == -1 or sec[1] == -1:
            break;
        elif sec[0] < sec[1]:
            sec[0] = drs[0].getRecord()
        elif sec[1] < sec[0]:
            sec[1] = drs[1].getRecord()
        else:
            sp_price = drs[0].price - drs[1].price
            sp_size  = min(drs[0].size, drs[1].size)
            result[util.sec2str(sec[0])] = [sp_price, sp_size]
            sec[0] = drs[0].getRecord()
            sec[1] = drs[1].getRecord()

def butterflyLoop(sec, drs, result):
    while 1:
        if sec[0] == -1 or sec[1] == -1 or sec[2] == -1:
            break;
        elif sec[0] < sec[1] and sec[0] < sec[2]:
            sec[0] = drs[0].getRecord()
        elif sec[1] < sec[0] and sec[1] < sec[2]:
            sec[1] = drs[1].getRecord()
        elif sec[2] < sec[0] and sec[2] < sec[1]:
            sec[2] = drs[2].getRecord()
        else:
            sp_price = drs[0].price - 2 * drs[1].price + drs[2].price
            sp_size  = min(drs[0].size, drs[1].size, drs[2].size)

            result[util.sec2str(sec[0])] = [sp_price, sp_size]
            sec[0] = drs[0].getRecord()
            sec[1] = drs[1].getRecord()
            sec[2] = drs[2].getRecord()


def main(fnames):
    drs = []
    chart_name = ""
    result = {}
    for f in fnames:
        drs.append(DataRecord(f))
        chart_name += util.getProdFromFilename(f) + ' '

    chart_name = chart_name[:-1].replace(' ', '-')

    sec = []
    for dr in drs:
        sec.append(dr.getRecord())

    if len(drs) == 1:
        outrightLoop(sec, drs, result)
    elif len(drs) == 2:
        spreadLoop(sec, drs, result)
    elif len(drs) == 3:
        butterflyLoop(sec, drs, result)

    dyplot.drawChart(result, chart_name)

if __name__ == "__main__":
    main(sys.argv[1:])
