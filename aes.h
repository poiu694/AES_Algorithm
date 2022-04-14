#ifndef	AES_H
# define AES_H

# include <cstring>
# include <iostream>
# include <algorithm>
# include <bitset>
# include <sstream>

using namespace	std;

string	aes_algorithm(string plaintext, string key);

void	byte_substitution(string &block);
void	shift_rows(string &block);
void	mix_column(string &block);
void	add_round_key(string &block, string &key, int round);

int		get_int_4bits(string bit);
void	divide_column(string block, string &col1, string &col2, string &col3, string &col4);
void	shift_left_by_count(string &key, int count);

string	get_binary_bits(string key);
string	get_bit_hex_alphabet(char ch);
string	get_hexa_bits(string bits);
string	get_int_to_bits(int num);
string	get_state(string plaintext);
string	get_2mval(string col);
string	get_mix_column(string col);
string	get_sbox_value(string key);
string	get_xor_rcon(string key, int round);
string	mval(int value, string col);

string	xor_8bit(string a, string b);
string	xor_8bit_4param(string a, string b, string c, string d);
string	xor_128bit(string a, string b);
string	xor_32bit(string a, string b);

#endif
