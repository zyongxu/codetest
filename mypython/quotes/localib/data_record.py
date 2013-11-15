import util

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

        fields = curr_line.split(',')
        self.sec   = util.str2sec(fields[0])
        self.price = float(fields[2])
        cur_size   = int(fields[3])

        self.size = cur_size - self.prev_size
        self.prev_size = cur_size

        return self.sec
