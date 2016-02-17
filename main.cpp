#include <iostream>
#include <queue>
using namespace std;

typedef struct pyr{
	struct pyr *leftU, *leftD;
	struct pyr *rightU, *rightD;
	int value;
};

void setPyr(pyr *t, int v = 0, pyr *lu = NULL, pyr *ru = NULL, pyr *ld = NULL, pyr *rd = NULL){
	t->leftU = lu;
	t->rightU = ru;
	t->leftD = ld;
	t->rightD = rd;
	t->value = v;
}

void draw(pyr *head){
	printf("%d\t", head->value);
	if(head->rightD != NULL){
		draw(head->rightD);
	}else
		printf("\n");
	if(head->leftU == NULL && head->leftD != NULL)
		draw(head->leftD);
}

int main(int argc, char *argv[]){

	pyr *q = new pyr;
	setPyr(q);
	queue <pyr*> build;
	build.push(q);

	pyr *p;
	for(int i = 0; i < 28; ){
		p = build.front();

		if(p->leftU == NULL){
			pyr *temp = new pyr;
			setPyr(temp);
			i++;
			if(p->leftD == NULL){
				setPyr(p, 0, p->leftU, p->rightU, temp, p->rightD);
				setPyr(temp, 0, temp->leftU, p, temp->leftD, temp->rightD);
				continue;
			}else{
				setPyr(p, 0, p->leftU, p->rightU, p->leftD, temp);
				setPyr(temp, 0, p, temp->rightU, temp->leftD, temp->rightD);				
				build.push(p->leftD);
				build.push(p->rightD);
				build.pop();
			}
		}else{
			if(p->leftD == NULL){
				setPyr(p, 0, p->leftU, p->rightU, p->leftU->leftD->rightD, p->rightD);
				setPyr(p->leftD, 0, p->leftD->leftU, p, p->leftD->leftD, p->leftD->rightD);
			}else{
				pyr *temp = new pyr;
				setPyr(temp);
				i++;
				setPyr(p, 0, p->leftU, p->rightU, p->leftD, temp);
				setPyr(temp, 0, p, temp->rightU, temp->leftD, temp->rightD);
				build.push(p->rightD);
				build.pop();
			}
		}
	}

	while(!build.empty())
		build.pop();

	build.push(q);
	int scn;
	while(scanf("%d", &scn)!=EOF){
		p = build.front();
		setPyr(p, scn, p->leftU, p->rightU, p->leftD, p->rightD);

		build.push(p->leftD);
		build.push(p->rightD);
		build.pop();
	}

	draw(q);

	system("pause");
	return 0;
}