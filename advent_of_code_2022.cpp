// advent_of_code_2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <array>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <map>
#include<stdlib.h> 
#include <chrono>
#include <thread>
#include <random>
#include <ctype.h>
#include <cmath>
#include <unordered_set>
#include <future>

template<typename T>
std::vector<T> read_vector_from_file( std::string file_name )
{
	std::ifstream infile( file_name );
	std::vector<T> vector;
	T read_in;
	while ( infile >> read_in )
	{
		vector.push_back( read_in );
	}

	return vector;
}

int day_one()
{
	std::string file_name{ "day_one_real.txt" };
	std::ifstream infile( file_name );
	int current = 0;

	std::vector<int> elves;

	std::string read_in;
	while ( std::getline( infile, read_in ) )
	{
		if ( read_in.empty() )
		{
			elves.push_back( current );
			current = 0;
			continue;
		}
		current += std::stoi( read_in );
	}

	std::sort( elves.rbegin(), elves.rend() );

	// day one part one is just the first element
	return elves.at(0) + elves.at(1) + elves.at(2);
}

int day_two_part_one()
{
	std::string file_name{ "day_two_test.txt" };
	std::ifstream infile( file_name );
	int current_score = 0;

	std::string rockpaperscissors = "ABC";

	std::string read_in;
	while ( std::getline( infile, read_in ) )
	{
		int round_score{0};

		if (read_in.back() == 'X') 
		{
			round_score += 1;
		}
		else if (read_in.back() == 'Y') 
		{
			round_score += 2;
		}
		else if (read_in.back() == 'Z') 
		{
			round_score += 3;
		}
		else
		{
			return -1;
		}

		int draw_index = round_score -1;

		if ( read_in.front() == rockpaperscissors.at( draw_index ) )
		{
			round_score += 3;
		}
		else if ( read_in.front() != rockpaperscissors.at( (draw_index + 1) % 3 ) )
		{
			round_score += 6;
		}

		current_score+=round_score;
	}

	return current_score;
}

int day_two_part_two()
{
	std::string file_name{ "day_two_real.txt" };
	std::ifstream infile( file_name );
	int current_score = 0;

	std::string rockpaperscissors = "ABC";

	std::string read_in;
	while ( std::getline( infile, read_in ) )
	{
		int round_score{ 0 };

		if ( read_in.back() == 'X' )
		{
			round_score += 0;
		}
		else if ( read_in.back() == 'Y' )
		{
			round_score += 1;
		}
		else if ( read_in.back() == 'Z' )
		{
			round_score += 2;
		}
		else
		{
			return -1;
		}

		int choice_index = 0;

		while ( rockpaperscissors.at( choice_index ) != read_in.front() )
		{
			choice_index++;
		}	
			
		choice_index += 2 + round_score;

		current_score += 1;
		current_score += choice_index % 3;
		current_score += round_score * 3;
	}

	return current_score;
}

int day_three_part_one( bool real )
{
	std::string file_name{ "day_three" };
	if ( real )
	{
		file_name += "_real.txt";
	}
	else
	{
		file_name += "_test.txt";
	}

	std::ifstream infile( file_name );
	int current_score = 0;
	std::string read_in;
	while ( std::getline( infile, read_in ) )
	{
		const auto halfway = read_in.size() / 2;
		bool found = false;
		for ( auto i = 0; i < halfway && !found; i++ )
		{
			for ( auto j = halfway; j < read_in.size() && !found; j++ )
			{
				if ( read_in.at( i ) == read_in.at( j ) )
				{
					auto line_score = 1 + read_in.at( i ) - 'a';
					if ( line_score < 1 )
					{
						line_score += 58;
					}

					std::cout << "line:" << line_score << std::endl;
					current_score += line_score;
					found = true;
				}
			}
		}
	}

	return current_score;
}

int day_three_part_two( bool real )
{
	std::string file_name{ "day_three" };
	if ( real )
	{
		file_name += "_real.txt";
	}
	else
	{
		file_name += "_test.txt";
	}

	std::ifstream infile( file_name );
	int current_score = 0;
	std::string line_one;
	while ( std::getline( infile, line_one ) )
	{
		std::string line_two, line_three;
		std::getline( infile, line_two );
		std::getline( infile, line_three );

		bool found = false;
		for ( auto i = 0; i < line_one.size() && !found; i++ )
		{
			for ( auto j = 0; j < line_two.size() && !found; j++ )
			{
				if ( line_one.at( i ) == line_two.at( j ) )
				{
					for ( auto k = 0; k < line_three.size() && !found; k++ )
					{
						if ( line_two.at( j ) == line_three.at( k ) )
						{
							auto line_score = 1 + line_one.at( i ) - 'a';
							if ( line_score < 1 )
							{
								// for capital letters ugh
								line_score += 58;
							}

							std::cout << "line:" << line_score << std::endl;
							current_score += line_score;
							found = true;
						}
					}
				}
			}
		}
	}

	return current_score;
}

int day_four( bool real )
{
	std::string file_name{ "day_four" };
	if ( real )
	{
		file_name += "_real.txt";
	}
	else
	{
		file_name += "_test.txt";
	}

	std::ifstream infile( file_name );

	int current_score = 0;
	int lower_a, upper_a, lower_b, upper_b;
	while ( infile >> lower_a )
	{
		char dummy;
		infile >> dummy;
		infile >> upper_a;
		infile >> dummy;
		infile >> lower_b;
		infile >> dummy;
		infile >> upper_b;

		// part one just has different checks here for what the overlap is
		if ( lower_a <= lower_b && upper_a >= lower_b )
		{
			current_score++;
		}
		else if ( lower_a <= upper_b && upper_a >= upper_b )
		{
			current_score++;
		}
		else if ( lower_a >= lower_b && upper_a <= upper_b )
		{
			current_score++;
		}
	}

	return current_score;
}

std::string day_five( bool real )
{
	std::string file_name{ "day_five" };
	if ( real )
	{
		file_name += "_real.txt";
	}
	else
	{
		file_name += "_test.txt";
	}

	std::ifstream infile( file_name );
	std::string line;
	std::vector<std::string> towers;
	towers.resize( 10 );

	bool entries = true;

	while ( std::getline( infile, line ) )
	{
		if ( line.length() > 2 && line.at(1) == '1' )
		{
			entries = false;
		}
		else if ( entries )
		{
			for ( auto index = 0; (index * 4) + 1 < line.length(); index++ )
			{
				if ( line.at( (index*4) + 1 ) != ' ' )
				{
					towers.at( index ).insert( towers.at( index ).begin(), line.at((index * 4) + 1 ));
				}
			}
		}
		else
		{
			std::string word;
			std::stringstream ss1( line );

			while ( std::getline( ss1, word, ' ' ) )
			{
				if ( std::isdigit( word.front() ) )
				{
					const int times = std::stoi( word );
					
					while ( std::getline( ss1, word, ' ' ) )
					{
						if ( std::isdigit( word.front() ) )
						{
							const int from = std::stoi( word ) - 1;
							while ( std::getline( ss1, word, ' ' ) )
							{
								if ( std::isdigit( word.front() ) )
								{
									const int to = std::stoi( word ) - 1;

									// this line is for part two, moving several letters at once
									towers.at( to ) += towers.at( from ).substr( towers.at(from).length() - times, times );;

									for ( int i = 0; i < times; i++ )
									{
										// this commented out line is how part one worked, one letter at a time
										//towers.at( to ) += towers.at( from ).back();
										towers.at( from ).pop_back();
									}
								}
							}
						}
					}
					
				}
			}
		}
	}

	std::string output_string;

	for ( auto string : towers )
	{ 
		if ( !string.empty() )
		{
			output_string += string.back();
		}
	}

	return output_string;
}

// rather have a function than copy and paste this every time...
std::ifstream get_file( std::string day, bool real )
{
	std::string file_name{ "day_" };

	file_name += day;
	if ( real )
	{
		file_name += "_real.txt";
	}
	else
	{
		file_name += "_test.txt";
	}
	return std::ifstream( file_name );
}

int day_six( bool real )
{
	std::ifstream file = get_file( "six", real );

	std::string line;

	const auto lambda_for_finding_marker = []( std::string& line ) 
	{
		// different constexpr for part one and two
		//constexpr int MARKER_SIZE = 4;
		constexpr int MARKER_SIZE = 14;
		for ( int i = MARKER_SIZE; i < line.length(); i++ )
		{
			auto marker_string = line.substr( i - MARKER_SIZE, MARKER_SIZE );
			std::sort( marker_string.begin(), marker_string.end() );
			auto last = std::unique( marker_string.begin(), marker_string.end() );
			marker_string.erase( last, marker_string.end() );

			if ( marker_string.length() == MARKER_SIZE )
			{
				return i;
			}
		}
		return -1;
	};

	while ( std::getline( file, line ) )
	{
		std::cout << lambda_for_finding_marker( line ) << std::endl;
	}
	return 100;
}

int day_seven( bool for_real )
{
	std::ifstream file = get_file( "seven", for_real );

	std::vector<std::string> file_path;
	std::map<std::string, std::pair<int, std::vector<std::string>>> files_in_directories;

	std::string line;
	while ( std::getline( file, line ) )
	{
		std::string word;
		std::stringstream ss( line );
		std::getline( ss, word, ' ' );

		if ( word == "$" )
		{
			// lets get the instruction
			while ( std::getline( ss, word, ' ' ) )
			{
				if ( word == "cd" )
				{
					std::getline( ss, word, ' ' );

					if ( word == ".." )
					{
						file_path.pop_back();
					}
					else if ( word == "/" )
					{
						file_path.clear();
						file_path.push_back( word );
					}
					else
					{
						file_path.push_back(word);
					}
				}
				else
				{
					// doesn't really matter, we'll look at the contents of the list next
				}
			}
		}
		else
		{
			// not an instruction so it must be a list entry of an object in the current_dir
			const bool is_file{ word != "dir"};
			if ( is_file )
			{
				std::string unique_dir_name;
				for ( auto directory : file_path )
				{
					unique_dir_name += "/" + directory;
					files_in_directories[unique_dir_name].first += stoi( word );
				}
			}
			else
			{
				// don't care really, it's a directory and we'll see what's in there later
			}
		}
	}

	int part_one_size{0};
	constexpr int TOTAL_CAPACITY	= 70000000;
	constexpr int SPACE_NEEDED		= 30000000;
	int part_two_size{ TOTAL_CAPACITY };
	int space_to_clear{TOTAL_CAPACITY};

	for ( auto it = files_in_directories.begin(); it != files_in_directories.end(); it++ )
	{
		// this is the part-one calculation:
		if ( it->second.first <= 100000 )
		{
			part_one_size += it->second.first;
		}

		if ( it->first == "//" )
		{
			space_to_clear = it->second.first + SPACE_NEEDED - TOTAL_CAPACITY;
		}

		if ( it->second.first >= space_to_clear && it->second.first < part_two_size )
		{
			part_two_size = it->second.first;
		}
	}

	return part_two_size;
}

