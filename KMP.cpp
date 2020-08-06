// KMP algorithm
#include<cstdio>
#include<cstring>
#define MAXN 1100000
//#define gets gets_s

int T, cnt;
int nxt[MAXN];
char txt[MAXN], st[MAXN];

void getNext(char *, int *);
void find(char *, char *, int *);

int main() {
	scanf("%d", &T);
	while(T--) {
		cnt = 0;
		memset(nxt, 0, sizeof(nxt));
		scanf("%s%s", st, txt);
		getNext(st, nxt);	
		find(txt, st, nxt);
		printf("%d\n", cnt);
	}
	return 0;
}

void getNext(char *st, int *nxt) {
	int len = strlen(st);
	nxt[0] = -1;
	for (int i = 0, j = -1; i < len; ) {
		if (j == -1 || st[i] == st[j]) 
			nxt[++i] = ++j;
		else
			j = nxt[j];
	}
}

void find(char *txt, char *st, int *nxt) {
	int len_txt = strlen(txt);
	int len_st = strlen(st);
	for (int i = 0, j = 0; i < len_txt; ) {
		if (j == -1 || txt[i] == st[j]) { 
			++i; ++j;
			if (j == len_st) {
				++cnt;
				j = nxt[j];
			}
		}
		else j = nxt[j];
	}
}