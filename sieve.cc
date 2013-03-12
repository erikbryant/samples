//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

//
// TODO
// Rewrite the pattern logic. Instead of pre-computing the entire pattern, have it
// slowly expand itself to fill the whole buffer.
// Watch out for those lines where we would have to set the sieve values as being primes.
//


#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

inline unsigned int offsetByte( unsigned int location )
{
	return ( location >> 3 );
}

inline unsigned char offsetBit( unsigned int location )
{
	return ( location & 0x07 );
}

inline unsigned char getbit( unsigned int location, char *buffer )
{
	return ( (buffer[offsetByte( location )] & ( 0x01 << offsetBit( location ) )) >> offsetBit( location ) );
}

inline void setbit( unsigned int location, char *buffer )
{
	buffer[offsetByte( location )] |= 0x01 << offsetBit( location );
}

inline void clearbit( unsigned int location, char *buffer )
{
	buffer[offsetByte( location )] &= ~( 0x01 << offsetBit( location ) );
}

unsigned int printCandidates( unsigned int max, char *buffer )
{
	unsigned int found = 0;

	cout << "Candidates:" << endl;

	for ( unsigned int i = 0; i <= max; i++ )
	{
		if ( getbit( i, buffer ) )
		{
			found++;
			cout << "  " << i << endl;
		}
	}

	return found;
}

unsigned int countCandidates( unsigned int max, char *buffer )
{
	unsigned int found = 0;

	// 2 is prime. Be sure to include it.
	found = 1;

	for ( unsigned int i = 3; i <= max; i += 2 )
	{
		found += getbit( i, buffer );
	}

	return found;
}

inline void sieve( unsigned int multiple, unsigned int max, char *buffer )
{
	for ( unsigned int i = multiple * 2; i <= max; i += multiple )
	{
		clearbit( i, buffer );
	}
}

unsigned int initbits( char *buffer, unsigned int buffLen )
{
	unsigned int pattLen = 8 * (3 * 5);
	unsigned int max = (pattLen * 8) - 1;
	char *pattern = new char[pattLen];

	if ( buffLen < pattLen )
	{
		cout << "ERROR: buffLen is less than pattLen." << endl;
		exit( 1 );
	}

	// Use this opportunity to clear all the even bits.
	memset( (void *) pattern, 0xaa, sizeof( char ) * pattLen );

	sieve( 3, max, pattern );
	clearbit( 3, pattern );
	sieve( 5, max, pattern );
	clearbit( 5, pattern );

	unsigned int i = 0;
	for ( i = 0; i <= (buffLen-pattLen); i += pattLen )
	{
		memcpy( &(buffer[i]), pattern, pattLen );
	}

	if ( buffLen % pattLen ) {
		memcpy( &(buffer[i]), pattern, buffLen % pattLen );
	}

	delete pattern;

	// By convention, 0 and 1 are not prime. 2 is prime.
	clearbit( 0, buffer );
	clearbit( 1, buffer );
	setbit( 2, buffer );
	setbit( 3, buffer );
	setbit( 5, buffer );

	// Tell the caller how far we got (i.e., where they should start from)
	return 7;
}

inline void clearallbits( char *buffer, unsigned int buffLen )
{
	memset( (void *) buffer, 0x00, sizeof( char ) * buffLen );
}

int main( int argc, char* argv[] )
{
#define max (1000)
#define max_len ( (max+8)>>3 )

	char *candidates = new char[max_len];

	unsigned int found = 0;
	clock_t start;
	clock_t finish;

	start = clock();

	unsigned int floor   = initbits( candidates, max_len );
	unsigned int ceiling = (unsigned int) sqrt( (double) max );

	for ( unsigned int i = floor; i <= ceiling; i++ )
	{
		if ( getbit( i, candidates ) ) {
			sieve( i, max, candidates );
		}
	}

	found = countCandidates( max, candidates );

	finish = clock();

	cout << "Examined:     " << max << endl;
	cout << "Found:        " << found << endl;
	cout << "Storage:      " << max_len << endl;
	cout << "Calc(msec):   " << finish - start << endl;
	cout << endl;
	// http://primes.utm.edu/howmany.shtml
	cout << "max                                                  # primes" << endl;
	cout << "10                                                          4" << endl;
	cout << "100                                                        25" << endl;
	cout << "1,000                                                     168" << endl;
	cout << "10,000                                                  1,229" << endl;
	cout << "100,000                                                 9,592" << endl;
	cout << "1,000,000                                              78,498" << endl;
	cout << "10,000,000                                            664,579" << endl;
	cout << "100,000,000                                         5,761,455" << endl;
	cout << "1,000,000,000                                      50,847,534" << endl;
	cout << "10,000,000,000                                    455,052,511" << endl;
	cout << "100,000,000,000                                 4,118,054,813" << endl;
	cout << "1,000,000,000,000                              37,607,912,018" << endl;
	cout << "10,000,000,000,000                            346,065,536,839" << endl;
	cout << "100,000,000,000,000                         3,204,941,750,802" << endl;
	cout << "1,000,000,000,000,000                      29,844,570,422,669" << endl;
	cout << "10,000,000,000,000,000                    279,238,341,033,925" << endl;
	cout << "100,000,000,000,000,000                 2,623,557,157,654,233" << endl;
	cout << "1,000,000,000,000,000,000              24,739,954,287,740,860" << endl;
	cout << "10,000,000,000,000,000,000            234,057,667,276,344,607" << endl;
	cout << "100,000,000,000,000,000,000         2,220,819,602,560,918,840" << endl;
	cout << "1,000,000,000,000,000,000,000      21,127,269,486,018,731,928" << endl;
	cout << "10,000,000,000,000,000,000,000    201,467,286,689,315,906,290" << endl;
	cout << "100,000,000,000,000,000,000,000 1,925,320,391,606,803,968,923" << endl;

	return 0;
}

