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
	encrypt = reverse_row_col(encrypt);
	encrypt = get_hexa_bits(encrypt);
	return (encrypt);
}
