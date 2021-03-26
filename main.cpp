#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <random>

#include <ctime>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <sstream>

extern int optind,opterr,optopt;
extern char *optargi;

using namespace std;

static struct option long_options[] =
    {
            {"zero",no_argument,NULL,'z'},
            {"random",no_argument,NULL,'r'},
            {"files",required_argument,NULL,'f'},
            {"help",no_argument,NULL,'h'}
    };

template<typename T> string toString(const T& t)
{
    ostringstream oss;
    oss<<t;
    return oss.str();
}

void zero_generator()
{
    time_t t = time(0);

    string file = "./" + toString(t) + "_zero.txt";
    ofstream outfile;
    cout << file << endl;
    outfile.open(file, std::ios::out);
    if (!outfile.is_open())
    {
        cout << file << endl;
        return;
    }

    int i = 0;

    for ( i=0; i<1000000; i++ ) {
        outfile << setiosflags(ios::uppercase) << hex << setw(2) << setfill('0') << 0 << " ";
        cout << setiosflags(ios::uppercase) << hex << setw(2) << setfill('0') << 0 << " ";
    }

    outfile.close();
}

void random_generator()
{
    time_t t = time(0);

    string file = "./" + toString(t) + "_random.txt";
    ofstream outfile;
    cout << file << endl;
    outfile.open(file, std::ios::out);
    if (!outfile.is_open())
    {
        cout << file << endl;
        return;
    }

    default_random_engine rand(time(NULL));
    uniform_int_distribution<int> rand1(0,256);

    int i = 0;

    for ( i=0; i<1000000; i++ ) {
//        cout << setiosflags(ios::uppercase) << hex << rand() << " ";
        outfile << setiosflags(ios::uppercase) << hex << setw(2) << setfill('0') << rand1(rand) << " ";
        cout << setiosflags(ios::uppercase) << hex << setw(2) << setfill('0') << rand1(rand) << " ";
    }

    outfile.close();
}

void files_generator(string str)
{
    char c;
    char array_c[2];
    ifstream infile;
    infile.open(str);

    if (!infile.is_open())
        return;

    int i = 0;
    while(!infile.eof())
    {
        infile>>c;
        array_c[i] = c;
        i++;
        if(i==2)
        {
            i=0;
            cout << array_c << " ";
            infile>>c;
        }
    }
    infile.close();

}

int InputGenerator(int argc,char *argv[]) {

    int index = 0;
    int c = 0;

    while(EOF != (c = getopt_long(argc,argv,"zrhf:",long_options,&index)))
    {
        switch(c)
        {
            case 'z':
                zero_generator();
                return 0;
            case 'r':
                random_generator();
                return 0;
            case 'f':
                files_generator(optarg);
                return 0;
            case 'h':
                cout << "usage: ./InputGenerator [option] ... [-c cmd | -m mod | file | -] [arg] ..." << endl <<
                    "Options and arguments (and corresponding environment variables):" << endl <<
                    "-z     : zero mode(Generate Input with all zeroes)" << endl <<
                    "-r     : random mode(Generate Input with random values)" << endl <<
                    "-f     : files mode(Generate Input from given input files). At the same time, the file should be given." << endl <<
                    "-h     : print this help message and exit (also --help)" << endl;
                return 0;
            case '?':
                printf("Unknown option: %c\n", optopt);
                cout << "Please use -h/--help options to get the right option." << endl;
                return 0;
            default:
                break;
        }
    }

    std::cout << "Welcome to use InputGenerator" << std::endl;
    return 0;
}
