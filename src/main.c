#include "main.h"
float shared_resource[SIZE];
int THREAD_COUNT = 2;

struct ThreadData {
	FILE *file;
};
void genrate_floats(float min,float max)
{
	FILE *file;
	srand((unsigned int)time(NULL));
    file = fopen("random_floats.txt", "w");
	for (int i = 0; i < SIZE; i++) {
		float scale = rand() / (float) RAND_MAX;
        float random_float = min + scale * (max - min);
        fprintf(file, "%f\n", random_float);
    }
	fclose(file);
}
void file_read(FILE *file)
{
	float read_float;
	int i = 0;
    while (fscanf(file, "%f", &read_float) == 1) {
        shared_resource[i++] = read_float;
    }
}
void *file_write(void *arg)
{
	struct ThreadData *data = (struct ThreadData *)arg;
	for (int i = 0; i < SIZE; i++) {
        fprintf(data->file, "%f\n", shared_resource[i]);
    }
}


int main()
{

	pthread_t threads[THREAD_COUNT];
    struct ThreadData threadData[THREAD_COUNT];
	
	
	FILE *file_r;
	FILE *file_w1,*file_w2;

	file_r = fopen("/home/ztl-ita080/workspace/c_opts/threads/data/random_floats.txt", "r");
	file_w1 = fopen("/home/ztl-ita080/workspace/c_opts/threads/data/outs_one.txt", "w");
	file_w2 = fopen("/home/ztl-ita080/workspace/c_opts/threads/data/outs_two.txt", "w");


	file_read(file_r);


    threadData[0].file = file_w1;
    pthread_create(&threads[0], NULL, file_write, &threadData[0]);

    threadData[1].file = file_w2;
    pthread_create(&threads[1], NULL, file_write, &threadData[1]);


	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(threads[i], NULL);
	}

	
	fclose(file_r);
	fclose(file_w1);
	fclose(file_w2);
	return 1;
}


