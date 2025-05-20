#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FNAME_MAXLEN	50		// ���ֵ���󳤶�
#define MAX_DEPTH		30		// CD���������������
typedef struct dirnode {
	char name[FNAME_MAXLEN+1];
	int tag;
	struct dirnode *firstChild, *nextSibling;
} DirNode;
typedef struct {
	DirNode *node[MAX_DEPTH];
	int top;
} Path;
typedef struct {
	DirNode *root, *current;
	Path path;
} DirTree;

// �йغ�����ԭ������
void getAbsolutePath(Path *path, char pathName[]);
int analyse(char command[], char cmd[][100]);
void execCommand(DirTree *dirTree, char cmd[][100]);
void initPath(Path *path);
void clearPath(Path *path);
void push(Path *path, DirNode *node);
DirNode *pop(Path *path);
DirNode *getTop(Path *path);
int isEmpty(Path *path);
int isFull(Path *path);
void getAbsolutePath(Path *path, char pathName[]);
DirNode *searchNode(DirNode *current, char name[], DirNode **preSibling);
void deleteSubTree(DirNode *node);
void initDirTree(DirTree *dirTree);
void showDir(DirTree *dirTree);
void makeDir(DirTree *dirTree, char dirName[]);
void makeFile(DirTree *dirTree, char fileName[]);
void deleteFileOrDir(DirTree *dirTree, char name[]);
void renameFileOrDir(DirTree *dirTree, char oldName[], char newName[]);
void toRootDir(DirTree *dirTree);
void toParentDir(DirTree *dirTree);
void toSubDir(DirTree *dirTree, char pathName[]);
void toDir(DirTree *dirTree, char pathName[]);
void preTree(DirNode* cur, int lev);
void tree(DirTree* dirTree);
// ������
void main() {
	DirTree dirTree;
	char absolutePath[200];
	char command[100], cmd[3][100];
	// ��ʼ��ֻ��һ�����������Ϳյĵ�ǰ·��ջ
	initDirTree(&dirTree);
	while(1) {
		getAbsolutePath(&dirTree.path, absolutePath);
		printf("%s>", absolutePath);		// ��ʾ������ʾ��
		char command[100];
		fgets(command, sizeof(command), stdin);//����û�����������������
		command[strcspn(command, "\n")] = '\0';
		if(!analyse(command, cmd)) {		// ��������ʽ�Ƿ���ȷ�����зֽ�
			printf("�����ʽ����ȷ\n");
			continue;
		}
		if(cmd[0][0] == 0) continue;
		if(strcmp(cmd[0], "exit") == 0) break;	// �˳�����
		execCommand(&dirTree, cmd);		// �������������ִ�ж�Ӧ�Ĳ���
	}
}

//��������ʽ�Ƿ���ȷ�����зֽ�
// ͨ��cmd��������1~3���ַ���������cmd[0]Ϊ���������Ϊ������
int analyse(char command[], char cmd[][100]) {
	int cnt = 0;
	char *validCmd[] = {"dir", "md", "mf", "del", "ren", "cd", "tree", "exit"};
	int validCnt[] =  {1, 2, 2, 2, 3, 2, 1, 1};
	char *token = strtok(command, " ");
	while(token != NULL) {
		strcpy(cmd[cnt ++], token);
		token = strtok(NULL, " ");
		if(cnt == 3) break;
	}
	if(token != NULL) {
		cnt ++;
	}
	if(cnt == 0) {
		cmd[0][0] = 0;
		return 1;
	}
	int i = 0;
	for(i = 0; i < 7; i ++) {
		if(strcmp(cmd[0], validCmd[i]) == 0) break;
	}
	return i == 7 || cnt != validCnt[i] ? 0 : 1;
}

// ִ������
void execCommand(DirTree *dirTree, char cmd[][100]) {
	if(strcmp(cmd[0], "dir") == 0) {
		showDir(dirTree);
	}
	else if(strcmp(cmd[0], "md") == 0) {
		makeDir(dirTree, cmd[1]);
	}
	else if(strcmp(cmd[0], "mf") == 0) {
		makeFile(dirTree, cmd[1]);
	}
	else if(strcmp(cmd[0], "del") == 0) {
		deleteFileOrDir(dirTree, cmd[1]);
	}
	else if(strcmp(cmd[0], "ren") == 0) {
		renameFileOrDir(dirTree, cmd[1], cmd[2]);
	}
	else if(strcmp(cmd[0], "cd") == 0) {
		toDir(dirTree, cmd[1]);
	}
	else if (strcmp(cmd[0], "tree") == 0) {
		tree(dirTree);
	}
}