int day_eight( bool real )
{
	std::ifstream file = get_file( "eight", real );

	std::vector<std::vector<int>> trees;
	std::vector<std::vector<int>> trees_T;
	int i = 0;
	std::string line;
	while ( std::getline( file, line ) )
	{
		trees.push_back( std::vector<int>() );
		for ( auto character : line )
		{
			trees.at(i).push_back(character - '0');
		}
		i++;
	}

	int can_see = 0;

	auto tree_score = [trees]( int x, int y )
	{
		auto h = trees.at( x ).at( y );

		int local_score=0;
		int score=1;

		for ( int i = x+1; i<trees.size(); i++ )
		{
			local_score++;
			if ( trees.at( i ).at( y ) >= h )
			{
				break;
			}
		}

		score *= local_score;
		local_score = 0;
		if ( score == 0 )
		{
			return 0;
		}

		for ( int i = x; i-->0; )
		{
			local_score++;
			if ( trees.at( i ).at( y ) >= h )
			{
				break;
			}	
		}

		score *= local_score;
		local_score = 0; 
		if ( score == 0 )
		{
			return 0;
		}

		for ( int i = y + 1; i < trees.size(); i++ )
		{
			local_score++;
			if ( trees.at( x ).at( i ) >= h )
			{
				break;
			}
		}

		score *= local_score; 
		local_score = 0;
		if ( score == 0 )
		{
			return 0;
		}

		for ( int i = y; i-- > 0; )
		{
			local_score++;
			if ( trees.at( x ).at( i ) >= h )
			{
				break;
			}
		}

		score *= local_score;
		local_score = 0;
		if ( score == 0 )
		{
			return 0;
		}

		return score;
	};

	auto can_see_tree = [trees]( int x, int y )
	{
		auto h = trees.at( x ).at( y );

		for ( int i = 0; i < trees.size(); i++ )
		{
			if ( i == x )
			{
				return true;
			}
			if ( trees.at( i ).at( y ) >= h )
			{
				break;
			}
		}

		for ( int i = trees.size(); i-- > 0; )
		{
			if ( i == x )
			{
				return true;
			}
			if ( trees.at( i ).at( y ) >= h )
			{
				break;
			}
		}

		for ( int i = 0; i < trees.at( x ).size(); i++ )
		{
			if ( i == y )
			{
				return true;
			}
			if ( trees.at( x ).at( i ) >= h )
			{
				break;
			}
		}

		for ( int i = trees.at( x ).size(); i-- > 0; )
		{
			if ( i == y )
			{
				return true;
			}
			if ( trees.at( x ).at( i ) >= h )
			{
				break;
			}
		}

		return false;
	};

	int best_score = 0;
	for ( int i = 0; i < trees.size(); i++ )
	{
		for ( int j = 0; j < trees.at(i).size(); j++ )
		{
			int this_score = tree_score( i, j );
			if ( this_score > best_score )
			{
				best_score = this_score;
			}	
		}
	}

	return best_score;
}

int day_nine( bool real )
{
	std::ifstream file = get_file( "nine", real );

	std::pair<int, int> head{ 0,0 };
	auto tail = head;

	std::vector<std::pair<int, int>> long_rope; 
	for ( int i = 0; i < 10; i++ )
	{
		long_rope.emplace_back( 0, 0 );
	}

	std::vector<std::pair<int, int>> part_one_history;
	part_one_history.emplace_back( tail );

	std::vector<std::pair<int, int>> part_two_history;
	part_two_history.emplace_back( long_rope.back() );

	auto update_tail_lambda = []( std::pair<int, int>& head, std::pair<int, int>& tail )
	{
		std::pair<int, int> distance{head.first - tail.first, head.second - tail.second};

		if ( abs( distance.first ) > 0 && abs( distance.second ) > 0 && abs( distance.first ) + abs( distance.second ) > 2 )
		{
			if ( distance.first > 0 )
			{
				tail.first++;
			}
			if ( distance.first < 0 )
			{
				tail.first--;
			}
			if ( distance.second > 0 )
			{
				tail.second++;
			}
			if ( distance.second < 0 )
			{
				tail.second--;
			}
		}
		else
		{
			if ( distance.first > 1 )
			{
				tail.first++;
			}
			if ( distance.first < -1 )
			{
				tail.first--;
			}
			if ( distance.second > 1 )
			{
				tail.second++;
			}
			if ( distance.second < -1 )
			{
				tail.second--;
			}
		}
	};

	std::string direct;
	while ( std::getline( file, direct ) )
	{
		std::string times = direct.substr( 2, direct.length() - 2);

		int times_number = stoi( times );
		std::pair<int, int> vector{ 0,0 };

		if ( direct.front() == 'U' )
		{
			vector.first++;
		} 
		else if ( direct.front() == 'D' )
		{
			vector.first--;
		} 
		else if ( direct.front() == 'R' )
		{
			vector.second++;
		} 
		else if ( direct.front() == 'L' )
		{
			vector.second--;
		}

		for ( int i = 0; i < times_number; i++ )
		{
			head.first += vector.first;
			head.second += vector.second;
			update_tail_lambda( head, tail );
			part_one_history.emplace_back( tail );

			long_rope.front().first += vector.first;
			long_rope.front().second += vector.second;

			for ( int i = 1; i < 10; i++ )
			{
				update_tail_lambda( long_rope[i-1], long_rope[i] );
			}
			part_two_history.emplace_back( long_rope.back() );
		}
	}

	std::sort( part_two_history.begin(), part_two_history.end(), []( std::pair<int, int> a, std::pair<int, int> b ) { return a.first == b.first ? a.second > b.second : a.first > b.first; } );
	auto last = std::unique( part_two_history.begin(), part_two_history.end() );
	part_two_history.erase( last, part_two_history.end() );

	return part_two_history.size();
}

int day_ten( bool real )
{
	std::ifstream file = get_file( "ten", real );

	int cycle = 0;
	int reg = 1;
	int score = 0;
	std::string word;

	std::string screen;

	auto cycle_lambda = [&]() 
	{
		cycle++;
		if ( cycle % 40 == 20 )
		{
			score += cycle * reg;
			//std::cout << cycle<< ", " << reg<< " : " << cycle * reg << std::endl;
		}
		if ( abs( 1+((cycle-1)%40) - (reg+1) ) < 2 )
		{
			screen.push_back( '#' );
		}
		else
		{
			screen.push_back( ' ');
		}
	};

	while(std::getline(file, word ) )
	{
		cycle_lambda();
		if ( word == "noop" )
		{
			// do nothing
		}
		if ( word.substr(0, 4) == "addx" )
		{
			cycle_lambda();
			int val = stoi( word.substr( 5, 100 ) );
			reg += val;
			//std::cout << cycle << " : " << reg << ", "<<val << std::endl;

		}
	}

	for ( auto i = 1; i <= screen.length(); i++ )
	{
		std::cout << screen[i-1];
		if ( i % 40 == 0 )
		{
			std::cout << std::endl;
		}
	}

	return score;
}

struct MONKEY
{
	long long inspections = 0;
	std::vector<unsigned long long> items_held;
	int test_div = 1;
	int true_target = 0;
	int false_target = 0;
	int sq_op = 0;
	int lin_op = 1;
	int con_op = 0;
};

long long day_eleven( bool real )
{
	std::ifstream file = get_file( "eleven", real );

	std::string line;

	std::vector<MONKEY> monkeys;

	unsigned long long divisor = 1;

	while ( std::getline( file, line ) )
	{
		if ( !line.empty() )
		{
			if ( line.front() == 'M' )
			{
				monkeys.emplace_back( MONKEY() );
			}
			else
			{
				std::string word;
				std::stringstream ss1( line );
				std::vector<std::string> words;

				while ( std::getline( ss1, word, ' ' ) )
				{
					if (!word.empty())
						words.push_back( word );
				}

				if ( !words.empty() )
				{
					if ( words.front() == "Starting" )
					{
						for ( auto item : words )
						{
							if ( item.length() > 0 )
							{
								if ( item.back() == ',' )
								{
									item.pop_back();
								}
								if ( std::isdigit( item.front() ) )
								{
									monkeys.back().items_held.push_back( stoi( item ) );
								}
							}
						}
					}
					else if ( words.front() == "Operation:" )
					{
						bool sq{false};
						bool lin{ false };
						bool con{ false };
						for ( auto item : words )
						{
							if ( item == "+" )
							{
								con = true;
							}
							if ( item == "*" )
							{
								lin = true;
							}

							if ( lin && item == "old" )
							{
								monkeys.back().sq_op = 1;
							}
							else if ( std::isdigit( item.front() ) )
							{
								if ( lin )
								{
									monkeys.back().lin_op = stoi( item );
								}
								else if ( con )
								{
									monkeys.back().con_op = stoi( item );
								}
							}
						}
					}
					else if ( words.front() == "Test:" )
					{
						monkeys.back().test_div = stoi( words.back() );
						divisor *= monkeys.back().test_div;
					}
					else if ( words.front() == "If" && words.at(1) == "true:" )
					{
						monkeys.back().true_target = stoi( words.back() );
					}
					else if ( words.front() == "If" && words.at( 1 ) == "false:" )
					{
						monkeys.back().false_target = stoi( words.back() );
					}
				}
			}
		}
	}

//	constexpr int ROUNDS = 20;
	constexpr int ROUNDS = 10000;
	int divided{ 0 }, total{ 0 };

	for ( int i = 0; i < ROUNDS; i++ )
	{
		for ( auto& monkey : monkeys )
		{
			// the monkey inspects the items
			for ( auto& item : monkey.items_held )
			{
				monkey.inspections++;
				total++;

				const auto old_item = item;

				if ( monkey.sq_op )
				{
					item *= item;
				}
				else
				{
					item = monkey.con_op + (item * monkey.lin_op);
				}

				item = item % divisor;
				if ( !item )
				{
					item = divisor;
				}

				// no more boredom in part two
				//item /= 3; // gets bored

				// throw it!
				if ( item % monkey.test_div == 0 )
				{
					monkeys.at( monkey.true_target ).items_held.push_back( item );
					divided++;
				}
				else
				{
					monkeys.at( monkey.false_target ).items_held.push_back( item );
				}
			}

			monkey.items_held.clear();
		}
	}

	std::cout << total << std::endl;
	std::cout << (float)divided / total << std::endl;

	std::sort( monkeys.begin(), monkeys.end(), []( const MONKEY& a, const MONKEY& b ) { return a.inspections > b.inspections; } );

	return monkeys.at( 0 ).inspections * monkeys.at( 1 ).inspections;
}

