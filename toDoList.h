struct Task {
    int id;
    char description[100];
    int deadlineHours;
    int isActive;
    struct Task *next;
    struct Task *prev;   
};
typedef struct Task task;

struct tasksList {
    task *head;
    task *tail;
};
typedef struct tasksList taskslist;

struct Node {
    task *task;
    struct Node *left, *right;
};
typedef struct Node node;



//criação
int isUniqueID(taskslist *tList, int id);
void initList(taskslist *tList);
task *inputTask(taskslist *tList);
node *createNode(task *task);
void addTask(taskslist *tList, task *task);
node *addNode(node *root, node *new);


//visualização
void showTasks(taskslist *tList);
int showTasksMenu();
int mainMenu();
void showInOrder (node *root);
int viewTaskMenuOption();
void viewTaskMenu(taskslist *tList, node *root);
void showSingleTask(task *task);
void showActiveInOrder (node *root);
void showCompletedInOrder (node *root);
int orderOption();


//atualização
node *completeTask(node *root, int key);
node *listToBinaryTree(taskslist *tl, node *root);
node *treeSortedByDeadline(taskslist *tl, node *root);
node *addSortedNode(node *root, node *new);


//exclusão
void freeTree(node *root);
node *deleteTreeNode(node *root, int id);
node *findMin(node *root);
void deleteTask(taskslist *tList, int id);
