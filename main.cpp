#include<iostream>
#include<fstream>  // need this for file I/O
#include<cstdlib>   // for exit()
#include "cache_class.h"


using namespace std;



  
int main(int argc, char*argv[]) {
    /* check if the correct number of arguments have been passed; bail otherwise */
  if (argc < 5) {
    cout << "Usage: " << endl;
    cout << "   ./cachesim num_entries associativity block_size filename" << endl;
    return 0;
  }

 /* get args; all args come in as strings; need to convert to int with atoi() */
  unsigned entries = atoi(argv[1]);
  unsigned assoc = atoi(argv[2]);
  unsigned block_size = atoi(argv[3]);
  string input_filename = argv[4];


  /* print the args */
  cout << "Number of entries: " << entries << endl;
  cout << "Associativity: " << assoc << endl;
  cout << "Input File Name: " << input_filename << endl;

  /* ================== fileio.cpp code =================== */

  /* create input and output files streams */
  ofstream output;
  ifstream input;


  /* open input stream for reading */
  input.open(input_filename);

  /* check if input stream has been succesfully opened; bail otherwise */
  if (!input.is_open()) {
    cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
    exit(0);
  }

  
  /* open output file stream for writing */
  string output_filename = "cachesimoutput";
  output.open(output_filename);

  unsigned long addr;
  Cache cache(entries, assoc, block_size);
  while (input >> addr) {
    if(cache.hit(output, addr)){
      output << addr << " : HIT"<< endl;
    }
    else{
      output << addr << " : MISS"<< endl;
      cache.update(output, addr);
    }
  }

  /* done reading from input file; close the stream */
  input.close();

  /* close output stream */
  output.close();
  return 0;
}
