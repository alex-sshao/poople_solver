#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using std::vector;

void get_poomap( std::string filename, vector<std::string> wordlist ) {
	std::ifstream words( filename );
	wordlist.resize( 1 );
	for ( int i = 0; std::getline( words, wordlist[i] ); ++i )
		wordlist.resize( i + 2 );
	words.close();
}

template <typename T> inline bool in_vec( vector<T> vec, T item ) {
	return std::find( std::begin( vec ), std::end( vec ), item ) !=
		   std::end( vec );
}

bool one_diff( std::string w1, std::string w2 ) {
	int diff = 0;
	for ( int i = 0; i < w1.length(); ++i )
		if ( w1[i] != w2[i] ) diff++;
	return diff == 1;
}

void poosolve( std::string word, const vector<std::string> wordlist ) {
	if ( in_vec( wordlist, word ) ) {
		std::cout << "Word not in list!\n";
		return;
	}
	vector<int> dist;
	int			nz = 0;
	for ( auto i = 0; i < wordlist.size(); ++i ) dist.push_back( 0 );
	for ( int i = 0; i < sizeof( dist ); ++i )
		if ( one_diff( wordlist[i], "poop" ) ) {
			nz++;
			dist[i] = 1;
		}
	while ( nz < sizeof( dist ) )
		for ( int i = 1; i < sizeof( dist ); ++i )
			if ( dist[i] != 0 )
				for ( int j = 0; j < sizeof( dist ); ++j )
					if ( one_diff( wordlist[i], wordlist[j] ) &&
						 dist[j] == 0 ) {
						dist[j] = dist[i] + 1;
						nz ++;
					}
}

int main( int argc, char **argv ) {
	if ( argc <= 1 ) {
		std::cout << "Not enough arguments!\n";
		return 0;
	}
	vector<std::string> wordlist;
	get_poomap( "poople_words.txt", wordlist );
	poosolve( argv[1], wordlist );

	return 0;
}
