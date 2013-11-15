#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
from localib import util
from localib import dyplot
from localib.data_record import DataRecord

def outrightLoop(sec, drs, result):
    sp_price = drs[0].price
    sp_size  = drs[0].size
    result[util.sec2str(sec[0])] = [sp_price, sp_size]
    sec[0] = drs[0].getRecord()

def spreadLoop(sec, drs, result):
    sp_price = drs[0].price - drs[1].price
    sp_size  = min(drs[0].size, drs[1].size)
    result[util.sec2str(sec[0])] = [sp_price, sp_size]
    sec[0] = drs[0].getRecord()
    sec[1] = drs[1].getRecord()

def butterflyLoop(sec, drs, result):
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

    while 1:
        if -1 in sec:
            break;
        elif len(set(sec)) <= 1:
            if len(drs) == 1:
                outrightLoop(sec, drs, result)
            elif len(drs) == 2:
                spreadLoop(sec, drs, result)
            elif len(drs) == 3:
                butterflyLoop(sec, drs, result)
        else:
            val, idx = min((val, idx) for (idx, val) in enumerate(sec))
            sec[idx] = drs[idx].getRecord()

    dyplot.drawChart(result, chart_name)

if __name__ == "__main__":
    main(sys.argv[1:])
