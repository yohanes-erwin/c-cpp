#include <stdio.h>
#include <stdlib.h>

#define FIFO_LEN 4

int fifo_mem[FIFO_LEN];
uint8_t wr_ptr = 0, rd_ptr = 0;
uint8_t empty = 1, full = 0;

void fifo_push(int data);
int fifo_pop(void);
void fifo_print(void);

int main()
{
	fifo_print();

	fifo_push(1);
	fifo_push(6);
	fifo_push(8);
	fifo_push(2);
	fifo_pop();
	fifo_pop();
	fifo_push(3);
	fifo_push(4);
	fifo_pop();
	fifo_pop();
	fifo_pop();
	fifo_pop();

	return 0;
}

void fifo_push(int data)
{
	fifo_mem[wr_ptr++] = data;
	if (wr_ptr == FIFO_LEN)
		wr_ptr = 0;
	empty = 0;
	if (wr_ptr == rd_ptr)
		full = 1;

	fifo_print();
}

int fifo_pop(void)
{
	int data;

	data = fifo_mem[rd_ptr++];
	if (rd_ptr == FIFO_LEN)
		rd_ptr = 0;
	full = 0;
	if (rd_ptr == wr_ptr)
		empty = 1;

	fifo_print();

	return data;
}

void fifo_print(void)
{
	printf("data=|");
	for (int i = 0; i < FIFO_LEN; i++)
		printf("%d|", fifo_mem[i]);
	printf(", wr_ptr=%d, rd_ptr=%d, empty=%d, full=%d\n", wr_ptr, rd_ptr, empty, full);
}
