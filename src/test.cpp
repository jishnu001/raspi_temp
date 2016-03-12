#include<iostream>
extern "C"{
#include "pi_dht_read.h"
}


int main()
{

float temp=0.0;
float hum=0.0;

if(pi_dht_read(11,4,&temp,&hum)==0)
{
std::cout<<"\n"<<temp<<"\n"<<hum<<std::endl;
}

else
 std::cout<<"\nReading...\n";
return 0;
}
