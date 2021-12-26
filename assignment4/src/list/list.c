/*
 * @Author: Mathis
 * @Date: 2021-12-23 00:13:28
 * @LastEditTime: 2021-12-26 18:08:46
 * @Description: list
 * @FilePath: /assignment4/src/list/list.c
 */

#include "list.h"


LinkList* LinkListInit(){
    LinkList *list = (LinkList*)malloc(sizeof(LinkList));
    if(NULL == list){
        puts("Error at LinkListInit\n");
        return NULL;
    }
    Node *node = (Node*)malloc(sizeof(Node));
    if(NULL == node){
        puts("Error at LinkListInit\n");
        return NULL;
    } 
    node->next = NULL;
    list->head = node;
    list->tail = node;
    list->len = 0;
    return list;
}


status LinkListRead(LinkList *list, size_t pos, Data* data){
    if(pos < 0 || pos > list->len){return ERROR;}
    if(pos == 0 || pos == list->len){
        data = &list->tail->data;
        return OK;
    }
    size_t j = 0;
    Node *p = list->head;
    while(p && j < pos){
        p = p->next;
        j++;
    }

    #if 0
    if(!p || j > pos){
        // p is null or j out of range
        return ERROR; 
    }
    #endif

    data = &p->data;
    return OK;
}


/**
 * @description: move n nodes from head
 * @param {LinkList} *list
 * @param {size_t} pos
 * @param {Node*} output
 * @return status
 */
static status PtrNodeMove(LinkList *list, size_t pos, Node** output){
    size_t j = 0;
    Node *p = list->head;
    while(p && j < pos){
        p = p->next;
        j++;
    }
    if(!p || j > pos){
        // p is null or j out of range
        return ERROR; 
    }
    *output = p;
    return OK;
}


status LinkListCreate(LinkList *list, size_t pos, Data* data){
    if(pos < 0 || pos > list->len+1){return ERROR;}
    
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(NULL == new_node){return ERROR;}
    new_node->data = *data;
    new_node->next = NULL;
    if(pos == 0 || pos == list->len+1){
        list->tail->next = new_node;
        list->tail = list->tail->next;
        // printf("len: %ld, tail is %s\n",list->len, list->tail->data.name);
        list->len++;
        return OK;
    }
    Node *p;
    // !: we need pos-1 not pos
    PtrNodeMove(list, pos-1, &p);
    new_node->next = p->next;
    p->next = new_node;
    list->len++;
    return OK;
}


status LinkListDelete(LinkList *list, size_t pos){
    if(pos < 0 || pos > list->len){return ERROR;}
    if(pos == 0){pos = list->len;}
    Node *p;
    Node *del;
    PtrNodeMove(list, pos-1, &p);
    if(pos == list->len){
        free(list->tail);
        list->tail = p;
        list->tail->next = NULL;
        list->len--;
        return OK;
    }
    del = p->next;
    p->next = del->next;
    free(del);
    list->len--;
    return OK;
}


status LinkListUpdate(LinkList *list, size_t pos, Data *data){
    if(pos < 0 || pos > list->len){return ERROR;}
    if(pos ==0 || pos == list->len){
        list->tail->data = *data;
        return OK;
    }
    Node *p;
    PtrNodeMove(list, pos, &p);
    p->data = *data;
    return OK;
}


status LinkListClear(LinkList *list){
    Node *p = list->head->next;
    Node *tmp = p;
    // printf("clear %s\n", list->tail->data.name);
    // printf("clear %s\n",p->data.name);
    for(size_t i = 0; i < list->len; ++i){
        tmp = p;
        p = p->next;
        // printf("clear %s\n", tmp->data.name);
        free(tmp);
    }
    list->head->next = NULL;
    list->tail = list->head;
    list->len = 0;
    return OK;
}


status LinkListDeinit(LinkList *list){
    LinkListClear(list);
    free(list->head);
    free(list);
    return OK;
}


static size_t GetDigitsNum(size_t x){
    size_t k = 0;
    while(x != 0){
        x /= 10;
        k++;
    }
    return k;
}

