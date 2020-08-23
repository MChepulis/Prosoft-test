#include <stdio.h>
#define N 9


int LinearSearch(const void *const arr, const size_t size, const void *const elem, const size_t sizeofElem, int(*equal)(const void*, const void*))
{
	size_t i;
	if (!arr || !elem || !equal) {
		return -1;
	}
	for (i = 0; i < size; i++) {
		if (equal((void*)((size_t)arr + sizeofElem * i), elem)) {
			return i;
		}
	}
	return -1;
}


int IntComp(const int *first, const int *second)
{
	return *first == *second;
}


int main() {
	int nums[N];
	int var;
	int ans, i;
	for (i = 0; i < N; i++) {
		nums[i] = i + 1;
	}
	var = nums[N / 2];

	ans = LinearSearch(nums, N, &var, sizeof(var), (int(*) (const void *, const void *))IntComp);

	printf("%i", ans);
	var = 100;
	ans = LinearSearch(nums, N, &var, sizeof(var), (int(*) (const void *, const void *))IntComp);
	printf("\n%i", ans);
	return 0;
}