struct DJI
{
	int height = 0;
	int distance = std::numeric_limits<int>().max();
	bool end = false;
	std::pair<int, int> location;
};

int day_twelve( bool real )
{
	std::ifstream file = get_file( "twelve", real );

	std::string line;

	std::vector<DJI> unvisited;

	int	row = 0;

	while ( std::getline( file, line ) )
	{
		int column = 0;
		for ( auto place : line )
		{
			DJI marker;
			marker.height = place - 'a';

			// for part one only the S is valid to start & the a is uninteresting
			if ( place == 'S' || place == 'a' )
			{
				marker.height = 0;
				// for part one I set the distance of the start to 0 and the end flag on the end but it doesn't really matter
				marker.end = true;
			}
			if ( place == 'E' )
			{
				marker.height = 'z' - 'a';
				marker.distance = 0;
			}

			marker.location.first = column;
			marker.location.second = row;

			unvisited.emplace_back( marker );

			column++;
		}

		row++;
	}

	int shortest_distance = -1;

	while ( !unvisited.empty() )
	{
		std::sort( unvisited.begin(), unvisited.end(), []( DJI& a, DJI& b ) { return a.distance > b.distance; });

		std::vector<std::pair<int, int>> possible_steps;

		auto location = unvisited.back().location;

		possible_steps.emplace_back( location.first, location.second + 1 );
		possible_steps.emplace_back( location.first, location.second - 1 );
		possible_steps.emplace_back( location.first + 1, location.second );
		possible_steps.emplace_back( location.first - 1, location.second );

		for ( auto step : possible_steps )
		{
			for ( auto& loc : unvisited )
			{
				// for part two we're searching backwards so only need to check that the height isn't much lower than current height
				if ( loc.location == step && loc.height >= unvisited.back().height -1 )
				{
					loc.distance = unvisited.back().distance + 1;
				}
			}
		}

		if ( unvisited.back().end )
		{
			if ( shortest_distance == -1 || shortest_distance > unvisited.back().distance )
			{
				return unvisited.back().distance;
			}
		}
		unvisited.pop_back();
	}

	return shortest_distance;
}

struct list_item
{
	std::vector<list_item> list;
	int integer = -1;
	bool is_decoder = false;
};

list_item get_list_item_from_string( std::string string )
{
	list_item item;

	if ( string.empty() )
	{
		return item;
	}

	if ( string.front() != '[' )
	{
		item.integer = std::stoi( string );
		return item;
	}

	// divide up by commas
	std::vector<std::string> words;
	auto depth = 0;
	std::string word;
	for ( auto character : string )
	{
		if ( character == ']' )
		{
			depth--;
		}

		if ( depth == 1 )
		{
			if ( character == ',' )
			{
				words.push_back( word );
				word.clear();
			}
			else
			{
				word.push_back( character );
			}
		}
		else if (depth > 1)
		{
			word.push_back( character );
		}

		if ( character == '[' )
		{
			depth++;
		}
	}
	words.push_back( word );

	for ( auto element : words )
	{
		item.list.emplace_back( get_list_item_from_string( element ) );
	}

	return item;
}

enum class trool
{
	correct,
	incorrect,
	maybe
};

trool is_correct_order( const list_item& a, const list_item& b )
{
	if ( !a.list.empty() && !b.list.empty() )
	{
		trool backup_result = trool::maybe;
		if ( a.list.size() < b.list.size() )
		{
			backup_result = trool::correct;
		}
		else if ( a.list.size() > b.list.size() )
		{
			backup_result = trool::incorrect;
		}

		// both lists!
		for ( int i = 0; i < a.list.size() && i < b.list.size(); i++ )
		{
			trool inner_result = is_correct_order( a.list[i], b.list[i] );
			if ( inner_result != trool::maybe )
			{
				return inner_result;
			}
		}

		return backup_result;
	}
	else if ( !a.list.empty() )
	{
		list_item new_item;
		new_item.list.emplace_back( b );
		return is_correct_order( a, new_item );
	}
	else if ( !b.list.empty() )
	{
		list_item new_item;
		new_item.list.emplace_back( a );
		return is_correct_order( new_item, b );
	}
	else
	{
		if ( a.integer < b.integer )
		{
			return trool::correct;
		}
		if ( a.integer > b.integer )
		{
			return trool::incorrect;
		}
	}

	return trool::maybe;
}

int day_thirteen( bool real )
{
	std::ifstream file = get_file( "thirteen", real );

	std::string line;
	std::vector<std::pair<list_item, list_item>> input;
	std::vector<list_item> part_two_list;

	while ( std::getline( file, line ) )
	{
		list_item a = get_list_item_from_string( line );
		std::getline( file, line );
		list_item b = get_list_item_from_string( line );

		input.emplace_back( a, b );
		part_two_list.emplace_back( a );
		part_two_list.emplace_back( b );

		std::getline( file, line );
	}

	// read them in, now compare the pairs!
	int score = 0;
	for ( int i = 0; i < input.size(); i++ )
	{
		list_item a = input[i].first;
		list_item b = input[i].second;
		if ( is_correct_order( a, b ) == trool::correct )
		{
			score += 1 + i;
		}
	}

	// extra items for part two 
	list_item decoder = get_list_item_from_string( std::string( "[[2]]" ) );
	decoder.is_decoder = true;
	part_two_list.push_back( decoder );
	decoder = get_list_item_from_string( std::string( "[[6]]" ) );
	decoder.is_decoder = true;
	part_two_list.push_back( decoder );

	std::sort( part_two_list.begin(), part_two_list.end(), []( list_item& a, list_item& b ) { return is_correct_order( a, b ) == trool::correct; } );

	int part_two_score = 1;
	for ( int i = 0; i < part_two_list.size(); i++ )
	{
		if ( part_two_list[i].is_decoder )
		{
			part_two_score *= (i+1);
		}
	}

	return part_two_score;
}

int day_fourteen( bool real )
{
	std::ifstream file = get_file( "fourteen", real );

	std::string line;

	std::vector< std::string > map;
	map.resize( 1000 );
	for ( auto& row : map )
	{
		row.resize( 1000 );
	}
	
	int max_y = 0;

	while ( std::getline( file, line ) )
	{
		std::string word;
		std::stringstream ss1( line );
		std::vector<std::string> words;
		int last_x = -1, last_y = -1;

		while ( std::getline( ss1, word, ' ' ) )
		{
			if ( word.front() == '-' )
			{
				continue;
			}
			else
			{
				std::stringstream ss2( word );
				std::string coord;
				std::getline( ss2, coord, ',' );
				int x = std::stoi( coord );
				std::getline( ss2, coord, ',' );
				int y = std::stoi( coord );

				if ( last_x != -1 )
				{
					for ( int i = std::min( last_y, y ); i <= std::max( last_y, y ); i++ )
					{
						for ( int j = std::min( last_x, x ); j <= std::max( last_x, x ); j++ )
						{
							map[i][j] = '#';
						}
					}
				}

				last_x = x;
				last_y = y;

				if ( y > max_y )
				{
					max_y = y;
				}
			}
		}
	}

	// actually only this loop is different between the two parts!
	for ( auto& character : map[max_y + 2] )
	{
		character = '#';
	}

	int number_of_sand = 0;

	auto sand_falling = [&map]( int&x, int&y )
	{
		if ( map[y + 1][x] == '\0' )
		{
			y++;
		}
		else if ( map[y + 1][x-1] == '\0' )
		{
			y++;
			x--;
		}
		else if ( map[y + 1][x+1] == '\0' )
		{
			y++;
			x++;
		}
		else
		{
			// if we've settled then return false!
			map[y][x] = '#';
			return false;
		}

		map[y][x] = '\0';
		return true;
	};

	// start dropping sand into the top at 500,0
	while ( true )
	{
		int sand_x = 500;
		int sand_y = 0;

		while ( true )
		{
			if ( sand_y >= 998 )
			{
				return number_of_sand;
			}
			if ( !sand_falling(sand_x, sand_y) )
			{
				if ( sand_x == 500 && sand_y == 0 )
				{
					return number_of_sand + 1;
				}
				break;
			}
		}

		number_of_sand++;
	}

	return number_of_sand;
}

bool digit( char ch ) {
	return ('0' <= ch && ch <= '9') || ch == '-';
}

std::string remove_non_digits( const std::string& input ) {
	std::string result;
	std::copy_if( input.begin(), input.end(),
				  std::back_inserter( result ),
				  digit );
	return result;
}

