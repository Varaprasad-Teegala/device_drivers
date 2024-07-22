
int add(int x,int y);
int sub(int x,int y);
int mul(int x,int y);
int modl(int x,int y);

struct calc
{
	char op[20];
	int (* cal)(int x,int y);
};
