#include "minitalk.h"
#include <signal.h>
#include <unistd.h>

void	send_signal(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(1, "Check the arguments!", 20);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid == -1)
		return (-1);
	while (*argv[2])
		send_signal(pid, *(argv[2]++));
	send_signal(pid, '\n');
	return (0);
}
