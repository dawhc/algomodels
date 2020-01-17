// KMP algorithm
#include<cstdio>
#include<string>
#define MAXN 1100
#define gets gets_s

int nxt[MAXN];
char txt[MAXN], st[MAXN];

void getNext(char *, int *);
void find(char *, char *, int *);

int main() {
	gets(txt);
	gets(st);
	getNext(st, nxt);
	find(txt, st, nxt);
	return 0;
}

void getNext(char *st, int *nxt) {
	int i = 0;
	int len = strlen(st);
	for (int j = 1; j < len; j++)
		if (st[i] == st[j]) {
			i++;
			nxt[j] = i;
		}
		else i = nxt[i];
}

void find(char *txt, char *st, int *nxt) {
	int len_txt = strlen(txt);
	int len_st = strlen(st);
	int j = 0;
	for (int i = 0; i < len_txt; i++) {
		while (j && txt[i] != st[j]) j = nxt[j-1];
		if (st[j] == txt[i]) j++;
		if (j == len_st) printf("%d\n", i);
	}
}