long long day_fifteen( bool real )
{
	std::ifstream file = get_file( "fifteen", real );

	const int y_of_interest = real ? 2000000 : 10;

	std::vector<std::pair<std::pair<int, int>, int>> sensors_and_ranges;

	std::vector<std::pair<int, int>> beacons;

	int max_x = 0, min_x = 0;

	std::string line;
	while ( std::getline( file, line ) )
	{
		std::string sensor_string;
		std::stringstream ss1( line );
		std::getline( ss1, sensor_string, ',' );

		int sens_x = std::stoi( remove_non_digits( sensor_string ));

		std::getline( ss1, sensor_string, ':' );

		int sens_y = std::stoi( remove_non_digits( sensor_string ) );

		std::getline( ss1, sensor_string, ',' );

		int beacon_x = std::stoi( remove_non_digits( sensor_string ) );

		std::getline( ss1, sensor_string );

		int beacon_y = std::stoi( remove_non_digits( sensor_string ) );

		int manhattan_dist = abs( sens_x - beacon_x ) + abs( sens_y - beacon_y );

		sensors_and_ranges.emplace_back( std::pair<int, int>( sens_x, sens_y ), manhattan_dist );

		if ( max_x < sens_x + manhattan_dist )
		{
			max_x = manhattan_dist + sens_x;
		}
		if ( min_x > sens_x - manhattan_dist )
		{
			min_x = sens_x - manhattan_dist;
		}

		beacons.emplace_back( beacon_x, beacon_y );
	}

	int blocked_spaces = 0;
	// look along the y of interest and see how many spots are impossible (part one)
// 	for ( int i = min_x; i <= max_x; i++ )
// 	{
// 		bool already_beacon = false;
// 		for ( auto beac : beacons )
// 		{
// 			if ( beac.first == i && beac.second == y_of_interest )
// 			{
// 				already_beacon = true;
// 				break;
// 			}
// 		}
// 
// 		if ( already_beacon )
// 		{
// 			continue;
// 		}
// 
// 		for ( auto sens : sensors_and_ranges )
// 		{
// 			int manhat_dist = abs( sens.first.first - i ) + abs( sens.first.second - y_of_interest );
// 			if ( manhat_dist <= sens.second )
// 			{
// 				//std::cout << i << std::endl;
// 				blocked_spaces++;
// 				break;
// 			}
// 		}
// 	}

	auto get_points_on_sensor_edge = []( const std::pair<std::pair<int, int>, int>& sensor, int max_x, int max_y )
	{
		std::vector<std::pair<int, int>> list;

		int dist = sensor.second + 1;

		int x=sensor.first.first, y= sensor.first.second + dist;

		while ( true )
		{
			if ( x >= 0 && x <= max_x && y >= 0 && y <= max_y )
			{
				list.emplace_back( x, y );
			}

			if ( x >= sensor.first.first && y > sensor.first.second )
			{
				x++;
				y--;
			}
			else if( x > sensor.first.first && y <= sensor.first.second )
			{
				x--;
				y--;
			}
			else if( x <= sensor.first.first && y < sensor.first.second )
			{
				x--;
				y++;
			}
			else if( x < sensor.first.first && y >= sensor.first.second )
			{
				x++;
				y++;

				if ( x == sensor.first.first )
				{
					break;
				}
			}
		}

		return list;
	};

	// to find the possible location we only need to check along the edges of the sensors ranges
	for ( auto sens : sensors_and_ranges )
	{
		auto list = get_points_on_sensor_edge( sens, y_of_interest * 2, y_of_interest * 2 );

		for ( auto point : list )
		{
			bool already_beacon = false;
			for ( auto beac : beacons )
			{
				if ( beac == point )
				{
					already_beacon = true;
					break;
				}
			}

			if ( already_beacon )
			{
				continue;
			}

			bool bad_point = false;
			for ( auto other_sens : sensors_and_ranges )
			{
				if (other_sens == sens)
				{
					continue;
				}
				else
				{
					int manhat_dist = abs( other_sens.first.first - point.first ) + abs( other_sens.first.second - point.second );
					if ( manhat_dist <= other_sens.second )
					{
						bad_point = true;
					}
				}

				if ( bad_point )
				{
					break;
				}
			}

			if ( !bad_point )
			{
				long long ans = (long long)((long long)(((long long)4000000 * (long long)point.first)) + (long long)point.second);
				std::cout << ans << std::endl;
			}
		}
	}
	return 0;
}

std::mutex high_score_mutex;
int highest_score_seen = 0;

struct GAME_STATE
{
	std::map<std::string, std::pair<int, std::vector<std::string>>> map_state;
	int time_remaining;
	int extra_time_remaining;
	std::string current_location;
	std::string other_location;
	std::vector<std::string> banned_locations;
	std::vector<std::string> visited_locations;
	int current_score;
	std::vector<int> sorted_rates;
	float goodness = 0;
	bool move_first = true;
};

int best_score_search( GAME_STATE state )
{
	if ( state.time_remaining == 0 && state.extra_time_remaining == 0 )
	{
		return state.current_score;
	}

	std::string loc = state.current_location;
	state.current_location = state.other_location;
	state.other_location = loc;

	int time = state.time_remaining;
	state.time_remaining = state.extra_time_remaining;
	state.extra_time_remaining = time;
	state.move_first = !state.move_first;

	state.time_remaining--;
	auto highest_score_possible = state.current_score;
	auto dummy_time_remaining = state.time_remaining;
	auto dummy_extra_time_remaining = state.extra_time_remaining;
	for ( int i = state.sorted_rates.size(); i-- > 0;)
	{
		if ( dummy_extra_time_remaining > dummy_time_remaining )
		{
			highest_score_possible += state.sorted_rates.at( i ) * dummy_extra_time_remaining;
			dummy_extra_time_remaining -= 2;
		}
		else
		{
			highest_score_possible += state.sorted_rates.at( i ) * dummy_time_remaining;
			dummy_time_remaining -= 2;
		}

		if ( dummy_time_remaining <= 0 && dummy_extra_time_remaining <= 0 )
		{
			break;
		}
	}

	if ( highest_score_possible <= highest_score_seen )
	{
		return state.current_score;
	}

	std::vector<GAME_STATE> possible_states;

	// find the possible moves, loop through them calling the same function!
	if ( state.map_state.at( state.current_location ).first > 0 )
	{
		GAME_STATE new_state = state;
		new_state.current_score += state.map_state.at( state.current_location ).first * state.time_remaining;

		for ( auto i = new_state.sorted_rates.size(); i-- > 0;)
		{
			if ( new_state.sorted_rates.at( i ) == new_state.map_state.at( new_state.current_location ).first )
			{
				new_state.sorted_rates.erase( new_state.sorted_rates.begin() + i );
				break;
			}
		}

		new_state.map_state.at( state.current_location ).first = 0;
		new_state.banned_locations.clear();
		if ( new_state.current_score > highest_score_seen )
		{
			std::thread::id this_id = std::this_thread::get_id();

			high_score_mutex.lock();
			highest_score_seen = new_state.current_score;
			std::cout << "Can score at least: " << highest_score_seen << "-" << highest_score_possible << "(from thread "<<this_id<<")" << std::endl;

			high_score_mutex.unlock();
		}

		new_state.goodness = state.move_first || state.map_state.at( state.current_location ).first < 10 ? 0.5f : 1;

		possible_states.emplace_back( new_state );
	}

	for ( auto valve : state.map_state.at( state.current_location ).second )
	{
		bool banned = false;
		for ( auto loc : state.banned_locations )
		{
			if ( valve == loc )
			{
				banned = true;
			}
		}

		if ( banned || state.map_state.at( valve ).first == 0 && state.map_state.at( valve ).second.size() == 1 )
		{
			continue;
		}

		bool visited = false;
		for ( auto loc : state.visited_locations )
		{
			if ( valve == loc )
			{
				visited = true;
			}
		} 

		GAME_STATE new_state = state;
		new_state.current_location = valve;
		new_state.banned_locations.push_back(state.current_location);
		new_state.visited_locations.push_back(state.current_location);
		if ( visited || banned || state.other_location == valve )
		{
			new_state.goodness = 0;
		}
		else
		{
			new_state.goodness = ((float)state.map_state.at( valve ).first / state.sorted_rates.back()) + (float)state.map_state.at( valve ).second.size() / 10.0f;
		}
		possible_states.emplace_back( std::move(new_state) );
	}
	
	int best_score = state.current_score;

	std::sort( possible_states.begin(), possible_states.end(), []( const GAME_STATE& a, const GAME_STATE& b ) { return a.goodness > b.goodness; } );

	if ( state.extra_time_remaining == 26 && state.time_remaining == 25 )
	{
		std::vector<std::future<int>> results;
		for ( auto solution : possible_states )
		{
			results.push_back( std::async( std::launch::async, best_score_search, solution ) );
		}

		while ( !results.empty() )
		{
			for ( int i = results.size(); i-- > 0; )
			{
				if ( results.at( i ).wait_for( std::chrono::seconds( 0 ) ) == std::future_status::ready )
				{
					auto score = results.at( i ).get();
					if ( score > best_score )
					{
						best_score = score;
					}

					results.erase( results.begin() + i );
				}
			}
		}
	}
	else
	{
		for ( auto solution : possible_states )
		{
			auto score = best_score_search( solution );
			if ( score > best_score )
			{
				best_score = score;
			}
		}
	}
	
	return best_score;
}

int day_sixteen( bool real )
{
	highest_score_seen = 0;
	std::ifstream file = get_file( "sixteen", real );

	// we'll have to do a search!
	std::map<std::string, std::pair<int, std::vector<std::string>>> tunnels;
	std::string line;
	int total_flow_rate= 0;
	std::vector<int> all_rates;

	while ( std::getline( file, line ) )
	{
		// Valve AA has flow rate=0; tunnels lead to valves DD, II, BB
		std::string valve_name;
		std::string string;
		std::vector<std::string> linked_valves;
		int flow_rate;
		std::stringstream ss1( line );
		int word_index = 0;

		while ( std::getline( ss1, string, ' ' ) )
		{
			if ( word_index == 1 )
			{
				valve_name = string;
			}
			if ( word_index == 4 )
			{
				flow_rate = std::stoi( remove_non_digits( string ) );
				total_flow_rate += flow_rate;

				all_rates.push_back( flow_rate );
			}
			if ( word_index > 8 )
			{
				if ( string.back() == ',' )
				{
					string.pop_back();
				}

				linked_valves.push_back( string );
			}
			word_index++;
		}

		tunnels.emplace( valve_name, std::pair<int, std::vector<std::string>>( flow_rate, linked_valves ) );
	}

	GAME_STATE starting_position;
	starting_position.current_location = "AA";
	starting_position.other_location = "AA";
	starting_position.map_state = tunnels;
	starting_position.time_remaining = 26;
	starting_position.extra_time_remaining = 26;
	starting_position.current_score = 0;

	std::sort( all_rates.begin(), all_rates.end() );

	starting_position.sorted_rates = all_rates;

	int score = best_score_search( starting_position );
	return score;
}

