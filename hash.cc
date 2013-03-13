//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>
#include <list>

using std::ostream;
using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::string;

template <typename KEY, typename VALUE>
class HashTable
{
public:
  HashTable();
  void add( const KEY &key, const VALUE &value );
  const VALUE *get( const KEY &key ) const;

  friend ostream &operator<<( ostream &os, const HashTable<KEY,VALUE> &map )
  {
    unsigned int i = 0;

    for ( i = 0; i < map.numBuckets; ++i )
      {
        if ( map.buckets[i] == NULL )
          {
            os << "Bucket[" << i << "] NULL" << endl;
          }
        else
          {
            os << "Bucket[" << i << "]";
            typename list< pair<KEY,VALUE> >::iterator it;
            for ( it = map.buckets[i]->begin(); it != map.buckets[i]->end(); ++it )
              {
                os << " --> Key: " << it->first << " => Value: " << it->second;
              }
          }
        cout << endl;
      }

    return os;
  }

private:
  unsigned int hash( const KEY &key ) const;

  static const unsigned int numBuckets = 10;
  list< pair<KEY,VALUE> > *buckets[numBuckets];
};

template <typename KEY, typename VALUE>
HashTable<KEY,VALUE>::HashTable( void )
{
  unsigned int i = 0;
  for ( i = 0; i < numBuckets; ++i )
    {
      buckets[i] = NULL;
    }
}

template <typename KEY, typename VALUE>
void HashTable<KEY,VALUE>::add( const KEY &key, const VALUE &value )
{
  unsigned int i = hash( key );

  if ( buckets[i] == NULL )
    {
      buckets[i] = new list< pair<KEY,VALUE> >();
    }
  else
    {
      // Search the list. If this key IS in there, update its value.
      typename list< pair<KEY,VALUE> >::iterator it;
      for ( it = buckets[i]->begin(); it != buckets[i]->end(); ++it )
        {
          if ( it->first == key )
            {
              it->second = value;
              return;
            }
        }
      // The key was NOT in there. Fall out and add the key/value.
    }

  pair<KEY,VALUE> p( key, value );
  buckets[i]->push_back( p );
}

template <typename KEY, typename VALUE>
const VALUE *HashTable<KEY,VALUE>::get( const KEY &key ) const
{
  unsigned int i = hash( key );

  if ( buckets[i] != NULL )
    {
      typename list< pair<KEY,VALUE> >::iterator it;
      for ( it = buckets[i]->begin(); it != buckets[i]->end(); ++it )
        {
          if ( it->first == key )
            {
              return &( it->second );
            }
        }
    }

  return NULL;
}

template <typename KEY, typename VALUE>
unsigned int HashTable<KEY,VALUE>::hash( const KEY &key ) const
{
  return key % numBuckets;
}

int main( int argc, char *argv[] )
{
  HashTable<int,string> map;

  map.add( 0, "Zero" );
  map.add( 1, "One" );
  map.add( 2, "Two" );
  map.add( 3, "Three" );
  map.add( 4, "Four" );
  map.add( 5, "Five" );
  map.add( 6, "Six" );
  map.add( 7, "Seven" );
  map.add( 8, "Eight" );
  map.add( 9, "Nine" );
  map.add( 10, "Ten" );
  map.add( 11, "Eleven" );

  cout << " 0: " << *(map.get( 0 )) << endl;
  cout << " 6: " << *(map.get( 6 )) << endl;
  cout << " 9: " << *(map.get( 9 )) << endl;
  cout << "10: " << *(map.get( 10 )) << endl;

  cout << map << endl;
}
