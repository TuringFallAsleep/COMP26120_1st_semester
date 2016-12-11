#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

unsigned long hcf(unsigned long a, unsigned long b){
	unsigned long result = 0;
	if (a<b){
		unsigned long temp = 0;
		temp = a;
		a = b;
		b = temp;
	}
	if (b==0){
		return a;
	}else{
		result = a % b;
		return hcf(b,result);
	}
	printf("This is in hcf\n");
	return result;
}

unsigned long fme(unsigned long g,unsigned long p,unsigned long x){
	unsigned long s=1;
	while (x!=0){
		if (x%2 != 0){
			s = s * g % p;
		}
		g = g * g % p;
		x = (int)(x/2);
	}
	return s; 
}

unsigned long dl(unsigned long y, unsigned long g, unsigned long p){
	unsigned long i = 0;
	for (i = 0; i < p; i++){
		unsigned long power = 1;
		for (int j=0; j < i; j++){
			power = power*g;
		}
		if((power-y) % p == 0)
			return i;
	}
	return 0; 
}

unsigned long imp(unsigned long y, unsigned long p){
	unsigned long x = 0;
	x = fme(y,p-2,p);
	return x;
}

int main(int argc, char const *argv[])
{
	/* code */
	unsigned long p = 65537;
	unsigned long g = 3;
	unsigned long publicKey = 0;
	unsigned long x = 0;
	printf("Choose: e(encrypt)|d(decrypt)|k(get public key)|x(exit)?\n");
	scanf("%s",cal);
	// switch(cal);
	switch(cal){
		case e: 
			randomize();
			int k = rand()%p;
			result = fme(g,p,k);

		case d: 
		case k: 
			printf("Type private key: \n");
			scanf("%lu",x);
			publicKey = fme(g,p,x);
			printf("Public key is %lu\n",publicKey);
			break;
		case x: break;
	}

	if (strncmp(cal,"hcf",3)==0){
		printf("Please input two positive numbers:\n");
		unsigned long a=0;
		unsigned long b=0;
		unsigned long result=0;
		scanf("%lu,%lu",&a,&b);
		result = hcf(a,b);
		printf("The result is %lu.\n",result);
	}
	else if (strncmp(cal,"fme",3)==0)
	{
		unsigned long g=0;
		unsigned long x=0;
		unsigned long p=0;
		unsigned long result=0;
		printf("Please input three positive numbers, g^x mod p, p is a prime:\n");
		scanf("%lu,%lu,%lu",&g,&x,&p);
		result = fme(g,x,p);
		printf("The result is %lu.\n",result);
	}else if (strncmp(cal,"dl",2)==0){
		unsigned long g=0;
		unsigned long y=0;
		unsigned long p=0;
		unsigned long result=0;
		printf("Please input three positive numbers y g p, (g^x-y) mod p, p is a prime:\n");
		scanf("%lu,%lu,%lu",&y,&g,&p);
		result = dl(y,g,p);
		printf("The result is %lu.\n",result);
	}else if (strncmp(cal,"imp",3)==0){
		unsigned long y = 0;
		unsigned long p = 0;
		unsigned long result = 0;
		printf("Please input two positive numbers y p, \n");
		scanf("%lu,%lu",&y,&p);
		result = imp(y,p);
		printf("The result is %lu.\n", result);
	}
	else{
		printf("Wrong input.\n");
	}
		
	return 0;
}