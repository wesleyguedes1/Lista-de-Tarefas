#include "toDoList.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initList(taskslist *tList){
    tList->head = NULL;
    tList->tail = NULL;
}

int isUniqueID(taskslist *tList, int id) {
    task *current = tList->head;
    while (current != NULL) {
        if (current->id == id) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
//recebe input do usuário e retorna uma task
task *inputTask(taskslist *tList) {
    task *tk = (task*) malloc(sizeof(task));
    printf("id da tarefa: ");
    int id;
    scanf(" %d", &id);
    getchar();
    if (isUniqueID(tList, id)== 0) {
        printf("ID já existente. Tente novamente.\n");
        free(tk);
        return NULL;
    }
    tk->id = id;
    printf("descrição da tarefa: ");
    fgets( tk->description, sizeof(tk->description), stdin);
    printf("tempo limite da tarefa(em horas): ");
    scanf(" %d", &tk->deadlineHours);
    getchar();
    tk->isActive = 1;
    tk->prev = NULL;
    tk->next = NULL;
    return tk;
}

void addTask(taskslist *tList, task *Task) {
    
    if (tList->head == NULL) {
        tList->head = Task;
        tList->tail = Task;
    } else {
        Task->prev = tList->tail;
        tList->tail->next = Task;
        tList->tail = Task;
    }

}

int viewTaskMenuOption() {
    int num;
    printf("Digite 1 para visualizar todas as tarefas\n");
    printf("Digite 2 para visualizar somente as tarefeas ativas\n");
    printf("Digite 3 para visualizar somente as tarefas concluídas\n");
    printf("Digite 4 para mudar a ordem de visualização\n");
    printf("Digite 0 para voltar ao menu anterior\n");
    scanf(" %d", &num);
    getchar();
    return num;
}

void showSingleTask(task *task) {
    printf("id: %d\n", task->id);
    printf("descrição: %s\n", task->description);
    printf("horas restantes: %d\n", task->deadlineHours);
    printf("situação: ");
    if (task->isActive == 0) {
        printf("completa\n");
    } else {
        printf("ativa\n");
    }
    printf("--------------------\n");
}
//mostra tarefas ativas seguindo um padrão de ordenação selecionado
void showActiveTasks(taskslist *tList, int isOrdered, node *root)    {
    task *aux;
    switch (isOrdered) {
    case 1:
        //cria uma árvore com as tarefas ativas ordenadas por tempo limite, mostra a árvore e a exlcui em seguida
        node *sortedRoot = NULL;
        sortedRoot = treeSortedByDeadline(tList, sortedRoot);
        showActiveInOrder(sortedRoot);
        freeTree(sortedRoot);
        break;
    case 2:
        //mostra tarefas ativas por ordem de ID
        showActiveInOrder(root);
        break;
    case 3:
        //mostra tarefas ativas por ordem de criação
        for (aux = tList->head; aux!= NULL; aux = aux->next) {
            if (aux->isActive) {
                showSingleTask(aux);
            }
        }
        break;
    default:
        break;
    }
}

void showCompletedTasks(taskslist *tList, int orderType, node *root) {
    task *aux;
   switch (orderType) {
   case 1:
        node *sortedRoot = NULL;
        sortedRoot = treeSortedByDeadline(tList, sortedRoot);
        showCompletedInOrder(sortedRoot);
        freeTree(sortedRoot);
        break;
    case 2:
        showCompletedInOrder(root);
        break;
    case 3:
        for (aux = tList->head; aux!= NULL; aux = aux->next) {
            if (aux->isActive == 0) {
                showSingleTask(aux);
            }
        }
        break;
    default:
        break;
   }
}

void showAllTasks(taskslist *tList, int orderType, node *root) {
   showActiveTasks(tList, orderType, root);
   showCompletedTasks(tList, orderType, root);
}

void viewTaskMenu(taskslist *tList, node *root) {
    int opt;
    int orderType = 1;
    do {
        opt = viewTaskMenuOption();
        switch (opt) {
            case 1:
                showActiveTasks(tList, orderType, root);
                showCompletedTasks(tList, orderType, root);
                break;
            case 2:
                showActiveTasks(tList, orderType, root);
                break;
            case 3:
                showCompletedTasks(tList, orderType, root);
                break;
            case 4:
                orderType = orderOption();
                //switch com as opções de visualização
                switch (orderType)
                {
                case 1:
                    printf("modo de visualização selecionado: horas restantes\n");
                    orderType = 1;
                    break;
                case 2:
                    printf("modo de visualização selecionado: por ID\n");
                    orderType = 2;
                    break;
                case 3:
                    printf("modo de visualização selecionado: por criação\n");
                    orderType = 3;
                    break;
                default:
                    printf("Escolha uma opção válida.\n");
                    break;
                }
            default:
                break;
        }
        

    }while (opt != 0);
}

node *createNode(task *task) {
    node *newnode = (node*) malloc(sizeof(node));
    newnode->task = task;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

node *treeSortedByDeadline(taskslist *tl, node *root) {
    task *aux;
    for (aux = tl->head; aux!= NULL; aux = aux->next) {
        node *newnode = createNode(aux);
        root = addSortedNode(root, newnode);
    }
    return root;
}

int mainMenu() {
    int num;
    printf("Digite 1 para adicionar uma tarefa\n");
    printf("Digite 2 para visualizar as tarefas\n");
    printf("Digite 3 para marcar tarefas como concluídas\n");
    printf("Digite 4 para excluir tarefas\n");
    printf("Digite 0 para sair\n");
    scanf(" %d", &num);
    getchar();
    return num;
}

//insere nó na árvore, ordenando por id (essa é a ordenação padrão)
node *addNode(node *root, node *new) {
    
    if (root == NULL) {
        return new;
    } else {
        if (new->task->id <= root->task->id) {

            root->left = addNode(root->left, new);
        } else {
            root->right = addNode(root->right, new);
        }
    }
    return root;
}

void showInOrder (node *root) {
    if(root == NULL) {
        return;
    }
    showInOrder(root->left);
    showSingleTask(root->task);
    showInOrder(root->right);
}

//mostra só tasks ativas
void showActiveInOrder (node *root) {
    if(root == NULL) {
        return;
    }
    showActiveInOrder(root->left);
    if(root->task->isActive == 1) {
        showSingleTask(root->task);
    }
    showActiveInOrder(root->right);
}
void showCompletedInOrder (node *root) {
    if(root == NULL) {
        return;
    }
    showCompletedInOrder(root->left);
    if(root->task->isActive == 0) {
        showSingleTask(root->task);
    }
    showCompletedInOrder(root->right);
}

//marca task como completa
node *completeTask(node *root, int id) {
    if (root == NULL) {
        printf("Tarefa não encontrada\n");
        return root;
    }

    if (root->task->id == id) {
        root->task->isActive = 0;
        printf("Tarefa %smarcada como completa.\n", root->task->description);
    } else if (id < root->task->id) {
        root->left = completeTask(root->left, id);
    } else {
        root->right = completeTask(root->right, id);
    }

    return root;

}
void freeTree(node *root) {
  if (root != NULL) {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}
//ordena nós por tempo limite
node *addSortedNode(node *root, node *new) {
    
    if (root == NULL) {
        return new;
    } else {
        if (new->task->deadlineHours <= root->task->deadlineHours) {

            root->left = addSortedNode(root->left, new);
        } else {
            root->right = addSortedNode(root->right, new);
        }
    }
    return root;
}

int orderOption() {
    int num;
    printf("Digite 1 para ordenar por horas restantes\n");
    printf("Digite 2 para ordenar por id\n");
    printf("Digite 3 para ordenar por criação\n");
    scanf(" %d", &num);
    getchar();
    return num;
}
//pega o menor valor
node *findMin(node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
node *deleteTreeNode(node *root, int id) {
    if (root == NULL) {
        printf("Tarefa não encontrada\n");
        return root;
    }
    if (id < root->task->id) {
        root->left = deleteTreeNode(root->left, id);
    }
    else if (id > root->task->id) {
        root->right = deleteTreeNode(root->right, id);
    }
    //id encontrado
    else {
        //nó com um ou nenhum filho
        if (root->left == NULL) {
            node *temp = root->right;
            free(root);
            printf("Tarefa excluída.\n");
            return temp;
        }
        else if (root->right == NULL) {
            node *temp = root->left;
            printf("Tarefa excluída.\n");
            free(root);
            return temp;
        }
        //nó com dois filhos
        node *temp = findMin(root->right);

        //copia o conteúdo do sucessor para esse nó
        root->task->id = temp->task->id;
        root->task->deadlineHours = temp->task->deadlineHours;
        root->task->isActive = temp->task->isActive;
        strcpy(root->task->description, temp->task->description);

        //exclui sucessor ordenadamente
        root->right = deleteTreeNode(root->right, temp->task->id);
    }
    return root;
}


void deleteTask(taskslist *tList, int id) {
    task *aux;
   for (aux = tList->head; aux != NULL; aux = aux->next){
       if (aux->id == id){
            //se for o primeiro
           if (aux == tList->head) {
               tList->head = tList->head->next;
               if (tList->head != NULL) {
                   tList->head->prev = NULL;
               }
               
            //se for o último
           }else  if (aux == tList->tail) { 
               tList->tail = tList->tail->prev;
               if (tList->tail != NULL) {
                   tList->tail->next = NULL;
               }
           }else {
               aux->prev->next = aux->next;
               aux->next->prev = aux->prev; 
           }
           free(aux);
           break;
       }
   }
}