unsigned long long day_seventeen( bool real )
{
	std::ifstream file = get_file( "seventeen", real );
	std::string wind;
	std::getline( file, wind );

	constexpr int max_count = 4000;	
	constexpr unsigned long long count_to_find = 1000000000000;

	std::vector<std::string> shaft;
	const std::string empty_layer	= "|       |";
	const std::string full_layer	= "|#######|";
	const std::string floor = "|-------|";
	shaft.push_back( floor );
	std::vector<std::vector<std::string>> shapes;
	std::vector<std::string> shape;

	shape.push_back( "|  #### |" );
	shapes.push_back( shape );
	shape.clear();

	shape.push_back( "|   #   |" );
	shape.push_back( "|  ###  |" );
	shape.push_back( "|   #   |" );
	shapes.push_back( shape );
	shape.clear();

	shape.push_back( "|  ###  |" );
	shape.push_back( "|    #  |" );
	shape.push_back( "|    #  |" );
	shapes.push_back( shape );
	shape.clear();

	shape.push_back( "|  #    |" );
	shape.push_back( "|  #    |" );
	shape.push_back( "|  #    |" );
	shape.push_back( "|  #    |" );
	shapes.push_back( shape );
	shape.clear();

	shape.push_back( "|  ##   |" );
	shape.push_back( "|  ##   |" );
	shapes.push_back( shape );
	shape.clear();

	bool still_falling = false;

	auto lambda_try_to_move = [&]( int x_direction, int y_direction )
	{
		auto copy_shaft = shaft;
		int index_to_start_at = 0;
		bool have_seen_rock = false;

		for ( int i = shaft.size(); i-- > 0;)
		{
			bool contains_falling_rock = false;
			for ( char character : shaft.at( i ) )
			{
				if ( character == '#' )
				{
					contains_falling_rock = true;
				}
			}

			if (!contains_falling_rock && have_seen_rock )
			{
				index_to_start_at = i;
				break;
			}

			have_seen_rock = contains_falling_rock;
		}

		for ( int i = index_to_start_at; i < shaft.size(); i++ )
		{
			for ( int j = x_direction > 0 ? shaft.at(i).size() - 1 : 0; j < shaft.at(i).size() && j >= 0; j-= x_direction ? x_direction : -1 )
			{
				if ( shaft[i][j] == '#' )
				{
					if ( shaft[i+ y_direction][j + x_direction] == ' ' || shaft[i+ y_direction][j + x_direction] == '#' )
					{
						copy_shaft[i + y_direction][j + x_direction] = '#';
						copy_shaft[i][j] = ' ';
					}
					else
					{
						if ( y_direction != 0 )
						{
							still_falling = false;
						}
						return shaft;
					}
				}
			}
		}

		return copy_shaft;
	};

	int direction_index = 0;
	int cumulative_score = 0;
	std::vector<int>score_after_object;
	score_after_object.push_back( 0 );

	for ( int i = 0; i < max_count; i++ )
	{
		//add a shape at the top of the shaft
		shaft.emplace_back( empty_layer );
		shaft.emplace_back( empty_layer );
		shaft.emplace_back( empty_layer );

		for ( auto layer : shapes[i % shapes.size()] )
		{
			shaft.emplace_back( layer );
		}

		still_falling = true;

		while ( still_falling )
		{
			char direction = wind[direction_index];
			direction_index = (direction_index + 1) % wind.size();
			int movement = -1;
			if ( direction == '>' )
			{
				movement = 1;
			}

			shaft = lambda_try_to_move( movement, 0 );
			shaft = lambda_try_to_move( 0, -1 );
		}

		for ( int j = shaft.size(); j-- > 0; )
		{
			if ( shaft.at( j ) == empty_layer )
			{
				shaft.pop_back();
				continue;
			}

			if ( shaft.at( j ) == full_layer )
			{
				shaft = std::vector<std::string>( shaft.begin() + j, shaft.end() );
				cumulative_score += j;
				std::cout << "clear" << std::endl;
				break;
			}

			for ( auto& symbol : shaft[j] )
			{
				if ( symbol == '#' )
				{
					symbol = '@';
				}
			}
		}

		score_after_object.push_back( cumulative_score + shaft.size()-1) ;

		if ( i % 1000 == 0 )
		{
			std::cout << "done " << i << std::endl;
		}
	}

	// we want to find a pattern where f(n) = f(b) * (n-a)/(b-a) + f((n-a)%(b-a))
	for ( int a = 0; a < max_count; a++ )
	{
		for ( int b = a + 1; b < max_count/ 2; b++ )
		{
			int fa = score_after_object[a];
			int fb = score_after_object[b];
			int period = b - a;

			// want to know that it works for all n!
			for ( int n = b + 1; n <= max_count; n++ )
			{
				int fn = score_after_object[n];
				int times_through = std::floor((n-a)/period);
				int remainder = (n - a) % (period);

				int fn_guess = fa + (fb-fa) * times_through + (score_after_object[remainder + a]- fa);
				if ( fn_guess != fn )
				{
					break;
				}

				if ( n == max_count )
				{
					// found a and b, now apply it to N!
					remainder = (count_to_find - a) % (period);
					unsigned long long times_through = std::floor( (count_to_find - a) / period );

					unsigned long long fN = fa + (fb - fa) * times_through + (score_after_object[remainder + a] - fa);
					return fN;
				}
			}
		}
	}

	return -1;
}

struct THREE_DEE
{
	THREE_DEE( int _x, int _y, int _z )
	{
		x = _x;
		y = _y;
		z = _z;
	}

	int x = -1;
	int y = -1;
	int z = -1;

	bool adjacent( THREE_DEE a ) {
		if ( a.x == x && a.y == y )
			return (abs (a.z - z) == 1);
		else if ( a.z == z && a.y == y )
			return (abs( a.x - x ) == 1);
		else if ( a.x == x && a.z == z )
			return (abs( a.y - y ) == 1);
		else
			return false;
	}

	bool operator ==( THREE_DEE a ) {
		return a.x == x && a.y == y && a.z == z;
	}
};

int get_all_connected_cubes( THREE_DEE space, std::vector<THREE_DEE>& open_cubes, std::vector<THREE_DEE>& adjacent_cubes, int depth )
{
	if ( depth == 1000 )
	{
		for ( int i = 0; i < adjacent_cubes.size(); i++ )
		{
			auto other_cube = open_cubes.at( i );
			if ( space.adjacent( other_cube ) )
			{
				return i;
			}
		}
	}

	int old_size = adjacent_cubes.size();

	for ( int i = 0; i<open_cubes.size(); i++)
	{
		auto other_cube = open_cubes.at( i );
		if ( space.adjacent(other_cube) )
		{
			adjacent_cubes.emplace_back(other_cube);
			open_cubes.erase( open_cubes.begin() + i );
		}
		else if ( other_cube == space )
		{
			adjacent_cubes.push_back( space );
			open_cubes.erase( open_cubes.begin() + i );
		}
	}

	int new_size = adjacent_cubes.size();

	for ( auto i = old_size; i < new_size; i++ )
	{
		if ( int value = get_all_connected_cubes( adjacent_cubes.at( i ), open_cubes, adjacent_cubes, depth + 1 ) != -1 )
		{
			return value;
		}
	}

	return -1;
}

unsigned long long day_eighteen( bool real )
{
	auto file = get_file( "eighteen", real );

	unsigned long long faces = 0;
	std::vector<THREE_DEE> cubes;
	std::vector<THREE_DEE> spaces;

	const int MAX_DIST = real? 24 : 9;
	for ( int i = -1; i < MAX_DIST; i++ )
	{
		for ( int j = -1; j < MAX_DIST; j++ )
		{
			for ( int k = -1; k < MAX_DIST; k++ )
			{
				spaces.emplace_back( THREE_DEE( i, j, k ) );
			}
		}
	}

	std::string cube_line;
	while ( std::getline( file, cube_line ) )
	{
		// new cube so 6 more faces
		faces += 6;
		int x, y, z;

		std::string coord_string;
		std::stringstream ss1( cube_line );
		std::getline( ss1, coord_string, ',' );
		x = std::stoi( coord_string );
		std::getline( ss1, coord_string, ',' );
		y = std::stoi( coord_string );
		std::getline( ss1, coord_string, ',' );
		z = std::stoi( coord_string );

		cubes.emplace_back( x, y, z );

		for ( int i = 0; i < cubes.size() - 1; i++ )
		{
			if ( cubes.at( i ).adjacent(cubes.back()) )
			{
				faces -= 2;
			}
		}

		for ( int i = 0; i < spaces.size(); i++ )
		{
			if ( cubes.back() == spaces.at( i ) )
			{
				spaces.erase( spaces.begin() + i );
			}
		}
	}

	// then for part two, also remove faces which are internal
	std::vector<THREE_DEE> outside_spaces;
	outside_spaces.emplace_back( spaces.front() );
	spaces.erase( spaces.begin() );
	while ( true )
	{
		int old_size = outside_spaces.size();
		// add any spaces in spaces to outside_spaces if they are adjacent to any other space in outside_spaces
		for ( int j = 0; j < old_size; j++ )
		{
			for ( int i = spaces.size(); i-- > 0; )
			{
				if ( outside_spaces.at( j ).adjacent( spaces.at( i ) ) )
				{
					outside_spaces.emplace_back( spaces.at( i ) );
					spaces.erase( spaces.begin() + i );
					continue;
				}
			}
		}

		if ( old_size == outside_spaces.size() )
		{
			break;
		}
	}

	for ( int i = 0; i < spaces.size(); i++ )
	{
		for ( int j = 0; j < cubes.size(); j++ )
		{
			if ( cubes.at( j ).adjacent( spaces.at(i) ) )
			{
				faces -= 1;
			}
		}
	}

	return faces;
}

enum RESOURCE
{
	ORE,
	CLAY,
	OBSIDIAN,
	GEODE,
	RESOURCE_COUNT
};

struct ROBOT
{
	ROBOT( RESOURCE produces )
	{
		m_type = produces;
	}

	// produces
	RESOURCE m_type;

	// costs
	int m_ore = 0;
	int m_clay = 0;
	int m_obsidian = 0;
};

