#include "aes.h"

int	main(int argc, char **argv)
{
	string	encrypt;

	if (argc == 3)
	{
		encrypt = aes_algorithm(argv[1], argv[2]);
		printf("---------------------------------------------\n");
		printf("Plain text  : %10s\n", argv[1]);
		printf("Key         : %10s\n", argv[2]);
		printf("Cipher text : %10s\n", encrypt.c_str());
		printf("---------------------------------------------\n");
	}
	else
	{
		cout << "Invalid Arguments\n";
	}
	return (0);
}
