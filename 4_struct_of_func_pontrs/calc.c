#include <stdio.h>
#include "structure.h"

int main()
{
	printf("Enter numbers in  <var1> <sign> <var2>:\n");
	int a,b;
	char c;
	scanf("%d%c%d",&a,&c,&b);

	if(c == '+')
	{
		struct calc arth = {
					"Addition",
					.cal = add,
				   };
		printf("%s : %d\n",arth.op,arth.cal(a,b));		
	}
	else if(c == '-')
	{
		struct calc arth = {
                                        "Subraction",
                                        .cal = sub,
                                   };    
                printf("%s : %d\n",arth.op,arth.cal(a,b));
	}
	else if(c == '*')
        {
		struct calc arth = {
                                        "Multiplication",
                                        .cal = mul,
                                   };    
                printf("%s : %d\n",arth.op,arth.cal(a,b));
        }
	else if(c == '%')
        {
        	struct calc arth = {
                                        "Modulus",
                                        .cal = modl,
                                   };    
                printf("%s : %d\n",arth.op,arth.cal(a,b));
        }
	else
	{
		printf("Invalid operator\n");
	}

}
