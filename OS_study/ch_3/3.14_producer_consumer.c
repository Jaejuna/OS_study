// 생산자 소비자 문제

#define BUFFER_SIZE 10

typedef struct{

} item;

item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

item next_produced;

while(true){
	/* produce an item in next_produced */
    
    while(((in+1) % BUFFER_SIZE) == out)
    {
    	/* do nothing*/
    }
    buffer[in] = next_produced;
    in = (in + 1) % BUFFER_SIZE;
}

item next_consumed;

while(true){
    while(in==out)
    {
    	/* do nothing*/
    }
    
    next_consumed = buffer[out];
    out = (out+1) % BUFFER_SIZE;
    
    /* consume the item in next_consumed*/
}