struct GEODE_GAME_STATE
{
	int m_time_remaining = 32;
	int resources[RESOURCE_COUNT] = { 0,0,0,0 };
	int resource_rate[RESOURCE_COUNT] = { 1,0,0,0 };
	std::vector<ROBOT> m_blueprint;
	RESOURCE new_resource{ RESOURCE_COUNT };

	int evaluate_game_state( int& high_score, std::vector<std::pair<RESOURCE,int >> previous_choices)
	{
		previous_choices.emplace_back( new_resource, resources[CLAY]);
		if ( m_time_remaining == 0 )
		{
			int score = resources[GEODE];
			if ( score > high_score )
			{
				high_score = score;
				std::cout << "new best score of " << high_score << " with time remaining " << m_time_remaining << std::endl;
				if ( false )
				{
					for ( auto choice : previous_choices )
					{
						std::string string = "   ";
						switch ( choice.first )
						{
						case ORE:
							string += "ore";
							break;
						case CLAY:
							string += "clay";
							break;
						case OBSIDIAN:
							string += "obsidian";
							break;
						case GEODE:
							string += "geode";
							break;
						case RESOURCE_COUNT:
							string += "none";
							break;
						}

						string += " clay:";
						string += std::to_string(choice.second);

						std::cout << string << std::endl;
					}
				}
			}

			return score;
		}

		int max_score = resources[GEODE] + resource_rate[GEODE] * m_time_remaining;
		int dummy_time_remaining = m_time_remaining;
		int dummy_obsidian = resources[OBSIDIAN];
		int dummy_obsidian_rate = resource_rate[OBSIDIAN];
		int dummy_clay = resources[CLAY];
		int dummy_clay_rate = resource_rate[CLAY];
		int dummy_ore = resources[ORE];
		int dummy_ore_rate = resource_rate[ORE];
		int obsidian_cost = m_blueprint.back().m_obsidian;
		int clay_cost = m_blueprint.at( OBSIDIAN ).m_clay;
		int ore_cost = m_blueprint.at( CLAY ).m_ore;

		switch ( new_resource )
		{
		case ORE:
			dummy_ore_rate++;
			break;
		case CLAY:
			dummy_clay_rate++;
			break;
		case OBSIDIAN:
			dummy_obsidian_rate++;
			break;
		case GEODE:
			max_score += m_time_remaining;
			break;
		}

		while ( dummy_time_remaining >=0 )
		{
			if ( true)
			{
				dummy_obsidian += dummy_obsidian_rate;
				dummy_clay += dummy_clay_rate;
				dummy_ore += dummy_ore_rate;
				if ( dummy_obsidian >= obsidian_cost )
				{
					max_score += dummy_time_remaining;
					dummy_obsidian -= obsidian_cost;
				}
				else if ( dummy_clay >= clay_cost )
				{
					dummy_obsidian_rate++;
					dummy_clay -= clay_cost;
				}
				else if ( dummy_ore >= ore_cost )
				{
					dummy_clay_rate++;
					dummy_ore -= ore_cost;
				}
				else
				{
					dummy_ore_rate++;
				}
			}
			else
			{
				max_score += dummy_time_remaining;
			}
			dummy_time_remaining--;
		}

		if ( max_score <= high_score )
		{
			if ( high_score == 8 && previous_choices.size() >= 15 && previous_choices[14].first == RESOURCE_COUNT && previous_choices[11].first == OBSIDIAN )
			{
				max_score = high_score;
			}
			return resources[GEODE];
		}

		if ( m_time_remaining == 24 )
		{
			std::cout <<"absolute max score of"<< max_score << std::endl;
		}

		if ( new_resource != RESOURCE_COUNT )
		{
			resource_rate[new_resource]++;
			new_resource = RESOURCE_COUNT;
		}

		std::vector<GEODE_GAME_STATE> possible_next_states;
		for ( int i = m_blueprint.size(); i-- > 0;)
		{
			const auto robot_to_build = m_blueprint.at( i );
			if ( robot_to_build.m_ore <= resources[ORE] &&
				 robot_to_build.m_clay <= resources[CLAY] &&
				 robot_to_build.m_obsidian <= resources[OBSIDIAN] )
			{
				GEODE_GAME_STATE new_state = *this;
				new_state.m_time_remaining--;

				new_state.resources[ORE] -= robot_to_build.m_ore;
				new_state.resources[CLAY] -= robot_to_build.m_clay;
				new_state.resources[OBSIDIAN] -= robot_to_build.m_obsidian;

				new_state.new_resource = robot_to_build.m_type;

				for ( int i = 0; i < RESOURCE_COUNT; i++ )
				{
					new_state.resources[i] += resource_rate[i];
				}

				possible_next_states.emplace_back( new_state );
			}
		}

		GEODE_GAME_STATE boring_state = *this;
		boring_state.m_time_remaining--;
		for ( int i = 0; i < RESOURCE_COUNT; i++ )
		{
			boring_state.resources[i] += resource_rate[i];
		}
		possible_next_states.emplace_back( boring_state );

		int best_score = 0;
		for ( int i = 0; i < possible_next_states.size(); i++ )
		{
			int score = possible_next_states[i].evaluate_game_state( high_score, previous_choices );
			if ( score > best_score )
			{
				best_score = score;
			}
		}

		return best_score;
	}
};

int day_nineteen( bool real )
{
	auto file = get_file( "nineteen", real );

	std::vector<GEODE_GAME_STATE> starting_positions;

	std::string blueprint;
	while ( std::getline( file, blueprint ) )
	{
		ROBOT ore_bot(ORE), clay_bot(CLAY), obsidian_bot(OBSIDIAN), geode_bot(GEODE);
		int num_dex = 0;

		std::string num_string;
		std::stringstream ss1( blueprint );
		while ( std::getline( ss1, num_string, ' ') && !num_string.empty() )
		{
			if ( std::isdigit( num_string.front() ) )
			{
				if ( num_dex == 1 )
				{
					ore_bot.m_ore = std::stoi( num_string );
				}
				else if ( num_dex == 2 )
				{
					clay_bot.m_ore = std::stoi( num_string );
				}
				else if ( num_dex == 3 )
				{
					obsidian_bot.m_ore = std::stoi( num_string );
				}
				else if ( num_dex == 4 )
				{
					obsidian_bot.m_clay = std::stoi( num_string );
				}
				else if ( num_dex == 5 )
				{
					geode_bot.m_ore = std::stoi( num_string );
				}
				else if ( num_dex == 6 )
				{
					geode_bot.m_obsidian = std::stoi( num_string );
				}
				num_dex++;
			}
		}

		GEODE_GAME_STATE this_game;
		this_game.m_blueprint.emplace_back( ore_bot );
		this_game.m_blueprint.emplace_back( clay_bot );
		this_game.m_blueprint.emplace_back( obsidian_bot);
		this_game.m_blueprint.emplace_back( geode_bot );

		starting_positions.emplace_back( this_game );
	}

	int total_score = 1;
	for ( int i = 0; i < starting_positions.size() && i < 3; i++ )
	{
		int score = 0;
		std::vector<std::pair<RESOURCE, int>> dummy;
		int final_score = starting_positions[i].evaluate_game_state( score,dummy );
		std::cout << " Blueprint " << i + 1 << " scored " << final_score << std::endl;
		total_score *= final_score;
	}

	return total_score;
}

long long day_twenty( bool real )
{
	auto file = get_file( "twenty", real );

	std::vector<std::pair<long long, int>> values_and_original_positions;
	constexpr long long key = 811589153;

	int i = 0;
	std::string number;
	while ( std::getline( file, number ) )
	{
		long long numnum = std::stoi( number );
		int pos = i;
		i++;
		values_and_original_positions.emplace_back( numnum* key, pos );
	}

	const int length = values_and_original_positions.size();

	for ( int time = 0; time < 10; time++ )
	{
		for ( int index = 0; index < length; index++ )
		{
			auto iterator = std::find_if( values_and_original_positions.begin(), values_and_original_positions.end(), [index]( std::pair<long long, int> &a ) { return a.second == index; } );

			auto copy = *iterator;
			int start_position = iterator - values_and_original_positions.begin();

			// remove the old entry
			values_and_original_positions.erase( iterator );

			int amount_to_move = std::abs( copy.first ) % (length - 1);

			if ( copy.first < 0 )
			{
				amount_to_move *= -1;
			}

			while ( amount_to_move < 0 )
			{
				amount_to_move += (length - 1);
			}

			while ( amount_to_move + start_position >= length )
			{
				amount_to_move -= (length - 1);
			}

			int new_position = (start_position + amount_to_move);

			values_and_original_positions.insert( values_and_original_positions.begin() + new_position, copy );
		}
	}

	auto zero_iterator = std::find_if( values_and_original_positions.begin(), values_and_original_positions.end(), [](std::pair<long long, int> &a) { return a.first == 0; });
	int zero_pos = zero_iterator - values_and_original_positions.begin();

	long long score = values_and_original_positions.at( (zero_pos +1000) % length ).first + values_and_original_positions.at( (zero_pos + 2000) % length ).first + values_and_original_positions.at( (zero_pos + 3000) % length ).first;

	return score;
}

bool resolve_monkey( std::string monkey_name, std::map<std::string, std::string>& monkeys, int depth, int max_depth )
{
	std::vector<std::string> words;
	std::string monkey_content = monkeys.at( monkey_name );

	std::stringstream ss( monkey_content );
	std::string word;
	while ( std::getline( ss, word, ' ' ) )
	{
		words.push_back( word );
	}

	long long this_value = 0;
	if ( words.size() == 1 )
	{
		// already resolved
		return true;
	}
	else if ( depth != max_depth &&
			  resolve_monkey( words.front(), monkeys, depth + 1, max_depth ) &&
			  resolve_monkey( words.back(), monkeys, depth + 1, max_depth ) )
	{
		long long number_one = std::stoll( monkeys.at( words.front() ) );
		long long number_two = std::stoll( monkeys.at( words.back() ) );

		if ( monkey_name == "root" )
		{
			// for part two!
			this_value = number_one - number_two;
		}
		else if ( words[1] == "+" )
		{
			this_value = number_one + number_two;
		}
		else if ( words[1] == "-" )
		{
			this_value = number_one - number_two;
		}
		else if ( words[1] == "/" )
		{
			this_value = number_one / number_two;
		}
		else if ( words[1] == "*" )
		{
			this_value = number_one * number_two;
		}

		monkeys.at( monkey_name ) = std::to_string( this_value );

		return true;
	}

	return false;
}

