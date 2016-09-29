#include "fastQ.hpp"
#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <chrono>


using namespace std;

void test_merge_compress() {
  vector<CApproxRank<int> > testS0;
  vector<CApproxRank<int> > testS1;

  CApproxRank<int> ar1(2,1,1);
  CApproxRank<int> ar2(4,3,4);
  CApproxRank<int> ar3(8,5,6);
  CApproxRank<int> ar4(17,8,8);

  testS0.push_back(ar1);
  testS0.push_back(ar2);
  testS0.push_back(ar3);
  testS0.push_back(ar4);


  CApproxRank<int> br1(1,1,1);
  CApproxRank<int> br2(7,3,3);
  CApproxRank<int> br3(12,5,6);
  CApproxRank<int> br4(15,8,8);
  testS1.push_back(br1);
  testS1.push_back(br2);
  testS1.push_back(br3);
  testS1.push_back(br4);

  CSummary<int> S;
  S.init(10, 0.2);

  cout << "S0" << endl;
  for (int i = 0; i<testS0.size(); i++){
  	cout << testS0[i].v << ' ' << 
  	   testS0[i].rmin << ' ' <<
  	   testS0[i].rmax << endl;
  }

  cout << "S1" << endl;
  for (int i = 0; i<testS1.size(); i++){
  	cout << testS1[i].v << ' ' << 
  	   testS1[i].rmin << ' ' <<
  	   testS1[i].rmax << endl;
  }
  
  vector<CApproxRank<int> > mergedS = S.merge(testS0, testS1);

  cout << "S merged with size: " << mergedS.size() << endl;
  for (int i = 0; i<mergedS.size(); i++) {
  	cout << mergedS[i].v << ' ' 
  	  << mergedS[i].rmin << ' '
  	  << mergedS[i].rmax << ' ' << endl;
  }


  cout << "compressed as: " << endl;
  vector<CApproxRank<int> > compressedS = S.compress(mergedS, 4);
  for (int i = 0; i < compressedS.size(); i++) {
  	cout << compressedS[i].v << ' '
  	<< compressedS[i].rmin << ' '
  	<< compressedS[i].rmax << endl;
  }

  return;
}


bool test_rank(int N, double eps) {
	CSummary<int> S;
	int L = static_cast<int>(floor(log(N)/log(2))+2);
	S.init(L, eps);

	vector<int> record;

    bool success = true;

    vector<double> q_true;
    q_true.resize(N);
    vector<double> q_approx;
    q_approx.resize(N);

    auto c_t0 = chrono::high_resolution_clock::now();
	for (int i = 0; i<N; i++) {
		int v = rand() % 200;
		record.push_back(v);

        double true_rank = 0;
        for (int j = 0; j < i; j++)
            if (record[j] <= record[i] ) true_rank++;

        q_true[i] = true_rank/(i+1);
	}
    auto c_t1 = chrono::high_resolution_clock::now();

    
    auto q_t0 = chrono::high_resolution_clock::now();
    for (int i = 0; i<N; i++){
        int v = record[i];
        S.update(v);
        q_approx[i] = S.query(v);

        if (fabs(q_true[i] - q_approx[i]) > eps) {
            cout << "True quantile: " << q_true[i] << " " 
            << "Estimated quantile:" << q_approx[i] ; 
            cout << " Failed " 
            << i  << endl;
            success = false;
        }

    }
    auto q_t1 = chrono::high_resolution_clock::now();
   
    cout << "Speed up rate: " << 
    chrono::duration_cast<std::chrono::milliseconds>(c_t1-c_t0).count()
    << ' '
    << chrono::duration_cast<std::chrono::milliseconds>(q_t1-q_t0).count()
    << endl;
	return(success);
}

int main() {
  CSummary<int> S;


  test_merge_compress();

  int testN= 5; // run 100 random tests
  int stream_size = 10000;
  double eps = 0.1;
  srand(time(NULL));

  bool all_success = true;
  for (int i = 0; i<testN; i++)
  	all_success = test_rank(stream_size, eps) && all_success;

  if (all_success) {
  	cout << "Run " << testN << " random streams of size " << stream_size
  	<< ". All of the approximate quantile has error bounded by " << eps << endl;
  } 
  return 0;
}
