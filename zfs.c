/*
*  Zos Attempt 5 v0.5
*  Author: Zac McChesney
*/
#include <system.h>

struct zfs zfsTable[128];
int zfsCount = 0;

void init_zfs()
{
	//restore saved content
}

void exit_zfs()
{
	//save content
}

void add_file(char* name, char type, char* contents)
{
	if (type == 't' || type == 'T' || type == 'b' || type == 'B')
	{
		if (strlen(name) > 0 && strlen(contents) > 0)
		{
			if (zfsCount < 128)
			{
				int id = zfsCount;
				zfsCount++;
				zfsTable[id].name = name;
				zfsTable[id].type = type;
				zfsTable[id].contents = contents;
				zfsTable[id].id = id;
				puts("File successfully stored\n");
			}
			else
			{
				puts("File system full\n");
			}
		}
		else
		{
			puts("No name or contents provided\n");
		}
	}
	else
	{
		puts("Invalid file type\n");
	}
}

void del_file(int id)
{
	if (id < zfsCount)
	{
		for (int i = id; i < zfsCount; i++)
		{
			zfsTable[i].name = zfsTable[i+1].name;
			zfsTable[i].type = zfsTable[i+1].type;
			zfsTable[i].contents = zfsTable[i+1].contents;
			zfsTable[i].id = zfsTable[i+1].id;
		}
		zfsCount--;
		puts("Successfully removed the file\n");
	}
	else
	{
		puts("Invalid id\n");
	}
}

void ren_file(int id, char* name)
{
	if (id < zfsCount)
	{
		if (strlen(name) > 0)
		{
			zfsTable[id].name = name;
			puts("Successfully renamed file\n");
		}
		else
		{
			puts("No name provided\n");
		}
	}
	else
	{
		puts("Invalid id\n");
	}
}

void list_files()
{
	puts("Name\t");
	puts("Type\t");
	puts("ID\n");
	for (int i = 0; i == zfsCount; i++)
	{
		puts(zfsTable[i].name);
		puts(zfsTable[i].type);
		puts(nums[zfsTable[i].id]);
	}
}
