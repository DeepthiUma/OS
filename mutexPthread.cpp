//
//  main.cpp
//  octasic
//
//  Created by Deepthi on 24/03/21.
//

#include<iostream>
#include<pthread.h>
#define LIMIT 20
using namespace std;
int cnt = 0;

pthread_mutex_t mutex1;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void* sample(void *)
{
    pthread_mutex_lock(&mutex1);
    cout << "In Sample Thread beginning" << endl;
    
    cout << cnt++ <<endl;
    
    cout << "In Sample Thread ending" << endl;
    pthread_mutex_unlock(&mutex1);
    return NULL;
}
void* even(void*)
{
        cout << "In Sample1 Thread" << endl;

    pthread_mutex_lock(&mutex1);
    while(cnt < LIMIT)
        {
            if((cnt % 2) != 0)
            {
                pthread_cond_wait(&cond, &mutex1);
            }
            cout << cnt++ << endl;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex1);
        }
    return NULL;
}
void* odd(void*)
{
        cout << "In Sample2 Thread" << endl;

        pthread_mutex_lock(&mutex1);
        while(cnt < LIMIT)
        {
            if((cnt % 2) == 0)
            {
                pthread_cond_wait(&cond, &mutex1);
            }
            cout << cnt++ << endl;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex1);
        }

    return NULL;
}
int main()
{
        pthread_t tid1;
        pthread_t tid2;

        pthread_mutex_init(&mutex1,NULL);

        // A block of code should not get afftected by the two thread then we go for mutex
        //pthread_create(&tid1,NULL,&sample,NULL);
        //pthread_create(&tid2,NULL,&sample,NULL);
        pthread_create(&tid1,NULL,&even,NULL);
        pthread_create(&tid2,NULL,&odd,NULL);
    

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        cout << "In Main Thread" << endl;
        return 0;
}
