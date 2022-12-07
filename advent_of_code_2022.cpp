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

int main()
{
	std::cout << day_seven( false ) << std::endl;
	std::cout << day_seven( true ) << std::endl;
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
