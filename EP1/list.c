typedef struct Node {
  int data;
  struct Node *next;
}List;

List* new_node(int data){
  List *new_node = malloc(sizeof(List));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

List* insert(List *ptr, int data){
  List *head = ptr;
  List *insert_node = new_node(data);
  insert_node->next = head;
  head = insert_node;
  return head;
}

List* append(List *ptr, int data){
  List *head = ptr;
  List *tail = head;
  List *append_node = new_node(data);
  
  if (head == NULL){
    head = append_node;
    tail = append_node;
  }else{
    tail->prox = append_node;
    tail = append_node;
  }
}

int exclude_node(List *ptr, int data){
  
}

bool empty_list(list L){
  return(L == NULL) ? TRUE : FALSE;
}


