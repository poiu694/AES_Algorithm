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

#endif