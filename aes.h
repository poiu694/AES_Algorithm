#ifndef	AES_H
# define AES_H

# include <cstring>
# include <iostream>
# include <algorithm>
# include <bitset>
# include <sstream>

using namespace	std;

string	aes_algorithm(string plaintext, string key);

string	get_binary_bits(string key);
string	get_bit_hex_alphabet(char ch);
string	get_hexa_bits(string bits);
string	get_int_to_bits(int num);
int		get_round(string key);
int 	get_int_4bits(string bit);
void	shift_left_by_count(string &key, int count);

void	byte_substitution(string &block);
void	shift_rows(string &block);
void	mix_column(string &block);

string xor_8bit(string a, string b);
string xor_8bit_4param(string a, string b, string c, string d);

#endif
