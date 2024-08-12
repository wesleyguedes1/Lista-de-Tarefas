#include "toDoList.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    taskslist *tl = (taskslist*) malloc(sizeof(taskslist));
    
    initList(tl);
    node *root = NULL;
    int num;
    do {
        num = mainMenu();
        switch (num) {
            case 1:
                task *tk = inputTask(tl);
                if (tk!= NULL) {
                    addTask(tl, tk);
                    node *newnode = createNode(tk);
                    root = addNode(root, newnode);
                }
                break;
            case 2:
                viewTaskMenu(tl, root);
                break;
            case 3:
                int key;
                printf("Digite o id da tarefa a ser marcada como concluída: ");
                scanf(" %d", &key);
                getchar();
                root = completeTask(root, key);

                break;
            case 4:
                if(tl->head == NULL) {
                    printf("lista vazia\n");
                    break;
                }
                int id;
                printf("Digite o id da tarefa a ser excluída: ");
                scanf(" %d", &id);
                getchar();
                root = deleteTreeNode(root, id);
                deleteTask(tl, id);
                break;
            case 0: {
                printf("Saindo do programa.\n");
                freeTree(root);
                free(tl);
                return 0;
            }
            default:
                printf("Opção inválida.\n");
                break;
        }
    }while (num != 0);
}