status LinkListPrint(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Name");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%0*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%s\t\n", p->data.name);
    }
    fprintf(fp, "\n");
    return OK;
}


LinkList* LinkListClone(LinkList *list){
    LinkList *output = LinkListInit();
    size_t i = 0;
    Node* p = list->head;
    for(i = 0; i < list->len; i++){
        p = p->next;
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = p->data;
        output->tail->next = new_node;
        output->tail = output->tail->next; 
    }
    output->len = list->len;
    return output;
}


static status LinkListPrintName(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Name");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%0*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%s\t\n", p->data.name);
    }
    fprintf(fp, "\n");
    return OK;
}

static status LinkListPrintAge(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%d\t\n", p->data.age);
    }
    fprintf(fp, "\n");
    return OK;
}

static status LinkListPrintClass(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%s\t\n", p->data.class_8);
    }
    fprintf(fp, "\n");
    return OK;
}

static status LinkListPrintMidTerm(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%d\t\n", p->data.mid_term_score);
    }
    fprintf(fp, "\n");
    return OK;
}

static status LinkListPrintHomework(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%d\t\n", p->data.homework_score);
    }
    fprintf(fp, "\n");
    return OK;
}
#if 0
static status LinkListPrintFinal(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%d\t\n", p->data.final_score);
    }
    fprintf(fp, "\n");
    return OK;
}
#endif

static status LinkListPrintFinal(LinkList *list, FILE* fp){
    size_t num_digits = GetDigitsNum(list->len);
    size_t i = 0;
    Node* p = list->head;
    size_t prefix = 3 + num_digits; 
    fprintf(fp, "%-*s\t%s\t\n", (int)prefix, "Idx", "Age");
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "%*ld\t", (int)num_digits, i+1);
        fprintf(fp, "%d\t\n", p->data.final_score);
    }
    fprintf(fp, "\n");
    return OK;
}

