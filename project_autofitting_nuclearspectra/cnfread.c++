#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios_base;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::hex;

#include <cstdlib>

//#define CHANNELN 0x642a
//#define SPECTRUM 0x6600

#define CHANNELN 0x6a16
#define SPECTRUM 0x6c00

int main(int argc, char ** argv)
{
  ifstream * in;
  ofstream * out;
  short int nch;
  
  ofstream file;
  
  
  if (argc < 2){
    cerr << "error, please write the input filename ..." << endl;
    // cerr << "Ge40_Co60_10min.CNF" << endl;
    exit(1);
  }

  if (argc > 3){
    cerr << "too many parameters" << endl;
    exit(1);
  }

  in= new ifstream(argv[1], ios_base::in);
  if (!in){
    cerr << "input file open error" << endl;
    exit(1);
  }

  if(argc == 3){
    out = new ofstream(argv[2],ios_base::out);
    if(!out){
      cerr << "output file open error" << endl;
      exit(1);
    }
  }
  in->seekg(CHANNELN);
  in->read(reinterpret_cast<char *>(&nch),sizeof(short int));
  
  int count;
  nch=0x1000;
  file.open("salida.dat");
  for(int i=1;i<=nch;i++){
    in->seekg(SPECTRUM+i*sizeof(int));
    in->read(reinterpret_cast<char *>(&count),sizeof(int));
    if(argc == 2)
      cout << i << "\t" << count << endl; 
    else
       *out << i << "\t" << count << endl;
 
    if(argc == 2)
    file << i << "\t" << count <<"\n";
    else
      file << i << "\t" << count << endl;
    // file.close();

    
  }
  return 0;
}
 
