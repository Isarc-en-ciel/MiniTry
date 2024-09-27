#include "../inc/minitry.h"

int main(int argc, char **argv)
{
	int	fd;
	char *del;
	char *hd;

	del = argv[2];
	hd = argv[1];
	fd = open("tmp", O_WRONLY, O_CREAT, 644);
}
