import sys

def findSwitch(fd):
    S=int(fd.readline())
    for i in range(S):
        fd.readline()

    Q=int(fd.readline())
    engines = set()
    ret=0
    for i in range(Q):
        query = fd.readline()
        if (len(engines)==S):
            ret += 1;
            engines.clear()
        engines.add(query)

    return ret

def main(filename):
    fd=open(filename)
    N=int(fd.readline())
    for i in range(N):
        num = findSwitch(fd)
        print "Case #%d: %d" % (i+1, num)


if __name__=="__main__":
    main(sys.argv[1])
