#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include "mkd.pb.h"
using namespace std;

void pbEncode(int secu_id, const string& instru,
              int bp, int bs, int ap, int as,
              string& str) {
    static acm::MktData md;
    md.Clear();

    md.set_secu_id(secu_id);
    md.set_instrument(instru);

    auto *bidq = md.add_quotes();
    bidq->set_price(bp);
    bidq->set_size(bs);
    bidq->set_side(acm::Side::BID);

    auto *askq = md.add_quotes();
    askq->set_price(ap);
    askq->set_size(as);
    askq->set_side(acm::Side::ASK);
    md.SerializeToString(&str);
}

int pbDecode(string &str) {
    static acm::MktData md;
    md.ParseFromString(str);
    volatile int secu_id; // prevent the compiler to optimize the parsing away
    string instru;
    volatile int bp, bs, ap, as;
    volatile int bd, ad;
    volatile int ret = 0;

    secu_id = md.secu_id();
    instru  = md.instrument();
    auto bid = md.quotes(0);
    bp = bid.price();
    bs = bid.size();
    bd = bid.side();
    auto ask = md.quotes(1);
    ap = ask.price();
    as = ask.size();
    ad = ask.side();
    ret = secu_id + instru[0] + bp + bs + ap + as + bd + ad;
    return ret;
}

void plainEncode(int secu_id, const string& instru,
                 int bp, int bs, int ap, int as,
                 string& md) {
    ostringstream oss;
    oss << secu_id << " " << instru << " "
        << bp << " " << bs << " " << 0 << " "
        << ap << " " << as << " " << 1;

    md = oss.str();
}

int plainDecode(string& md) {
    int secu_id;
    string instru;
    int bp, bs, ap, as;
    int bd, ad;
    istringstream iss(md);
    iss >> secu_id >> instru
        >> bp >> bs >> bd
        >> ap >> as >> ad;

    volatile int ret = 0;
    ret = secu_id + instru[0] + bp + bs + ap + as + bd + ad;
    return ret;
}

int main() {
    int repeat = 10000;

    auto start_tp = chrono::high_resolution_clock::now();
    vector<string> mds(repeat, string());
    for (int i=0; i<repeat; i++) {
        pbEncode(12345, "test_pb", i, i-1, i+1, i-1, mds[i]);
    }
    auto end_tp = chrono::high_resolution_clock::now();
    cout << "protobuf encoding time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp).count() << endl;

    start_tp = chrono::high_resolution_clock::now();
    uint64_t dummy = 0;
    for (int i=0; i<repeat; i++) {
        dummy += pbDecode(mds[i]);
    }
    end_tp = chrono::high_resolution_clock::now();
    cout << "protobuf decoding time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp).count() << endl;
    cout << dummy << endl;

    //--------------------------------------------------------------

    start_tp = chrono::high_resolution_clock::now();
    vector<string> strs(repeat, string());
    for (int i=0; i<repeat; i++) {
        plainEncode(12345, "test_pb", i, i-1, i+1, i-1, strs[i]);
    }
    end_tp = chrono::high_resolution_clock::now();
    cout << "sstream encoding time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp).count() << endl;

    start_tp = chrono::high_resolution_clock::now();
    dummy = 0;
    for (int i=0; i<repeat; i++) {
        dummy += plainDecode(strs[i]);
    }
    end_tp = chrono::high_resolution_clock::now();
    cout << "sstream decoding time: " << std::chrono::duration_cast<std::chrono::microseconds>(end_tp - start_tp).count() << endl;
    cout << dummy << endl;

    return 0;
}
