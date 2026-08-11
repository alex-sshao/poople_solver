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

int get_poomap( std::string filename, vector<word *> *wl ) {
	std::ifstream words( filename );
	std::string	  buff;
	int			  poop_index = 0;
	for ( int i = 0; std::getline( words, buff ); ++i ) {
		word *w = new word;
		w->word += buff;
		w->dist = -1;
		if ( buff.compare( "POOP" ) == 0 ) {
			poop_index = i;
			w->dist	   = 0;
		}
		w->upstream = new vector<word *>;
		wl->push_back( w );
	}
	words.close();
	return poop_index;
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

void ps_help( word *w, vector<std::string> *s ) {
	if ( w->upstream->size() == 0 ) {
		std::cout << "  ";
		for ( auto i : *s ) std::cout << i << " » ";
		std::cout << "POOP \n";
	}
	s->push_back( w->word );
	for ( int i = 0; i < w->upstream->size(); ++i ) {
		ps_help( w->upstream->at( i ), s );
		s->pop_back();
	}
}

void print_solves( word *w ) {
	vector<std::string> *str = new vector<std::string>;
	ps_help( w, str );
}

void poosolve( word *word, vector<struct word *> *wl, int pind ) {
	int pos = in_vec( word, wl );
	if ( pos == -1 ) {
		std::cout << "Word not in list!\n";
		return;
	}
	int					   done = 1;
	vector<struct word *> *step = new vector<struct word *>;
	step->push_back( ( *wl ).at( pind ) );
	for ( int i = 0; done < wl->size(); ++i ) {
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
	struct word *s			 = ( *wl )[pos];
	int			 solve_count = calc_solution_count( s );
	std::cout << "\"" + word->word + "\" has an optimal solution of "
			  << ( *wl )[pos]->dist << "\n";
	std::cout << "Found " << solve_count << " optimal solves\n";
	print_solves( s );
}

int main( int argc, char **argv ) {
	if ( argc <= 1 ) {
		std::cout << "Not enough arguments!\n";
		return 0;
	}
	vector<word *> *wordlist = new vector<word *>;
	int				ind		 = get_poomap( "poople_words.txt", wordlist );
	word		   *arg		 = new word{ .word = argv[1] };
	for ( auto &c : arg->word ) c = toupper( c );
	poosolve( arg, wordlist, ind );
	return 0;
}