// ��ǰ·��ջ�ĸ��ֲ���
// ��ǰ·��ջ�ĳ�ʼ��
void initPath(Path *path) {
	path->top = 0;
}
// ��յ�ǰ·��ջ
void clearPath(Path *path) {
	path->top = 0;
}
// ��ǰ·��ջ����ջ����
void push(Path *path, DirNode *node) {
	path->node[path->top ++] = node;
}
// ��ǰ·��ջ��ջ����
DirNode *pop(Path *path) {
	return path->node[-- path->top];
}
// ȡջ��Ԫ��
DirNode *getTop(Path *path) {
	return path->node[path->top - 1];
}
// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Path *path) {
	return path->top == 0;
}
// �ж�ջ�Ƿ�Ϊ��
int isFull(Path *path) {
	return path->top == MAX_DEPTH;
}
// ȡ����·����
void getAbsolutePath(Path *path, char pathName[]) {
	if(path->top == 0) {
		pathName[0] = '/';
		pathName[1] = 0;
		return;
	}
	pathName[0] = 0;
	for(int i = 0; i < path->top; i ++) {
		strcat(pathName, "/");
		strcat(pathName, path->node[i]-> name);
	}
}

// �ڵ�ǰĿ¼�²���ָ�����ֵ��ļ�����Ŀ¼�����ظý��ָ���ǰһ���ֵܵ�ָ��
// ���ؿ�ָ��˵������ʧ�ܣ�������ҳɹ���*preSiblingָ��ǰһ���ֵ�
DirNode *searchNode(DirNode *current, char name[], DirNode **preSibling) {
	DirNode *pre = NULL, *node= current->firstChild;
	while(node != NULL && strcmp(node->name, name) != 0) {
		pre = node;
		node = node->nextSibling;
	}
	*preSibling = pre;
	return node;
}

// ɾ����ָ�����Ϊ��������
void deleteSubTree(DirNode *node) {
	if(node != NULL) {
		DirNode *p = node->firstChild;
		free(node);
		while(p != NULL) {
			DirNode *q = p->nextSibling;
			deleteSubTree(p);
			p = q;
		}
	}
}

// Ŀ¼���Ĳ���
// ��ʼ��ֻ�и�����Ŀ¼��
void initDirTree(DirTree *dirTree) {
	DirNode *node = (DirNode *)malloc(sizeof(DirNode));
	node->name[0] = 0;
	node->firstChild = node->nextSibling = NULL;
	dirTree->root = dirTree->current = node;
	initPath(&dirTree->path);
}

// ��Ŀ¼
void showDir(DirTree *dirTree) {
	DirNode *node = dirTree->current->firstChild;
	if(node == NULL) {
		printf("��ǰĿ¼�������κ��ļ�����Ŀ¼\n");
		return;
	}
	while(node != NULL) {		// �ӵ�һ�����ӿ�ʼ������ǰ�������к���
		if(node->tag == 1) {
			printf("[%s]\n", node->name);
		}
		else {
			printf("%s\n", node->name);
		}
		node = node->nextSibling;
	}
}

// �½���Ŀ¼
void makeDir(DirTree *dirTree, char dirName[]) {
	// �ڵ�ǰĿ¼�²�����ΪdirName���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ��node�Լ���ǰһ���ֵ�ָ��preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, dirName, &preSibling);
	if(node != NULL) {
		printf("ͬ���ļ�����Ŀ¼�Ѿ�����\n");
		return;
	}
	node = (DirNode *)malloc(sizeof(DirNode));
	strcpy(node->name, dirName);
	node->tag = 1;
	node->firstChild = NULL;
	node->nextSibling = dirTree->current->firstChild;
	dirTree->current->firstChild = node;	// �½����Ϊ��ǰ���ĵ�һ������
}

