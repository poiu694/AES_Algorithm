#include "aes.h"

int	get_int_4bits(string bit)
{
	bitset<4>	bits(bit);

	return ((int)bits.to_ulong());
}

string	get_int_to_bits(int num)
{
	switch(num)
	{
		case 0:
			return ("0000");
		case 1:
			return ("0001");
		case 2:
			return ("0010");
		case 3:
			return ("0011");
		case 4:
			return ("0100");
		case 5:
			return ("0101");
		case 6:
			return ("0110");
		case 7:
			return ("0111");
		case 8:
			return ("1000");
		case 9:
			return ("1001");
		case 10:
			return ("1010");
		case 11:
			return ("1011");
		case 12:
			return ("1100");
		case 13:
			return ("1101");
		case 14:
			return ("1110");
		case 15:
			return ("1111");
	}
	return ("null");
}

string	get_bit_hex_alphabet(char ch)
{
	if (ch == 'A' || ch == 'a')
		return ("1010");
	if (ch == 'B' || ch == 'b')
		return ("1011");
	if (ch == 'C' || ch == 'c')
		return ("1100");
	if (ch == 'D' || ch == 'd')
		return ("1101");
	if (ch == 'E' || ch == 'e')
		return ("1110");
	if (ch == 'F' || ch == 'f')
		return ("1111");
	return (NULL);
}

string	get_hexa_bits(string bits)
{
	string			hexa_bits;
	stringstream	ss;
	bitset<4>		temp_bits;

	for (int i=0; i<bits.length(); i+=4)
	{
		temp_bits = bitset<4>(bits.substr(i, 4));
		ss << hex << uppercase << temp_bits.to_ulong();
		hexa_bits += ss.str();
		ss.str("");
	}
	return (hexa_bits);
}

string	get_binary_bits(string key)
{
	const char	*c_key	= key.c_str();
	bitset<4>			bit4;
	string				ret;

	ret = "";
	for (int i=0; i<key.length(); i++)
	{
		bit4 = bitset<4>(c_key[i]);
		if (('a' <= c_key[i] && c_key[i] <= 'z') || ('A' <= c_key[i] && c_key[i] <= 'Z'))
			ret += get_bit_hex_alphabet(c_key[i]);
		else
			ret += bit4.to_string();
	}
	return (ret);
}


void	shift_left_by_count(string &key, int count)
{
	if (key.length() < count)
	{
		printf("ERROR COUNT\n");
		return ;
	}
	rotate(key.begin(), key.begin() + count, key.end());
}

string	xor_8bit(string a, string b)
{
	bitset<8>	bit1(a);
	bitset<8>	bit2(b);

	return ((bit1 ^ bit2).to_string());
}

string	xor_8bit_4param(string a, string b, string c, string d)
{
	bitset<8>	bit1(a);
	bitset<8>	bit2(b);
	bitset<8>	bit3(c);
	bitset<8>	bit4(d);

	return ((bit1 ^ bit2 ^ bit3 ^ bit4).to_string());
}

string	xor_128bit(string a, string b)
{
	bitset<128>	bit1(a);
	bitset<128>	bit2(b);

	return ((bit1 ^ bit2).to_string());
}

string	xor_32bit(string a, string b)
{
	bitset<32>	bit1(a);
	bitset<32>	bit2(b);

	return ((bit1 ^ bit2).to_string());
}

string	reverse_row_col(string block)
{
	string	col1;
	string	col2;
	string	col3;
	string	col4;
	string	rev_block;

	divide_column(block, col1, col2, col3, col4);
	rev_block = col1 + col2 + col3 + col4;
	return (rev_block);
}
