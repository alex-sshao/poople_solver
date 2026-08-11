#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;

struct word {
	std::string			   word;
	int					   dist;
	vector<struct word *> *upstream;
} typedef word;

void get_poomap( std::string filename, vector<word *> *wl ) {
	std::ifstream words( filename );
	std::string	  buff;
	for ( int i = 0; std::getline( words, buff ); ++i ) {
		word *w = new word;
		w->word += buff;
		w->dist = -1;
		if ( buff.compare( "poop" ) == 0 ) w->dist = 0;
		w->upstream = new vector<word *>;
		wl->push_back( w );
	}
	words.close();
}

int in_vec( word *w, vector<word *> *wl ) {
	for ( int i = 0; i < wl->size(); ++i ) {
		if ( !w->word.compare( ( *wl )[i]->word ) ) return i;
	}
	return -1;
}

bool one_diff( std::string w1, std::string w2 ) {
	int diff = 0;
	for ( int i = 0; i < w1.length(); ++i )
		if ( w1[i] != w2[i] ) diff++;
	return diff == 1;
}

int calc_solution_count( word *w ) {
	if ( w->upstream->size() == 0 ) return 1;
	int solves = 0;
	for ( int i = 0; i < w->upstream->size(); ++i )
		solves += calc_solution_count( w->upstream->at( i ) );
	return solves;
}

void poosolve( word *word, vector<struct word *> *wl ) {
	int pos = in_vec( word, wl );
	if ( pos == -1 ) {
		std::cout << "Word not in list!\n";
		return;
	}
	std::cout << "Word in list, finding solution...\n";

	int					   done = 0;
	vector<struct word *> *step = new vector<struct word *>;
	for ( int i = 0; i < wl->size(); ++i ) {
		if ( one_diff( "POOP", ( *wl )[i]->word ) ) {
			( *wl )[i]->dist = 1;
			step->push_back( ( *wl )[i] );
			done++;
		}
	}
	for ( int i = 1; done < wl->size(); ++i ) {
		vector<struct word *> *s2 = new vector<struct word *>;
		for ( int j = 0; j < step->size(); ++j )
			for ( int k = 0; k < wl->size(); ++k ) {
				if ( one_diff( ( *step )[j]->word, ( *wl )[k]->word ) &&
					 ( ( *wl )[k]->dist > i || ( *wl )[k]->dist == -1 ) ) {
					if ( ( *wl )[k]->dist == -1 ) ( *wl )[k]->dist = i + 1;
					( *wl )[k]->upstream->push_back( step->at( j ) );
					if ( in_vec( ( *wl )[k], s2 ) == -1 ) {
						s2->push_back( ( *wl )[k] );
						done++;
					}
				}
			}
		delete step;
		step = s2;
	}
	std::cout << "Word " + word->word + " has an optimal solution of "
			  << ( *wl )[pos]->dist << "\n";
	struct word *s = ( *wl )[pos];
	std::cout << "Found " << calc_solution_count( s ) << " optimal solves\n";
	while ( true ) {
		std::cout << s->word + " -> ";
		if ( s->upstream->size() == 0 ) break;
		s = ( *s->upstream )[0];
	}
	std::cout << "POOP\n";
}

int main( int argc, char **argv ) {
	if ( argc <= 1 ) {
		std::cout << "Not enough arguments!\n";
		return 0;
	}
	vector<word *> *wordlist = new vector<word *>;
	get_poomap( "poople_words.txt", wordlist );
	word *arg = new word{ .word = argv[1] };
	for ( auto &c : arg->word ) c = toupper( c );
	std::cout << "word: " << arg->word << std::endl;

	poosolve( arg, wordlist );

	return 0;
}