// �½��ļ�
void makeFile(DirTree *dirTree, char fileName[]) {
	// �ڵ�ǰĿ¼�²�����ΪfileName���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ��node�Լ���ǰһ���ֵ�ָ��preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, fileName, &preSibling);
	if(node != NULL) {
		printf("ͬ���ļ�����Ŀ¼�Ѿ�����\n");
		return;
	}
	node = (DirNode *)malloc(sizeof(DirNode));
	strcpy(node->name, fileName);
	node->tag = 0;
	node->firstChild = NULL;
	node->nextSibling = dirTree->current->firstChild;
	dirTree->current->firstChild = node;	// �½����Ϊ��ǰ���ĵ�һ������
}

// ɾ���ļ�������Ŀ¼
void deleteFileOrDir(DirTree *dirTree, char name[]) {
	// �ڵ�ǰĿ¼�²�����Ϊname���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ��node�Լ���ǰһ���ֵ�ָ��preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, name, &preSibling);
	if(node == NULL) {
		printf("Ҫɾ�����ļ�����Ŀ¼������\n");
		return;
	}
	// ��ʾ�û�����ѡ��
	printf("�Ƿ����Ҫɾ��<Y/N>��");
	char ch = getchar();
	getchar();
	if(ch == 'Y' || ch == 'y') {
		if(preSibling != NULL) {
			preSibling->nextSibling = node->nextSibling;
		}
		else {
			dirTree->current->firstChild = node->nextSibling;
		}
		deleteSubTree(node);		// ɾ��node��ָ��㼰������
	}
}

// �ļ�����Ŀ¼����
void renameFileOrDir(DirTree *dirTree, char oldName[], char newName[]) {
	// �ڵ�ǰĿ¼�²�����ΪoldName���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ��node�Լ���ǰһ���ֵ�ָ��preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, oldName, &preSibling);
	if(node == NULL) {
		printf("Ҫ�������ļ�����Ŀ¼������\n");
		return;
	}
	// �ڵ�ǰĿ¼�²�����ΪnewName���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ���Լ���ǰһ���ֵ�ָ��
	if(searchNode(dirTree->current, newName, &preSibling) != NULL) {
		printf("��������ԭ���ļ�����Ŀ¼����\n");
		return;
	}
	strcpy(node->name, newName);			// ��ԭ����е�name����
}

// ���ظ�Ŀ¼
void toRootDir(DirTree *dirTree) {
	dirTree->current = dirTree->root;
	clearPath(&dirTree->path);			// ���pathջ
}

// ���ظ�Ŀ¼
void toParentDir(DirTree *dirTree) {
	if(dirTree->current == dirTree->root) {
		return;
	}
	pop(&dirTree->path);
	if(isEmpty(&dirTree->path)) {
		dirTree->current = dirTree->root;
	}
	else {
		dirTree->current = getTop(&dirTree->path);		// �ص������
	}
}

// ����ָ����Ŀ¼
void toSubDir(DirTree *dirTree, char pathName[]) {
	// �ڵ�ǰĿ¼�²�����ΪpathName���ļ�����Ŀ¼
	// �����ҵ��Ľ��ָ��node�Լ���ǰһ���ֵ�ָ��preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, pathName, &preSibling);
	if(node == NULL || node->tag == 0) {
		printf("δ����ָ�����ֵ���Ŀ¼\n");
		return;
	}
	if(isFull(&dirTree->path)) {
		printf("�Ѵﵽ����������ȣ����ܼ���\n");
		return;
	}
	dirTree->current = node;		// ����ָ����Ŀ¼
	push(&dirTree->path, node);
}

// ת��ָ��Ŀ¼
void toDir(DirTree *dirTree, char pathName[]) {
	if(strcmp(pathName, "/") == 0) {
		toRootDir(dirTree);
	}
	else if(strcmp(pathName, "..") == 0) {
		toParentDir(dirTree);
	}
	else {
		toSubDir(dirTree, pathName);
	}
}

void preTree(DirNode* cur, int lev) {
	if (cur == NULL) {
		return;
	}
	for (int i = 0; i < lev; i++) {
		printf("  ");
	}
	if (cur->tag == 1){
		printf("[%s]\n", cur->name);
	}
	else{
		printf("%s\n", cur->name);
	}
	preTree(cur->firstChild, lev + 1);
	preTree(cur->nextSibling, lev);
}

void tree(DirTree* dirTree){
	if (dirTree->current->firstChild == NULL) {
		printf("��ǰĿ¼�������κ��ļ�����Ŀ¼\n");
		return;
	}
	preTree(dirTree->current->firstChild, 0);
}
