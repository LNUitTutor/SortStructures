#ifndef _DATA_PROCEDURES_GUARD_
#define _DATA_PROCEDURES_GUARD_

#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;

const unsigned n = 3;
const unsigned m = 4;

void SortEachRow();
void SortMatrix();
void SortMatrixSum();
void SortByChain();
void SortByTree();
void MergeSequences();
void MergeLists();
void SortByMerge();

void FillFile(ofstream& f, unsigned n);
void ShowFile(const char* fileName);
void SortFile(const char* fileName);
void Distribute(ifstream& f, ofstream& a, ofstream& b, long long& ka, long long& kb);
void MergeFile(ifstream& a, ifstream& b, ofstream& c, long long k);

void ReadMatrix(int a[n][m]);
void PrintMatrix(int a[n][m]);
void SimpleInsertSort(int* a, unsigned n);
void SwapArray(int* a, int* b, unsigned n);
void PrintVector(int* a, unsigned n);

#endif