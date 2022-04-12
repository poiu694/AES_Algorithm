#include "aes.h"

int	get_round(string key)
{
	if (key.length() == 128)
		return (10);
	if (key.length() == 192)
		return (12);
	if (key.length() == 256)
		return (14);
	return (0);
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

string	aes_algorithm(string plaintext, string key)
{
	string	encrypt;
	string	bin_key;
	int		round;

	encrypt = get_state(plaintext);
	bin_key = get_state(key);
	round = get_round(bin_key);
	add_round_key(encrypt, bin_key, 0);
	for (int i=1; i<=round; i++)
	{
		byte_substitution(encrypt);
		shift_rows(encrypt);
		if (i != round)
			mix_column(encrypt);
		add_round_key(encrypt, bin_key, i);
	}
	encrypt = get_hexa_bits(encrypt);
	return (encrypt);
}
