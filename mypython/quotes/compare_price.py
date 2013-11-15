#!/usr/bin/python

# Use goolge-visualization-python
#   https://code.google.com/p/google-visualization-python/
# and dygraph to plot

import sys
from localib import util
from localib import dyplot
from localib.data_record import DataRecord

def main(fnames):
    drs = []
    chart_name = ""
    result = {}
    base_price = []
    for f in fnames:
        dr = DataRecord(f)
        drs.append(dr)
        chart_name += util.getProdFromFilename(f) + ' '

    chart_name = chart_name[:-1].replace(' ', '-')

    sec = []
    for dr in drs:
        sec.append(dr.getRecord())
        base_price.append(dr.price)

    while 1:
        if -1 in sec:
            break;
        elif len(set(sec)) <= 1:
            result[util.sec2str(sec[0])] = [drs[0].price - base_price[0], drs[1].price - base_price[1]]
            sec[0] = drs[0].getRecord()
            sec[1] = drs[1].getRecord()
        else:
            val, idx = min((val, idx) for (idx, val) in enumerate(sec))
            result[util.sec2str(sec[idx])] = [drs[0].price - base_price[0], drs[1].price - base_price[1]]
            sec[idx] = drs[idx].getRecord()

    dyplot.drawTwoLines(result, chart_name, util.getProdFromFilename(fnames[0]), util.getProdFromFilename(fnames[1]))

if __name__ == "__main__":
    main(sys.argv[1:])
