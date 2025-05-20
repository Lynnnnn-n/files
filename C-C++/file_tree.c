#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FNAME_MAXLEN	50		// 名字的最大长度
#define MAX_DEPTH		30		// CD命令允许的最大深度
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

// 有关函数的原型声明
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
// 主程序
void main() {
	DirTree dirTree;
	char absolutePath[200];
	char command[100], cmd[3][100];
	// 初始化只有一个根结点的树和空的当前路径栈
	initDirTree(&dirTree);
	while(1) {
		getAbsolutePath(&dirTree.path, absolutePath);
		printf("%s>", absolutePath);		// 显示命令提示符
		char command[100];
		fgets(command, sizeof(command), stdin);//获得用户所输入的命令及参数串
		command[strcspn(command, "\n")] = '\0';
		if(!analyse(command, cmd)) {		// 检查命令格式是否正确并进行分解
			printf("命令格式不正确\n");
			continue;
		}
		if(cmd[0][0] == 0) continue;
		if(strcmp(cmd[0], "exit") == 0) break;	// 退出命令
		execCommand(&dirTree, cmd);		// 根据命令及参数串执行对应的操作
	}
}

//检查命令格式是否正确并进行分解
// 通过cmd返回至少1~3个字符串，其中cmd[0]为命令串，其余为参数串
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

// 执行命令
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

// 当前路径栈的各种操作
// 当前路径栈的初始化
void initPath(Path *path) {
	path->top = 0;
}
// 清空当前路径栈
void clearPath(Path *path) {
	path->top = 0;
}
// 当前路径栈的入栈操作
void push(Path *path, DirNode *node) {
	path->node[path->top ++] = node;
}
// 当前路径栈出栈操作
DirNode *pop(Path *path) {
	return path->node[-- path->top];
}
// 取栈顶元素
DirNode *getTop(Path *path) {
	return path->node[path->top - 1];
}
// 判断栈是否为空
int isEmpty(Path *path) {
	return path->top == 0;
}
// 判断栈是否为满
int isFull(Path *path) {
	return path->top == MAX_DEPTH;
}
// 取绝对路径名
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

// 在当前目录下查找指定名字的文件或子目录，返回该结点指针和前一个兄弟的指针
// 返回空指针说明查找失败，如果查找成功则*preSibling指向前一个兄弟
DirNode *searchNode(DirNode *current, char name[], DirNode **preSibling) {
	DirNode *pre = NULL, *node= current->firstChild;
	while(node != NULL && strcmp(node->name, name) != 0) {
		pre = node;
		node = node->nextSibling;
	}
	*preSibling = pre;
	return node;
}

// 删除以指定结点为根的子树
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

// 目录树的操作
// 初始化只有根结点的目录树
void initDirTree(DirTree *dirTree) {
	DirNode *node = (DirNode *)malloc(sizeof(DirNode));
	node->name[0] = 0;
	node->firstChild = node->nextSibling = NULL;
	dirTree->root = dirTree->current = node;
	initPath(&dirTree->path);
}

// 列目录
void showDir(DirTree *dirTree) {
	DirNode *node = dirTree->current->firstChild;
	if(node == NULL) {
		printf("当前目录不存在任何文件或子目录\n");
		return;
	}
	while(node != NULL) {		// 从第一个孩子开始遍历当前结点的所有孩子
		if(node->tag == 1) {
			printf("[%s]\n", node->name);
		}
		else {
			printf("%s\n", node->name);
		}
		node = node->nextSibling;
	}
}

// 新建子目录
void makeDir(DirTree *dirTree, char dirName[]) {
	// 在当前目录下查找名为dirName的文件或子目录
	// 返回找到的结点指针node以及其前一个兄弟指针preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, dirName, &preSibling);
	if(node != NULL) {
		printf("同名文件或子目录已经存在\n");
		return;
	}
	node = (DirNode *)malloc(sizeof(DirNode));
	strcpy(node->name, dirName);
	node->tag = 1;
	node->firstChild = NULL;
	node->nextSibling = dirTree->current->firstChild;
	dirTree->current->firstChild = node;	// 新结点作为当前结点的第一个孩子
}

// 新建文件
void makeFile(DirTree *dirTree, char fileName[]) {
	// 在当前目录下查找名为fileName的文件或子目录
	// 返回找到的结点指针node以及其前一个兄弟指针preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, fileName, &preSibling);
	if(node != NULL) {
		printf("同名文件或子目录已经存在\n");
		return;
	}
	node = (DirNode *)malloc(sizeof(DirNode));
	strcpy(node->name, fileName);
	node->tag = 0;
	node->firstChild = NULL;
	node->nextSibling = dirTree->current->firstChild;
	dirTree->current->firstChild = node;	// 新结点作为当前结点的第一个孩子
}

// 删除文件或者子目录
void deleteFileOrDir(DirTree *dirTree, char name[]) {
	// 在当前目录下查找名为name的文件或子目录
	// 返回找到的结点指针node以及其前一个兄弟指针preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, name, &preSibling);
	if(node == NULL) {
		printf("要删除的文件或子目录不存在\n");
		return;
	}
	// 提示用户做出选择
	printf("是否真的要删除<Y/N>：");
	char ch = getchar();
	getchar();
	if(ch == 'Y' || ch == 'y') {
		if(preSibling != NULL) {
			preSibling->nextSibling = node->nextSibling;
		}
		else {
			dirTree->current->firstChild = node->nextSibling;
		}
		deleteSubTree(node);		// 删除node所指结点及其子树
	}
}

// 文件或子目录改名
void renameFileOrDir(DirTree *dirTree, char oldName[], char newName[]) {
	// 在当前目录下查找名为oldName的文件或子目录
	// 返回找到的结点指针node以及其前一个兄弟指针preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, oldName, &preSibling);
	if(node == NULL) {
		printf("要改名的文件或子目录不存在\n");
		return;
	}
	// 在当前目录下查找名为newName的文件或子目录
	// 返回找到的结点指针以及其前一个兄弟指针
	if(searchNode(dirTree->current, newName, &preSibling) != NULL) {
		printf("新名字与原有文件或子目录重名\n");
		return;
	}
	strcpy(node->name, newName);			// 对原结点中的name改名
}

// 返回根目录
void toRootDir(DirTree *dirTree) {
	dirTree->current = dirTree->root;
	clearPath(&dirTree->path);			// 清空path栈
}

// 返回父目录
void toParentDir(DirTree *dirTree) {
	if(dirTree->current == dirTree->root) {
		return;
	}
	pop(&dirTree->path);
	if(isEmpty(&dirTree->path)) {
		dirTree->current = dirTree->root;
	}
	else {
		dirTree->current = getTop(&dirTree->path);		// 回到父结点
	}
}

// 进入指定子目录
void toSubDir(DirTree *dirTree, char pathName[]) {
	// 在当前目录下查找名为pathName的文件或子目录
	// 返回找到的结点指针node以及其前一个兄弟指针preSibling
	DirNode *preSibling, *node;
	node = searchNode(dirTree->current, pathName, &preSibling);
	if(node == NULL || node->tag == 0) {
		printf("未发现指定名字的子目录\n");
		return;
	}
	if(isFull(&dirTree->path)) {
		printf("已达到允许的最大深度，不能继续\n");
		return;
	}
	dirTree->current = node;		// 进入指定子目录
	push(&dirTree->path, node);
}

// 转入指定目录
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
		printf("当前目录不存在任何文件或子目录\n");
		return;
	}
	preTree(dirTree->current->firstChild, 0);
}
