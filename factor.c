// Jason Angell
// [needs better hobbies]

#include <stdio.h>
#include <stdlib.h>
#define TOTALPERCENT 50

struct node{
  int val;
  struct node * next;
};

int parse_num();
int next_prime();
int check_if_prime();

int main(int argc, char * argv[]){
  int mainnum = parse_num(argv[1]);
  int workingnum = mainnum;
  struct node * primes = malloc(sizeof(struct node));
  primes->val = -1; // dummy last node
  primes->next = NULL;
  struct node * factors = malloc(sizeof(struct node));
  factors->val = -1; // dummy last node
  factors->next = NULL;

  // let's factor this biznitch
  int counting = 2;
  while(workingnum > 2){
    counting = next_prime(counting, primes);
    //printf("%i\n", counting); // uncomment if you want verbose
    // add it to primes
    struct node * addprime = malloc(sizeof(struct node));
    addprime->val = counting;
    addprime->next = primes;
    primes = addprime;
    // check if it's a factor
    if(workingnum % counting == 0){
      workingnum = workingnum / counting;
      struct node * addfactor = malloc(sizeof(struct node));
      addfactor->val = counting;
      addfactor->next = factors;
      factors = addfactor;
    }
  }

  // print factors here
  printf("The factors of %i are", mainnum);
  while(factors->next != NULL){
    printf(" %i", factors->val);
    factors = factors->next;
  }
  printf("\n");
  
}


// parses an int out of a string
int parse_num(char numstring[]){
  int to_ret = 0;
  int i = 0;
  while(numstring[i] != '\0'){
    to_ret = to_ret * 10;
    to_ret += (numstring[i] - '0');
    i++;
  }
  return to_ret;
}

// gets the next prime, given any positive integer
int next_prime(int cur_int, struct node * primes){
  cur_int++;
  while(check_if_prime(cur_int, primes) == 0){
    cur_int++;
  }
  return cur_int;
}

// checks if a number is prime, via the working list of primes (prime returns 1)
int check_if_prime(int checkme, struct node * primes){
  while(primes->next != NULL && checkme / primes->val > 1){
    // second condition in above line: if less than twice largest prime, # automatically prime
    if((checkme % primes->val) == 0){
      return 0;
    }
    primes = primes->next;
  }
  // hey, it's prime!
  return 1;
  
}
