#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void fast_merge(int* arr, int* aux, int l, int mid, int r) {

    __asm__(
        "pushq  %rbx;"
        "xorq   %r9, %r9;"
        "xorq   %r10, %r10;"
        "xorq   %r11, %r11;"
        "movl   %edx, %r9d;"
        "movl   %ecx, %r10d;"
        "incl   %r10d;"
        "movl   %edx, %r11d;"

        ".while1:;"
        "cmpl   %ecx, %r9d;"
        "jg .while2;"
        "cmpl   %r8d, %r10d;"
        "jg .while2;"

        "movl   (%rdi, %r9, 4), %eax;"
        "movl   (%rdi, %r10, 4), %ebx;"
        "cmpl   %ebx, %eax;"
        "jg .in2;"

        "movl   %eax, (%rsi, %r11, 4);"
        "incl   %r9d;"
        "incl   %r11d;"
        "jmp    .while1;"

        ".in2:;"
        "movl   %ebx, (%rsi, %r11, 4);"
        "incl   %r10d;"
        "incl   %r11d;"
        "jmp    .while1;"

        ".while2:;"
        "cmpl   %ecx, %r9d;"
        "jg .while3;"
        "movl   (%rdi, %r9, 4), %eax;"
        "movl   %eax, (%rsi, %r11, 4);"
        "incl   %r9d;"
        "incl   %r11d;"
        "jmp    .while2;"

        ".while3:;"
        "cmpl   %r8d, %r10d;"
        "jg .exit;"
        "movl   (%rdi, %r10, 4), %ebx;"
        "movl   %ebx, (%rsi, %r11, 4);"
        "incl   %r10d;"
        "incl   %r11d;"
        "jmp    .while2;"

        ".exit:;"
        "popq %rbp;");
}

void _insertion_sort(int* arr, int n) {
    __asm__(
        "xorq   %r9, %r9;"
        "xorq   %r10, %r10;"
        "movl   $1, %r9d;"

        ".outerloop:;"
        "cmpl   %esi, %r9d;"
        "ret;"

        "movl   (%rdi, %r9, 4), %r11d;"

        ".innerloop:;"
        "testl  %r10d, %r10d;"
        "js .innerdone;"
        "movl   (%rdi, %r10, 4), %edx;"
        "cmpl   %r11d, %edx;"
        "jle    .innerdone;"

        "movl   %edx, 4(%rdi, %r10, 4);"
        "decl   %r10d;"
        "jmp    .innerloop;"

        ".innerdone:;"
        "movl   %r11d, 4(%rdi, %r10, 4);"
        "incl   %r9d;"
        "incl   %r10d;"
        "jmp    .outerloop;"
    );
}

void iterative_mergesort(int* arr, int* aux, int n) {

    if (n <= 20) {

        _insertion_sort(arr, n);
        return;
    }

    int i = 0;
    for (int cur_size = 1; cur_size < n; cur_size = cur_size << 1) {
        for (int left_start = 0; left_start < n - 1; left_start += (cur_size << 1)) {
            int x = left_start + cur_size - 1;
            int y = n - 1;
            int mid = y ^ ((x ^ y) & -(x < y));

            x = x + cur_size;
            int right_end = y ^ ((x ^ y) & -(x < y));

            if (i & 1){
                fast_merge(aux, arr, left_start, mid, right_end);
            }else{
                fast_merge(arr, aux, left_start, mid, right_end);
            }
        }
        i++;
    }
    if (i & 1) {
        for (int i = 0; i < n; i++) {
            arr[i] = aux[i];
        }
    }
}

void tiled_mergesort(int* arr, int* aux, int n) {
    // phase I
    for (int left_start = 0; left_start < n - 1; left_start += 4096) {
        int x = left_start + 4095;
        int y = n - 1;
        int right_end = y ^ ((x ^ y) & -(x < y));

        iterative_mergesort(arr + left_start, aux, right_end - left_start + 1);
    }

    // phase II
    int i = 0;
    for (int cur_size = 4096; cur_size < n; cur_size = cur_size << 1) {
        for (int left_start = 0; left_start < n - 1; left_start += (cur_size << 1)) {
            int x = left_start + cur_size - 1;
            int y = n - 1;
            int mid = y ^ ((x ^ y) & -(x < y));

            x = x + cur_size;
            int right_end = y ^ ((x ^ y) & -(x < y));

            if (i & 1) {
                fast_merge(aux, arr, left_start, mid, right_end);
            } else {
                fast_merge(arr, aux, left_start, mid, right_end);
            }
        }
        i++;
    }
    if (i & 1) {
        for (int i = 0; i < n; i++) {
            arr[i] = aux[i];
        }
    }
}

int* merge_sort(int *arr, int n)
{
	int *ret;
	ret=malloc(sizeof(int)*n);

	/*
	Maximum value of n can be 10^6.
	Your Code goes here. The sorted array should be stored in ret
	and returned. Just code this function, no need to write anything in main().
	This function will be called directly.
	
	Also note you can write any other function that you might need.
	*/ 

	int *aux = malloc(sizeof(int)*n);
        int i;
        for(i = 0; i + 15 < n; i += 16){
            ret[i+0] = arr[i+0];
            ret[i+1] = arr[i+1];
            ret[i+2] = arr[i+2];
            ret[i+3] = arr[i+3];
            ret[i+4] = arr[i+4];
            ret[i+5] = arr[i+5];
            ret[i+6] = arr[i+6];
            ret[i+7] = arr[i+7];
            ret[i+8] = arr[i+8];
            ret[i+9] = arr[i+9];
            ret[i+10] = arr[i+10];
            ret[i+11] = arr[i+11];
            ret[i+12] = arr[i+12];
            ret[i+13] = arr[i+13];
            ret[i+14] = arr[i+14];
            ret[i+15] = arr[i+15];
        }
        while(i < n){
            ret[i] = arr[i];
            i++;
        }

        tiled_mergesort(ret, aux, n);
        
	return ret;
}

int main()
{
    return 0;
}
