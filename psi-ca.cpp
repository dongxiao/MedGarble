/*The following c++ program is prepared as a part of the following article:

  Dong X, Randolph D, Wang X. The Feasibility of Garbled Circuits for Cross-Site Clinical Data Analytics,
  to appear in Proceedings of AMIA 2020 Informatics Summit, Houston, TX, March, 2020.

  This script is modified from the testing program innerprod.cpp from the forllowing article, we used 
  innerprod.cpp as the template to develop this program.

  Hastings M, Hemenway B, Noble D, Zdancewic S. SoK: General Purpose Compilers for Secure Multi-Party
  Computation. 2019 2019 IEEE Symp Secur Priv. 2019.
  https://github.com/MPC-SoK/frameworks/blob/master/emp/source/innerprod.cpp

  This program is for demo purpose only, do not modify and use it in the production system. 
 
  Author: Xiao Dong                                                                          */


#include "emp-sh2pc/emp-sh2pc.h"
#include <new>
#include <chrono>
using namespace emp;
using namespace std;

int LEN = 10000;

void psi_ca(int bitsize, string inputs_a[], string inputs_b[], int len) {

    Integer prod(bitsize, 0, PUBLIC);
	Integer a[len];
	Integer b[len];
	Batcher b1, b2;

	for (int i = 0; i < len; ++i) {
		b1.add<Integer>(bitsize, inputs_a[i]);
		b2.add<Integer>(bitsize, inputs_b[i]);
	}
 
	b1.make_semi_honest(ALICE);
	b2.make_semi_honest(BOB);

    for( int i=0; i<len; i++) {
        a[i] = b1.next<Integer>();
        b[i] = b2.next<Integer>();
    }

	Integer res(32, 0, PUBLIC);
    for( int i=0; i<len; i++) {
		
		for( int j=0; j<len; j++) { 
			Bit eqij = a[i].equal(b[j]);
			Integer resplus1 = res + Integer(32, 1, PUBLIC);
			res = If(eqij, resplus1, res);
		}
    }

    cout << "SUM: " << res.reveal<int>() << endl;
}


int main(int argc, char** argv) {
    int bitsize;

    // run computation with semi-honest model
    int port, party;
    parse_party_and_port(argv, &party, &port);
    NetIO * io = new NetIO(party==ALICE ? nullptr : "127.0.0.1", port);

    setup_semi_honest(io, party);

    if (argc != 4) {
      cout << "Usage: ./psi-ca <party> <port> <bitsize>" << endl
           << endl;
      delete io;
      return 0;
    }

    cout << "Calculating the cardinality of private set intersection of size: " << LEN << endl;

    bitsize = atoi(argv[3]);

    char fname_a[40];
    char fname_b[40];

    sprintf(fname_a, "../data/psi-ca/%d.1.dat", bitsize);
    sprintf(fname_b, "../data/psi-ca/%d.2.dat", bitsize);

    ifstream infile_a(fname_a);
    ifstream infile_b(fname_b);

    string inputs_a[LEN];
    string inputs_b[LEN];

    if( infile_a.is_open() && infile_b.is_open()) {
        for( int i=0; i<LEN; i++) {
            getline( infile_a, inputs_a[i]);
            getline( infile_b, inputs_b[i]);
        }
        infile_a.close();
        infile_b.close();
    }
	auto t1 = std::chrono::high_resolution_clock::now();
    psi_ca(bitsize, inputs_a, inputs_b, LEN);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << duration;
	
    delete io;
}


