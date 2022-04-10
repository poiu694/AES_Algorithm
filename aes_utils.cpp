#include "aes.h"
#include "constant.h"

void	byte_substitution(string &block)
{
	int		row;
	int		column;
	string	left_bytes;
	string	right_bytes;
	string	temp;

	temp = "";
	for (int i=0; i<block.length(); i+=8)
	{
		left_bytes = block.substr(i, 4);
		right_bytes = block.substr(i + 4, 4);
		row = get_int_4bits(left_bytes);
		column = get_int_4bits(right_bytes);
		
		temp += get_hexa_bits(get_binary_bits(SBOX[16 * row + column].substr(2, 2)));
	}
	block = temp;
}

void	shift_rows(string &block)
{
	string	byte1;
	string	byte2;
	string	byte3;
	string	byte4;

	byte1 = block.substr(0, 32);
	byte2 = block.substr(32, 32);
	byte3 = block.substr(64, 32);
	byte4 = block.substr(96, 32);
	shift_left_by_count(byte2, 8);
	shift_left_by_count(byte3, 16);
	shift_left_by_count(byte4, 24);
	block = byte1 + byte2 + byte3 + byte4;
}

