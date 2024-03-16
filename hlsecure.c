void repeat_alpha(char *s)
{
	int i;
	int index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
				index = s[i] - 64;
			if (s[i] >= 'a' && s[i] <= 'z')
				index = s[i] - 96;
			while (index--)
				write(1, &s[i], 1);
		}
		else
		{
			write(1, &s[i], 1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		repeat_alpha(av[1]);
	}
	write(1, "\n", 1);
	return (0);
}