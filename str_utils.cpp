#include "aes.h"

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
	if (ch == 'A')
		return ("1010");
	if (ch == 'B')
		return ("1011");
	if (ch == 'C')
		return ("1100");
	if (ch == 'D')
		return ("1101");
	if (ch == 'E')
		return ("1110");
	if (ch == 'F')
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
		if (c_key[i] == 'A' || c_key[i] == 'B' || c_key[i] == 'C'
				|| c_key[i] == 'D' || c_key[i] == 'E' || c_key[i] == 'F')
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

