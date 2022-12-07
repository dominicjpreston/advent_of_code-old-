// advent_of_code_2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

template<typename T>
std::vector<T> read_vector_from_file(std::string file_name)
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

std::vector<int> read_comma_vector_from_file( std::string file_name )
{
	std::ifstream infile( file_name );
	std::vector<int> vector;
	std::string read_in;
	while ( std::getline(infile, read_in, ',') )
	{
		vector.push_back( std::stoi(read_in) );
	}

	return vector;
}

std::vector<std::pair<std::string, int>> read_directions_from_file( std::string file_name )
{
	std::ifstream infile( file_name );
	std::vector<std::pair<std::string, int>> vector;
	std::pair<std::string, int > read_in;
	while ( infile >> read_in.first )
	{
		infile >> read_in.second;
		vector.push_back( read_in );
	}

	return vector;
}

bool get_moving_average( std::vector<int> input_data, int index, int window_size, int& sum )
{
	sum = 0;

	if ( index < 0 || index + window_size > input_data.size() )
	{
		return false;
	}

	for ( int i = index; i < index + window_size; i++ )
	{
		sum += input_data.at( i );
	}

	return sum;
}

int puzzle_one()
{
	std::vector<int> input_data = read_vector_from_file<int>( "input_puzzle_one.txt" );

	int previous_value = -1;
	int value{};
	int number_of_increases{};

	for ( int i = 0; i<input_data.size(); i++ )
	{
		if ( !get_moving_average( input_data, i, 3, value ) )
		{
			continue;
		}

		if ( value > previous_value && previous_value != -1 )
		{
			number_of_increases++;
		}

		previous_value = value;
	}

	return number_of_increases;
}

int puzzle_two()
{
	auto input_direction = read_directions_from_file( "input_puzzle_two.txt" );
	
	int depth{0};
	int horizontal{0};
	int aim{ 0 };

	for ( auto direction : input_direction )
	{
		if ( direction.first == "forward" )
		{
			horizontal += direction.second;
			depth += direction.second * aim;
		}
		else if ( direction.first == "down" )
		{
			aim += direction.second;
		}
		else if ( direction.first == "up" )
		{
			aim -= direction.second;
		}
		else
		{
			return -1;
		}
	}

	return depth * horizontal;
}

int puzzle_three()
{
	constexpr size_t N = 12;

	auto input = read_vector_from_file<std::bitset<N>>( "input_puzzle_three.txt" );

	std::array<int, N> counts = { 0 };
	std::bitset<N> gamma, epsilon;

	for ( auto& reading : input )
	{
		for ( size_t i = 0; i < N; i++ )
		{
			counts[i] += reading[i];
		}
	}

	for ( size_t i = 0; i < N; i++ )
	{
		gamma[i] = counts[i] > input.size() / 2 ? 1 : 0;
	}

	epsilon = gamma.flip();
	gamma.flip();

	return epsilon.to_ulong() * gamma.to_ulong();
}

constexpr size_t N_p2 = 12;

std::vector<std::bitset<N_p2>> check_and_remove_readings( bool looking_for_most_frequent, std::vector<std::bitset<N_p2>> input, int index )
{
	if ( input.size() == 1 )
	{
		return input;
	}

	// otherwise get key bit, remove any that don't match it and call the next index
	int count{ 0 };
	for ( auto& reading : input )
	{
		count += reading[index];
	}

	bool key = count >= input.size() / 2.0f;

	for ( size_t i = input.size(); i-- > 0;)
	{
		if ( (input[i][index] == key) != looking_for_most_frequent )
		{
			input.erase( input.begin() + i );
		}
	}

	return check_and_remove_readings( looking_for_most_frequent, input, index - 1 );
}

int puzzle_three_b()
{
	auto input = read_vector_from_file<std::bitset<N_p2>>( "input_puzzle_three.txt" );

	auto oxygen = check_and_remove_readings( true, input, N_p2 - 1 ).front();
	auto dioxide = check_and_remove_readings( false, input, N_p2 - 1 ).front();

	return oxygen.to_ulong() * dioxide.to_ulong();
}

constexpr int N_p4 = 5;

std::vector<int> read_comma_array( std::string filename, std::vector< std::array< std::array< int, N_p4 >, N_p4 > >& cards )
{
	std::ifstream infile( filename );
	std::vector<int> vector;
	std::string number_as_string;
	std::string topline;

	while ( std::getline( infile, number_as_string, ',' ) )
	{
		vector.push_back( std::stoi( number_as_string ) );
	}

	// now the cards will all be stored in number_as_string
	std::stringstream array_stream;
	array_stream << number_as_string;

	std::vector<int> card_numbers;

	array_stream >> number_as_string;
	while ( array_stream >> number_as_string )
	{
		number_as_string.erase( std::remove_if( number_as_string.begin(), number_as_string.end(),
					[]( unsigned char c ) { return not std::isdigit( c ); } ),
								number_as_string.end() );
		card_numbers.push_back( std::stoi( number_as_string ) );
	}

	int i = 0;
	int j = 0;
	std::array< std::array< int, N_p4 >, N_p4 > card;
	for ( int n = 0; n < card_numbers.size(); n++ )
	{
		int number = card_numbers.at( n );
		card[i][j] = number;

		j++;

		if ( j == N_p4 )
		{
			j = 0;
			i++;
		}

		if ( i == N_p4 )
		{
			cards.push_back( card );
			i = 0;
		}		
	}

	return vector;
}

bool is_board_finished( std::array< std::array< int, N_p4 >, N_p4 > board )
{
	// look through every column and row for a sum of -5 to see that it's finished
	for ( int i = 0; i < N_p4; i++ )
	{
		int ijsum = 0;
		int jisum = 0;
		for ( int j = 0; j < N_p4; j++ )
		{
			ijsum += board[i][j];
			jisum += board[j][i];
		}

		if ( ijsum == -5 || jisum == -5 )
		{
			return true;
		}
	}

	return false;
}

int get_score( std::array< std::array< int, N_p4 >, N_p4 > board )
{
	int score = 0;
	for ( int i = 0; i < N_p4; i++ )
	{
		for ( int j = 0; j < N_p4; j++ )
		{
			if (board[i][j] != -1)
			{
				score += board[i][j];
			}
		}
	}

	return score;
}

std::pair<int, int> check_and_score_board( std::vector<int> bingo_list, std::array< std::array< int, N_p4 >, N_p4 > board )
{
	// for every item in the bingo list remove the corresponding number from the board, if there's ever a blank row or column then we're done and can score!
	int n;
	for ( n = 0; n < bingo_list.size() && !is_board_finished( board ); n++ )
	{
		auto value = bingo_list.at( n );

		for ( int i = 0; i < N_p4; i++ )
		{
			for ( int j = 0; j < N_p4; j++ )
			{
				if ( board[i][j] == value )
				{
					board[i][j] = -1;
				}
			}
		}
	}

	if ( !is_board_finished( board ) )
	{
		return std::make_pair( n, -1 );
	}
	else
	{
		int remaining_vals = get_score( board );
		int score = remaining_vals * bingo_list.at( n-1 );
		return std::make_pair( n, score );
	}
}

