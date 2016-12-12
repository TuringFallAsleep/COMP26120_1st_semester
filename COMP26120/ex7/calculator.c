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

unsigned long fme(unsigned long g,unsigned long p,int x){
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
    x = fme(y,p,p-2);
    return x;
}


int main(int argc, char const *argv[])
{
    /* code */
    unsigned long p = 65537;//65537
    unsigned long g = 3;
    unsigned long x = 0;// private key
    unsigned long publicKey = 0;
    unsigned long y = 0;// public key
    unsigned long a = 0;
    unsigned long b = 0;
    unsigned long k = 0;// random 
    unsigned long M = 0;
    unsigned long s = 0;
    char cal;
    int loop = 1;

    while(loop){
        printf("Choose: e(encrypt)|d(decrypt)|k(get public key)|x(exit)? ");
        cal = getchar();
        switch(cal){
            case 'e':
                // k = random_at_most(p);
                printf("Type secret number to send: ");
                scanf("%lu",&M);
                printf("Type recipient’s public key: ");
                scanf("%lu",&y);
                srand((unsigned)time(NULL));
                k = (unsigned long)rand()%(p-1);
                printf("%lu\n", k);
                a = fme(g,p,k);
                b = M*fme(y,p,k)%p;
                printf("Type recipient’s public key: (%lu,%lu)\n",a,b);
                break;
            case 'd':
                printf("Type in received message in form (a,b)\na: ");
                scanf("%lu",&a);
                printf("b: ");
                scanf("%lu",&b);
                printf("Type in your private key: ");
                scanf("%lu",&x);
                s = fme(a,p,x);
                M = b*imp(s,p)%p;
                // k = dl(a,g,p);
                // printf("%lu\n", k);
                printf("The decrypted secret is: %lu\n s = %lu, h = %lu", M, s, imp(s,p));
                break;
            case 'k': 
                printf("Type private key: ");
                scanf("%lu",&x);
                publicKey = fme(g,p,x); // public key
                printf("Public key is %lu\n",publicKey);
                break;
            case 'x': 
                loop = 0;
                break;
            default :
                printf("Wrong enter!\n");
                break;
        }
        getchar();
    }
    		
	return 0;
}