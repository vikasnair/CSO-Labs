// Author: Vikas Nair
// Reverse-engineered code using only disassembly as reference.

int f1(int x) {
	if (x > 15) {
		int y = 8 * x;
		int z = x << 2;
		y = y + z;
        z = x + x;
        x = y + z;
    } else {
    	x = x >> 1;
    	x = x + 7;
    }
    
    return x;
}

long f2(int x) {
    unsigned int y;
    unsigned long int z = 17;
    unsigned int i = 0;

    y = x << 3;
    y = y - x;
    
    while (i < y) {
        z = z + (long int) i;
        i = i + 1;
    }

    return z;
}

int f3(unsigned int i) {
    unsigned int j = 0;

    while (i) {
        j += i & 1;
        i >>= 1;
    }
    
    return -j;
}

char f4(unsigned int i) {
    if(i > 10)
        if(i > 15)
            return 65;
        else
            return i + 96;
    else
        return i + 64;
}

unsigned int check(unsigned int x);
unsigned int count(unsigned int x);

unsigned int f5(unsigned int x) {
    unsigned int result;
    unsigned int temp;

    if (x > 5)
        result = 3 * x;
    else {
        switch (x) {
            case 0:
                result = x >> 2;
                break;
            case 1:
                result = x << 2;
                break;
            case 2:
                temp = x;
                x = *(&x + 1);
                result = temp;
                break;
            case 3:
                result = check(x);
                break;
            case 4:
                result = count(x);
                break;
            case 5:
                result = 7;
                break;
            default:
                break;
        }
    }

    return result;
}

unsigned int check(unsigned int x){
    int i;
    unsigned int j = 1;

    for (i = x; i > 0; --i)
        j += i;

    return j;
}

unsigned int count(unsigned int x){
    int i;
    unsigned int j = 0;

    for (i = x; i != 0; i = i >> 1) {
        x = x & 1;
        j = j<<x;
    }

    return j;
}