long long day_twentyone( bool real )
{
	auto file = get_file( "twentyone", real );

	std::map<std::string, std::string> monkeys;

	std::string line;
	while ( std::getline( file, line ) )
	{
		std::string monkey_name = line.substr( 0, 4 );
		std::string monkey_content = line.substr( 6, line.size() -5 );

		monkeys.emplace( monkey_name, monkey_content );
	}

	long long human_value = std::numeric_limits<long long>().max() / 100000;
	long long human_value_increments = -human_value/5;
	long long previous_root_value = 0;

	auto monkeys_copy = monkeys;

	while(true)
	{
		monkeys = monkeys_copy;

		monkeys.at( "humn" ) = std::to_string( human_value );
		while ( !resolve_monkey( "root", monkeys, 0, 5 ) )
		{
			int resolves = 0;
			for ( const auto& monkey : monkeys )
			{
				if ( resolve_monkey( monkey.first, monkeys, 0, 1 ) )
				{
					resolves++;
				}
			}
		}

		auto root_value = std::stoll( monkeys.at( "root" ) );

		std::cout << "at humn value of " << human_value << " root found " << root_value << std::endl;

		if ( root_value == 0 )
		{
			break;
		}
		else if (previous_root_value <0 && root_value >0 || previous_root_value >0 && root_value <0)
		{
			human_value_increments /= 10;
			human_value_increments *= -1;
			human_value += human_value_increments;
		}
		else
		{
			human_value += human_value_increments;
		}
		previous_root_value = root_value;
	}
	

	return human_value;
}

int day_twentytwo( bool real )
{
	auto file = get_file( "twentytwo", real );

	std::vector<std::string> map;
	std::string line;

	while ( std::getline( file, line ) && !line.empty() )
	{
		map.push_back( line );
	}

	// and the instructions:
	std::getline( file, line );
	std::vector<int> instructions;
	std::string current_word;
	for ( auto character : line )
	{
		if ( character == 'L' )
		{
			instructions.push_back( std::stoi( current_word ) );
			current_word.clear();
			instructions.push_back( -1 );
		}
		else if ( character == 'R' )
		{
			instructions.push_back( std::stoi( current_word ) );
			current_word.clear();
			instructions.push_back( -2 );
		}
		else
		{
			current_word.push_back( character );
		}
	}

	std::pair<int, int> coordinates{ 0,0 };
	int facing = 0;

	// before we start reading the instructions move to the first open space
	while ( map[coordinates.first][coordinates.second] != '.' )
	{
		coordinates.second++;
	}

	auto map_copy = map;

	struct EDGE_MOVE
	{
		EDGE_MOVE( int a, int b, int rel ){ edge_a_index = a; edge_b_index = b; b_position_from_a = rel; }

		int edge_a_index;
		int edge_b_index;

		int b_position_from_a; // 1 is same as a, -1 is N-a
	};

	auto move_steps = [ map, &coordinates, &map_copy, real, &facing ]( bool ignore_walls, int facing_to_use, int steps, const auto& move_lam )
	{
		for ( int i = 0; i<steps; i++ )
		{
			auto loc_copy = coordinates;
			if ( facing_to_use == 0 )
			{
				loc_copy.second++;
			}
			else if ( facing_to_use == 1 )
			{
				loc_copy.first++;
			}
			else if ( facing_to_use == 2 )
			{
				loc_copy.second--;
			}
			else if ( facing_to_use == 3 )
			{
				loc_copy.first--;
			}

			if ( loc_copy.first < 0 || loc_copy.second < 0 || map.size() <= loc_copy.first || map[loc_copy.first].size() <= loc_copy.second || map[loc_copy.first][loc_copy.second] == ' ' )
			{
				constexpr int PART = 2;

				if ( PART == 1 )
				{
					if ( ignore_walls )
					{
						return;
					}

					auto old_coord = coordinates;
					move_lam( true, (facing_to_use + 2) % 4, 200, move_lam );
					if ( map[coordinates.first][coordinates.second] == '#' )
					{
						coordinates = old_coord;
						return;
					}
				}
				else
				{
					if ( coordinates.first == 0 && facing == 3 )
					{
						if ( coordinates.second < 100 )
						{
							// goes to bottom left edge
							loc_copy.first = coordinates.second % 50 + 150;
							loc_copy.second = 0;
							facing_to_use = 0;
						}
						else if ( coordinates.second<150)
						{
							// goes to left bottom edge
							loc_copy.first = 199;
							loc_copy.second = coordinates.second % 50;
							facing_to_use = 3;
						}
						else
						{
							return;
						}
					}
					else if ( coordinates.second == 149 && facing == 0 && coordinates.first < 50 )
					{
						// goes to right middle
						loc_copy.first = 149-coordinates.first%50;
						loc_copy.second = 99;
						facing_to_use = 2;
					}
					else if ( coordinates.first == 49 && facing == 1 && coordinates.second > 100 )
					{
						// goes to above right middle
						loc_copy.first = 50 + coordinates.second % 50;
						loc_copy.second = 99;
						facing_to_use = 2;
					}
					else if ( coordinates.second == 99 && facing == 0 )
					{
						if ( loc_copy.first < 100 && loc_copy.first >= 50 )
						{
							// goes back to above right middle
							loc_copy.first = 49;
							loc_copy.second = 100 + coordinates.first%50;
							facing_to_use = 3;
						}
						else if ( loc_copy.first < 150 && loc_copy.first >= 100 )
						{
							// goes back to top right
							loc_copy.first = 49 - coordinates.first % 50;
							loc_copy.second = 149;
							facing_to_use = 2;
						}
						else
						{
							return;
						}
					}
					else if ( coordinates.first == 149 && facing == 1 && coordinates.second >= 50 )
					{
						// goes to bottom right
						loc_copy.first = 150 + coordinates.second % 50;
						loc_copy.second = 49;
						facing_to_use = 2;
					}
					else if ( coordinates.second == 49 && facing == 0 && coordinates.first >= 150 )
					{
						// goes to bottom middle
						loc_copy.first = 149;
						loc_copy.second = 50 + coordinates.first%50;
						facing_to_use = 3;
					}
					else if ( coordinates.first == 199 && facing == 1 && coordinates.second < 50 )
					{
						loc_copy.first = 0;
						loc_copy.second = 100 + coordinates.second%50;
						facing_to_use = 1;
					}
					else if ( coordinates.second == 0 && facing == 2 )
					{
						if ( coordinates.first <= 149 && coordinates.first >= 100 )
						{
							loc_copy.first = 49 - coordinates.first % 50;
							loc_copy.second = 50;
							facing_to_use = 0;
						}
						else if (coordinates.first >= 150 && coordinates.first<200)
						{
							loc_copy.first = 0;
							loc_copy.second = 50 + coordinates.first % 50;
							facing_to_use = 1;							
						}
						else
						{
							return;
						}
					}
					else if ( coordinates.first == 100 && facing == 3 && coordinates.second < 50 )
					{
						loc_copy.first = 50 + coordinates.second % 50;
						loc_copy.second = 50;
						facing_to_use = 0;
					}
					else if ( coordinates.second == 50 && facing == 2 )
					{
						if ( coordinates.first >= 50 )
						{
							loc_copy.first = 100;
							loc_copy.second = coordinates.first % 50;
							facing_to_use = 1;
						}
						else if (coordinates.first < 100)
						{
							loc_copy.first = 149 - coordinates.first % 50;
							loc_copy.second = 0;
							facing_to_use = 0;
						}
						else
						{
							return;
						}
					}
					else
					{
						return;
					}

					if ( map[loc_copy.first][loc_copy.second] == '.' )
					{
						std::cout << coordinates.first << ", " << coordinates.second << " to " << loc_copy.first << ", " << loc_copy.second;
						coordinates = loc_copy;
						facing = facing_to_use;

						if ( facing == 0 )
						{
							std::cout << ">";
						}
						else if ( facing == 1 )
						{
							std::cout << "v";
						}
						else if ( facing == 2 )
						{
							std::cout << "<";
						}
						else if ( facing == 3 )
						{
							std::cout << "^";
						}

						std::cout<<std::endl;
					}
					else if ( map[loc_copy.first][loc_copy.second] == '#' )
					{
						return;
					}
					else
					{
						return;
					}
				}
			}
			else if ( map[loc_copy.first][loc_copy.second] == '.' )
			{
				coordinates = loc_copy;
			}
			else if ( map[loc_copy.first][loc_copy.second] == '#' )
			{
				if ( !ignore_walls )
				{
					return;
				}
				else
				{
					coordinates = loc_copy;
				}
			}
		}

	};

	for ( auto instruction : instructions )
	{
		if ( facing == 0 )
		{
			map_copy[coordinates.first][coordinates.second] = '>';
		}
		else if ( facing == 1 )
		{
			map_copy[coordinates.first][coordinates.second] = 'v';
		}
		else if ( facing == 2 )
		{
			map_copy[coordinates.first][coordinates.second] = '<';
		}
		else if ( facing == 3 )
		{
			map_copy[coordinates.first][coordinates.second] = '^';
		}

		if ( instruction == -1 )
		{
			facing--;

			if ( facing == -1 )
			{
				facing = 3;
			}

			facing %= 4;
		}
		else if ( instruction == -2 )
		{
			facing++;
			facing %= 4;
		}
		else
		{
			move_steps( false, facing, instruction, move_steps );
		}
	}

	std::ofstream ofs( "output.txt", std::ofstream::out );

	for ( auto line : map_copy )
	{
		ofs << line << std::endl;;
	}

	ofs.close();

	return 1000 * (coordinates.first+1) + 4 * (coordinates.second+1) + facing;
}

