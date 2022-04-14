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
	block = get_binary_bits(temp);
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

void	mix_column(string &block)
{
	string	col1;
	string	col2;
	string	col3;
	string	col4;
	string	temp;

	divide_column(block, col1, col2, col3, col4);
	col1 = get_mix_column(col1);
	col2 = get_mix_column(col2);
	col3 = get_mix_column(col3);
	col4 = get_mix_column(col4);
	temp = "";
	for (int i=0; i<16; i++)
	{
		if (i % 4 == 0)
			temp += col1.substr(i / 2, 2);
		else if (i % 4 == 1)
			temp += col2.substr((i - 1) / 2, 2);
		else if (i % 4 == 2)
			temp += col3.substr((i - 2) / 2, 2);
		else
			temp += col4.substr((i - 3) / 2, 2);
	}
	block = get_binary_bits(temp);
}

void	add_round_key(string &block, string &key, int round)
{
	string	key1;
	string	key2;
	string	key3;
	string	key4;
	string	origin_key4;
	string	temp;

	divide_column(key, key1, key2, key3, origin_key4);
	key4 = origin_key4;
	shift_left_by_count(key4, 8);
	key4 = get_sbox_value(key4);
	key4 = get_xor_rcon(key4, round);
	key1 = xor_32bit(key1, key4);
	key2 = xor_32bit(key1, key2);
	key3 = xor_32bit(key2, key3);
	key4 = xor_32bit(key3, origin_key4);

	block = xor_128bit(block, key);
	temp = "";
	for (int i=0; i<32; i++)
 	{
 		if (i % 4 == 0)
 			temp += key1.substr(i, 8);
 		else if (i % 4 == 1)
 			temp += key2.substr((i - 1), 8);
 		else if (i % 4 == 2)
 			temp += key3.substr((i - 2), 8);
 		else
		{
 			temp += key4.substr((i - 3), 8);
			i += 4;
		}
 	}
	key = temp;
}

string	get_state(string plaintext)
{
	string	state;

	state = "";
	for (int i=0; i<8; i+=2)
	{
		for (int j=i; j<32; j+=8)
		{
			state += plaintext.substr(j, 2);
		}
	}
	state = get_binary_bits(state);
	return (state);
}

void	divide_column(string block, string &col1, string &col2, string &col3, string &col4)
{
	block = get_hexa_bits(block);
	for (int i=0; i<block.length(); i++)
	{
		if (i % 8 <= 1)
			col1 += block[i];
		else if (i % 8 <= 3)
			col2 += block[i];
		else if (i % 8 <= 5)
			col3 += block[i];
		else
			col4 += block[i];
	}
	col1 = get_binary_bits(col1);
	col2 = get_binary_bits(col2);
	col3 = get_binary_bits(col3);
	col4 = get_binary_bits(col4);
}

// x4 x3 x 1
string	get_2mval(string col)
{
	bitset<8>	constant("00011011");
	bitset<8>	bits;
	string		temp;

	temp = col;
	shift_left_by_count(temp, 1);
	temp[temp.length() - 1] = '0';
	if (col[0] == '0')
		return (temp);
	bits = bitset<8>(temp);
	return ((bits ^ constant).to_string());
}

string	mval(int value, string col)
{
	string		bin_col;
	bitset<8>	bit;
	bitset<8>	bit2;

	bin_col = get_binary_bits(col);
	if (value == 1)
	{
		return (bin_col);
	}
	else if (value == 2)
	{
		return (get_2mval(bin_col));
	}
	bit = bitset<8>(bin_col);
	bit2 = bitset<8>(get_2mval(bin_col));
	return ((bit ^ bit2).to_string());
}

string	get_mix_column(string col)
{
	string	ret;

	col = get_hexa_bits(col);
	ret = xor_8bit_4param(mval(2, col.substr(0, 2)), mval(3, col.substr(2, 2)),
								mval(1, col.substr(4, 2)), mval(1, col.substr(6, 2)));
	ret += xor_8bit_4param(mval(1, col.substr(0, 2)), mval(2, col.substr(2, 2)),
								mval(3, col.substr(4, 2)), mval(1, col.substr(6, 2)));
	ret += xor_8bit_4param(mval(1, col.substr(0, 2)), mval(1, col.substr(2, 2)),
								mval(2, col.substr(4, 2)), mval(3, col.substr(6, 2)));
	ret += xor_8bit_4param(mval(3, col.substr(0, 2)), mval(1, col.substr(2, 2)),
								mval(1, col.substr(4, 2)), mval(2, col.substr(6, 2)));
	return (get_hexa_bits(ret));
}

string	get_sbox_value(string key)
{
	int		row;
	int		column;
	string	left_bytes;
	string	right_bytes;
	string	temp;

	temp = "";
	for (int i=0; i<key.length(); i+=8)
	{
		left_bytes = key.substr(i, 4);
		right_bytes = key.substr(i + 4, 4);
		row = get_int_4bits(left_bytes);
		column = get_int_4bits(right_bytes);
	
		temp += get_binary_bits(SBOX[16 * row + column].substr(2, 2));
	}
	return (temp);
}

string	get_xor_rcon(string key, int round)
{
	bitset<32>	bit1(key);
	bitset<32>	bit2(get_binary_bits(ROUND_CONSTANT[round]));

	return ((bit1 ^ bit2).to_string());
}

