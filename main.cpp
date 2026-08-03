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

void dist_from_poop( vector<std::string>						   wordlist,
					 std::map<std::string, int, std::greater<int>> wordmap ) {
	for ( auto word : wordlist ) wordmap.insert( { word, 0 } );
	wordmap.at("poop") = -1;
	int nz = 0; 
	while ( nz < wordmap.size() ) {
		
	}
}

void poosolve( std::string word, const vector<std::string> wordlist ) {
	if ( in_vec( wordlist, word ) ) {
		std::cout << "Word not in list!\n";
		return;
	}
	std::map<std::string, int, std::greater<int>> wordmap;
	dist_from_poop( wordlist, wordmap );
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
