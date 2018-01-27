#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  even  = PTHREAD_COND_INITIALIZER;
pthread_cond_t  odd = PTHREAD_COND_INITIALIZER;

void *thread1(void *arg){
  pthread_mutex_lock(&lock);
  for(int i = 0;i <= 1000;i++){
    if(i%2==1){
      printf("%d ",i);
      pthread_cond_wait(&even,&lock);
    }
    else
      pthread_cond_signal(&odd);
  }
  pthread_mutex_unlock(&lock);
}

void *thread2(void *arg){
  pthread_mutex_lock(&lock);
  for(int i = 0;i <= 1000;i++){
    if(i%2==0){
        printf("%d ",i);
        pthread_cond_wait(&odd,&lock);
    }
    else
        pthread_cond_signal(&even);
  }
  pthread_mutex_unlock(&lock);
}

int main(){
  printf("program start...\n");
  pthread_t t1,t2;
  pthread_create(&t1,NULL,(void*)thread1,NULL);
  pthread_create(&t2,NULL,(void*)thread2,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  return 0;
}