int puzzle_four()
{
	std::vector < std::array< std::array< int, N_p4 >, N_p4 > > cards;
	const auto bingo_list = read_comma_array( "input_puzzle_four.txt", cards );

	std::vector<std::pair<int, int>> list_of_scores;
	for ( auto card : cards )
	{
		list_of_scores.push_back( check_and_score_board( bingo_list, card ) );
	}

	std::sort( list_of_scores.begin(), list_of_scores.end(), []( std::pair<int, int>& a, std::pair<int, int>& b ) { return a.first < b.first; } );

	return list_of_scores.back().second;
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > read_in_vent_lines( std::string file_name, std::pair<int, int> & max_values )
{
	std::ifstream infile( file_name );
	std::vector<int> vector;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > output;

	std::string reading;
	while ( std::getline( infile, reading ) )
	{   // get a whole line
		std::stringstream ss1( reading );
		std::pair<std::pair<int, int>, std::pair<int, int>> coord_pair = std::make_pair( std::make_pair( -1, -1 ), std::make_pair( -1, -1 ) );

		while ( std::getline( ss1, reading, ' ' ) )
		{
			std::stringstream ss2( reading );
			while ( std::getline( ss2, reading, ',' ) )
			{
				if ( !reading.empty() && std::isdigit( reading.at( 0 ) ) )
				{
					std::pair<int, int> * coord = &coord_pair.first;
					if ( coord->second != -1 )
					{
						coord = &coord_pair.second;
					}

					auto number = std::stoi( reading );

					if ( coord->first == -1 )
					{
						coord->first = number;
						if ( number > max_values.first )
						{
							max_values.first = number;
						}
					}
					else
					{
						coord->second = number;
						if ( number > max_values.second )
						{
							max_values.second = number;
						}
					}
				}
			}
		}

		output.push_back( coord_pair );
	}

	return output;
}

int puzzle_five()
{
	std::pair<int, int> max_values = std::make_pair(-1,-1);

	auto lines = read_in_vent_lines( "input_puzzle_five.txt", max_values );

	std::vector<std::vector<int>> map;
	map.resize( max_values.first + 1 );
	for ( auto& line : map )
	{
		line.resize( max_values.second + 1 );
	}

	for ( auto line : lines )
	{
		// start at the first coordinate
		auto begin = line.first;
		auto end = line.second;

		if ( true )
		{
			int x_direction = begin.first == end.first ? 0 : 1;
			int y_direction = begin.second == end.second ? 0 : 1;

			if ( begin.first > end.first )
			{
				x_direction *= -1;
			}
			if ( begin.second > end.second )
			{
				y_direction *= -1;
			}

			for ( std::pair<int, int> loc = begin; loc != end; loc.first += x_direction, loc.second += y_direction )
			{
				map[loc.first][loc.second]++;
			}

			map[end.first][end.second]++;
		}
	}

	int danger{ 0 };
	for ( auto line : map )
	{
		for ( auto vla : line )
		{
			if ( vla > 1 )
			{
				danger++;
			}
		}
	}

	return danger;
}

void apply_lanternfish( std::vector<int>& fishes )
{
	constexpr int INIT = 8;
	constexpr int PERIOD = 6;
	const int initial_size = fishes.size();
	for ( int i = 0; i< initial_size; i++ )
	{
		if ( fishes.at(i) == 0 )
		{
			fishes.push_back( INIT );
			fishes.at( i ) = PERIOD;
		}
		else
		{
			fishes.at( i )--;
		}
	}
}

std::array<unsigned long long,9> apply_lanternfish_buckets( std::array<unsigned long long, 9>& fishes )
{
	constexpr int INIT = 8;
	constexpr int PERIOD = 6;
	const int initial_size = fishes.size();
	std::array<unsigned long long, 9> output{};

	for ( int i = initial_size; i-->0;)
	{
		// work out where to move these fish to and do it
		auto index = i - 1;
		if ( index == -1 )
			index = PERIOD;

		output.at( index ) += fishes.at( i );

		if ( i == 0 )
		{
			// and add the new fish at the top
			output.at( INIT ) += fishes.at( i );
		}
	}

	std::cout << std::accumulate( output.begin(), output.end(), (unsigned long long)0 ) << std::endl;

	return output;
}

int puzzle_six()
{
	auto input = read_comma_vector_from_file( "input_puzzle_six.txt" );

	std::array<unsigned long long, 9> fish_buckets{};
	for ( auto fish : input )
	{
		fish_buckets.at( fish )++;
	}

	constexpr int DAYS = 256;

	for ( int i = 0; i < DAYS; i++ )
	{
		fish_buckets = apply_lanternfish_buckets( fish_buckets );
	}

	return std::accumulate( fish_buckets.begin(), fish_buckets.end(), (unsigned long long)0 );
}

int get_triangle_number( int input )
{
	if ( input == 0 )
	{
		return 0;
	}

	return get_triangle_number( input - 1 ) + input;
}

int get_fuel_for_answer( int answer, std::vector<int> locations )
{
	int fuel = 0;

	for ( auto location : locations )
	{
		fuel += get_triangle_number( abs(location - answer) );
	}

	return fuel;
}

int puzzle_seven()
{
	auto input = read_comma_vector_from_file( "input_puzzle_seven.txt" );

	int current_value = 0;
	int current_fuel = get_fuel_for_answer( current_value, input );
	int previous_fuel = current_fuel + 1;

	while ( previous_fuel >= current_fuel )
	{
		previous_fuel = current_fuel;
		current_value++;
		current_fuel = get_fuel_for_answer( current_value, input );
		std::cout << current_value << ", " << current_fuel << std::endl;
	}

	return previous_fuel;
}

std::map<char, char> analyse_readings( std::vector<std::string> readings )
{
	std::sort( readings.begin(), readings.end(), []( std::string& a, std::string& b ) { return a.size() < b.size(); } );
	std::map<char, char> key;

	// first compare the two shortest, the extra element is 'a'
	for ( auto letter : readings.at( 1 ) )
	{
		auto found = readings.at(0).find( letter );
		if ( found == std::string::npos )
		{
			key.insert( std::pair<char, char>( 'a', letter ));
		}
	}

	// 'g' is the letter missing from the first three words and present in all others 
	std::string all_letters = "abcdefg";
	for ( int i = 0; i < 3; i++ )
	{
		all_letters.erase( std::remove_if( all_letters.begin(), all_letters.end(),
						   [&]( unsigned char c ) { return readings.at( i ).find( c ) != std::string::npos; } ),
						   all_letters.end() );
	}
	// now all_letters will only have the missing letters, now remove all the letters which don't appear in the other words
	for ( int i = 3; i < 10; i++ )
	{
		all_letters.erase( std::remove_if( all_letters.begin(), all_letters.end(),
						   [&]( unsigned char c ) { return readings.at( i ).find( c ) == std::string::npos; } ),
						   all_letters.end() );
	}
	key.insert( std::pair<char, char>( 'g', all_letters.front()));

	// 'b' and 'f' appears in 0,6 and 9 (only other letters are a and g)
	std::string b_and_f = "abcdefg";
	for ( int i = 6; i < 9; i++ )
	{
		b_and_f.erase( std::remove_if( b_and_f.begin(), b_and_f.end(),
					   [&]( unsigned char c ) { return readings.at( i ).find( c ) == std::string::npos; } ),
					   b_and_f.end() );
	}
	b_and_f.erase( std::remove_if( b_and_f.begin(), b_and_f.end(),
				   [&]( char c ) { return c == key.at('a'); }),
				   b_and_f.end() );
	b_and_f.erase( std::remove_if( b_and_f.begin(), b_and_f.end(),
				   [&]( char c ) { return c == key.at( 'g' ); } ),
				   b_and_f.end() );

	// smallest word will contain f, other one is b, only thing in second-smallest word that isn't in smallest word or b is d
	std::string only_b = b_and_f;
	std::string only_f = b_and_f;

	only_f.erase( std::remove_if( only_f.begin(), only_f.end(),
				   [&]( unsigned char c ) { return readings.at( 0 ).find( c ) == std::string::npos; } ),
				  only_f.end() );
	only_b.erase( std::remove_if( only_b.begin(), only_b.end(),
				   [&]( unsigned char c ) { return readings.at( 0 ).find( c ) != std::string::npos; } ),
				  only_b.end() );

	key.insert( std::pair<char, char>( 'b', only_b.front() ) );
	key.insert( std::pair<char, char>( 'f', only_f.front() ) );


	// d is the letter that isn't in the shortest word and isn't b
	std::string finding_d = readings.at( 2 );
	finding_d.erase( std::remove_if( finding_d.begin(), finding_d.end(),
				   [&]( char c ) { return c == key.at( 'b' ); } ),
					 finding_d.end() );
	finding_d.erase( std::remove_if( finding_d.begin(), finding_d.end(),
				   [&]( unsigned char c ) { return readings.at( 0 ).find( c ) != std::string::npos; } ),
					 finding_d.end() );

	key.insert( std::pair<char, char>( 'd', finding_d.front() ) );

	// c is the letter in the shortest word that isn't f
	std::string finding_c = readings.at( 0 );
	finding_c.erase( std::remove_if( finding_c.begin(), finding_c.end(),
					 [&]( char c ) { return c == key.at( 'f' ); } ),
					 finding_c.end() );
	key.insert( std::pair<char, char>( 'c', finding_c.front() ) );

	// and e is the other letter
	std::string finding_e = "abcdefg";
	all_letters = "abcdfg";
	for ( int i = 0; i < 6; i++ )
	{
		finding_e.erase( std::remove_if( finding_e.begin(), finding_e.end(),
						 [&]( char c )
						 {
							 return key.at( all_letters.at( i ) ) == c;
						 } ),
						 finding_e.end() );
	}

	key.insert( std::pair<char, char>( 'e', finding_e.front() ) );

	return key;
}

int convert_letters_to_num( std::string digit, std::map<char, char> key )
{
	const std::string all_letter = "abcdefg";
	for ( auto& character : digit )
	{
		for ( int i = 0; i < 7; i++ )
		{
			char letter = all_letter.at( i );
			char target_swap = key.at( letter );
			if ( character == target_swap )
			{
				character = letter;
				break;
			}
		}
	}

	if ( digit.size() == 2 )
	{
		return 1;
	}
	else if ( digit.size() == 3 )
	{
		return 7;
	}
	else if ( digit.size() == 4 )
	{
		return 4;
	}
	else if ( digit.size() == 7 )
	{
		return 8;
	}
	else if ( digit.size() == 5 )
	{
		if ( digit.find( 'e' ) != std::string::npos )
		{
			return 2;
		}
		if ( digit.find( 'c' ) != std::string::npos )
		{
			return 3;
		}
		return 5;
	}
	else
	{
		if ( digit.find( 'd' ) == std::string::npos )
		{
			return 0;
		}
		if ( digit.find( 'c' ) == std::string::npos )
		{
			return 6;
		}
		return 9;
	}

}

int parse_notes( std::string filename, int& number_of_unique_outputs )
{
	std::ifstream infile( filename );
	std::vector<std::string> vector;
	std::string read_in;
	std::string reading;
	int answer = 0;

	while ( std::getline( infile, reading ) )
	{   // get a whole line
		std::stringstream whole_line( reading );
		std::getline( whole_line, reading, '|' );
		std::stringstream input( reading );
		while ( input >> reading )
		{
			vector.push_back( reading );
		}

		auto key = analyse_readings( vector );
		vector.clear();

		while ( whole_line >> reading )
		{
			vector.push_back( reading );

			if ( reading.size() == 2 || reading.size() == 3 || reading.size() == 4 || reading.size() == 7 )
			{
				std::cout << reading << std::endl;
				number_of_unique_outputs++;
			}
		}

		std::string number = "";
		for ( auto digit : vector )
		{
			// turn the digit from letters into a number
			int num_digit = convert_letters_to_num(digit, key);
			number += std::to_string(num_digit);
		}
		int result = std::stoi( number );
		answer += result;
		vector.clear();
	}

	return answer;
}

int puzzle_eight()
{
	int part_one = 0;
	auto answer = parse_notes( "input_puzzle_eight.txt", part_one );

	return answer;
}

std::vector<std::vector<int>> read_digit_grid( std::string filename )
{
	std::ifstream infile( filename );
	std::vector<std::vector<int>> grid;
	std::string read_in;
	char read_char;
	while ( std::getline( infile, read_in ) )
	{   // get a whole line
		std::vector<int> row;
		std::stringstream whole_line( read_in );
		while ( whole_line.get( read_char ) )
		{
			int value = read_char - '0';
			row.push_back( value );
		}
		grid.push_back( row );
	}

	return grid;
}

std::pair<int, int> get_basin_coord( std::pair<int, int> start_point, std::vector<std::vector<int>> grid )
{
	int x = start_point.first;
	int y = start_point.second;

	std::vector<std::pair<int, int>> list_of_moves;
	const auto row = grid.at( x );

	// now check all adjacent values
	if ( y > 0 )
	{
		list_of_moves.push_back( std::make_pair( x, y - 1 ) );
	}
	if ( y < row.size() - 1 )
	{
		list_of_moves.push_back( std::make_pair( x, y + 1 ) );
	}
	if ( x > 0 )
	{
		list_of_moves.push_back( std::make_pair( x - 1, y ) );
	}
	if ( x < grid.size() - 1 )
	{
		list_of_moves.push_back( std::make_pair( x + 1, y ) );
	}


	auto value = grid.at( x ).at( y );

	bool is_low_point = true;

	for ( auto location : list_of_moves )
	{
		if ( grid.at( location.first ).at( location.second ) < value )
		{
			is_low_point = false;
			break;
		}
	}

	if ( is_low_point )
	{
		return start_point;
	}

	std::sort( list_of_moves.begin(), list_of_moves.end(), [&]( std::pair<int, int>& a, std::pair<int, int>& b ) { return grid.at( a.first ).at( a.second) < grid.at( b.first ).at( b.second ); } );

	return get_basin_coord( list_of_moves.front(), grid );
}

int puzzle_nine()
{
	auto grid = read_digit_grid( "input_puzzle_nine.txt" );
	
	int running_total{ 1 };

	std::vector<std::pair<std::pair<int, int>, int>> list_of_basins;

	int number_of_spaces = 0;

	for ( int i = 0; i<grid.size(); i++)
	{
		auto row = grid.at( i );
		for ( int j = 0; j < row.size(); j++ )
		{
			if ( grid.at( i ).at( j ) == 9 )
			{
				continue;
			}

			const auto basin_location = get_basin_coord( std::make_pair( i, j ), grid );

			bool added = false;

			for ( auto& basin : list_of_basins )
			{
				if ( basin.first == basin_location )
				{
					basin.second++;
					number_of_spaces++;
					std::cout << number_of_spaces << " " << i<< ","<<j << std::endl;
					added = true;
				}
			}

			if ( !added )
			{
				list_of_basins.push_back( std::make_pair( basin_location, 1 ) );
			}

		}
	}

	std::sort( list_of_basins.begin(), list_of_basins.end(), []( std::pair<std::pair<int, int>, int>& a, std::pair<std::pair<int, int>, int>& b ) { return a.second > b.second; } );

	for ( int i = 0; i < 3; i++ )
	{
		running_total *= list_of_basins.at(i).second;
	}

	return running_total;

}

char get_matching_char( char character )
{
	switch ( character )
	{
	case ')':
		return '(';
	case '}':
		return '{';
	case ']':
		return '[';
	case '>':
		return '<';
	case '(':
		return ')';
	case '{':
		return '}';
	case '[':
		return ']';
	case '<':
		return '>';
	}

	return ' ';
}

char get_last_unclosed_opening_char( std::vector<char> input )
{
	std::vector<char> chars_to_skip;

	for ( int i = input.size(); i-- > 0; )
	{
		auto character = input.at( i );

		std::vector<char>::iterator position = std::find( chars_to_skip.begin(), chars_to_skip.end(), character );
		if ( position != chars_to_skip.end() ) // == myVector.end() means the element was not found
		{
			chars_to_skip.erase( position );
			continue;
		}

		if ( character == '(' || character == '{' || character == '[' || character == '<' )
		{
			return character;
		}

		chars_to_skip.push_back( get_matching_char( character ) );
	}
	return ' ';
}

long long puzzle_ten()
{
	std::ifstream infile( "input_puzzle_ten.txt" );
	std::vector<long long> scores;
	std::string read_line;
	char read_char;
	int line = 0;

	while ( std::getline( infile, read_line ) )
	{   // get a whole line
		std::vector<char> row;
		std::stringstream whole_line( read_line );
		bool error{};
		long long score = 0;
		int next_score = 0;
		while ( whole_line.get( read_char ) && !error )
		{
			if ( read_char == '(' || read_char == '{' || read_char == '[' || read_char == '<' )
			{
				//nice!
			}
			else
			{
				auto last_opening_char = get_last_unclosed_opening_char( row );
				error = last_opening_char != get_matching_char( read_char );

			}

			row.push_back( read_char );
		}

		if ( error )
		{
			//score += next_score;
		}
		else
		{
			while ( auto next_char = get_last_unclosed_opening_char( row ) ) 
			{
				if ( next_char == ' ' )
				{
					break;
				}

				switch ( next_char )
				{
				case '(':
					next_score = 1;
					break;
				case '{':
					next_score = 3;
					break;
				case '[':
					next_score = 2;
					break;
				case '<':
					next_score = 4;
					break;
				}

				row.push_back( get_matching_char( next_char ) );

				score *= 5;
				score += next_score;
			}
			scores.push_back( score );
		}
		line++;
		std::cout << line << ", " << score << std::endl;
	}

	std::sort( scores.begin(), scores.end() );

	return scores.at(scores.size()/2);

}

int do_flash( std::pair<int, int> coord, std::vector<std::vector<int>>& grid )
{
	std::vector<std::pair<int, int>> nearby_octopi;

	bool left{}, right{};

	if ( coord.first > 0 )
	{
		nearby_octopi.emplace_back( coord.first - 1, coord.second );
		left = true;
	}
	if ( coord.first < grid.size()-1)
	{
		nearby_octopi.emplace_back( coord.first + 1, coord.second );
		right= true;
	}
	if ( coord.second > 0 )
	{
		nearby_octopi.emplace_back( coord.first, coord.second -1);
		if ( left )
		{
			nearby_octopi.emplace_back( coord.first-1, coord.second - 1 );
		}
		if ( right )
		{
			nearby_octopi.emplace_back( coord.first + 1, coord.second - 1 );
		}
	}
	if ( coord.second < grid.size()-1)
	{
		nearby_octopi.emplace_back( coord.first, coord.second + 1 );
		if ( left )
		{
			nearby_octopi.emplace_back( coord.first - 1, coord.second + 1 );
		}
		if ( right )
		{
			nearby_octopi.emplace_back( coord.first + 1, coord.second + 1 );
		}
	}


	int flashes = 1;

	for ( auto nearby : nearby_octopi )
	{
		grid.at( nearby.first ).at( nearby.second )++;

		if ( grid.at( nearby.first ).at( nearby.second ) == 10 )
		{
			flashes += do_flash( nearby, grid );
		}
	}

	return flashes;
}

std::vector<std::vector<int>> create_random_grid( int N )
{
	std::vector<std::vector<int>> output;

	for ( int i = 0; i < N; i++ )
	{
		std::vector<int> row;

		for ( int j = 0; j < N; j++ )
		{
			std::random_device dev;
			std::mt19937 rng( dev() );
			std::uniform_int_distribution<std::mt19937::result_type> dist6( 0, 9 ); // distribution in range [1, 6]

			row.push_back( dist6( rng ) );
		}

		output.push_back( row );
	}

	return output;
}


int puzzle_eleven()
{
	auto input = read_digit_grid( "input_puzzle_eleven.txt" );
	input = create_random_grid( 40 );

	constexpr int steps = 1000;
	int flashes_this_step = 0;

	auto print_lambda = [&input]( int step, int count )
	{
		system( "cls" );
		// print the grid so I can debug it
		std::cout << step <<", "<<count<< std::endl;
		bool print_nums = false;
		for ( int x = 0; x < input.size(); x++ )
		{
			auto& row = input.at( x );
			for ( int y = 0; y < row.size(); y++ )
			{
				auto& octopus = row.at( y );

				if ( print_nums )
				{
					if ( octopus > 9 )
					{
						std::cout << '0';
					}
					else
					{
						std::cout << octopus;
					}
				}
				else if ( octopus <= 3 )
				{
					std::cout << '.';
				}
				else if ( octopus <= 9 )
				{
					std::cout << '_';
				}
				else
				{
					std::cout << 'O';
				}
			}
			std::cout << std::endl;
		}

		if ( print_nums )
		{
			getchar();
		}
		else
		{
			std::this_thread::sleep_for( std::chrono::milliseconds( 35 ) );
		}
	};

	int i=0;
	for (  i = 0; i < steps ; i++ )
	{
		flashes_this_step = 0;
		// go through the whole grid, increasing the energy level of every octopus by 1
		for ( int x = 0; x < input.size(); x++ )
		{
			auto& row = input.at( x );
			for ( int y = 0; y < row.size(); y++ )
			{
				auto& octopus = row.at( y );

				if ( octopus > 9 )
				{
					octopus = 0;
				}
			}
		}

		for ( int x = 0; x<input.size(); x++)
		{
			auto& row = input.at( x );
			for ( int y = 0; y < row.size(); y++ )
			{
				auto& octopus = row.at( y );

				octopus++;
				if ( octopus == 10 )
				{
					flashes_this_step += do_flash( std::make_pair( x, y ), input );
				}
			}
		}
		print_lambda( i, flashes_this_step );
	}

	return i;
}

int get_number_of_paths_to_end( std::string start_point, const std::vector<std::pair<std::string, std::string>>& map, std::vector<std::string> banned_locations, std::vector<std::string> previous_locations, bool have_used_double_step )
{	
	// from the start point look for every neighboring cell, and just call this again
	int running_total = 0;

	if ( start_point == "end" )
	{
		for ( auto location : previous_locations )
		{
			//std::cout << location << " -> ";
		}

		//std::cout << start_point << std::endl;

		return 1;
	}

	previous_locations.push_back( start_point );

	if ( !isupper( start_point[0] ) )
	{
		banned_locations.push_back( start_point );
	}

	for ( auto connection : map )
	{
		std::string end_point;

		if ( connection.first == start_point )
		{
			end_point = connection.second;
		}
		else if ( connection.second == start_point )
		{
			end_point = connection.first;
		}
		else
		{
			continue;
		}

		bool this_step_is_the_double_step{};

		if ( std::find( banned_locations.begin(), banned_locations.end(), end_point ) != banned_locations.end() )
		{
			if ( have_used_double_step || end_point == "start" )
			{
				continue;
			}

			this_step_is_the_double_step = true;
		}

		running_total += get_number_of_paths_to_end( end_point, map, banned_locations, previous_locations, this_step_is_the_double_step || have_used_double_step );
	}

	return running_total;
}

int puzzle_twelve()
{
	std::ifstream infile( "input_puzzle_twelve.txt" );
	std::vector<std::pair<std::string, std::string>> map;
	std::string read_line;
	std::string read_location;

	while ( std::getline( infile, read_line ) )
	{   // get a whole line
		std::stringstream ss1( read_line );
		std::pair<std::string, std::string> map_pair;

		std::getline( ss1, map_pair.first, '-' );
		std::getline( ss1, map_pair.second, '-' );

		map.push_back( map_pair );
	}

	std::vector<std::string> empty_vector;
	int number_of_paths = get_number_of_paths_to_end( "start", map, empty_vector, empty_vector, false );

	return number_of_paths;
}

int puzzle_thirteen()
{
	std::ifstream infile( "input_puzzle_thirteen.txt" );
	std::vector<std::vector<bool>> map;
	std::string read_line;
	std::string read_location;

	while ( std::getline( infile, read_line ) )
	{   // get a whole line
		if ( read_line.empty() )
		{
			break;
		}

		std::stringstream ss1( read_line );
		std::string x_s, y_s;

		std::getline( ss1, x_s, ',' );
		std::getline( ss1, y_s, ',' );

		int x{ stoi( x_s ) };
		int y{ stoi( y_s ) };

		if ( x+1 > map.size() )
		{
			map.resize( x+1 );
		}

		auto& row = map.at( x );

		if ( y+1 > row.size() )
		{
			row.resize( y+1 );
		}

		row.at( y ) = true;
	}

	// now read the folds
	std::vector<std::pair< bool, int>> folds;
	while ( std::getline( infile, read_line ) )
	{   
		std::stringstream ss1( read_line );
		std::string axis_section, number_section;

		std::getline( ss1, axis_section, '=' );
		std::getline( ss1, number_section, '=' );

		int number{ stoi( number_section ) };

		bool x_axis = axis_section.back() == 'x';

		folds.emplace_back( x_axis, number );
	}

	auto result_lambda = [&map]()
	{
		int number_of_points = 0;

		for ( auto row : map )
		{
			for ( auto square : row )
			{
				if ( square )
				{
					number_of_points++;
					std::cout << "#";
				}
				else
				{
					std::cout << ' ';
				}
			}
			std::cout << std::endl;
		}

		return number_of_points;
	};
	
	auto apply_fold_lambda = [&map]( std::pair<bool, int> input )
	{
		int number_of_points = 0;

		int start_x = input.first ? input.second : 0;
		int start_y = input.first ? 0 : input.second;

		for ( int i = start_x; i < map.size();i++ )
		{
			auto& row = map.at( i );

			for ( int j = start_y; j < row.size(); j++ )
			{
				if ( row.at( j ) )
				{
					// any dot we see is fine to move
					int x{ i }, y{j};
					if ( input.first )
					{
						// folding along x=n
						x = input.second - (x - input.second);
					}
					else
					{
						// folding along y=n
						y = input.second - (y - input.second);
					}

					auto& new_row = map.at( x );
					if ( new_row.size() < y + 1 )
					{
						new_row.resize( y + 1 );
					}

					new_row.at( y ) = true;
					row.at( j ) = false;
				}
			}

			if ( !input.first )
			{
				row.resize( input.second );
			}
		}

		if ( input.first )
		{
			map.resize( input.second );
		}

		return number_of_points;
	};

	for ( auto fold : folds )
	{
		apply_fold_lambda( fold );
	}

	return result_lambda();
}

long long puzzle_fourteen()
{
	std::ifstream infile( "input_puzzle_fourteen.txt" );
	std::string template_string;
	std::vector < std::pair<std::string, char>> instructions;
	std::vector < std::pair<std::string, unsigned long long>> pairs_in_template;
	std::string read_line;
	std::string read_location;

	std::getline( infile, template_string );
	while ( std::getline( infile, read_line ) )
	{   // get a whole line
		if ( read_line.empty() )
		{
			continue;
		}

		char first_char = read_line[0];
		char second_char = read_line[1];
		char insertion_char = read_line.back();

		std::string pair_string;
		pair_string.push_back( first_char );
		pair_string.push_back( second_char );

		instructions.emplace_back( pair_string, insertion_char );
		pairs_in_template.emplace_back( pair_string, 0 );
	}

	const char start = template_string.front();
	const char end = template_string.back();

	// then count each pair in the template string
	for ( int j = 0; j < template_string.size() - 1; j++ )
	{
		char first_char = template_string[j];
		char second_char = template_string[j + 1];
		std::string test_pair_string;
		test_pair_string.push_back( first_char );
		test_pair_string.push_back( second_char );

		auto iter = std::find_if( pairs_in_template.begin(), pairs_in_template.end(), [test_pair_string]( std::pair<std::string, unsigned long long>& test ) { return test.first == test_pair_string; } );
		if ( iter != pairs_in_template.end() )
		{
			int index = std::distance( pairs_in_template.begin(), iter );
			pairs_in_template.at( index ).second++;
		}
	}

	auto get_answer = [&]()
	{
		std::vector<std::pair<char, unsigned long long>> counts;
		for ( auto pair : pairs_in_template )
		{
			for ( auto character : pair.first )
			{
				auto iter = std::find_if( counts.begin(), counts.end(), [character]( std::pair<char, unsigned long long>& test ) { return test.first == character; } );
				if ( iter == counts.end() )
				{
					// add it it!
					counts.emplace_back( character, pair.second );
				}
				else
				{
					int index = std::distance( counts.begin(), iter );
					counts.at( index ).second += pair.second;
				}
			}
		}


		auto iter = std::find_if( counts.begin(), counts.end(), [start]( std::pair<char, unsigned long long>& test ) { return test.first == start; } );
		int index = std::distance( counts.begin(), iter );
		counts.at( index ).second++;
		iter = std::find_if( counts.begin(), counts.end(), [end]( std::pair<char, unsigned long long>& test ) { return test.first == end; } );
		index = std::distance( counts.begin(), iter );
		counts.at( index ).second++;

		std::sort( counts.begin(), counts.end(), []( std::pair<char, unsigned long long>& a, std::pair<char, unsigned long long>& b ) { return a.second > b.second; } );

		return (counts.front().second - counts.back().second) / 2;
	};

	// now that we have a list of the pairs, go through them swapping for two other pairs

	const int number_steps = 40;
	for ( int i = 0; i < number_steps; i++ )
	{
		std::vector<std::pair<std::string, unsigned long long>> new_template_pairs;
		for ( int j = 0; j < pairs_in_template.size(); j++ )
		{
			// find the insertion for this pair
			auto pair = pairs_in_template.at( j ).first;
			auto iter = std::find_if( instructions.begin(), instructions.end(), [pair]( std::pair<std::string, char>& test ) { return test.first == pair; } );
			if ( iter != instructions.end() )
			{
				int index = std::distance( instructions.begin(), iter );
				const char insertion_char = instructions.at( index ).second;

				std::string first_string, second_string;
				first_string.push_back( pair.front() );
				first_string.push_back( insertion_char );
				second_string.push_back( insertion_char );
				second_string.push_back( pair.back() );

				auto string_iter = std::find_if( new_template_pairs.begin(), new_template_pairs.end(), [first_string]( std::pair<std::string, unsigned long long> test ) { return test.first == first_string; } );
				if ( string_iter == new_template_pairs.end() )
				{
					new_template_pairs.emplace_back( first_string, pairs_in_template.at( j ).second );
				}
				else
				{
					index = std::distance( new_template_pairs.begin(), string_iter );
					new_template_pairs.at( index ).second += pairs_in_template.at( j ).second;
				}

				string_iter = std::find_if( new_template_pairs.begin(), new_template_pairs.end(), [second_string]( std::pair<std::string, unsigned long long> test ) { return test.first == second_string; } );
				if ( string_iter == new_template_pairs.end() )
				{
					new_template_pairs.emplace_back( second_string, pairs_in_template.at( j ).second );
				}
				else
				{
					index = std::distance( new_template_pairs.begin(), string_iter );
					new_template_pairs.at( index ).second += pairs_in_template.at( j ).second;
				}
			}
		}
		std::cout << get_answer() << std::endl;
		pairs_in_template = new_template_pairs;
	}

	return get_answer();
}

int brute_force_route_search( std::pair<int, int> yx_start, std::vector<std::vector<int>> map_tile, std::vector<std::vector<int>>& wip_map, std::vector<std::pair<int, int>> route_map, int cutoff_risk, int running_risk, const int horizon_distance )
{
	// if we already know the distance from this cell, just return that
	if ( wip_map.at( yx_start.first ).at( yx_start.second ) != -1 )
	{
		return wip_map.at( yx_start.first ).at( yx_start.second );
	}

	route_map.push_back( yx_start );
	int offset = ((int)yx_start.first / map_tile.size() + (int)yx_start.second / map_tile.size());
	int risk_of_entering_this_square = (map_tile.at( yx_start.first % map_tile.size() ).at( yx_start.second % map_tile.size() ) + offset) % 9;
	if ( risk_of_entering_this_square == 0 )
	{
		risk_of_entering_this_square = 9;
	}

	running_risk += risk_of_entering_this_square;
	const int min_distance_to_horizon = horizon_distance - (yx_start.first + yx_start.second);

	if ( running_risk + min_distance_to_horizon > cutoff_risk && cutoff_risk != -1 )
	{
		return -1;
	}

	// otherwise check all adjacent spaces and return the lowest
	std::vector<std::pair<int, int>> adj_cells;
	if ( yx_start.second < wip_map.size() - 1 )
	{
		adj_cells.emplace_back( yx_start.first, yx_start.second + 1 );
	}
	if ( yx_start.first < wip_map.size() - 1 )
	{
		adj_cells.emplace_back( yx_start.first + 1, yx_start.second );
	}
	if ( yx_start.first > 0 )
	{
		adj_cells.emplace_back( yx_start.first - 1, yx_start.second );
	}
	if ( yx_start.second > 0 )
	{
		adj_cells.emplace_back( yx_start.first, yx_start.second - 1 );
	}


	int shortest_route = -1;

	// the maximum number of risk it could take is 9 times the spaces remaining
	int max_risk = 9 * (wip_map.size() - yx_start.first) + 9 * (wip_map.size() - yx_start.second);
	if (max_risk < cutoff_risk)
	{
		cutoff_risk = max_risk;
	}

	for ( auto cell : adj_cells )
	{
		if ( std::find( route_map.begin(), route_map.end(), cell ) != route_map.end() )
		{
			// don't double back
			continue;
		}

		int offset = ((int)cell.first / map_tile.size() + (int)cell.second / map_tile.size());
		int risk_of_entering_that_square = (map_tile.at( cell.first % map_tile.size() ).at( cell.second % map_tile.size() ) + offset) % 9;
		if ( risk_of_entering_that_square == 0 )
		{
			risk_of_entering_that_square = 9;
		}

		auto route = brute_force_route_search( cell, map_tile, wip_map, route_map, cutoff_risk, running_risk, horizon_distance );
		if ( route == -1 )
		{
			continue;
		}

		route += risk_of_entering_that_square;
		if ( route < shortest_route || shortest_route == -1 )
		{
			shortest_route = route;

			if ( cutoff_risk > route )
			{
				cutoff_risk = route;
			}
		}
	}

	return shortest_route;
}

int puzzle_fifteen()
{
	auto input = read_digit_grid("input_puzzle_fifteen.txt");
	const int input_full_size = input.size() * 5;
	const int input_old_size = input.size();
	
	// create a copy of the map which instead contains the minimum risk from a space to the finish
	auto integrated_map = input;
	integrated_map.resize( input_full_size );
	for ( auto& row : integrated_map )
	{
		row.resize( input_full_size );
		for ( auto& cell : row )
		{
			cell = -1;
		}
	}

	integrated_map.back().back() = 0;

	//return brute_force_route_search( std::make_pair( 0, 0 ), input, integrated_map, std::vector<std::pair<int, int>>{}, 100, 0 );

	bool keep_going = true;
	int xy_sum = input_full_size * 2;
	int lowest_risk_this_loop = -1;

	while ( xy_sum >0 )
	{
		xy_sum -= 1;
		int lowest_risk_loop_before = lowest_risk_this_loop;
		int max_risk = lowest_risk_loop_before + 9;
		lowest_risk_this_loop = -1;
		std::cout << xy_sum<<", "<<max_risk<<", " << lowest_risk_loop_before << std::endl;

		for ( int y = 0; y < integrated_map.size(); y++ )
		{
			auto row = integrated_map.at( y );

			for ( int x = xy_sum-y; x < row.size(); x++ )
			{
				if ( x + y != xy_sum )
				{
					// only consider the diagonal we care about on this loop
					break;
				}


				int value = brute_force_route_search( std::make_pair( y, x ), input, integrated_map, std::vector<std::pair<int, int>>{}, max_risk, lowest_risk_loop_before, xy_sum );
				integrated_map.at( y ).at( x ) = value;
				if ( value < lowest_risk_this_loop || lowest_risk_this_loop == -1 )
				{
					lowest_risk_this_loop = value;
				}
			}
		}

// 		for ( auto row : integrated_map )
// 		{
// 			for ( auto cell : row )
// 			{
// 				std::cout << std::setw( 4 );
// 				std::cout << cell;
// 			}
// 
// 			std::cout << std::endl;
// 		}
	}

	return integrated_map.at( 0 ).at(0);
}

std::string decode_packet( std::string whole_packet )
{
	std::string output;

	for ( auto symbol : whole_packet )
	{
		switch ( symbol )
		{
		case '0':
			output += "0000";
			break;
		case '1':
			output += "0001";
			break;
		case '2':
			output += "0010";
			break;
		case '3':
			output += "0011";
			break;
		case '4':
			output += "0100";
			break;
		case '5':
			output += "0101";
			break;
		case '6':
			output += "0110";
			break;
		case '7':
			output += "0111";
			break;
		case '8':
			output += "1000";
			break;
		case '9':
			output += "1001";
			break;
		case 'A':
			output += "1010";
			break;
		case 'B':
			output += "1011";
			break;
		case 'C':
			output += "1100";
			break;
		case 'D':
			output += "1101";
			break;
		case 'E':
			output += "1110";
			break;
		case 'F':
			output += "1111";
			break;
		}
	}

	return output;
}

long long read_packet( std::string& packet )
{
	int this_packet_versions = 0;
	for ( int i = 0; i < 3; i++ )
	{
		if ( packet[i] == '1' )
		{
			this_packet_versions += std::pow( 2, 2 - i );
		}
	}

	auto type_string = packet.substr( 3, 3 );
	int type = stoi( type_string, 0, 2 );

	if ( type == 4 )
	{
		// read the number so that we know where the packet ends
		int end_of_packet = 0;
		std::string value_string;
		for ( int i = 0; i < packet.length(); i += 5 )
		{
			value_string += packet.substr( i + 7, 4 );

			char bit = packet[i + 6];
			if ( i % 5 == 0 && bit == '0' )
			{
				end_of_packet = i + 11;
				break;
			}
		}

		packet = packet.substr( end_of_packet );
		// number packets don't contain other packets so we're done!
		return stoll(value_string, 0, 2);
	}

	// length in bits or packets?
	int number_of_bits = -1;
	int number_of_packets = -1;
	const bool uses_bit_length_mode = packet[6] == '0';
	int contents_start = 0;
	if ( uses_bit_length_mode )
	{
		auto length_substring = packet.substr( 7, 15 );
		number_of_bits = stoi( length_substring, 0, 2 );
		contents_start = 7 + 15;
	}
	else
	{
		auto length_substring = packet.substr( 7, 11 );
		number_of_packets = stoi( length_substring, 0, 2 );
		contents_start = 7 + 11;
	}

	auto contents_string = packet.substr( contents_start );
	auto length_remaining = contents_string.length();
	std::vector<long long> inner_values;
	while ( number_of_bits!= 0 && number_of_packets!=0 )
	{
		inner_values.push_back (read_packet( contents_string ));
		number_of_packets--;
		number_of_bits -= (length_remaining - contents_string.length());
		length_remaining = contents_string.length();
	}

	long long value = 0;

	// and apply the operation
	switch ( type )
	{
	case 0:
		// sum
		for ( auto& subpacket : inner_values )
		{
			value += subpacket;
		}
		break;
	case 1:
		// product
		value = 1;
		for ( auto& subpacket : inner_values )
		{
			value *= subpacket;
		}
		break;
	case 2:
		// minimum
		std::sort( inner_values.begin(), inner_values.end() );
		value = inner_values.front();
		break;
	case 3:
		// maximum
		std::sort( inner_values.begin(), inner_values.end() );
		value = inner_values.back();
		break;
	case 5:
		// greater
		value = inner_values.front() > inner_values.back();
		break;
	case 6:
		// lesser
		value = inner_values.front() < inner_values.back();
		break;
	case 7:
		// equal
		value = inner_values.front() == inner_values.back();
		break;
	}

	packet = contents_string;

	return value;
}

long long puzzle_sixteen()
{
	std::ifstream infile( "input_puzzle_sixteen.txt" );
	std::string read_line;

	while (std::getline( infile, read_line ) )
	{
		std::stringstream ss1( read_line );

		auto decoded_packet = decode_packet( read_line );

		long long value = read_packet( decoded_packet );

		std::cout << value << std::endl;
	}

	return 1;

}

int puzzle_seventeen()
{
	FILE* fp;

	fopen_s( &fp, "input_puzzle_seventeen.txt", "r" );

	int x1{0}, x2{ 0 }, y1{ 0 }, y2{ 0 };
	fscanf_s( fp, "target area: x=%d..%d, y=%d..%d", &x1, &x2, &y1, &y2 );
	fclose( fp );

	int max_height = 0;
	int number_of_routes = 0;

	for ( int initial_xv = 1; initial_xv <= x2; initial_xv++ )
	{
		for ( int initial_yv = y1; initial_yv <= -y1; initial_yv++ )
		{
			int xv{ initial_xv }, yv{ initial_yv };
			int x_pos{ 0 }, y_pos{ 0 };

			while ( x_pos <= x2 && y_pos >= y1 )
			{
				// are we at the target yet?
				if ( x_pos >= x1 && y_pos <= y2 )
				{
					int max_height_for_this_flight = 0;
					for ( int i = 0; i <= initial_yv; i++ )
					{
						max_height_for_this_flight += i;
					}

					if ( max_height_for_this_flight > max_height )
					{
						max_height = max_height_for_this_flight;
					}

					std::cout << initial_xv << ", " << initial_yv << " : " << max_height_for_this_flight << std::endl;
					number_of_routes++;

					break;
				}

				x_pos += xv;
				y_pos += yv;

				if ( xv > 0 )
				{
					xv--;
				}
				else if ( xv < 0 )
				{
					xv++;
				}

				yv--;
			}
		}
	}

	return number_of_routes;
}

typedef std::vector<std::pair<int, int>> SNAILFISH_NUMBER;

int get_magnitude( SNAILFISH_NUMBER number )
{
	while ( number.size() > 1 )
	{
		// find the left-most deepest number, replace it and the next number with a number
		int depth = 0;
		for ( auto element : number )
		{
			if ( element.second > depth )
			{
				depth = element.second;
			}
		}

		int i = 0;
		for ( i=0; i < number.size() - 1; i++ )
		{
			if ( number.at( i ).second == depth )
			{
				number.at( i ).first *= 3;
				number.at( i ).first += number.at( i + 1 ).first * 2;

				number.at( i ).second--;
				break;
			}
		}

		number.erase( number.begin() + i + 1 );
	}

	return number.front().first;
}

SNAILFISH_NUMBER add_snailfish_numbers( SNAILFISH_NUMBER a, SNAILFISH_NUMBER b )
{
	// append it
	a.insert( a.end(), b.begin(), b.end() );

	// and increment the depth of every element
	for ( auto& element : a )
	{
		element.second++;
	}

	bool keep_reducing{ true };
	while ( keep_reducing )
	{
		keep_reducing = false;

		int explosions = 0;

		// check for explosions at depth 4
		for ( int j = 0; j < a.size(); j++ )
		{
			auto& element = a.at( j );
			if ( element.second > 4 )
			{
				keep_reducing = true;
				explosions++;
				if ( explosions == 1 )
				{
					// look left to add this number
					if ( j > 0 )
					{
						a.at( j - 1 ).first += element.first;
					}

					element.first = 0;
					element.second--;
				}
				if ( explosions == 2 )
				{
					// look right to add this number
					if ( j < a.size() - 1 )
					{
						a.at( j + 1 ).first += element.first;
					}

					// and remove this element
					a.erase( a.begin() + j );
					break;
				}
			}
		}

		if ( explosions == 0 )
		{
			// check splits at value 10+
			for ( int j = 0; j < a.size(); j++ )
			{
				auto& element = a.at( j );
				if ( element.first >= 10 )
				{
					element.second++;
					if ( element.first % 2 == 0 )
					{
						element.first /= 2;
						a.insert( a.begin() + j, element );
					}
					else
					{
						element.first /= 2;
						std::pair<int, int> new_element = element;
						new_element.first++;
						a.insert( a.begin() + j + 1, new_element );
					}

					keep_reducing = true;
					break;
				}
			}
		}
	}

	return a;
}

int puzzle_eighteen()
{
	std::ifstream infile( "input_puzzle_eighteen.txt" );
	std::vector<SNAILFISH_NUMBER> snail_numbers;
	std::string read_line;

	while ( std::getline( infile, read_line ) )
	{
		SNAILFISH_NUMBER snail_number;
		// each line is a snail_number
		std::stringstream line_stream( read_line );
		char read_char;
		int depth = 0;
		while ( line_stream.get( read_char ) )
		{
			if ( read_char == '[' )
			{
				// next element is 1 layer deeper
				depth++;
			}
			else if ( read_char == ']' )
			{
				// next element is one layer shallower
				depth--;
			}
			else if ( read_char == ',' )
			{
				continue;
			}
			else
			{
				// it's a number so add it to the snailnum
				snail_number.emplace_back( (int)read_char - '0', depth );
			}
		}

		snail_numbers.push_back( snail_number );
	}

	// now try every i,j combination of addition
	int best_result = 0;
	for ( int i = 0; i < snail_numbers.size(); i++ )
	{
		for ( int j = 0; j < snail_numbers.size(); j++ )
		{
			if ( i != j )
			{
				int this_pair_result = get_magnitude( add_snailfish_numbers( snail_numbers.at( i ), snail_numbers.at( j ) ));
				std::cout << this_pair_result << std::endl;
				if ( this_pair_result > best_result )
				{
					best_result = this_pair_result;
				}
			}
		}
	}

	return best_result;
}

enum ROTATION_INDEX
{
	R012, 
	R021,
	R120,
	R102, 
	R201, 
	R210
};

enum INVERSION_INDEX
{
	INONE,
	IX,
	IXY,
	IY,
	IYZ,
	IZ,
	IZX,
	IXYZ
};

std::vector<int> get_rotated_beacon( std::vector<int> beacon, ROTATION_INDEX rotation, INVERSION_INDEX inversion )
{
	std::vector<int> return_vector=beacon;
	
	switch ( rotation )
	{
	case R021:
		{
			return_vector.at( 2 ) = beacon.at( 1 );
			return_vector.at( 1 ) = beacon.at( 2 );
		}
		break;
	case R102:
		{
			return_vector.at( 0 ) = beacon.at( 1 );
			return_vector.at( 1 ) = beacon.at( 0 );
		}
		break;
	case R120:
		{
			return_vector.at( 0 ) = beacon.at( 1 );
			return_vector.at( 1 ) = beacon.at( 2 );
			return_vector.at( 2 ) = beacon.at( 0 );
		}
		break;
	case R201:
		{
			return_vector.at( 0 ) = beacon.at( 2 );
			return_vector.at( 1 ) = beacon.at( 0 );
			return_vector.at( 2 ) = beacon.at( 1 );
		}
		break;
	case R210:
		{
			return_vector.at( 0 ) = beacon.at( 2 );
			return_vector.at( 2 ) = beacon.at( 0 );
		}
		break;
	}

	// and now invert
	switch ( inversion )
	{
	case IXY:
		return_vector.at( 0 ) *= -1;
		return_vector.at( 1 ) *= -1;
		break;
	case IYZ:
		return_vector.at( 2 ) *= -1;
		return_vector.at( 1 ) *= -1;
		break;
	case IZX:
		return_vector.at( 0 ) *= -1;
		return_vector.at( 2 ) *= -1;
		break;
	case IX:
		return_vector.at( 0 ) *= -1;
		break;
	case IY:
		return_vector.at( 1 ) *= -1;
		break;
	case IZ:
		return_vector.at( 2 ) *= -1;
		break;
	case IXYZ:
		return_vector.at( 0 ) *= -1;
		return_vector.at( 1 ) *= -1;
		return_vector.at( 2 ) *= -1;
		break;
	default:
		break;
	}

	return return_vector;
}

int puzzle_nineteen()
{
	std::ifstream infile( "input_puzzle_nineteen.txt" );
	std::vector<std::vector<std::vector<int>>> scanner_list;
	std::vector<int> original_lengths;
	std::string read_line;

	std::vector<std::vector<int>> scanner;
	std::getline( infile, read_line );
	while ( std::getline( infile, read_line ) )
	{
		if ( read_line.empty() )
		{
			continue;
		}

		if ( read_line.back() == '-' )
		{
			scanner_list.push_back( scanner );
			original_lengths.push_back( scanner.size() );
			scanner.clear();
		}
		else
		{
			std::vector<int> line;
			std::stringstream line_stream( read_line );
			std::string read_num;
			while(std::getline( line_stream, read_num, ',' ) )
			{
				line.push_back( std::stoi( read_num ) );
			}

			scanner.push_back( line );
		}
	}
	scanner_list.push_back( scanner );
	original_lengths.push_back( scanner.size() );
	scanner.clear();

	std::vector<std::vector<int>> true_beacons = scanner_list.front();

	struct SCANNER_INFO
	{
		std::array<int, 3> coordinates; // relative to scanner 0
		int rotation_index; // 0-123, 1-132, 2-213, 3-231, 4-312, 5-321
		int inversions_index; // 0-none, 1-xy, 2-yz, 3-zx
	};

	std::vector<std::pair<std::vector<int>, int>> transforms;
	std::vector<int> zero_transform;
	zero_transform.push_back( 0 );
	zero_transform.push_back( 0 );
	zero_transform.push_back( 0 );
	transforms.emplace_back( zero_transform, 0 );

	// now pair each scanner
	for ( int j = scanner_list.size(); j-->0; )
	{

		for ( int test = 0; test < 2; test++ )
		{
			bool found_match{ false };

			for ( int i =0; i<j && !found_match; i++)
			{
				if ( i == j )
				{
					continue;
				}
				//std::cout << "testing " << j << "->" << i << std::endl;

				auto& scanner_i = scanner_list.at( i );
				auto& scanner_j = scanner_list.at( j );


				int num_to_test_j = test == 0 ? 3 : scanner_j.size();
				int num_to_test_i = test == 0 ? original_lengths.at(i) : scanner_i.size();

				// now try every pair of beacons in the two scanners
				for ( int bj = 0; bj < num_to_test_j && !found_match; bj++ )
				{
					for ( int bi = 0; bi < num_to_test_i && !found_match; bi++ )
					{
						// we assume that bj and bi are the same beacons from different viewpoints, there are 48 different ways to imagine this, so make a list of them and see if any can explain 11 other beacons
						for ( int rotation_index = 0; rotation_index < 6 && !found_match; rotation_index++ )
						{
							for ( int inversion_index = 0; inversion_index < 8 && !found_match; inversion_index++ )
							{
								if ( rotation_index % 2 != inversion_index % 2 )
								{
									continue;
								}

								int j_x = scanner_j.at( bj ).front();
								if ( j_x == 577 && i == 0 )
								{
									j_x += 0;
								}

								auto beacon_j_from_i = get_rotated_beacon( scanner_j.at( bj ), (ROTATION_INDEX)rotation_index, (INVERSION_INDEX)inversion_index );

								std::vector<int> translation = beacon_j_from_i;
								for ( int t = 0; t < 3; t++ )
								{
									translation.at( t ) -= scanner_i.at( bi ).at( t );
								}

								if ( test == 0 )
								{
									if ( abs( translation.at( 0 ) ) > 2000 || abs( translation.at( 1 ) ) > 2000 || abs( translation.at( 2 ) ) > 2000 )
									{
										continue;
									}
								}

								// now we have an idea of where scanner j could be, try the same transformation on the remaining beacons from j
								int count = 0;
								std::vector<int> indices;
								for ( int obj = bj; obj < scanner_j.size(); obj++ )
								{
									//take the beacon
									auto test_beacon = scanner_j.at( obj );
									// apply the same transformations
									test_beacon = get_rotated_beacon( test_beacon, (ROTATION_INDEX)rotation_index, (INVERSION_INDEX)inversion_index );
									for ( int t = 0; t < 3; t++ )
									{
										test_beacon.at( t ) -= translation.at( t );
									}

									// and now look for this beacon in scanner_i's list
									auto iter = std::find_if( scanner_i.begin(), scanner_i.end(), [&test_beacon]( std::vector<int>& beacon ) { return beacon.at( 0 ) == test_beacon.at( 0 ) && beacon.at( 1 ) == test_beacon.at( 1 ) && beacon.at( 2 ) == test_beacon.at( 2 ); } );
									if ( iter != scanner_i.end() )
									{
										count++;
										indices.push_back( obj );
									}
								}

								if ( count >= 12 )
								{

									// done it! add every new element from scanner j to scanner i's list (after transforming)
									for ( auto element : scanner_j )
									{
										auto transformed_beacon = get_rotated_beacon( element, (ROTATION_INDEX)rotation_index, (INVERSION_INDEX)inversion_index );
										for ( int t = 0; t < 3; t++ )
										{
											transformed_beacon.at( t ) -= translation.at( t );
										}

										auto iter = std::find_if( scanner_i.begin(), scanner_i.end(), [&transformed_beacon]( std::vector<int>& beacon ) { return beacon.at( 0 ) == transformed_beacon.at( 0 ) && beacon.at( 1 ) == transformed_beacon.at( 1 ) && beacon.at( 2 ) == transformed_beacon.at( 2 ); } );
										if ( iter == scanner_i.end() )
										{
											scanner_i.push_back( transformed_beacon );
										}
									}

									found_match = true;
									std::cout << "completed " << j << "->" << i << " new size:" << scanner_i.size() << std::endl;

									transforms.emplace_back( translation, i );

									// and finally go through the existing transforms and move any from j to i
									for ( auto& transform : transforms )
									{
										if ( transform.second == j )
										{
											transform.first = get_rotated_beacon( transform.first, (ROTATION_INDEX)rotation_index, (INVERSION_INDEX)inversion_index );

											transform.second = i;
											for ( int tra = 0; tra < 3; tra++ )
											{
												transform.first.at( tra ) += translation.at( tra );
											}
										}
									}
								}
							}
						}
					}
				}
			

			}
			if ( found_match )
			{
				break;
			}
		}
		
	}

	int biggest_manhat = 0;
	for ( auto transform : transforms )
	{
		std::cout << transform.first.at( 0 ) << ", " << transform.first.at( 1 ) <<", "<< transform.first.at(2) << std::endl;
		for ( auto transform_b : transforms )
		{
			int manhat = 0;
			for ( int i = 0; i < 3; i++ )
			{
				manhat += abs( transform.first.at( i ) - transform_b.first.at( i ) );
			}

			if ( manhat > biggest_manhat )
			{
				biggest_manhat = manhat;
			}
		}
	}

	return biggest_manhat;
}

char get_pixel_value( const std::vector<std::vector<bool>>& image, int x, int y, bool brightness_outside )
{
	if ( x <= 0 || x >= image.size() -1 )
	{
		return brightness_outside? '1':'0';
	}

	auto line = image.at( x );

	if ( y <= 0 || y>= line.size() -1 )
	{
		return brightness_outside ? '1' : '0';
	}

	return line.at( y ) ? '1' : '0';
}

int puzzle_twenty()
{
	std::vector<std::vector<bool>> image;
	std::vector<bool> algorithm;

	std::ifstream infile( "input_puzzle_twenty.txt" );
	
	std::string read_line;

	std::getline( infile, read_line );
	for ( auto symbol : read_line )
	{
		if ( symbol == '.' )
		{
			algorithm.push_back( false );
		}
		else
		{
			algorithm.push_back( true );
		}
	}

	while ( std::getline( infile, read_line ) )
	{
		if ( read_line.empty() )
		{
			continue;
		}
		std::vector<bool> line;
		for ( auto symbol : read_line )
		{
			if ( symbol == '.' )
			{
				line.push_back( false );
			}
			else
			{
				line.push_back( true );
			}
		}

		image.push_back( line );
	}

	int enhancements = 50;
	int light = 0;
	int dark;
	bool infinite_brightness = false;

	for ( int i = 0; i < enhancements; i++ )
	{
		light = 0;
		dark = 0;


		// add borders to the image
		for ( auto& line : image )
		{
			line.push_back( false );
			line.emplace( line.begin(), false );
		}

		image.push_back( image.back() );
		image.emplace( image.begin(), image.front() );

		auto output_image = image;
		auto start = std::chrono::high_resolution_clock::now();

		for ( int x = 0; x<image.size(); x++ )
		{
			for ( int y = 0; y < image.at( x ).size(); y++ )
			{
				std::string binary_string;
				for ( int dx = -1; dx < 2; dx++ )
				{
					for ( int dy = -1; dy < 2; dy++ )
					{
						binary_string.push_back(get_pixel_value( image, x + dx, y + dy, infinite_brightness ));
					}
				}

				int index = std::stoi( binary_string, 0, 2 );

				output_image.at( x ).at( y ) = algorithm.at( index );
				if ( output_image.at( x ).at( y ) )
				{
					light++;
				}
				else
				{
					dark++;
				}
			}
		}

		if ( algorithm.front() )
		{
			infinite_brightness = !infinite_brightness;
		}

		std::cout <<i<<" : " << light << ", " << dark << " : " << light + dark << ", " << image.size() * image.size() << std::endl;

		image = output_image;

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << " s\n";

// 		for ( auto line : image )
// 		{
// 			for ( auto element : line )
// 			{
// 				std::cout << element ? '\#' : '\.';
// 			}
// 			std::cout << std::endl;
// 		}
// 		std::cout << std::endl << std::endl;
	}

	return light;
}

long long long_pow( int number, int exponent )
{
	long long result = 1;
	while ( exponent )
	{
		result *= number;
		exponent--;
	}

	return result;
}

long long puzzle_twentyone()
{
	std::cout << long_pow( 2, 2 ) << std::endl;
	auto start = std::chrono::high_resolution_clock::now();

	int number_rolls = 0;
	int one_score = 0;
	int two_score = 0;

	int one_pos = 10;
	int two_pos = 10;

	std::ifstream infile( "input_puzzle_twentyone.txt" );

	std::string read_line;

	std::getline( infile, read_line );
	if ( read_line.back() != '0' )
	{
		one_pos = (int)read_line.back() - '0';
	}

	std::getline( infile, read_line );
	if ( read_line.back() != '0' )
	{
		two_pos = (int)read_line.back() - '0';
	}

	auto compute_result_list = [](int starting_pos) 
	{
		auto start = std::chrono::high_resolution_clock::now();
		std::vector<std::pair<std::pair<int, int>, long long>> board_states;
		std::vector<long long> finishes;
		std::vector<long long> unfinishes;
		board_states.emplace_back( std::make_pair(0, starting_pos), 1 );
		bool keep_going = true;
		int number_rolls=0;
		while ( keep_going )
		{
			keep_going = false;
			std::vector<std::pair<std::pair<int, int>, long long>> results_after_this;
			finishes.push_back( 0 );
			unfinishes.push_back( 0 );
			for ( int j = board_states.size(); j-->0; )
			{
				auto element = board_states.at( j );

				if ( element.first.first < 21 )
				{
					keep_going = true;
					unfinishes.back() += element.second;

					for ( int x = 1; x < 4; x++ )
					{
						for ( int y = 1; y < 4; y++ )
						{
							for ( int z = 1; z < 4; z++ )
							{
								int next_pos = element.first.second + x + y + z;
								next_pos %= 10;
								if ( next_pos == 0 )
								{
									next_pos = 10;
								}

 								auto pair = std::make_pair( element.first.first + next_pos, next_pos );
 								auto iter = std::find_if( results_after_this.begin(), results_after_this.end(), [&]( std::pair<std::pair<int, int>, long long>& test ) { return test.first.first == pair.first && test.first.second == pair.second; } );

								if ( iter == results_after_this.end() )
								{
									results_after_this.push_back( std::make_pair(pair, element.second) );
								}
								else
								{
									int index = std::distance( results_after_this.begin(), iter );
									results_after_this.at( index ).second += element.second;
								}
							}
						}
					}
				}
				else
				{
					finishes.back() += element.second;
					board_states.erase( board_states.begin() + j );
				}
			}
			number_rolls++;
			board_states = std::move( results_after_this );
		}

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << " s\n";

		return std::make_pair(finishes, unfinishes);
	};

	auto one_results = compute_result_list(one_pos);
	auto two_results = compute_result_list( two_pos );

	long long universes_one = 0;
	long long universes_two = 0;

	for ( int i = 1; i < one_results.first.size(); i++ )
	{
		universes_one += one_results.first.at( i ) * two_results.second.at( i - 1 );
		universes_two += two_results.first.at( i ) * one_results.second.at( i );
	}

	std::cout << universes_one << " - " << universes_two << std::endl;
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	return universes_one;
}

int puzzle_twentytwo()
{
	std::vector<std::pair<bool, std::array<int, 6>>> instructions;
	std::ifstream infile( "input_puzzle_twentytwo.txt" );

	std::string read_line;

	while ( std::getline( infile, read_line ) )
	{
		auto start = std::chrono::high_resolution_clock::now();

		const bool switch_on = read_line[1] == 'n';

		int x1{ 0 }, x2{ 0 }, y1{ 0 }, y2{ 0 }, z1{ 0 }, z2{ 0 };

		int start_point = switch_on ? 2:3;
		const auto substring = read_line.substr( start_point );

		sscanf_s( substring.c_str(), " x=%d..%d,y=%d..%d,z=%d..%d", &x1, &x2, &y1, &y2, &z1, &z2 );

		instructions.emplace_back( switch_on, std::array<int, 6>( { x1, x2, y1, y2, z1, z2 } ) );
	}

	long long count{0};
	while ( !instructions.empty() )
	{
		// loop until we've turned every instruction into cubes numbers

		// take the first element of the instructions
		auto& instruction = instructions.front();
		bool delete_ins{false};
		if ( instruction.first )
		{
			long long x_size = 1 + instruction.second[1] - instruction.second[0];
			long long y_size = 1 + instruction.second[3] - instruction.second[2];
			long long z_size = 1 + instruction.second[5] - instruction.second[4];
			long long total_size = x_size * y_size * z_size;

			// if it's an ON then continue through the instructions until it overlaps with any other instruction
			for ( int i = 1; i < instructions.size(); i++ )
			{
				const auto& later_instruction = instructions.at(i);

				int overlap_x = 1 + std::min( instruction.second[1], later_instruction.second[1] ) - std::max( instruction.second[0], later_instruction.second[0] );
				int overlap_y = 1 + std::min( instruction.second[3], later_instruction.second[3] ) - std::max( instruction.second[2], later_instruction.second[2] );
				int overlap_z = 1 + std::min( instruction.second[5], later_instruction.second[5] ) - std::max( instruction.second[4], later_instruction.second[4] );

				if ( overlap_x > 0 && overlap_y > 0 && overlap_z > 0 )
				{
					total_size = 0;
					if ( overlap_x < x_size )
					{
						// partial overlap on x so split into two cuboids based on overlap/no overlap
						int split = instruction.second[0] < later_instruction.second[0] ? later_instruction.second[0] - 1: later_instruction.second[1];

						auto new_instruction = instruction;
						new_instruction.second[0] = split + 1;
						instruction.second[1] = split;

						instructions.emplace( instructions.begin(), new_instruction );
					}
					else if ( overlap_y < y_size )
					{
						// partial overlap on y so split into two cuboids based on overlap/no overlap
						int split = instruction.second[2] < later_instruction.second[2] ? later_instruction.second[2] - 1: later_instruction.second[3];

						auto new_instruction = instruction;
						new_instruction.second[2] = split + 1;
						instruction.second[3] = split;

						instructions.emplace( instructions.begin(), new_instruction );
					}
					else if ( overlap_z < z_size )
					{
						// partial overlap on z so split into two cuboids based on overlap/no overlap
						int split = instruction.second[4] < later_instruction.second[4] ? later_instruction.second[4] - 1: later_instruction.second[5];

						auto new_instruction = instruction;
						new_instruction.second[4] = split + 1;
						instruction.second[5] = split;

						instructions.emplace( instructions.begin(), new_instruction );
					}
					else
					{
						// total overlap, just delete the instruction
						delete_ins = true;
					}
					break;
				}
			}

			if ( total_size )
			{
				count += total_size;
				std::cout << count << " - " << instructions.size() << std::endl;
				delete_ins = true;
			}
		}
		else
		{
			delete_ins = true;
		}

		if ( delete_ins )
		{
			instructions.erase( instructions.begin() );
		}
	}

	return count;
}

std::vector<int> get_journey_spaces( int a, int b )
{
	if ( a < 0 )
	{
		return get_journey_spaces( b, a );
	}

	auto start_room = a % 4;

	std::vector<int> result;

	switch ( b )
	{
	case -1:
		{
			result.push_back( -1 );
			result.push_back( -2 );
			result.push_back( -10 );

			if ( start_room > 0 )
			{
				result.push_back( -3 );
				result.push_back( -10 );
			}
			if ( start_room > 1 )
			{
				result.push_back( -4 );
				result.push_back( -10 );
			}
			if ( start_room > 2 )
			{
				result.push_back( -5 );
				result.push_back( -10 );
			}
		}
		break;
	case -2:
		{
			result.push_back( -2 );
			result.push_back( -10 );

			if ( start_room > 0 )
			{
				result.push_back( -3 );
				result.push_back( -10 );
			}
			if ( start_room > 1 )
			{
				result.push_back( -4 );
				result.push_back( -10 );
			}
			if ( start_room > 2 )
			{
				result.push_back( -5 );
				result.push_back( -10 );
			}
		}
		break;
	case -3:
		{
			result.push_back( -3 );
			result.push_back( -10 );

			if ( start_room > 1 )
			{
				result.push_back( -4 );
				result.push_back( -10 );
			}
			if ( start_room > 2 )
			{
				result.push_back( -5 );
				result.push_back( -10 );
			}
		}
		break;
	case -4:
		{
			result.push_back( -4 );
			result.push_back( -10 );

			if ( start_room < 1 )
			{
				result.push_back( -3 );
				result.push_back( -10 );
			}
			if ( start_room > 2 )
			{
				result.push_back( -5 );
				result.push_back( -10 );
			}
		}
		break;
	case -5:
		{
			result.push_back( -5 );
			result.push_back( -10 );

			if ( start_room < 1 )
			{
				result.push_back( -3 );
				result.push_back( -10 );
			}
			if ( start_room < 2 )
			{
				result.push_back( -4 );
				result.push_back( -10 );
			}
		}
		break;
	case -6:
		{
			result.push_back( -6 );
			result.push_back( -10 );

			if ( start_room < 1 )
			{
				result.push_back( -3 );
				result.push_back( -10 );
			}
			if ( start_room < 2 )
			{
				result.push_back( -10 );
				result.push_back( -4 );
			}
			if ( start_room < 3 )
			{
				result.push_back( -10 );
				result.push_back( -5 );
			}
		}
		break;
	case -7:
		{
			result.push_back( -6 );
			result.push_back( -7 );
			result.push_back( -10 );

			if ( start_room < 1 )
			{
				result.push_back( -10 );
				result.push_back( -3 );
			}
			if ( start_room < 2 )
			{
				result.push_back( -10 );
				result.push_back( -4 );
			}
			if ( start_room < 3 )
			{
				result.push_back( -5 );
				result.push_back( -10 );
			}
		}
		break;
	}

	// and add the spaces inside the rooms
	while ( a >= 0 )
	{
		result.push_back( a );
		a -= 4;
	}

	return result;
}

int puzzle_twentythree()
{
	std::ifstream infile( "input_puzzle_twentythree.txt" );

	std::string read_line;

	std::vector<std::pair<int, int>> pieces_and_locations; // first is the piece (A-0...D-3), second is location (Atop-0, Btop-1...)
	int location = 0;

	while ( std::getline( infile, read_line ) )
	{
		for ( auto symbol : read_line )
		{
			switch ( symbol )
			{
			case 'A':
				pieces_and_locations.emplace_back( 0, location );
				location++;
				break;
			case 'B':
				pieces_and_locations.emplace_back( 1, location );
				location++;
				break;
			case 'C':
				pieces_and_locations.emplace_back( 2, location );
				location++;
				break;
			case 'D':
				pieces_and_locations.emplace_back( 3, location );
				location++;
				break;
			}
		}
	}

	typedef std::vector<std::pair<int, int>> STATE;

	auto find_piece_at_space = []( int location, const STATE& map )
	{
		for ( auto& piece : map )
		{
			if ( piece.second == location )
				return piece.first;
		}

		return -1;
	};


	auto is_same_state = [&find_piece_at_space]( const STATE& a, const STATE& b )
	{
		for ( int i = 0; i < a.size(); i++ )
		{
			if ( find_piece_at_space(a.at(i).second, b) != a.at(i).first )
			{
				return false;
			}
		}

		return true;
	};

	auto get_lower_bound = [find_piece_at_space]( const STATE& map )
	{
		int bound = 0;
		for ( auto element : map )
		{
			// just move them directly to the end points to guess at how long this might take
			if ( element.second >= 0 )
			{
				if ( element.second % 4 == element.first )
				{
					continue;
				}

				const auto spaces_to_move_through = 2 + abs( element.second % 4 - element.first ) * 2;
				int total_cost = spaces_to_move_through * pow( 10, element.first );
				bound += total_cost;
			}
			else
			{
				const auto spaces_to_move_through = get_journey_spaces(element.second, element.first);
				int total_cost = (spaces_to_move_through.size()-1) * pow( 10, element.first );
				bound += total_cost;
			}
		}

		// also go through the deeper spaces which contain the wrong thing and add a movement for each
		for ( int i = 4; i < map.size(); i++ )
		{
			auto other_piece = find_piece_at_space( i, map );
			if ( other_piece != i % 4 )
			{
				if ( other_piece != -1 )
				{
					bound += pow( 10, other_piece ) * floor( i / 4 );
				}
				bound += pow( 10, i % 4 ) * floor(i/4);
			}
		}
		return bound;
	};

	std::vector <std::pair<STATE, std::pair<int, int>>> unvisited;
	std::vector <std::pair<STATE, std::pair<int, int>>> visited;
	unvisited.emplace_back( pieces_and_locations, std::make_pair(0, get_lower_bound(pieces_and_locations) ));
	STATE finished_puzzle;
	STATE clearfour;
	for ( int i = 0; i < pieces_and_locations.size(); i++ )
	{
		finished_puzzle.emplace_back( i%4, i );
		if ( i % 4 != 3 )
		{
			clearfour.emplace_back( pieces_and_locations.at( i ) );
		}
		else
		{
			switch ( i/4 )
			{
			case 0:
				clearfour.emplace_back( 2, -7 );
				break;
			case 1:
				clearfour.emplace_back( 0, -1 );
				break;
			case 2:
				clearfour.emplace_back( 2, -6 );
				break;
			case 3:
				clearfour.emplace_back( 0, -2 );
				break;
			}
		}
	}

	STATE clearfour_andone=clearfour;
	clearfour_andone.at( 0 ).second = 15;
	clearfour_andone.at( 4 ).second = 11;
	clearfour_andone.at( 8 ).second = 7;
	clearfour_andone.at( 12 ).second = 3;

	while ( true )
	{
		auto start = std::chrono::high_resolution_clock::now();
		std::sort( unvisited.begin(), unvisited.end(), [get_lower_bound]( std::pair<STATE, std::pair<int, int>>& a, std::pair<STATE, std::pair<int, int>>& b ) { return a.second.second < b.second.second; } );
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> sort_time = finish - start;

		STATE current_location = unvisited.front().first;

		//print_map( current_location );

		if ( is_same_state( current_location, finished_puzzle ) )
		{
			return unvisited.front().second.first;
		}

		if ( is_same_state( current_location, clearfour ) )
		{
			std::cout << "wow :" << get_lower_bound( current_location ) << std::endl;
		}

		if ( is_same_state( current_location, clearfour_andone ) )
		{
			std::cout << "wowee :" << get_lower_bound( current_location ) << std::endl;
		}

		if ( unvisited.front().second.first > 44000 )
		{
			std::cout << "wazoo :" << get_lower_bound( current_location ) << std::endl;
		}

		start = std::chrono::high_resolution_clock::now();
		std::vector <std::pair<STATE, std::pair<int, int>>> neighbours;
		bool found_best_move{};
		for ( int j = 0; j<current_location.size() && !found_best_move; j++ )
		{
			auto piece = current_location.at( j );
			// add all the possible moves for this piece onto the neighbour array
			if ( piece.second >= 0 )
			{
				if ( piece.first == piece.second % 4 )
				{
					// already in the right room, continue if there are no incorrect pieces below
					int space = piece.second + 4;
					bool already_in_correct_space = true;
					while ( space < 16)
					{
						if ( find_piece_at_space( space, current_location ) != piece.first )
						{
							already_in_correct_space = false;
						}
						space += 4;
					}

					if ( already_in_correct_space )
					{
						continue;
					}
				}

				for ( int i = -1; i > -8; i-- )
				{
					const auto spaces_to_move_through = get_journey_spaces( piece.second, i );

					bool possible = true;
					for ( auto space : spaces_to_move_through )
					{
						if ( space != piece.second && find_piece_at_space(space, current_location) != -1 )
						{
							possible = false;
						}
					}

					if ( possible )
					{
						STATE new_location = current_location;
						new_location.at( j ).second = i;
						int total_cost = unvisited.front().second.first + (spaces_to_move_through.size() - 1) * pow( 10, piece.first );
						auto pair = std::make_pair( total_cost, total_cost + get_lower_bound( new_location ) );

						int diff = pair.second - unvisited.front().second.second;
						if ( diff < 0 )
						{
							std::cout << "ERROR!" << std::endl;
							auto old_bound = get_lower_bound( current_location );
							auto new_bound = get_lower_bound( new_location );

							diff = old_bound - (spaces_to_move_through.size() - 1) * pow( 10, piece.first );
							diff = unvisited.front().second.first + old_bound;
							std::cout << diff << std::endl;
						}

						if ( pair.second < 48410 )
						{
							neighbours.push_back( std::make_pair( new_location, pair ) );
						}
					}
				}
			}
			else 
			{
				// piece is in hall, waiting to go into room
				for ( int i = 3; i >= 0; i-- )
				{
					int space = i * 4 + piece.first;
					auto piece_in_space = find_piece_at_space( space, current_location );
					if ( piece_in_space != -1 && piece_in_space != piece.first )
					{
						break;
					}
					else if ( piece_in_space == -1 )
					{
						const auto spaces_to_move_through = get_journey_spaces( piece.second, space );

						bool possible = true;
						for ( auto space : spaces_to_move_through )
						{
							if ( space != piece.second && find_piece_at_space( space, current_location ) != -1 )
							{
								possible = false;
							}
						}

						if ( possible )
						{
							STATE new_location = current_location;
							new_location.at( j ).second = space;
							int total_cost = unvisited.front().second.first + (spaces_to_move_through.size() - 1) * pow( 10, piece.first );
							int diff = total_cost - (get_lower_bound( current_location ) - get_lower_bound( new_location ));
							if ( diff < 0 )
							{
								std::cout << "ERROR!" << std::endl;
							}
							auto pair = std::make_pair( total_cost, total_cost + get_lower_bound( new_location ) );
							found_best_move = true;
							neighbours.clear();
							neighbours.push_back( std::make_pair( new_location, pair ) );
							break;
						}
					}
				}
			}
		}
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> neighbour_time = finish - start;
		start = finish;

		for ( auto element : neighbours )
		{
			bool found = false;

			if ( is_same_state( element.first, finished_puzzle ) )
			{
				std::cout << "found a solution at cost" << element.second.first << std::endl;
				get_lower_bound( element.first );
			}

			for ( auto& unvisited_location : unvisited )
			{
				// check to see if it exists already
				if ( is_same_state( element.first, unvisited_location.first ) )
				{
					unvisited_location.second.first = std::min( unvisited_location.second.first, element.second.first );
					unvisited_location.second.second = std::min( unvisited_location.second.second, element.second.second );
					found = true;
					break;
				}
			}

			if ( !found )
			{
// 				for ( auto visited_location : visited )
// 				{
// 					// check to see if it exists already
// 					if ( is_same_state( element.first, visited_location.first ) )
// 					{
// 						if ( visited_location.second.first > element.second.first )
// 						{
// 							unvisited.emplace_back( element );
// 						}
// 						found = true;
// 						break;
// 					}
// 				}

				if ( !found )
				{
					unvisited.emplace_back( element );
				}
			}
		}

		auto cost = unvisited.front().second.second;

		visited.emplace_back( unvisited.front() );
		unvisited.erase( unvisited.begin() );

		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> admin_time = finish - start;

		if ( visited.size() % 100 == 0 )
		{
			start = finish;
			std::cout << "visited : " << visited.size() << " current cost : " << cost << std::endl;
			std::cout << "sort time: " << sort_time.count() << " s\n";
			std::cout << "neighbour time: " << neighbour_time.count() << " s\n";
			std::cout << "admin time: " << admin_time.count() << " s\n";
		}
	}

	return 5;
}

bool do_op( const std::string& op, long long* register_to_use, long long value, long long& i )
{
	if ( op == "inp" )
	{
		auto string = std::to_string( i );
		int number = string.front() - '0';
		*register_to_use = number;
		
		if ( string.size() > 1 )
		{
			i = std::stoll( string.substr( 1 ) );
		}
	}
	else if ( op == "add" )
	{
		*register_to_use += value;
	}
	else if ( op == "mul" )
	{
		*register_to_use *= value;
	}
	else if ( op == "div" )
	{
		*register_to_use = floor( *register_to_use / value );
	}
	else if ( op == "mod" )
	{
		*register_to_use %= value;
	}
	else if ( op == "eql" )
	{
		*register_to_use = value == *register_to_use;
	}

	return false;
};

long long puzzle_twentyfour()
{

	std::array<long long, 4> registers = { 0,0,0,0 };
	std::unordered_set<std::string> cached_results; // these will all be fails by definition since we'd have returned if they didn't

	std::ifstream infile( "input_puzzle_twentyfour.txt" );

	long long input_number = 11151111111111;

	std::string read_line;

	while ( std::cin >> input_number )
	{
		//input_number;
		registers = { 0,0,0,0 };
		infile.clear();
		infile.seekg(0);
		while ( std::getline( infile, read_line ) )
		{
			std::stringstream ss1( read_line );
			std::string op, reg, val;

			ss1 >> op;
			ss1 >> reg;

			// get the pointer to the right register
			long long* regn = &registers[0];
			if ( reg == "x" )
				regn = &registers[1];
			if ( reg == "y" )
				regn = &registers[2];
			if ( reg == "z" )
				regn = &registers[3];

			long long valn = 0;
			if ( ss1.peek() != EOF )
			{
				ss1 >> val;

				if ( val == "w" )
					valn = registers[0];
				else if ( val == "x" )
					valn = registers[1];
				else if ( val == "y" )
					valn = registers[2];
				else if ( val == "z" )
					valn = registers[3];
				else
				{
					valn = std::stoi( val );
				}
			}

			if ( op == "inp" )
			{
				std::cout << registers[0] << ", " << registers[1] << ", " << registers[2] << ", " << registers[3] << ", "<< registers[3]%26 << ", " << input_number << std::endl;
			}
			do_op( op, regn, valn, input_number );
		}
		std::cout << registers[0] << ", " << registers[1] << ", " << registers[2] << ", " << registers[3] << std::endl;
	}
	return registers[3];
}

int puzzle_final()
{
	std::ifstream infile( "input_final.txt" );
	std::string read_line;
	std::vector<std::string> map;

	while ( std::getline( infile, read_line ) )
	{
		map.push_back( read_line );
	}

	int i = 0;
	while ( true )
	{
		std::vector<std::string> old_map = map;
		i++;

		for ( int y = 0; y < old_map.size(); y++ )
		{
			for ( int x = 0; x < old_map.at( y ).size(); x++ )
			{
				if ( old_map.at( y ).at( x ) == '>' )
				{
					int destination = (x + 1) % (old_map.at( y ).size());
					if ( old_map.at( y ).at( destination ) == '.' )
					{
						map.at( y ).at( x ) = '.';
						map.at( y ).at( destination ) = '>';
					}
				}
			}
		}

		auto intermediate_map = map;

		for ( int y = 0; y < old_map.size(); y++ )
		{
			for ( int x = 0; x < old_map.at( y ).size(); x++ )
			{
				if ( old_map.at( y ).at( x ) == 'v' )
				{
					int destination = (y + 1) % (old_map.size());
					if ( intermediate_map.at( destination ).at( x ) == '.' )
					{
						map.at( y ).at( x ) = '.';
						map.at( destination ).at( x ) = 'v';
					}
				}
			}
		}

// 		for ( auto line : map )
// 		{
// 			std::cout << line << std::endl;
// 		}
		std::cout << i << std::endl;

		bool all_same = true;
		for ( int j = 0;j < map.size(); j++ )
		{
			for ( int k = 0; k < map.at( j ).size(); k++ )
			{

				if ( map.at( j ).at(k) != old_map.at( j ).at( k ) )
				{
					all_same = false;
				}
			}
		}

		if ( all_same )
		{
			return i;
		}
	}

	return -1;
}

int main()
{
    std::cout << puzzle_final();

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
