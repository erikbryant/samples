//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::min;

#undef CACHE_FILE
#undef TEXT_OUTPUT
#define CACHE_FILE
#define TEXT_OUTPUT

int main( int argc, char* argv[] )
{
#ifdef TEXT_OUTPUT
  const char *primesFile       = "primes.cache";
#endif
  const char *primesFileBinary = "primes.cache.binary";
  unsigned int max = 100 * 1000 * 1000;
  unsigned int first = 0;
  unsigned int found = 0;
  // A storage ratio of 0.867 gets us to max = 10,000,000,000
  unsigned int space   = static_cast<unsigned int>(pow(static_cast<double>(max), 0.867));
  unsigned int *primes = new unsigned int[space];
  clock_t start;
  clock_t finish;

  cout << "Prime number generator." << endl;

#ifdef CACHE_FILE
  ifstream cacheInB( primesFileBinary, ios::in | ios::binary );
  unsigned int max_file = 0;
  if ( cacheInB.is_open() )
    {
      unsigned int found_file = 0;

      start = clock();
      cout << "Binary cache file exists. Initializing from cache." << endl;
      cacheInB.read( reinterpret_cast<char*>(&max_file), sizeof( max_file ) );
      cacheInB.read( reinterpret_cast<char*>(&found_file), sizeof( found_file ) );
      cout << "Cache file contains: max: " << max_file << " found: " << found_file << endl;

      // Skip even numbers. The algorithm depends on starting number being odd.
      if ( max_file & 0x01 ) {
        first = max_file + 2;
      } else {
        first = max_file + 1;
      }

      unsigned int preload = min( space, found_file );
      cacheInB.read( reinterpret_cast<char*>(primes), sizeof( primes[0] ) * preload );
      if ( max < max_file ) {
        for( unsigned int i = 0; i < preload; i++ ) {
          if ( primes[i] < max ) {
            found++;
          }
        }
      } else {
        found = preload;
      }
      cacheInB.close();
      finish = clock();
      cout << "Cache(msec):  " << finish - start << endl;
    }
  else
#endif
    {
      cout << "Unable to open cache file: " << primesFileBinary
           << ". Calculating from scratch." << endl;
      // 1 is not prime, but 2 is. Record it.
      primes[found] = 2;
      found++;
      first = 3;
    }

  start = clock();
  for ( unsigned int candidate = first; candidate <= max; candidate += 2 ) {
    primes[found] = candidate;
    found++;
    int ceiling = static_cast<int>(sqrt( static_cast<double>(candidate) )) + 1;
    for ( unsigned int i = 0; (i < found) && (static_cast<int>(primes[i]) < ceiling); i++ ) {
      if ( candidate % primes[i] == 0 ) {
        found--;
        break;
      }
    }
  }
  finish = clock();

  cout << "Examined:     " << max << endl;
  cout << "Found:        " << found << endl;
  cout << "Storage:      " << space << endl;
  cout << "Calc(msec):   " << finish - start << endl;
  cout << endl;
  // http://primes.utm.edu/howmany.shtml
  cout << "max                                          # primes" << endl;
  cout << "10                                                  4" << endl;
  cout << "100                                                25" << endl;
  cout << "1,000                                             168" << endl;
  cout << "10,000                                          1,229" << endl;
  cout << "100,000                                         9,592" << endl;
  cout << "1,000,000                                      78,498" << endl;
  cout << "10,000,000                                    664,579" << endl;
  cout << "100,000,000                                 5,761,455" << endl;
  cout << "1,000,000,000                              50,847,534" << endl;
  cout << "10,000,000,000                            455,052,511" << endl;
  cout << "100,000,000,000                         4,118,054,813" << endl;
  cout << "1,000,000,000,000                      37,607,912,018" << endl;
  cout << "10,000,000,000,000                    346,065,536,839" << endl;
  cout << "100,000,000,000,000                 3,204,941,750,802" << endl;
  cout << "1,000,000,000,000,000              29,844,570,422,669" << endl;
  cout << "10,000,000,000,000,000            279,238,341,033,925" << endl;
  cout << "100,000,000,000,000,000         2,623,557,157,654,233" << endl;
  cout << "1,000,000,000,000,000,000      24,739,954,287,740,860" << endl;
  cout << "10,000,000,000,000,000,000    234,057,667,276,344,607" << endl;
  cout << "100,000,000,000,000,000,000 2,220,819,602,560,918,840" << endl;

  //
  // If we have gone further with the search for primes
  // than what was in the cace file, add the new data
  // to the cache file.
  //
#ifdef CACHE_FILE
  if ( max > max_file ) {
    cout << "We have new calculated data. Writing back to cache file." << endl;

#ifdef TEXT_OUTPUT
    ofstream cacheOut( primesFile );
    if ( cacheOut.is_open() )
      {
        cacheOut << max << endl;
        cacheOut << found << endl;
        for ( unsigned int i = 0; i < found; i++ ) {
          cacheOut << primes[i] << endl;
        }
        cacheOut.close();
      } else {
      cout << "Unable to create cache file: " << primesFile << endl;
    }
#endif

    ofstream cacheOutB( primesFileBinary, ios::binary );
    if ( cacheOutB.is_open() )
      {
        cacheOutB.write( reinterpret_cast<char*>(&max), sizeof( max ) );
        cacheOutB.write( reinterpret_cast<char*>(&found), sizeof( found ) );
        cacheOutB.write( reinterpret_cast<char*>(primes), sizeof( primes[0] ) * found );
        cacheOutB.close();
      } else {
      cout << "Unable to create cache file: " << primesFileBinary << endl;
    }
  }
#endif

  delete[] primes;

  return 0;
}