static status LinkListPrintAll(LinkList *list, FILE* fp){
    size_t i = 0;
    Node* p = list->head;
    int align = 14;
    for(i = 0; i < list->len; i++){
        p = p->next;
        fprintf(fp, "\033[1mNO.%ld:\033[0m\n", i+1);
        fprintf(fp, "%-*s: %s\n", align, "Name", p->data.name);
        fprintf(fp, "%-*s: %s\n", align, "Class", p->data.class_8);
        fprintf(fp, "%-*s: %d\t\n", align, "Age",p->data.age);
        fprintf(fp, "%-*s: %d\t\n", align, "Mid-term-Score",p->data.mid_term_score);
        fprintf(fp, "%-*s: %d\t\n", align, "Homework-Score",p->data.homework_score);
        fprintf(fp, "%-*s: %d\t\n", align, "Final-Score",p->data.final_score);
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    return OK;
}


status LinkListPrintById(LinkList *list, FILE* fp, item_id id){
    switch (id)
    {
    case NAME:
        LinkListPrintName(list, fp);
        break;
    case AGE:
        LinkListPrintAge(list, fp);
        break; 
    case CLASS:
        LinkListPrintClass(list, fp);
        break; 
    case MID_TERM_SCORE:
        LinkListPrintMidTerm(list, fp);
        break; 
    case HOMEWORK_SCORE:
        LinkListPrintHomework(list, fp);
        break; 
    case FINAL_SCORE:
        LinkListPrintFinal(list, fp);
        break; 
    case ALL:
        LinkListPrintAll(list, fp);
        break; 
    default:
        printf("Wrong id\n");
        break;
    }
    return OK;
}


static void HeapDownAdjust(Number scores[], Node* nodes[], size_t parent_index, size_t length){
    // printf("in: %ld",parent_index);
    Number temp = scores[parent_index];
    Node *temp_ptr = nodes[parent_index];

    size_t child_index = 2 * parent_index + 1;
    while(child_index < length){
        if(child_index + 1 < length && scores[child_index+1] < scores[child_index]){
            child_index++;
        }
        if(temp <= scores[child_index]){
            break;
        }
        scores[parent_index] = scores[child_index];
        nodes[parent_index] = nodes[child_index];
        parent_index = child_index;
        child_index = 2 * child_index + 1;
    }
    scores[parent_index] = temp;
    nodes[parent_index] = temp_ptr;
}

static void HeapSort(Number scores[], Node* nodes[], size_t length){
    size_t i = 0;
    for(i = (length-2)/2; i > 0; i--){
        // printf("before: %ld\n",i);
        HeapDownAdjust(scores, nodes, i, length);
        // printf("after: %ld\n",i);
    }
    
    // attention: if i = 0, and use i--, horrible, because
    i = 0;
    HeapDownAdjust(scores, nodes, i, length);
    // type of i is unsigned, something wrong;

    for(i = length - 1; i > 0; i--){
        Number temp = scores[i];
        Node *temp_ptr = nodes[i];
        scores[i] = scores[0];
        nodes[i] = nodes[0];
        scores[0] = temp;
        nodes[0] = temp_ptr;
        HeapDownAdjust(scores, nodes, 0, i);
    }

}

static void ArrayToLinkList(LinkList* list, Node * nodes[], size_t length){
    size_t i = 0;
    list->head->next = nodes[0];
    for(i = 0; i < length-1; i++){
        // list->tail->next = nodes[i];
        // list->tail = list->tail->next;
        nodes[i]->next = nodes[i+1];
    }
    list->tail->next = nodes[length-1];
    return;
}

void LinkListSortByScore(LinkList* list){

    size_t N = list->len;
    if(N < 1){return;}
    Number* scores = (Number*)malloc(sizeof(size_t)*N);
    Node ** nodes = (Node**)malloc(sizeof(Node *)*N);
    size_t i = 0;
    Node *p = list->head;
    for(i = 0; i < N; i++){
        p = p->next;
        nodes[i] = p;
        scores[i] = p->data.mid_term_score + p->data.homework_score + p->data.final_score;
    }
    HeapSort(scores, nodes, N);
    ArrayToLinkList(list, nodes, N);
    free(scores);
    free(nodes);
}


Data DataInitKeyboard(){
    Data data;
    int length = 16;
    printf("%-*s> ",length, "Name:");
    setbuf(stdin, NULL); // CLEAR STDIN
    fgets(data.name, sizeof(data.name)/sizeof(data.name[0]), stdin);
    char *find = strchr(data.name, '\n');
    if(find){*find = '\0';}
    printf("%-*s> ",length, "Class:");
    scanf("%s", data.class_8);
    printf("%-*s> ",length, "Age:");
    scanf("%hd", &data.age);
    printf("%-*s> ",length, "mid-term score:");
    scanf("%hd", &data.mid_term_score);
    printf("%-*s> ",length, "homework score:");
    scanf("%hd", &data.homework_score);
    printf("%-*s> ",length, "final score:");
    scanf("%hd", &data.final_score);
    printf("\n");
    return data;
}


void LinkListReverse(LinkList* list){

    if(list->len <= 1){
        return;
    }

    #if 0 
    if(list->len == 2){
        Node* tmp = list->head->next;
        list->head->next = list->tail;
        list->tail->next = tmp;
        list->tail = tmp;
        return;
    }
    #endif

    if(list->len >= 2){
        list->tail = list->head->next;
        Node *pre = list->head->next;
        Node *middle = pre->next;
        Node *pass = middle->next;
        while (pass){
            // printf("middle: %s\n", middle->data.name);
            // printf("pass: %s\n", pass->data.name);
            middle->next = pre;
            pre = middle;
            middle = pass;
            pass = pass->next;
        }
        // printf("middle: %s\n", middle->data.name);
        // printf("pass: %s\n", pass->data.name);
        middle->next = pre;
        list->head->next = middle;
        list->tail->next = NULL;
        return; 
    }
    printf("Error, can't be reversed\n");
    return;
}


void load_from_data_dir(LinkList *list, char* path, size_t N){
    FILE *fp;
    Data data_buf;
    fp = fopen(path,"rb");
    for( int i = 0; i < N; i++){
        fread(&data_buf, sizeof(Data), 1, fp);
        LinkListCreate(list, 0, &data_buf);
        // printf("tail is %s\n",list->tail->data.name);
    }
    
    fclose(fp);
}