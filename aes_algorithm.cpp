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

string	aes_algorithm(string plaintext, string key)
{
	string	encrypt;
	string	bin_key;
	string	sub_key;
	int		round;

	encrypt = plaintext;
	bin_key = get_binary_bits(key);
	round = get_round(bin_key);
	for (int i=1; i<=round; i++)
	{
		sub_key = byte_substitution(encrypt);
		if (i != round)
	}
	return (encrypt);
}