int day_twentythree( bool real )
{
	auto input = get_file( "twentythree", real );
	std::vector<std::string> map;
	std::string line;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> elves;

	int j = 0;
	while ( std::getline( input, line ) && !line.empty() )
	{
		for ( int i = 0; i < line.size(); i++ )
		{
			if ( line[i] == '#' )
			{
				elves.emplace_back( std::pair<int, int>(j,i), std::pair<int, int>(j,i) );
			}
		}
		j++;
	}

	//constexpr int ROUNDS_TO_DO = 10;
	constexpr int ROUNDS_TO_DO = 10000000;
	char directions[4] = { 'N', 'S', 'W', 'E' };

	for ( int i = 0; i < ROUNDS_TO_DO; i++ )
	{
		// consider moving
		for ( auto& elf : elves )
		{
			// look for elves adjacent
			bool noone_near = true;
			std::array<bool, 4> elf_position = { false, false, false, false }; // north, south, west, east

			for ( const auto other_elf : elves )
			{
				if ( other_elf == elf )
				{
					continue;
				}

				int x_dist = abs( other_elf.first.first - elf.first.first );
				int y_dist = abs( other_elf.first.second - elf.first.second );
				if ( y_dist <= 1 && x_dist <= 1 )
				{
					noone_near = false;
					if ( other_elf.first.first - elf.first.first > 0 )
					{
						elf_position[1] = true;
					}
					if ( other_elf.first.first - elf.first.first < 0 )
					{
						elf_position[0] = true;
					}
					if ( other_elf.first.second - elf.first.second > 0 )
					{
						elf_position[3] = true;
					}
					if ( other_elf.first.second - elf.first.second < 0 )
					{
						elf_position[2] = true;
					}
				}
			}

			if ( !noone_near )
			{
				for ( int d = 0; d < 4; d++ )
				{
					int rotated_d = (d + i) % 4;

					if ( !elf_position[rotated_d] )
					{
						if ( rotated_d == 0 )
						{
							elf.second.first--;
						}
						if ( rotated_d == 1 )
						{
							elf.second.first++;
						}
						if ( rotated_d == 2 )
						{
							elf.second.second--;
						}
						if ( rotated_d == 3 )
						{
							elf.second.second++;
						}
						break;
					}
				}
			}
		}

		// try moving
		int elves_moved = 0;
		for ( auto& elf : elves )
		{
			if ( elf.first != elf.second )
			{
				for ( auto& other_elf : elves )
				{
					if ( other_elf.first != other_elf.second && other_elf.first != elf.first )
					{
						if ( elf.second == other_elf.second )
						{
							elf.second = elf.first;
							other_elf.second = other_elf.first;
							break;// assumes only a pair of elves can try the same move!
						}
					}
				}
			}

			if ( elf.first != elf.second )
			{
				elf.first = elf.second;
				elves_moved++;
			}
		}

		std::cout << "Round " << i << ", " << elves_moved << "/" << elves.size() << "elves moved" << std::endl;

		if ( elves_moved == 0 )
		{
			return i+1;
		}
	}

	int min_x = std::numeric_limits<int>().max();
	int min_y = std::numeric_limits<int>().max();
	int max_x = std::numeric_limits<int>().min();
	int max_y = std::numeric_limits<int>().min();
	// now find the positions
	for ( auto& elf : elves )
	{
		min_x = std::min(min_x, elf.first.first);
		min_y = std::min( min_y, elf.first.second );
		max_x = std::max( max_x, elf.first.first );
		max_y = std::max( max_y, elf.first.second );
	}

	// todo with how we count the rows and columns
	max_x++;
	max_y++;
	int size = (max_x - min_x) * (max_y - min_y);
	size -= elves.size();

	return size;
}

int day_twentyfour( bool real )
{
	auto file = get_file( "twentyfour", real );

	int right_hand_edge, bottom_edge;
	int start_index = -1, goal_index = -1;
	std::vector<std::pair<std::pair<int, int>, char >> blizzards; // first number is horizontal, second is row
	std::string line;
	int j = 0;

	while ( std::getline( file, line ) && !line.empty() )
	{
		if (( start_index == -1 || goal_index == -1 ) && (line[1] == '#' || line[2] == '#' ))
		{
			for ( int i = 0; i < line.size(); i++ )
			{
				if ( line[i] == '.' )
				{
					if ( start_index == -1 )
					{
						start_index = i;
						right_hand_edge = line.size() - 1;
					}
					else
					{
						goal_index = i;
						bottom_edge = j;
					}

					break;
				}
			}
		}
		else
		{
			for ( int i = 0; i < line.size(); i++ )
			{
				if ( line[i] != '#' && line[i] != '.' )
				{
					blizzards.emplace_back( std::pair<int, int>( i, j ), line[i] );
				}
			}
		}

		j++;
	}

	const int manhattan_distance = bottom_edge + abs( start_index - goal_index );

	// create a cheat-sheet of blizzard locations after each minute
	std::vector< std::vector<std::pair<std::pair<int, int>, char >> > blizzards_after_time;
	for ( int i = 0; i < manhattan_distance * 30; i++ )
	{
		for ( auto& blizzard : blizzards )
		{
			if ( blizzard.second == '>' )
			{
				blizzard.first.first++;
				if ( blizzard.first.first == right_hand_edge )
				{
					blizzard.first.first = 1;
				}
			}
			else if ( blizzard.second == '<' )
			{
				blizzard.first.first--;
				if ( blizzard.first.first == 0 )
				{
					blizzard.first.first = right_hand_edge - 1;
				}
			}
			if ( blizzard.second == 'v' )
			{
				blizzard.first.second++;
				if ( blizzard.first.second == bottom_edge )
				{
					blizzard.first.second = 1;
				}
			}
			if ( blizzard.second == '^' )
			{
				blizzard.first.second--;
				if ( blizzard.first.second == 0 )
				{
					blizzard.first.second = bottom_edge - 1;
				}
			}
		}

		blizzards_after_time.emplace_back( blizzards );
	}

	// great, now find the possible routes (surely there can't be that many!)
	std::vector<std::pair<int, int>> possible_positions;
	possible_positions.emplace_back( start_index, 0 );

	int stage = 0;

	for ( int i = 0; i < blizzards_after_time.size(); i++ )
	{
		// remove any duplicates!
		for ( int j = possible_positions.size(); j-- > 0; )
		{
			for ( int k = possible_positions.size() -1; k>j; k-- )
			{
				if ( possible_positions[k] == possible_positions[j] )
				{
					possible_positions.erase( possible_positions.begin() + k );
				}
			}
		}

		std::vector<std::pair<int, int>> new_positions;

		for ( auto current_position : possible_positions )
		{
			new_positions.emplace_back( current_position.first, current_position.second );
			new_positions.emplace_back( current_position.first + 1, current_position.second );
			new_positions.emplace_back( current_position.first - 1, current_position.second );
			new_positions.emplace_back( current_position.first, current_position.second + 1 );
			new_positions.emplace_back( current_position.first, current_position.second - 1 );
		}

		bool clear_all_but_front = false;
		for ( int n = new_positions.size(); n-- > 0; )
		{
			auto new_pos = new_positions[n];

			// does this already exist later in the list?
			bool already_found = false;
			for ( int k = new_positions.size() - 1; k > n; k-- )
			{
				if ( new_positions[k] == new_positions[n] )
				{
					already_found = true;
				}
			}

			if ( already_found )
			{
				new_positions.erase( new_positions.begin() + n );
				continue;
			}

			if ( clear_all_but_front )
			{
				new_positions.erase( new_positions.begin() + n );
				continue;
			}

			if ( new_pos.first < 0 || new_pos.second < 0 || new_pos.second > bottom_edge )
			{
				new_positions.erase( new_positions.begin() + n );
				continue;
			}

			if ( new_pos.first == 0 || new_pos.first == right_hand_edge )
			{
				new_positions.erase( new_positions.begin() + n );
				continue;
			}

			if ( new_pos.second == 0 )
			{
				if ( new_pos.first != start_index )
				{
					new_positions.erase( new_positions.begin() + n );
					continue;
				}
				else if ( stage == 1 )
				{
					stage++;
					clear_all_but_front = true;
					std::cout << "returned to start in " << i + 1 << std::endl;
				}
			}

			if ( new_pos.second == bottom_edge )
			{
				if ( new_pos.first == goal_index )
				{
					if ( stage == 0 )
					{
						stage++;
						clear_all_but_front = true;
						std::cout << "reached end in " << i + 1 << std::endl;
					}
					else if ( stage == 2 )
					{
						std::cout << "reached end again in " << i + 1 << std::endl;
						return i + 1;
					}
				}
				else
				{
					new_positions.erase( new_positions.begin() + n );
				}
				continue;
			}

			// finally look through the blizzard locations
			for ( auto blizzard : blizzards_after_time[i] )
			{
				if ( blizzard.first == new_pos )
				{
					new_positions.erase( new_positions.begin() + n );
					break;
				}
			}
		}

		while ( clear_all_but_front && new_positions.size() > 1 )
		{
			new_positions.erase( new_positions.begin() + 1 );
		}

		possible_positions = new_positions;
	}

	return blizzards.size();
}

long long day_twentyfive( bool real )
{
	auto file = get_file( "twentyfive", real );

	auto read_snafu = []( std::string snafu ) 
	{
		long long decimal = 0;

		for ( int i = 1; i <= snafu.size(); i++ )
		{
			long long column = std::pow( 5, i-1 );
			auto symbol = snafu.at( snafu.size() - i );

			if ( symbol == '=' )
			{
				decimal -= 2 * column;
			}
			else if ( symbol == '-' )
			{
				decimal -= column;
			}
			else
			{
				decimal += column * (symbol - '0');
			}
		}

		return decimal;
	};

	long long answer = 0;
	std::string line;

	while ( std::getline( file, line ) && !line.empty() )
	{
		long long val = read_snafu( line );
		answer += val;
		// std::cout << val << std::endl;
	}

	long long answer_copy = answer;

	// and now to go back to SNAFU...
	int i = 0;
	std::string snafu;
	while ( answer_copy > 0 )
	{
		long long column = std::pow( 5, i );
		long long next_column = std::pow( 5, i + 1 );

		long long remainder = (answer_copy % next_column)/column;
		char symbol;

		int extra = 0;
		if ( remainder == 3 )
		{
			symbol = '=';
			extra++;
		}
		else if ( remainder == 4 )
		{
			symbol = '-';
			extra++;
		}
		else
		{
			symbol = '0' + remainder;
		}

		snafu.insert( snafu.begin(), symbol);
		answer_copy += extra * next_column - remainder * column;
		i++;
	}

	std::cout << snafu << std::endl;

	return answer - read_snafu(snafu);
}

int main()
{
	std::cout << day_twentyfive( false ) << std::endl;
	std::cout << day_twentyfive( true ) << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
