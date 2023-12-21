/*******************************************************************************
*Author: Arieh Farber 
*Reviewer: Elinor Fuchs
*Date: 20/12/2023
*******************************************************************************/
#include <time.h>	   /*time_t					*/
#include <unistd.h>	   /*getpid 				*/
#include <sys/types.h> /*pid_t  				*/
#include <arpa/inet.h> /*inet_ntoa				*/
#include <ifaddrs.h>   /*getifaddrs, freeifaddrs*/
#include <string.h>    /*memcmp, memcpy			*/

#include "uid.h"

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR -1
#define EPSILON 0.0005

const ilrd_uid_t bad_uid = {0};

static int GetIP(unsigned char *ip);

ilrd_uid_t UIDCreate(void)
{
	static size_t counter = 1;
	ilrd_uid_t my_ilrd_uid = {0};
	int state = SUCCESS;

	my_ilrd_uid.counter = counter;
	counter++;
	
	my_ilrd_uid.pid = getpid();
	
	my_ilrd_uid.time = time(NULL);
	if (ERROR == my_ilrd_uid.time)
	{
		return (bad_uid);
	}

	state = GetIP(my_ilrd_uid.ip);
	if (ERROR == state)
	{
		return (bad_uid);
	}
	
	return (my_ilrd_uid);
}

int UIDIsEqual(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	int state = TRUE;
	
	if (uid1.counter != uid2.counter 			 ||\
		uid1.pid != uid2.pid 	 				 ||\
		difftime(uid1.time, uid2.time) > EPSILON ||\
		0 != memcmp(uid1.ip, uid2.ip, IP_SIZE))
	{
		state = FALSE;
	}
	
	return (state);
}

static int GetIP(unsigned char *ip)
{
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	char *addr;
	
	if (ERROR == getifaddrs(&ifap))
	{
		return (ERROR);
	}
	
	for (ifa = ifap; ifa; ifa = ifa->ifa_next) 
	{
        if (0 != ifa->ifa_addr && AF_INET == ifa->ifa_addr->sa_family) 
        {
            sa = (struct sockaddr_in *)ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            memcpy(ip, addr, IP_SIZE);
        }
    }
    
    freeifaddrs(ifap);
    
    return (SUCCESS);
}
